#pragma once
#include <iostream>
#include <queue>
#include <memory>
#include <boost/asio.hpp>
#include <thread>
#include <Common/Protobuf/ProtobufStrategy.h>
#include <Common/Network/GamePacket.hpp>
#include <Common/Protobuf/generated/InitGameData.pb.h>

class NetworkManagerClient;
class Client
{
public:
	Client(
		boost::asio::io_service& io_service,
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

	void send(const unsigned char* buffer, std::size_t length);
	void close();
	void processRecv();
	void processSend();

private:
	void connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
	void readHeader();
	void readBody(unsigned int body_size);

	
	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::socket socket_;

	GamePacket<ProtobufStrategy> recv_packet_;
	std::queue<GamePacket<ProtobufStrategy> > recv_queue_;
	std::unique_ptr<NetworkManagerClient> network_mgr_;
};