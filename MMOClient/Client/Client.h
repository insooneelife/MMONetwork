#pragma once
#include <iostream>
#include <queue>
#include <memory>
#include <mutex>
#include <boost/asio.hpp>
#include <thread>
#include <Common/Protobuf/ProtobufStrategy.h>
#include <Common/Network/GamePacket.hpp>
#include <Common/Network/NetworkManagerBase.hpp>
#include <Common/Protobuf/generated/InitGameData.pb.h>
#include "ProtobufClientUtils.h"

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

	template<typename NetworkManager>
	void copyPacketsTo(NetworkManager& to)
	{
		//que_mutex_.lock();
		to.copyPackets(recv_queue_);
		//que_mutex_.unlock();
	}

	void enqueue(const ProtobufClientUtils::RecvPacket& packet);

private:
	void connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
	void readHeader();
	void readBody(unsigned int body_size);

	
	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::socket socket_;
	boost::asio::io_service::strand strand_;

	ProtobufClientUtils::RecvPacket recv_packet_;
	std::mutex que_mutex_;
	std::queue<ProtobufClientUtils::RecvPacket> recv_queue_;
	std::unique_ptr<NetworkManagerClient> network_mgr_;
};