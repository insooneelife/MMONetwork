#include "Session.h"

#include <boost/thread/thread.hpp>

class Server
{
public:

	inline Room& getRoom() { return room_; }

	explicit Server(int port)
		:
		endpoint_(boost::asio::ip::tcp::v4(), port),
		acceptor_(io_service_, endpoint_),
		socket_(io_service_),
		work_(io_service_)
	{
		thread_pool_.create_thread(boost::bind(&boost::asio::io_service::run, &io_service_));

		std::cout << "ip : " << endpoint_.address().to_string() << "  port : " << port << std::endl;
		accept();
	}

	void sendToSession(unsigned int id, unsigned char* buffer, unsigned int size)
	{
		room_.sendTo(id, buffer, size);
	}

	void sendToRoom(unsigned char* buffer, unsigned int size)
	{
		room_.broadcast(buffer, size);
	}

private:
	void accept()
	{
		acceptor_.async_accept(
			socket_,
			[this](boost::system::error_code ec)
		{
			if (!ec)
			{
				std::cout <<"!"<< acceptor_.local_endpoint().address().to_string() << std::endl;
				std::make_shared<Session>(std::move(socket_), room_)->start();
			}
			else
			{
				std::cout << "@@";
			}

			accept();
		});
	}

	
	boost::asio::ip::tcp::endpoint endpoint_;
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::ip::tcp::socket socket_;

	boost::asio::io_service::work work_;
	boost::thread_group thread_pool_;

	Room room_;
};