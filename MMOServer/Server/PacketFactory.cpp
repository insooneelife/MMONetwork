#include "PacketFactory.h"
#include "../Entity/Entity.h"
#include "../Entity/Prey.h"
#include "../Entity/Projectile.h"
#include "../Entity/Snake.h"
#include "../Entity/Wall.h"
#include "../Entity/RigidBody.h"
#include "../EntityManager.h"
#include "../World.h"

void PacketFactory::serializeVec2(float x, float y, Data::Vec2& out)
{
	out.set_x(x);
	out.set_y(y);
}

void PacketFactory::serializeCommandData(unsigned int pid, Data::CommandType cmd, Data::CommandData& out)
{
	out.set_pid(pid);
	out.set_cmd(cmd);
}

void PacketFactory::serializeUserData(unsigned int pid, Data::UserData& out)
{
	out.set_pid(pid);
}

void PacketFactory::serializeUserData(unsigned int pid, int point, Data::UserData& out)
{
	out.set_pid(pid);
	out.set_point(point);
}

void PacketFactory::serializeUserData(
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

void PacketFactory::serializeSnakeAdditionalUpdateData(
	Snake* snake,
	Data::SnakeAdditionalUpdateData& out)
{
	for (auto e : snake->getBodies())
	{
		auto body = out.add_body();
		body->set_x(e->getPos().x);
		body->set_y(e->getPos().y);
	}
}

void PacketFactory::serializeEntityUpdateData(
	unsigned int eid,
	Vec2 pos,
	Data::EntityUpdateData& out)
{
	out.set_eid(eid);
	auto p = out.mutable_pos();
	p->set_x(pos.x);
	p->set_y(pos.y);
}

void PacketFactory::serializeEntityUpdateData(
	unsigned int eid,
	const Data::SnakeAdditionalUpdateData& sdata,
	Data::EntityUpdateData& out)
{
	out.set_eid(eid);
	auto s = out.mutable_sdata();
	
	for (int i = 0; i < sdata.body_size(); ++i)
	{
		auto add_here = s->add_body();

		auto b = sdata.body(i);
		add_here->set_x(b.x());
		add_here->set_y(b.y());
	}
}

void PacketFactory::serializeUpdateData(
	const std::map <unsigned int, Entity*>& entities,
	const std::map<unsigned int, Data::UserData>& users,
	Data::UpdateData& out)
{
	for (auto e : entities)
	{
		Entity* ent = e.second;
		Entity::Type type = ent->getType();

		
		
		if (type == Entity::Type::kPrey)
		{}

		else if (type == Entity::Type::kProjectile)
		{
			auto add_here = out.add_updated_entities();
			Projectile* p = static_cast<Projectile*>(ent);

			add_here->set_eid(ent->getID());
			auto pos = add_here->mutable_pos();
			pos->set_x(p->getPos().x);
			pos->set_y(p->getPos().y);
		}

		else if (type == Entity::Type::kSnake)
		{
			auto add_here = out.add_updated_entities();
			add_here->set_eid(ent->getID());

			Snake* s = static_cast<Snake*>(ent);
			auto sdata = add_here->mutable_sdata();
			serializeSnakeAdditionalUpdateData(s, *sdata);
		}

		else if (type == Entity::Type::kWall)
		{}
		
	}
}

void PacketFactory::serializeWallAdditionalCreateData(
	Vec2 begin,
	Vec2 end,
	Data::WallAdditionalCreateData& out)
{
	auto b = out.mutable_begin();
	auto e = out.mutable_end();
	b->set_x(begin.x);
	b->set_y(begin.y);
	e->set_x(end.x);
	e->set_y(end.y);
}

void PacketFactory::serializeSnakeAdditionalCreateData(
	Snake* snake,
	Data::SnakeAdditionalCreateData& out)
{
	out.set_control_type(snake->getControlType());

	for (auto e : snake->getBodies())
	{
		auto body = out.add_bodies();
		body->set_x(e->getPos().x);
		body->set_y(e->getPos().y);
	}
}


void PacketFactory::serializeEntityCreateData(Entity* ent, Data::EntityCreateData& out)
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
		serializeSnakeAdditionalCreateData(s, *sdata);
	}

	else if (ent->getType() == Entity::Type::kWall)
	{
		Wall* w = static_cast<Wall*>(ent);
		auto wdata = out.mutable_wdata();
		serializeWallAdditionalCreateData(w->getBegin(), w->getEnd(), *wdata);
	}
}

void PacketFactory::serializeCreateData(
	World* world,
	Data::CreateData& out)
{
	for (auto ent : world->getEntityMgr().getEntities())
	{
		auto cdata = out.add_created_entities();
		serializeEntityCreateData(ent.second, *cdata);
	}
}

void PacketFactory::serializeModifyData(
	World* world,
	Data::ModifyData& out)
{
	for (auto e : world->getModifies())
	{
		auto mdata = out.add_modifies();
		if (e.What == ModifyInfo::Create)
		{
			auto cdata = mdata->mutable_created();
			Entity* ent = world->getEntityMgr().getEntity(e.ID);
			if (ent != nullptr)
			{
				Entity::Type type = ent->getType();
				serializeEntityCreateData(ent, *cdata);
			}
		}
		else if (e.What == ModifyInfo::Delete)
		{
			mdata->set_destroyed(e.ID);
		}
	}
}

void PacketFactory::serializeReplicateData(
	World* world,
	Data::ReplicateData& out)
{
	auto udata = out.mutable_updated();
	auto mdata = out.mutable_modified();
	
	serializeUpdateData(world->getEntityMgr().getEntities(), world->getUsers(), *udata);
	serializeModifyData(world, *mdata);
}

void PacketFactory::serializeInitGameData(
	World* world,
	unsigned int pid,
	unsigned int eid,
	Data::InitGameData& out)
{
	out.set_eid(eid);
	out.set_level(world->getLevel());
	out.set_pid(pid);
	auto cdata = out.mutable_creates();

	serializeCreateData(world, *cdata);
}

void PacketFactory::serializeJoinedData(
	const std::map<unsigned int, Data::UserData>& users,
	Data::JoinedData& out)
{
	for (auto e : users)
	{
		auto add_here = out.add_users();
		*add_here = e.second;
	}
}
