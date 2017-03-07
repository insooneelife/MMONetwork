#include "NetworkManager.h"
#include "PacketFactory.h"
#include "../World.h"
#include "Room.h"

NetworkManager::NetworkManager(World& world, Room& room)
	:
	world_(world),
	room_(room)
{}


void NetworkManager::copyPackets()
{
	GamePacket<ProtobufStrategy> packet;
	while (room_.dequeue(packet) && idx_ < copied_packets_.size())
	{
		copied_packets_[idx_++] = packet;
	}

	while (room_.dequeue(packet)) {}
}


void NetworkManager::processQueuedPackets()
{
	for (int i = 0; i < idx_; ++i)
	{
		processByType(copied_packets_[i]);
	}
	idx_ = 0;
}



void NetworkManager::processByType(const GamePacket<ProtobufStrategy>& packet)
{
	Data::HeaderData header;
	packet.parseHeader(header);

	if (header.type() == Data::PacketType::RequestConnect)
	{
		processRequestConnect(header, packet);
	}

}

void NetworkManager::processRequestConnect(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
	std::cout << "processRequestConnect" << std::endl;
	unsigned int pid = room_.getGenID();

	//# fix
	unsigned int eid = 0;

	Data::InitGameData idata;
	PacketFactory::serializeInitGameData(&world_, pid, eid, idata);

	GamePacket<ProtobufStrategy> send_packet;
	send_packet.serializeFrom(idata, Data::PacketType::InitGame);

	room_.sendTo(pid, send_packet.data(), send_packet.size());
	
}