#include "Client.h"
#include "NetworkManagerClient.h"

Client::Client(
	boost::asio::io_service& io_service,
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
	:
	io_service_(io_service),
	socket_(io_service),
	_network_mgr(new NetworkManagerClient(*this))
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

void Client::enqueue(const GamePacket<ProtobufStrategy>& packet)
{
	recv_queue_.emplace(packet);
}

bool Client::dequeue(GamePacket<ProtobufStrategy>& packet)
{
	if (!recv_queue_.empty())
	{
		packet = recv_queue_.front();
		recv_queue_.pop();
		return true;
	}
	return false;
}

void Client::update()
{
	std::chrono::duration<double> start = std::chrono::system_clock::now().time_since_epoch();

	_network_mgr->copyPackets();
	_network_mgr->processQueuedPackets();

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
		std::cout << "readheader" << std::endl;

		Data::HeaderData header;

		// parse header
		if (!ec && recv_packet_.parseHeader(header))
		{
			readBody(header.size(), header.type());
		}
		else
		{
			socket_.close();
		}
	});
}

void Client::readBody(unsigned int body_size, unsigned int body_type)
{
	std::cout << "readbody" << std::endl;
	std::cout << "body size : " << body_size << "  " << "body type : " << body_type << std::endl;

	boost::asio::async_read(
		socket_,
		boost::asio::buffer(recv_packet_.body(), body_size),
		[this, body_size, body_type](boost::system::error_code ec, std::size_t len)
	{
		if (!ec)
		{
			// process..
			recv_queue_.emplace(recv_packet_);

			readHeader();
		}
		else
		{
			socket_.close();
		}
	});
}