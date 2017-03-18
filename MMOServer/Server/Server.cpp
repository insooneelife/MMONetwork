#include "Server.h"

Server::Server(int port)
	:
	endpoint_(boost::asio::ip::tcp::v4(), port),
	acceptor_(io_service_, endpoint_),
	socket_(io_service_),
	work_(new boost::asio::io_service::work(io_service_)),
	strand_(io_service_),
	room_(new Room())
{
	for(int i = 0; i< 8; i++)
		thread_pool_.create_thread(boost::bind(&boost::asio::io_service::run, &io_service_));
	
	std::cout << "ip : " << endpoint_.address().to_string() << "  port : " << port << std::endl;
	accept();
}

Server::~Server()
{
	work_.reset();
	thread_pool_.join_all();
	io_service_.stop();
}

void Server::sendToSession(unsigned int id, const unsigned char* buffer, unsigned int size)
{
	room_->sendTo(id, buffer, size);
}

void Server::sendToRoom(const unsigned char* buffer, unsigned int size)
{
	room_->broadcast(buffer, size);
}

void Server::accept()
{
	acceptor_.async_accept(
		socket_,
		strand_.wrap([this](boost::system::error_code ec)
	{
		if (!ec)
		{
			std::cout << "new client accepted : " << acceptor_.local_endpoint().address().to_string() << std::endl;
			std::make_shared<Session>(std::move(socket_), strand_, *room_)->start();
		}
		else
		{
		}

		accept();
	}));
}

