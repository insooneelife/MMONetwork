#include "Client.h"
#include "NetworkManagerClient.h"

Client::Client(
	boost::asio::io_service& io_service,
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
	:
	io_service_(io_service),
	socket_(io_service),
	network_mgr_(new NetworkManagerClient(*this)),
	strand_(io_service)
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
	strand_.post([this]() { socket_.close(); });
	//io_service_.post([this]() { socket_.close(); });
}


void Client::processRecv()
{
	copyPacketsTo(*network_mgr_);
	network_mgr_->processQueuedPackets();
}

void Client::processSend()
{
	network_mgr_->sendUpdates();
}

void Client::enqueue(const ProtobufClientUtils::RecvPacket& packet)
{
	//que_mutex_.lock();
	recv_queue_.emplace(packet);
	//que_mutex_.unlock();
}


void Client::connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	boost::asio::async_connect(
		socket_,
		endpoint_iterator,
		strand_.wrap([this](boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator)
	{
		if (!ec)
		{
			readHeader();
		}
		else
		{
			
			std::cout << "connection failed!  message : "<< ec.value() << std::endl;
		}
	}));
}

void Client::readHeader()
{
	boost::asio::async_read(
		socket_,
		boost::asio::buffer(recv_packet_.data(), ProtobufClientUtils::RecvPacket::HeaderLength),
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
			recv_packet_.setSize(recv_packet_.size() + len);

			enqueue(recv_packet_);
			//recv_queue_.push(recv_packet_);
			readHeader();
		}
		else
		{
			socket_.close();
		}
	});
}