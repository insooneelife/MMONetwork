#include <Common/Utils.h>
#include "NetworkManagerServer.h"
#include "ProtobufServerUtils.h"
#include "Room.h"
#include "../World.h"
#include "../Entity/Snake.h"

NetworkManagerServer::NetworkManagerServer(World& world, Room& room)
	:
	world_(world),
	room_(room)
{
	using namespace std::placeholders;

	_process_map.emplace(
		Data::PacketType::RequestConnect,
		std::bind(&NetworkManagerServer::processRequestConnect, this, _1, _2));

	_process_map.emplace(
		Data::PacketType::Hello,
		std::bind(&NetworkManagerServer::processHello, this, _1, _2));

	_process_map.emplace(
		Data::PacketType::ReadyToJoin,
		std::bind(&NetworkManagerServer::processReadyToJoin, this, _1, _2));

	_process_map.emplace(
		Data::PacketType::ClientCommand,
		std::bind(&NetworkManagerServer::processClientCommand, this, _1, _2));

	_process_map.emplace(
		Data::PacketType::ReadyToChange,
		std::bind(&NetworkManagerServer::processReadyToChange, this, _1, _2));

	_process_map.emplace(
		Data::PacketType::Disconnected,
		std::bind(&NetworkManagerServer::processDisconnected, this, _1, _2));

}

void NetworkManagerServer::processRequestConnect(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
	unsigned int pid = room_.getGenID();

	Data::UserData for_pid;
	for_pid.set_pid(pid);

	GamePacket<ProtobufStrategy> send_packet = createAcceptedPacket(for_pid);
	room_.sendTo(pid, send_packet.data(), send_packet.size());
}

void NetworkManagerServer::processHello(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
	Data::UserData joined;
	packet.parseBody(joined, header.size());

	// make eid, pawn
	float fwidth = (world_.getWidth() - World::Dummy) / 2;
	Snake* pawn = world_.createPlayerPawn(Vec2(random(-fwidth, fwidth), random(-fwidth, fwidth)));
	joined.set_eid(pawn->getID());
	
	// send InitGame packet to joined user
	Data::InitGameData idata;
	ProtobufServerUtils::serializeInitGameData(&world_, joined, idata);

	auto init_packet = createInitGamePacket(idata);
	room_.sendTo(joined.pid(), init_packet.data(), init_packet.size());

	// send Intro packet to others
	auto intro_packet = createIntroPacket(joined);
	room_.broadcast(intro_packet.data(), intro_packet.size());

	all_users_.emplace(joined.pid(), joined);
	showAllUsers();
}


void NetworkManagerServer::processReadyToJoin(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
}

void NetworkManagerServer::processClientCommand(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
}

void NetworkManagerServer::processReadyToChange(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
}

void NetworkManagerServer::processDisconnected(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
	Data::UserData disconnected;
	packet.parseBody(disconnected, header.size());

	unsigned int pid = disconnected.pid();

	auto it = all_users_.find(pid);
	if (it != std::end(all_users_))
	{
		auto discon_packet = createNotifyDisconnectedPacket(it->second);
		room_.broadcast(discon_packet.data(), discon_packet.size());
		all_users_.erase(it);
	}
	showAllUsers();
}

void NetworkManagerServer::showAllUsers()
{
	std::cout << std::endl << "-------- show all users --------" << std::endl;
	for (auto e : all_users_)
	{
		std::cout << e.second.DebugString() << std::endl;
	}
	std::cout<<"--------------------------------" << std::endl << std::endl;
}

void NetworkManagerServer::replicateToClients()
{
	Data::ReplicateData rdata;
	ProtobufServerUtils::serializeReplicateData(&world_, rdata);

	auto packet = createReplicatePacket(rdata);
	room_.broadcast(packet.data(), packet.size());
}


GamePacket<ProtobufStrategy>
NetworkManagerServer::createAcceptedPacket(const Data::UserData& data)
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(data, Data::PacketType::Accepted);
	return packet;
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


GamePacket<ProtobufStrategy>
NetworkManagerServer::createDisconnectedPacket(const Data::UserData& data)
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(data, Data::PacketType::Disconnected);
	return packet;
}