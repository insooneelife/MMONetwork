#include "Client.h"
#include "NetworkManagerClient.h"

Client::Client(
	boost::asio::io_service& io_service,
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
	:
	io_service_(io_service),
	socket_(io_service),
	network_mgr_(new NetworkManagerClient(*this))
{
	connect(endpoint_iterator);
}

void Client::send(const unsigned char* buffer, std::size_t length)
{
	boost::asio::async_write(
		socket_,
		boost::asio::buffer(buffer, length),
		[this](boost::system::error_code ec, std::size_t len)
	{
		if (!ec)
		{
			//std::cout << "send length : " << len << std::endl;
		}
		else
		{
			socket_.close();
		}
	});
}

void Client::close()
{
	io_service_.post([this]() { socket_.close(); });
}

void Client::update()
{
	std::chrono::duration<double> start = std::chrono::system_clock::now().time_since_epoch();

	network_mgr_->copyPackets(recv_queue_);
	network_mgr_->processQueuedPackets();

	

	//network_mgr_->sendUpdates();

	
	std::chrono::duration<double> end = std::chrono::system_clock::now().time_since_epoch();
}

void Client::connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	boost::asio::async_connect(
		socket_,
		endpoint_iterator,
		[this](boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator)
	{
		if (!ec)
		{
			readHeader();
		}
	});
}

void Client::readHeader()
{
	boost::asio::async_read(
		socket_,
		boost::asio::buffer(recv_packet_.data(), GamePacket<ProtobufStrategy>::HeaderLength),
		[this](boost::system::error_code ec, std::size_t length)
	{
		
		Data::HeaderData header;

		// parse header
		if (!ec && recv_packet_.parseHeader(header))
		{
			//std::cout << "readed header : " << length << std::endl;
			recv_packet_.setSize(length);
			readBody(header.size());
		}
		else
		{
			socket_.close();
		}
	});
}

void Client::readBody(unsigned int body_size)
{
	boost::asio::async_read(
		socket_,
		boost::asio::buffer(recv_packet_.body(), body_size),
		[this](boost::system::error_code ec, std::size_t len)
	{
		if (!ec)
		{
			//std::cout << "readed body : " << len << std::endl;
			recv_packet_.setSize(GamePacket<ProtobufStrategy>::HeaderLength + len);
			recv_queue_.push(recv_packet_);
			readHeader();
		}
		else
		{
			socket_.close();
		}
	});
}