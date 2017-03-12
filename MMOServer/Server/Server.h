#include "Session.h"

#include <boost/thread/thread.hpp>

#include <mutex>
#include <memory>

class Server
{
public:

	inline Room& getRoom() { return *room_; }

	explicit Server(int port);
	~Server();
	void sendToSession(unsigned int id, const unsigned char* buffer, unsigned int size);
	void sendToRoom(const unsigned char* buffer, unsigned int size);

private:
	void accept();
	

	boost::asio::io_service io_service_;
	boost::asio::io_service::strand strand_;
	std::unique_ptr<boost::asio::io_service::work> work_;
	boost::thread_group thread_pool_;

	boost::asio::ip::tcp::endpoint endpoint_;
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::ip::tcp::socket socket_;


	std::unique_ptr<Room> room_;

	
};