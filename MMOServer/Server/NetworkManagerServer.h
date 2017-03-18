#pragma once

#include <array>
#include <queue>
#include <memory>
#include <Common/Protobuf/ProtobufStrategy.h>
#include <Common/Network/GamePacket.hpp>
#include <Common/Network/NetworkManagerBase.hpp>
#include "ProtobufServerUtils.h"
#include "PlayerState.h"

class Room;
class World;
class NetworkManagerServer 
	: public NetworkManagerBase<ProtobufServerUtils::RecvPacket, ProtobufServerUtils::PacketBufferSize >
{
public:

	typedef ProtobufServerUtils::RecvPacket RecvPacket;
	typedef ProtobufServerUtils::SendPacket SendPacket;

	static SendPacket createAcceptedPacket(const Data::UserData& user);
	static SendPacket createInitGamePacket(const Data::InitGameData& user);
	static SendPacket createFullPacket();
	static SendPacket createJoinedPacket(const Data::JoinedData& user);
	static SendPacket createIntroPacket(const Data::UserData& user);
	static SendPacket createNotifyDisconnectedPacket(const Data::UserData& user);
	static SendPacket createChangeLevelPacket(const Data::InitGameData& user);
	static SendPacket createEnterPlayingPacket();
	static SendPacket createReplicatePacket(const Data::ReplicateData& data);
	static RecvPacket createDisconnectedPacket(const Data::UserData& user);

	//inline const std::map<unsigned int, Data::UserData>& getUsers() { return all_users_; }
	inline const std::map<unsigned int, std::unique_ptr<PlayerState> >& getUsers() const { return all_users_; }
	inline const std::set<unsigned int>& getIgnoreUsers() { return ignore_users_; }

	NetworkManagerServer(World& world, Room& room);

	void showAllUsers();

	void replicateToClients();

	bool queryUserDataByEID(unsigned int eid, Data::UserData& user_data);

	void processRequestConnect(
		const Data::HeaderData& header,
		const RecvPacket& packet);

	void processHello(
		const Data::HeaderData& header,
		const RecvPacket& packet);

	void processReadyToJoin(
		const Data::HeaderData& header,
		const RecvPacket& packet);

	void processClientCommand(
		const Data::HeaderData& header,
		const RecvPacket& packet);

	void processReadyToChange(
		const Data::HeaderData& header,
		const RecvPacket& packet);

	void processDisconnected(
		const Data::HeaderData& header,
		const RecvPacket& packet);

private:
	World& world_;
	Room& room_;

	std::map<unsigned int, std::unique_ptr<PlayerState> > all_users_;
	std::set<unsigned int> ignore_users_;
};