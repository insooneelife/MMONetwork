#pragma once

#include <array>
#include <Common/Protobuf/ProtobufStrategy.h>
#include <Common/Network/GamePacket.hpp>
#include "ProtobufServerUtils.h"

class Room;
class World;
class NetworkManagerServer
{
public:

	static GamePacket<ProtobufStrategy> createInitGamePacket(const Data::InitGameData& user);
	static GamePacket<ProtobufStrategy> createFullPacket();
	static GamePacket<ProtobufStrategy> createJoinedPacket(const Data::JoinedData& user);
	static GamePacket<ProtobufStrategy> createIntroPacket(const Data::UserData& user);
	static GamePacket<ProtobufStrategy> createNotifyDisconnectedPacket(const Data::UserData& user);
	static GamePacket<ProtobufStrategy> createChangeLevelPacket(const Data::InitGameData& user);
	static GamePacket<ProtobufStrategy> createEnterPlayingPacket();
	static GamePacket<ProtobufStrategy> createReplicatePacket(const Data::ReplicateData& user);



	NetworkManagerServer(World& world, Room& room);

	void copyPackets();
	void processQueuedPackets();

	void processByType(const GamePacket<ProtobufStrategy>& packet);

	void processRequestConnect(
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
	std::array<GamePacket<ProtobufStrategy>, 50> copied_packets_;
	int idx_;
};