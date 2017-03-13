#include "ProtobufServerUtils.h"
#include "../Entity/Entity.h"
#include "../Entity/Prey.h"
#include "../Entity/Projectile.h"
#include "../Entity/Snake.h"
#include "../Entity/Wall.h"
#include "../Entity/RigidBody.h"
#include "../EntityManager.h"
#include "../World.h"
#include "../Server/NetworkManagerServer.h"

void ProtobufServerUtils::serializeVec2(float x, float y, Data::Vec2& out)
{
	out.set_x(x);
	out.set_y(y);
}

void ProtobufServerUtils::serializeCommandData(unsigned int pid, Data::CommandType cmd, Data::CommandData& out)
{
	out.set_pid(pid);
	out.set_cmd(cmd);
}

void ProtobufServerUtils::serializeUserData(unsigned int pid, Data::UserData& out)
{
	out.set_pid(pid);
}

void ProtobufServerUtils::serializeUserData(unsigned int pid, int point, Data::UserData& out)
{
	out.set_pid(pid);
	out.set_point(point);
}

void ProtobufServerUtils::serializeUserData(
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


void ProtobufServerUtils::serializeWallAdditionalData(
	Vec2 begin,
	Vec2 end,
	Data::WallAdditionalData& out)
{
	auto b = out.mutable_begin();
	auto e = out.mutable_end();
	b->set_x(begin.x);
	b->set_y(begin.y);
	e->set_x(end.x);
	e->set_y(end.y);
}

void ProtobufServerUtils::serializeSnakeAdditionalData(
	Snake* snake,
	Data::SnakeAdditionalData& out)
{
	out.set_control_type(snake->getControlType());

	for (auto e : snake->getBodies())
	{
		auto body = out.add_bodies();
		body->set_x(e->getPos().x);
		body->set_y(e->getPos().y);
	}
}


void ProtobufServerUtils::serializeEntityData(Entity* ent, Data::EntityData& out)
{
	out.set_eid(ent->getID());
	out.set_etype(ent->getType());

	if (ent->getType() == Entity::Type::kPrey)
	{
		Prey* p = static_cast<Prey*>(ent);
		auto pos = out.mutable_pos();
		pos->set_x(p->getPos().x);
		pos->set_y(p->getPos().y);
	}

	else if (ent->getType() == Entity::Type::kProjectile)
	{
		Projectile* p = static_cast<Projectile*>(ent);
		auto pos = out.mutable_pos();
		pos->set_x(p->getPos().x);
		pos->set_y(p->getPos().y);
	}

	else if (ent->getType() == Entity::Type::kSnake)
	{
		Snake* s = static_cast<Snake*>(ent);
		auto sdata = out.mutable_sdata();
		serializeSnakeAdditionalData(s, *sdata);
	}

	else if (ent->getType() == Entity::Type::kWall)
	{
		Wall* w = static_cast<Wall*>(ent);
		auto wdata = out.mutable_wdata();
		serializeWallAdditionalData(w->getBegin(), w->getEnd(), *wdata);
	}
}

void ProtobufServerUtils::serializeCreateData(
	World* world,
	Data::CreateData& out)
{
	for (auto ent : world->getEntityMgr().getEntities())
	{
		auto cdata = out.add_created_entities();
		serializeEntityData(ent.second, *cdata);
	}
}



void ProtobufServerUtils::serializeReplicateData(
	World* world,
	Data::ReplicateData& out)
{
	for (auto e : world->getEntityMgr().getEntities())
	{
		auto add_here = out.add_entities();
		serializeEntityData(e.second, *add_here);
	}

	auto udata = out.mutable_updated_users();
	for (auto e : world->getNetworkMgr().getUsers())
	{
		auto add_here = out.add_updated_users();
		*add_here = e.second;
	}
}

void ProtobufServerUtils::serializeInitGameData(
	World* world,
	Data::UserData joined,
	Data::InitGameData& out)
{
	*(out.mutable_joined()) = joined;

	out.set_level(world->getLevel());

	auto cdata = out.mutable_creates();
	serializeCreateData(world, *cdata);
	
	auto jdata = out.mutable_others();
	serializeJoinedData(world->getNetworkMgr().getUsers(), *jdata);
}

void ProtobufServerUtils::serializeJoinedData(
	const std::map<unsigned int, Data::UserData>& users,
	Data::JoinedData& out)
{
	for (auto e : users)
	{
		auto add_here = out.add_users();
		*add_here = e.second;
	}
}
