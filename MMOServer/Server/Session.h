#pragma once

#include "Room.h"
#include "Participant.h"
#include <Common/Network/GamePacket.hpp>
#include <boost/asio.hpp>
#include "PacketFactory.h"

class Session
	:
	public Participant,
	public std::enable_shared_from_this<Session>
{
public:

	Session(boost::asio::ip::tcp::socket socket, Room& room)
		:
		socket_(std::move(socket)),
		room_(room)
	{}

	void start()
	{
		room_.insert(shared_from_this());
		recv_packet_.serializeFrom(Data::PacketType::RequestConnect);
		room_.enqueue(recv_packet_);

		readHeader();
	}
	
	virtual void send(unsigned char* buffer, unsigned int length) override
	{
		auto self(shared_from_this());
		boost::asio::async_write(
			socket_,
			boost::asio::buffer(buffer, length),
			[this, self](boost::system::error_code ec, std::size_t len)
		{
			if (!ec)
			{

			}
			else
			{
				room_.remove(shared_from_this());
			}
		});
	}

private:
	void readHeader()
	{
		auto self(shared_from_this());
		boost::asio::async_read(
			socket_,
			boost::asio::buffer(recv_packet_.data(), GamePacket<ProtobufStrategy>::HeaderLength),
			[this, self](boost::system::error_code ec, std::size_t length)
		{
			Data::HeaderData header;

			if (!ec && recv_packet_.parseHeader(header))
			{
				readBody(header.size(), header.type());
			}
			else
			{
				room_.remove(shared_from_this());
			}
		});
	}

	void readBody(unsigned int body_size, unsigned int body_type)
	{
		auto self(shared_from_this());
		boost::asio::async_read(
			socket_,
			boost::asio::buffer(recv_packet_.body(), body_size),
			[this, self, body_size, body_type](boost::system::error_code ec, std::size_t len)
		{

			if (!ec)
			{
				// process..
				//room_.broadcast(read_msg_);

				room_.enqueue(recv_packet_);

				std::cout << "body size : " << body_size << "  " << "body type : " << body_type << std::endl;

				readHeader();
			}
			else
			{
				room_.remove(shared_from_this());
			}
		});
	}

	boost::asio::ip::tcp::socket socket_;
	Room& room_;
	GamePacket<ProtobufStrategy> recv_packet_;
};