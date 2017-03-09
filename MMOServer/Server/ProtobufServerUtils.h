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
#include <Common/Network/GamePacket.hpp>
#include <Common/Protobuf/generated/Base.pb.h>
#include <Common/Protobuf/generated/Base.pb.h>
#include <Common/Protobuf/generated/HeaderData.pb.h>
#include <Common/Protobuf/generated/CommandData.pb.h>
#include <Common/Protobuf/generated/UserData.pb.h>
#include <Common/Protobuf/generated/CreateData.pb.h>
#include <Common/Protobuf/generated/UpdateData.pb.h>
#include <Common/Protobuf/generated/ReplicateData.pb.h>
#include <Common/Protobuf/generated/InitGameData.pb.h>
#include <Common/Protobuf/generated/JoinedData.pb.h>
#include <Common/Math/Vec2.h>

struct ModifyInfo
{
	enum What
	{
		Create, Delete
	};

	unsigned int ID;
	What What;
};

class Entity;
class Snake;
class World;
class ProtobufServerUtils
{
public:
	
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

	static void serializeSnakeAdditionalUpdateData(
		Snake* snake,
		Data::SnakeAdditionalUpdateData& out);

	static void serializeEntityUpdateData(
		unsigned int eid,
		Vec2 pos,
		Data::EntityUpdateData& out);

	static void serializeEntityUpdateData(
		unsigned int eid,
		const Data::SnakeAdditionalUpdateData& sdata,
		Data::EntityUpdateData& out);

	static void serializeUpdateData(
		const std::map <unsigned int, Entity*>& entities,
		const std::map<unsigned int, Data::UserData>& users,
		Data::UpdateData& out);

	static void serializeWallAdditionalCreateData(
		Vec2 begin, 
		Vec2 end,
		Data::WallAdditionalCreateData& out);

	static void serializeSnakeAdditionalCreateData(
		Snake* snake,
		Data::SnakeAdditionalCreateData& out);

	static void serializeEntityCreateData(Entity* ent, Data::EntityCreateData& out);


	static void serializeCreateData(
		World* world,
		Data::CreateData& out);

	static void serializeModifyData(
		World* world,
		Data::ModifyData& out);

	static void serializeReplicateData(
		World* world,
		Data::ReplicateData& out);

	static void serializeInitGameData(
		World* world,
		unsigned int pid,
		unsigned int eid,
		Data::InitGameData& out);

	static void serializeJoinedData(
		const std::map<unsigned int, Data::UserData>& users,
		Data::JoinedData& joined);

};