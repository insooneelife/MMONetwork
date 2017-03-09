#include "ProtobufClientUtils.h"

void ProtobufClientUtils::serializeVec2(float x, float y, Data::Vec2& out)
{
	out.set_x(x);
	out.set_y(y);
}

void ProtobufClientUtils::serializeCommandData(unsigned int pid, Data::CommandType cmd, Data::CommandData& out)
{
	out.set_pid(pid);
	out.set_cmd(cmd);
}

void ProtobufClientUtils::serializeUserData(unsigned int pid, Data::UserData& out)
{
	out.set_pid(pid);
}

void ProtobufClientUtils::serializeUserData(unsigned int pid, int point, Data::UserData& out)
{
	out.set_pid(pid);
	out.set_point(point);
}

void ProtobufClientUtils::serializeUserData(
	unsigned int pid,
	const std::string& name,
	unsigned int eid,
	unsigned int character,
	int point,
	Data::UserData& out)
{
	out.set_pid(pid);
	out.set_name(name);
	out.set_eid(eid);
	out.set_character(character);
	out.set_point(point);
}


void ProtobufClientUtils::serializeJoinedData(
	const std::map<unsigned int, Data::UserData>& users,
	Data::JoinedData& out)
{
	for (auto e : users)
	{
		auto add_here = out.add_users();
		*add_here = e.second;
	}
}
