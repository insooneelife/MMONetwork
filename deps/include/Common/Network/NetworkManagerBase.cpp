#include "NetworkManagerBase.h"

void NetworkManagerBase::copyPackets(std::queue<Packet>& recv_que)
{
	while (!recv_que.empty() && idx_ < copied_packets_.size())
	{
		copied_packets_[idx_++] = recv_que.front();
		recv_que.pop();
	}

	while (!recv_que.empty()) { recv_que.pop(); }
}

void NetworkManagerBase::processQueuedPackets()
{
	for (int i = 0; i < idx_; ++i)
	{
		processByType(copied_packets_[i]);
	}
	idx_ = 0;
}

void NetworkManagerBase::processByType(const Packet& packet)
{
	Data::HeaderData header;
	packet.parseHeader(header);
	Data::PacketType ptype = (Data::PacketType)header.type();
	std::cout <<
		"packet type : " << Data::PacketType_Name(ptype) <<
		"  body size : " << header.size() << std::endl;

	auto found = _process_map.find(ptype);

	if (found != std::end(_process_map))
	{
		found->second(header, packet);
	}
	else
	{
		assert(false && "invalid packet type!");
	}
}