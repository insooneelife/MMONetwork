#pragma once
//------------------------------------------------------------------------
//
//  Name:		ProtobufServerUtils.h
//
//  Desc:		For create game packet.
//			
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include <vector>
#include <Common/Protobuf/ProtobufStrategy.h>
#include <Common/Network/GamePacket.hpp>
#include <Common/Protobuf/generated/Base.pb.h>
#include <Common/Protobuf/generated/HeaderData.pb.h>
#include <Common/Protobuf/generated/CommandData.pb.h>
#include <Common/Protobuf/generated/UserData.pb.h>
#include <Common/Protobuf/generated/CreateData.pb.h>
#include <Common/Protobuf/generated/ReplicateData.pb.h>
#include <Common/Protobuf/generated/InitGameData.pb.h>
#include <Common/Protobuf/generated/JoinedData.pb.h>
#include <Common/Math/Vec2.h>

class Entity;
class Snake;
class World;
class ProtobufServerUtils
{
public:

	typedef GamePacket<ProtobufStrategy, 100> RecvPacket;
	typedef GamePacket<ProtobufStrategy, 200000> SendPacket;
	enum { PacketBufferSize = 1000 };
	
	static void serializeVec2(float x, float y, Data::Vec2& out);

	static void serializeCommandData(unsigned int pid, Data::CommandType cmd, Data::CommandData& out);

	static void serializeUserData(unsigned int pid,	Data::UserData& out);

	static void serializeUserData(unsigned int pid, int point, Data::UserData& out);

	static void serializeUserData(
		unsigned int pid,
		const std::string& name,
		unsigned int eid,
		unsigned int character,
		int point,
		Data::UserData& out);

	static void serializeWallAdditionalData(
		Vec2 begin, 
		Vec2 end,
		Data::WallAdditionalData& out);

	static void serializeSnakeAdditionalData(
		Snake* snake,
		Data::SnakeAdditionalData& out);

	static void serializeEntityData(Entity* ent, Data::EntityData& out);


	static void serializeCreateData(
		World* world,
		Data::CreateData& out);

	static void serializeReplicateData(
		World* world,
		Data::ReplicateData& out);

	static void serializeInitGameData(
		World* world,
		Data::UserData joined,
		Data::InitGameData& out);

	static void serializeJoinedData(
		World* world,
		Data::JoinedData& joined);

};