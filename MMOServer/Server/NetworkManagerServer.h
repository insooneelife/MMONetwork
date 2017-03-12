#pragma once

#include <array>
#include <queue>
#include <Common/Protobuf/ProtobufStrategy.h>
#include <Common/Network/GamePacket.hpp>
#include <Common/Network/NetworkManagerBase.hpp>
#include "ProtobufServerUtils.h"

class Room;
class World;
class NetworkManagerServer : public NetworkManagerBase<GamePacket<ProtobufStrategy> >
{
public:

	static GamePacket<ProtobufStrategy> createAcceptedPacket(const Data::UserData& user);
	static GamePacket<ProtobufStrategy> createInitGamePacket(const Data::InitGameData& user);
	static GamePacket<ProtobufStrategy> createFullPacket();
	static GamePacket<ProtobufStrategy> createJoinedPacket(const Data::JoinedData& user);
	static GamePacket<ProtobufStrategy> createIntroPacket(const Data::UserData& user);
	static GamePacket<ProtobufStrategy> createNotifyDisconnectedPacket(const Data::UserData& user);
	static GamePacket<ProtobufStrategy> createChangeLevelPacket(const Data::InitGameData& user);
	static GamePacket<ProtobufStrategy> createEnterPlayingPacket();
	static GamePacket<ProtobufStrategy> createReplicatePacket(const Data::ReplicateData& data);
	static GamePacket<ProtobufStrategy> createDisconnectedPacket(const Data::UserData& user);

	inline const std::map<unsigned int, Data::UserData>& getUsers() { return all_users_; }

	NetworkManagerServer(World& world, Room& room);

	void showAllUsers();

	void processRequestConnect(
		const Data::HeaderData& header,
		const GamePacket<ProtobufStrategy>& packet);

	void processHello(
		const Data::HeaderData& header,
		const GamePacket<ProtobufStrategy>& packet);

	void processReadyToJoin(
		const Data::HeaderData& header,
		const GamePacket<ProtobufStrategy>& packet);

	void processClientCommand(
		const Data::HeaderData& header,
		const GamePacket<ProtobufStrategy>& packet);

	void processReadyToChange(
		const Data::HeaderData& header,
		const GamePacket<ProtobufStrategy>& packet);

	void processDisconnected(
		const Data::HeaderData& header,
		const GamePacket<ProtobufStrategy>& packet);

private:
	World& world_;
	Room& room_;

	std::map<unsigned int, Data::UserData> all_users_;
};