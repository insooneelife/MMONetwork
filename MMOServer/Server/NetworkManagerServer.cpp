#include "NetworkManagerServer.h"
#include "ProtobufServerUtils.h"
#include "../World.h"
#include "Room.h"

NetworkManagerServer::NetworkManagerServer(World& world, Room& room)
	:
	world_(world),
	room_(room)
{}


void NetworkManagerServer::copyPackets()
{
	GamePacket<ProtobufStrategy> packet;
	while (room_.dequeue(packet) && idx_ < copied_packets_.size())
	{
		copied_packets_[idx_++] = packet;
	}

	while (room_.dequeue(packet)) {}
}


void NetworkManagerServer::processQueuedPackets()
{
	for (int i = 0; i < idx_; ++i)
	{
		processByType(copied_packets_[i]);
	}
	idx_ = 0;
}



void NetworkManagerServer::processByType(const GamePacket<ProtobufStrategy>& packet)
{
	Data::HeaderData header;
	packet.parseHeader(header);

	if (header.type() == Data::PacketType::RequestConnect)
	{
		processRequestConnect(header, packet);
	}

	else if (header.type() == Data::PacketType::ReadyToJoin)
	{
		processReadyToJoin(header, packet);
	}

	else if (header.type() == Data::PacketType::ClientCommand)
	{
		processClientCommand(header, packet);
	}

	else if (header.type() == Data::PacketType::ReadyToChange)
	{
		processReadyToChange(header, packet);
	}

	else if (header.type() == Data::PacketType::Disconnected)
	{
		processDisconnected(header, packet);
	}

}

void NetworkManagerServer::processRequestConnect(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
	std::cout << "processRequestConnect" << std::endl;
	unsigned int pid = room_.getGenID();

	//# fix
	unsigned int eid = 0;

	Data::InitGameData idata;
	ProtobufServerUtils::serializeInitGameData(&world_, pid, eid, idata);

	GamePacket<ProtobufStrategy> send_packet;
	send_packet.serializeFrom(idata, Data::PacketType::InitGame);

	room_.sendTo(pid, send_packet.data(), send_packet.size());
}


void NetworkManagerServer::processReadyToJoin(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
	std::cout << "processReadyToJoin" << std::endl;
}

void NetworkManagerServer::processClientCommand(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
	std::cout << "processClientCommand" << std::endl;
}

void NetworkManagerServer::processReadyToChange(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
	std::cout << "processReadyToChange" << std::endl;
}

void NetworkManagerServer::processDisconnected(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
	std::cout << "processDisconnected" << std::endl;
}



GamePacket<ProtobufStrategy> 
NetworkManagerServer::createInitGamePacket(const Data::InitGameData& data)
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(data, Data::PacketType::InitGame);
	return packet;
}

GamePacket<ProtobufStrategy> 
NetworkManagerServer::createFullPacket()
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(Data::PacketType::Full);
	return packet;
}

GamePacket<ProtobufStrategy> 
NetworkManagerServer::createJoinedPacket(const Data::JoinedData& user)
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(user, Data::PacketType::Joined);
	return packet;
}

GamePacket<ProtobufStrategy> 
NetworkManagerServer::createIntroPacket(const Data::UserData& user)
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(user, Data::PacketType::Intro);
	return packet;
}

GamePacket<ProtobufStrategy> 
NetworkManagerServer::createNotifyDisconnectedPacket(const Data::UserData& user)
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(user, Data::PacketType::NotifyDisconnected);
	return packet;
}

GamePacket<ProtobufStrategy> 
NetworkManagerServer::createChangeLevelPacket(const Data::InitGameData& data)
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(data, Data::PacketType::ChangeLevel);
	return packet;
}

GamePacket<ProtobufStrategy> 
NetworkManagerServer::createEnterPlayingPacket()
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(Data::PacketType::EnterPlaying);
	return packet;
}

GamePacket<ProtobufStrategy> 
NetworkManagerServer::createReplicatePacket(const Data::ReplicateData& data)
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(data, Data::PacketType::Replicate);
	return packet;
}
