#include "Session.h"

Session::Session(
	boost::asio::ip::tcp::socket socket,
	boost::asio::io_service::strand& strand,
	Room& room)
	:
	socket_(std::move(socket)),
	strand_(strand),
	room_(room)
{}

void Session::start()
{
	room_.insert(shared_from_this());
	recv_packet_.serializeFrom(Data::PacketType::RequestConnect);
	room_.enqueue(recv_packet_);

	readHeader();
}

void Session::send(const unsigned char* buffer, unsigned int length)
{
	auto self(shared_from_this());
	boost::asio::async_write(
		socket_,
		boost::asio::buffer(buffer, length),
		strand_.wrap(
			[this, self](boost::system::error_code ec, std::size_t len)
	{
		if (!ec)
		{
			log("send", "data", len);
		}
		else
		{
			room_.remove(shared_from_this());
		}
	}));
}

void Session::readHeader()
{
	auto self(shared_from_this());
	boost::asio::async_read(
		socket_,
		boost::asio::buffer(recv_packet_.data(), GamePacket<ProtobufStrategy>::HeaderLength),
		strand_.wrap(
			[this, self](boost::system::error_code ec, std::size_t length)
	{
		Data::HeaderData header;

		if (!ec && recv_packet_.parseHeader(header))
		{
			log("read", "header", length);
			recv_packet_.setSize(length);
			readBody(header.size());
		}
		else
		{
			room_.remove(shared_from_this());
		}
	}));
}

void Session::readBody(unsigned int body_size)
{
	auto self(shared_from_this());
	boost::asio::async_read(
		socket_,
		boost::asio::buffer(recv_packet_.body(), body_size),
		strand_.wrap(
			[this, self](boost::system::error_code ec, std::size_t len)
	{
		if (!ec)
		{
			// process..
			log("read", "body", len);
			recv_packet_.setSize(GamePacket<ProtobufStrategy>::HeaderLength + len);
			room_.enqueue(recv_packet_);

			readHeader();
		}
		else
		{
			room_.remove(shared_from_this());
		}
	}));
}

void Session::log(const std::string& action, const std::string& what, int size)
{
	std::thread::id this_id = std::this_thread::get_id();

	log_mutex_.lock();
	std::cout << "thread id : " << this_id << "  "<< action <<" " << what << " : " << size << std::endl;
	log_mutex_.unlock();
}