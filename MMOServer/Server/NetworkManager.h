#pragma once

#include <array>
#include <Common/Protobuf/ProtobufStrategy.h>
#include <Common/Network/GamePacket.hpp>
class Room;
class World;
class NetworkManager
{
public:

	explicit NetworkManager(World& world, Room& room);

	void copyPackets();
	void processQueuedPackets();

	void processByType(const GamePacket<ProtobufStrategy>& packet);

	void processRequestConnect(
		const Data::HeaderData& header,
		const GamePacket<ProtobufStrategy>& packet);

private:
	World& world_;
	Room& room_;
	std::array<GamePacket<ProtobufStrategy>, 50> copied_packets_;
	int idx_;
};