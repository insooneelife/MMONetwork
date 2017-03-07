#pragma once
#include <iostream>
#include <queue>
#include <boost/asio.hpp>
#include <thread>
#include <Common/Protobuf/ProtobufStrategy.h>
#include <Common/Network/GamePacket.hpp>
#include <Common/Protobuf/generated/InitGameData.pb.h>

class Client
{
public:
	Client(
		boost::asio::io_service& io_service,
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
		:
		io_service_(io_service),
		socket_(io_service)
	{
		connect(endpoint_iterator);
	}

	void send(unsigned char* buffer, std::size_t length)
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

	void close()
	{
		io_service_.post([this]() { socket_.close(); });
	}

private:
	void connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
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

	void readHeader()
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

	void readBody(unsigned int body_size, unsigned int body_type)
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
				Data::InitGameData idata;
				recv_packet_.parseBody(idata, body_size);

				std::cout << idata.DebugString() << std::endl;

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

	


private:
	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::socket socket_;


	GamePacket<ProtobufStrategy> recv_packet_;
	std::queue<GamePacket<ProtobufStrategy> > recv_queue_;
};