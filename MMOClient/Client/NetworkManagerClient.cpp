#include "NetworkManagerClient.h"
#include "Client.h"

NetworkManagerClient::NetworkManagerClient(Client& session)
	:
	session_(session)
{}


void NetworkManagerClient::copyPackets()
{
	GamePacket<ProtobufStrategy> packet;
	while (session_.dequeue(packet) && idx_ < copied_packets_.size())
	{
		copied_packets_[idx_++] = packet;
	}

	while (session_.dequeue(packet)) {}
}


void NetworkManagerClient::processQueuedPackets()
{
	for (int i = 0; i < idx_; ++i)
	{
		processByType(copied_packets_[i]);
	}
	idx_ = 0;
}



void NetworkManagerClient::processByType(const GamePacket<ProtobufStrategy>& packet)
{
	Data::HeaderData header;
	packet.parseHeader(header);

	if (header.type() == Data::PacketType::RequestConnect)
	{
		processInitGame(header, packet);
	}
	else if (header.type() == Data::PacketType::Full)
	{
		processFull(header, packet);
	}
	else if (header.type() == Data::PacketType::Joined)
	{
		processJoined(header, packet);
	}
	else if (header.type() == Data::PacketType::Intro)
	{
		processIntro(header, packet);
	}
	else if (header.type() == Data::PacketType::NotifyDisconnected)
	{
		processNotifyDisconnected(header, packet);
	}
	else if (header.type() == Data::PacketType::ChangeLevel)
	{
		processChangeLevel(header, packet);
	}
	else if (header.type() == Data::PacketType::EnterPlaying)
	{
		processEnterPlaying(header, packet);
	}
	else if (header.type() == Data::PacketType::Replicate)
	{
		processReplicate(header, packet);
	}
}

void NetworkManagerClient::processInitGame(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{
	std::cout << "processInitGame" << std::endl;
	
	// parse data
	Data::InitGameData idata;
	packet.parseBody(idata, header.size());

	// init world
	unsigned int pid = idata.pid();
	unsigned int eid = idata.eid();
	int level = idata.level();
	auto cdata = idata.creates();

	_user_data.set_pid(pid);
	_user_data.set_eid(eid);
	
	// make name, character at client side
	const std::string name = "insooneelife";
	const int character = 0;

	_user_data.set_name(name);
	_user_data.set_character(character);

	// send ready packet
	auto send_packet = createReadyToJoinPacket(_user_data);
	session_.send(send_packet.data(), send_packet.size());
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
{}

void NetworkManagerClient::processNotifyDisconnected(
	const Data::HeaderData& header,
	const GamePacket<ProtobufStrategy>& packet)
{}

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