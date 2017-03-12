#include "NetworkManagerClient.h"
#include "Client.h"
#include <Common/Utils.h>

NetworkManagerClient::NetworkManagerClient(Client& session)
	:
	session_(session)
{
	using namespace std::placeholders;

	_process_map.emplace(
		Data::PacketType::Accepted,
		std::bind(&NetworkManagerClient::processAccepted, this, _1, _2));

	_process_map.emplace(
		Data::PacketType::InitGame,
		std::bind(&NetworkManagerClient::processInitGame, this, _1, _2));

	_process_map.emplace(
		Data::PacketType::Full,
		std::bind(&NetworkManagerClient::processFull, this, _1, _2));

	_process_map.emplace(
		Data::PacketType::Joined,
		std::bind(&NetworkManagerClient::processJoined, this, _1, _2));

	_process_map.emplace(
		Data::PacketType::Intro,
		std::bind(&NetworkManagerClient::processIntro, this, _1, _2));

	_process_map.emplace(
		Data::PacketType::NotifyDisconnected,
		std::bind(&NetworkManagerClient::processNotifyDisconnected, this, _1, _2));

	_process_map.emplace(
		Data::PacketType::ChangeLevel,
		std::bind(&NetworkManagerClient::processChangeLevel, this, _1, _2));

	_process_map.emplace(
		Data::PacketType::EnterPlaying,
		std::bind(&NetworkManagerClient::processEnterPlaying, this, _1, _2));

	_process_map.emplace(
		Data::PacketType::Replicate,
		std::bind(&NetworkManagerClient::processReplicate, this, _1, _2));

}

void NetworkManagerClient::processAccepted(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
	packet.parseBody<Data::UserData>(_user_data, header.size());

	// set user data
	_user_data.set_name(generateRandomName());
	_user_data.set_character(1);
	
	_all_users.emplace(_user_data.pid(), _user_data);

	auto send_packet = createHelloPacket(_user_data);
	session_.send(send_packet.data(), send_packet.size());
}

void NetworkManagerClient::processInitGame(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
	// parse data
	Data::InitGameData idata;
	packet.parseBody(idata, header.size());

	// init world
	int level = idata.level();
	auto cdata = idata.creates();

	_user_data = idata.joined();
	_all_users[_user_data.pid()] = _user_data;

	auto jdata = idata.others();
	for (int i = 0; i < jdata.users_size(); ++i)
	{
		_all_users.emplace(jdata.users(i).pid(), jdata.users(i));
	}

	// send ready packet
	auto send_packet = createReadyToJoinPacket(_user_data);
	session_.send(send_packet.data(), send_packet.size());

	showAllUsers();
}

void NetworkManagerClient::processFull(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{}

void NetworkManagerClient::processJoined(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{}

void NetworkManagerClient::processIntro(
	const Data::HeaderData& header, 
	const GamePacket<ProtobufStrategy>& packet)
{
	Data::UserData udata;
	packet.parseBody(udata, header.size());
	_all_users.emplace(udata.pid(), udata);

	showAllUsers();
}

void NetworkManagerClient::processNotifyDisconnected(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
	Data::UserData udata;
	packet.parseBody(udata, header.size());
	_all_users.erase(udata.pid());

	showAllUsers();
}

void NetworkManagerClient::processChangeLevel(
	const Data::HeaderData& header, 
	const GamePacket<ProtobufStrategy>& packet)
{}

void NetworkManagerClient::processEnterPlaying(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{}

void NetworkManagerClient::processReplicate(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{}

void NetworkManagerClient::showAllUsers()
{
	std::cout << std::endl << "-------- show all users --------" << std::endl;
	for (auto e : _all_users)
	{
		std::cout << e.second.DebugString() << std::endl;
	}
	std::cout << "--------------------------------" << std::endl << std::endl;
}

std::string NetworkManagerClient::generateRandomName()
{
	std::string name = "";

	for (int i = 0; i < random(3, 20); ++i)
	{
		int a = random(0, 2);
		if(a % 2 == 0)
			name += 'a' + (char)random(0, 26);
		else
			name += 'A' + (char)random(0, 26);
	}
	return name;
}

GamePacket<ProtobufStrategy> NetworkManagerClient::createHelloPacket(const Data::UserData& user)
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(user, Data::PacketType::Hello);
	return packet;
}

GamePacket<ProtobufStrategy> NetworkManagerClient::createReadyToJoinPacket(const Data::UserData& user)
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(user, Data::PacketType::ReadyToJoin);
	return packet;
}

GamePacket<ProtobufStrategy> NetworkManagerClient::createReadyToChangePacket(const Data::UserData& user)
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(user, Data::PacketType::ReadyToChange);
	return packet;
}

GamePacket<ProtobufStrategy> NetworkManagerClient::createClientCommandPacket(const Data::CommandData& cmd)
{
	GamePacket<ProtobufStrategy> packet;
	packet.serializeFrom(cmd, Data::PacketType::ClientCommand);
	return packet;
}