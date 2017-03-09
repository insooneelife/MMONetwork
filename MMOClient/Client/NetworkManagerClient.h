#pragma once

#include <array>
#include <Common/Protobuf/ProtobufStrategy.h>
#include <Common/Network/GamePacket.hpp>
#include "ProtobufClientUtils.h"

class Client;
class NetworkManagerClient
{
public:

	static GamePacket<ProtobufStrategy> createReadyToJoinPacket(const Data::UserData& user);
	static GamePacket<ProtobufStrategy> createReadyToChangePacket(const Data::UserData& user);
	static GamePacket<ProtobufStrategy> createClientCommandPacket(const Data::CommandData& cmd);

	explicit NetworkManagerClient(Client& session);

	void copyPackets();

	void processQueuedPackets();

	void processByType(const GamePacket<ProtobufStrategy>& packet);

	void processInitGame(
		const Data::HeaderData& header,
		const GamePacket<ProtobufStrategy>& packet);


	void processFull(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);

	void processJoined(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);

	void processIntro(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);

	void processNotifyDisconnected(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);

	void processChangeLevel(const Data::HeaderData& header,	const GamePacket<ProtobufStrategy>& packet);

	void processEnterPlaying(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);

	void processReplicate(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);


private:

	Client& session_;
	std::array<GamePacket<ProtobufStrategy>, 50> copied_packets_;
	int idx_;
	
	Data::UserData _user_data;
	std::map<unsigned int, Data::UserData> _all_users;
};