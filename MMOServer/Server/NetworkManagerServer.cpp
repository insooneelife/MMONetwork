#include <set>
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
	const RecvPacket& packet)
{
	/*unsigned int pid = room_.getGenID();

	Data::UserData for_pid;
	for_pid.set_pid(pid);

	GamePacket<ProtobufStrategy> send_packet = createAcceptedPacket(for_pid);
	room_.sendTo(pid, send_packet.data(), send_packet.size());*/
}

void NetworkManagerServer::processHello(
	const Data::HeaderData& header,
	const RecvPacket& packet)
{
	Data::UserData joined;
	packet.parseBody(joined, header.size());

	// make eid, pawn
	float fwidth = (world_.getWidth() - World::Dummy) / 2;
	Snake* pawn = world_.createPlayerPawn(Vec2(random(-fwidth, fwidth), random(-fwidth, fwidth)), joined);
	joined.set_eid(pawn->getID());
	
	// send InitGame packet to joined user
	Data::InitGameData idata;
	ProtobufServerUtils::serializeInitGameData(&world_, joined, idata);

	auto init_packet = createInitGamePacket(idata);
	room_.sendTo(joined.pid(), init_packet.data(), init_packet.size());

	// send Intro packet to others
	std::set<unsigned int> ignore;
	ignore.emplace(joined.pid());

	auto intro_packet = createIntroPacket(joined);
	room_.broadcast(intro_packet.data(), intro_packet.size(), ignore);

	// create player controller
	std::unique_ptr<PlayerState> pstate(new PlayerState());
	pstate->setUserData(joined);

	std::cout << joined.DebugString() << std::endl;

	all_users_.emplace(joined.pid(), std::move(pstate));
	ignore_users_.emplace(joined.pid());
	//showAllUsers();
}


void NetworkManagerServer::processReadyToJoin(
	const Data::HeaderData& header,
	const RecvPacket& packet)
{
	Data::UserData joined;
	packet.parseBody(joined, header.size());

	ignore_users_.erase(joined.pid());

	Data::JoinedData jdata;
	auto joined_packet = createJoinedPacket(jdata);
	room_.sendTo(joined.pid(), joined_packet.data(), joined_packet.size());
}

void NetworkManagerServer::processClientCommand(
	const Data::HeaderData& header,
	const RecvPacket& packet)
{
	Data::CommandData cmd;
	packet.parseBody(cmd, header.size());

	unsigned int pid = cmd.pid();
	Data::CommandType ctype = cmd.cmd();

	auto it = all_users_.find(pid);
	if (it != std::end(all_users_))
	{
		world_.getEntityMgr().dispatchMsg(0, it->second->getUserData().eid(), Message::kCommand, &ctype);
	}
}

void NetworkManagerServer::processReadyToChange(
	const Data::HeaderData& header,
	const RecvPacket& packet)
{
}

void NetworkManagerServer::processDisconnected(
	const Data::HeaderData& header,
	const RecvPacket& packet)
{
	Data::UserData disconnected;
	packet.parseBody(disconnected, header.size());

	unsigned int pid = disconnected.pid();

	auto it = all_users_.find(pid);
	if (it != std::end(all_users_))
	{
		auto discon_packet = createNotifyDisconnectedPacket(it->second->getUserData());
		room_.broadcast(discon_packet.data(), discon_packet.size());
		all_users_.erase(it);
	}
	//showAllUsers();
}

void NetworkManagerServer::showAllUsers()
{
	std::cout << std::endl << "-------- show all users --------" << std::endl;
	for (auto e = std::begin(all_users_); e != std::end(all_users_); ++e)
	{
		std::cout << e->second->getUserData().DebugString() << std::endl;
	}
	std::cout<<"--------------------------------" << std::endl << std::endl;
}

void NetworkManagerServer::replicateToClients()
{
	Data::ReplicateData rdata;
	ProtobufServerUtils::serializeReplicateData(&world_, rdata);

	auto packet = createReplicatePacket(rdata);
	room_.broadcast(packet.data(), packet.size(), ignore_users_);
}

bool NetworkManagerServer::queryUserDataByEID(unsigned int eid, Data::UserData& user_data)
{
	for (auto u = std::begin(all_users_); u != std::end(all_users_); ++u)
	{
		if (u->second->getUserData().eid() == eid)
		{
			user_data = u->second->getUserData();
			return true;
		}
	}
	return false;
}


NetworkManagerServer::SendPacket
NetworkManagerServer::createAcceptedPacket(const Data::UserData& data)
{
	NetworkManagerServer::SendPacket packet;
	packet.serializeFrom(data, Data::PacketType::Accepted);
	return packet;
}

NetworkManagerServer::SendPacket
NetworkManagerServer::createInitGamePacket(const Data::InitGameData& data)
{
	NetworkManagerServer::SendPacket packet;
	packet.serializeFrom(data, Data::PacketType::InitGame);
	return packet;
}

NetworkManagerServer::SendPacket
NetworkManagerServer::createFullPacket()
{
	NetworkManagerServer::SendPacket packet;
	packet.serializeFrom(Data::PacketType::Full);
	return packet;
}

NetworkManagerServer::SendPacket
NetworkManagerServer::createJoinedPacket(const Data::JoinedData& user)
{
	NetworkManagerServer::SendPacket packet;
	packet.serializeFrom(user, Data::PacketType::Joined);
	return packet;
}

NetworkManagerServer::SendPacket
NetworkManagerServer::createIntroPacket(const Data::UserData& user)
{
	NetworkManagerServer::SendPacket packet;
	packet.serializeFrom(user, Data::PacketType::Intro);
	return packet;
}

NetworkManagerServer::SendPacket
NetworkManagerServer::createNotifyDisconnectedPacket(const Data::UserData& user)
{
	NetworkManagerServer::SendPacket packet;
	packet.serializeFrom(user, Data::PacketType::NotifyDisconnected);
	return packet;
}

NetworkManagerServer::SendPacket
NetworkManagerServer::createChangeLevelPacket(const Data::InitGameData& data)
{
	NetworkManagerServer::SendPacket packet;
	packet.serializeFrom(data, Data::PacketType::ChangeLevel);
	return packet;
}

NetworkManagerServer::SendPacket
NetworkManagerServer::createEnterPlayingPacket()
{
	NetworkManagerServer::SendPacket packet;
	packet.serializeFrom(Data::PacketType::EnterPlaying);
	return packet;
}

NetworkManagerServer::SendPacket
NetworkManagerServer::createReplicatePacket(const Data::ReplicateData& data)
{
	NetworkManagerServer::SendPacket packet;
	packet.serializeFrom(data, Data::PacketType::Replicate);
	return packet;
}


NetworkManagerServer::RecvPacket
NetworkManagerServer::createDisconnectedPacket(const Data::UserData& data)
{
	NetworkManagerServer::RecvPacket packet;
	packet.serializeFrom(data, Data::PacketType::Disconnected);
	return packet;
}