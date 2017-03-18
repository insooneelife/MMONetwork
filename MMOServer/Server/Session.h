#pragma once

#include "Room.h"
#include "Participant.h"
#include <string>
#include <Common/Network/GamePacket.hpp>
#include <boost/asio.hpp>
#include "ProtobufServerUtils.h"



class Session
	:
	public Participant,
	public std::enable_shared_from_this<Session>
{
public:

	Session(
		boost::asio::ip::tcp::socket socket,
		boost::asio::io_service::strand& strand,
		Room& room);

	void start();
	virtual void send(const unsigned char* buffer, unsigned int length) override;

private:
	void readHeader();
	void readBody(unsigned int body_size);
	void log(const std::string& action, const std::string& what, int size);

	boost::asio::ip::tcp::socket socket_;
	Room& room_;
	ProtobufServerUtils::RecvPacket recv_packet_;

	std::mutex log_mutex_;
	boost::asio::io_service::strand& strand_;
};