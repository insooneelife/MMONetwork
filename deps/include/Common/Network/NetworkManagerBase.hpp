#pragma once

#include <array>
#include <functional>
#include <map>
#include <queue>
#include "GamePacket.hpp"
#include "../Protobuf/generated/Base.pb.h"
#include "../Protobuf/generated/HeaderData.pb.h"

template<typename Packet, int PacketBufferSize = 100>
class NetworkManagerBase
{
public:

	NetworkManagerBase() :idx_(0) {}

	void copyPackets(std::queue<Packet>& recv_que)
	{
		while (!recv_que.empty() && idx_ < copied_packets_.size())
		{
			copied_packets_[idx_++] = recv_que.front();
			recv_que.pop();
		}

		while (!recv_que.empty()) { recv_que.pop(); }
	}

	void processQueuedPackets()
	{
		for (int i = 0; i < idx_; ++i)
		{
			processByType(copied_packets_[i]);
		}
		idx_ = 0;
	}

	void processByType(const Packet& packet) 
	{
		Data::HeaderData header;
		packet.parseHeader(header);
		Data::PacketType ptype = (Data::PacketType)header.type();
		
		auto found = _process_map.find(ptype);

		if (found != std::end(_process_map))
		{
			//std::cout <<
			//	"handled  packet type : [" << Data::PacketType_Name(ptype) << "]" <<
			//	"  body size : " << header.size() << std::endl;

			found->second(header, packet);
		}
		else
		{
			assert(false && "invalid packet type!");
		}
	}

protected:

	std::array<Packet, PacketBufferSize> copied_packets_;
	int idx_;
	
	std::map<Data::PacketType, std::function<void(const Data::HeaderData&, const Packet&)> > _process_map;
};