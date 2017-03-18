#pragma once
//------------------------------------------------------------------------
//
//  Name:		ProtobufClientUtils.h
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


class ProtobufClientUtils
{
public:
	
	typedef GamePacket<ProtobufStrategy, 100000> RecvPacket;
	typedef GamePacket<ProtobufStrategy, 100> SendPacket;
	enum { PacketBufferSize = 5 };

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

	static void serializeJoinedData(
		const std::map<unsigned int, Data::UserData>& users,
		Data::JoinedData& joined);

};