#pragma once

#include <array>
#include <queue>
#include <string>
#include <Common/Protobuf/ProtobufStrategy.h>
#include <Common/Network/GamePacket.hpp>
#include <Common/Network/NetworkManagerBase.hpp>
#include "ProtobufClientUtils.h"

class Client;
class NetworkManagerClient : public NetworkManagerBase<GamePacket<ProtobufStrategy> >
{
public:

	static GamePacket<ProtobufStrategy> createHelloPacket(const Data::UserData& user);
	static GamePacket<ProtobufStrategy> createReadyToJoinPacket(const Data::UserData& user);
	static GamePacket<ProtobufStrategy> createReadyToChangePacket(const Data::UserData& user);
	static GamePacket<ProtobufStrategy> createClientCommandPacket(const Data::CommandData& cmd);

	inline const Data::UserData& getUserData() { return _user_data; }

	explicit NetworkManagerClient(Client& session);

	void showAllUsers();

	void sendUpdates();

	void processAccepted(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);

	void processInitGame(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);

	void processFull(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);

	void processJoined(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);

	void processIntro(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);

	void processNotifyDisconnected(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);

	void processChangeLevel(const Data::HeaderData& header,	const GamePacket<ProtobufStrategy>& packet);

	void processEnterPlaying(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);

	void processReplicate(const Data::HeaderData& header, const GamePacket<ProtobufStrategy>& packet);


private:

	std::string generateRandomName();

	Client& session_;
	
	Data::UserData _user_data;
	std::map<unsigned int, Data::UserData> _all_users;
	bool start_send_;
};