#include <iostream>
#include "World.h"
#include "EntityManager.h"
#include "Camera2D.h"
#include "GraphicsDriver.h"

#include <Common/Utils.h>
#include <Common/Math/Transformations.h>

#include <Box2D/Box2D.h>

#include "Entity/Snake.h"
#include "Entity/Prey.h"
#include "Entity/Projectile.h"
#include "Entity/Structure.h"

#include "Server/NetworkManagerServer.h"

using namespace std;

const float World::OneStep = 0.50f;

const float World::SnakeSpeed = 0.25f;
const float World::SnakeRadius = 0.25f;
const float World::ProjectileSpeed = 1.0f;
const float World::ProjectileRadius = 0.15f;

const float World::PreyRadius = 0.15f;

const float World::Dummy = 2.0f;
const float World::WorldSize = 200.0f;

const int World::SnakeNum = 1000;
const int World::ProjectileNum = 200;
const int World::PreyNum = 1000;
const int World::CellNum = 40;

void World::collide(Snake& s1, Snake& s2)
{
	//cout << "collide!  Snake && Snake" << endl;
}

void World::collide(Snake& s, Projectile& p)
{
	//cout << "collide!  Snake && Projectile" << endl;
}

void World::collide(Projectile& pro, Prey& prey)
{
	//cout << "collide!  Projectile && Prey" << endl;
}

void World::collide(Structure& w, Projectile& p)
{
	//cout << "collide!  Projectile && Structure" << endl;
}

void World::collide(Structure& w, Snake& s)
{
	//cout << "collide!  Snake && Structure" << endl;
}

void World::collide(Snake& s, Prey& p)
{
	if ((s.getPos().distance(p.getPos()) < s.getBRadius() + p.getBRadius()))
	{
		p.setGarbage(true);

		int increase = 1;
		
		p.getWorld().getEntityMgr().dispatchMsg(
			p.getID(), s.getID(), Message::kIncrease, &increase);
	}
}

void World::regenPlayerPawn(Snake* pawn)
{
	
}

void World::updateEntity()
{
	auto s = begin(_snakes);
	while (s != end(_snakes))
	{
		// Test for any dead entities and remove them if necessary.
		if (!(*s)->isGarbage())
		{
			(*s)->update();
			++s;
		}
		else
		{
			if ((*s)->getWorld().getPlayerEntity() != nullptr &&
				(*s)->getID() == (*s)->getWorld().getPlayerEntity()->getID())
				(*s)->getWorld().setPlayerEntity(nullptr);

			if ((*s)->getControlType() == Data::ControlType::Player)

			{
				Data::UserData user_data;
				bool success = _network_mgr->queryUserDataByEID((*s)->getID(), user_data);
				if (success)
				{
					float fwidth = (_width - Dummy) / 2;
					Snake* sn = createPlayerPawn(Vec2(random(-fwidth, fwidth), random(-fwidth, fwidth)), user_data);
					auto it = _network_mgr->getUsers().find(user_data.pid());
					if (it != std::end(_network_mgr->getUsers()))
					{
						it->second->setUserData(user_data);
					}
				}
			}

			delete *s;
			s = _snakes.erase(s);
		}
	}
	
	auto e = begin(_preys);
	while (e != end(_preys))
	{
		// Test for any dead entities and remove them if necessary.
		if (!(*e)->isGarbage())
		{
			(*e)->update();
			++e;
		}
		else
		{
			delete *e;
			e = _preys.erase(e);
		}
	}

	for (auto p = std::begin(_projectiles); p != std::end(_projectiles); ++p)
	{
		(*p)->update();
	}
}

void World::regenEntity()
{
	float fwidth = (_width - Dummy) / 2;
	// Create hunters
	for (int i = 0; i < std::max(SnakeNum - (int)_snakes.size(), 0); ++i)
		createHunter(Vec2(random(-fwidth, fwidth), random(-fwidth, fwidth)));
	
	for (int i = 0; i < std::max(ProjectileNum - (int)_projectiles.size(), 0); ++i)
	{
		float headingX = random(-1, 1);
		float headingY = 1 - sqrt(headingX * headingX);

		createProjectile(
			Vec2(random(-fwidth, fwidth), random(-fwidth, fwidth)),
			Vec2(headingX, headingY), 3);
	}

	// Create preys
	for (int i = 0; i < std::max(PreyNum - (int)_preys.size(), 0); ++i)
		createPrey(Vec2(random(-fwidth, fwidth), random(-fwidth, fwidth)));
}

// World의 생성자에서 모든 entity의 초기화가 이루어진다.
World::World(Room& room, float width)
	:
	_next_validate_id(1),
	_width(width),
	_network_mgr(new NetworkManagerServer(*this, room)),
	_physics(new PhysicsManager(WorldSize, WorldSize)),
	level_(0)
{
	// Create player with hunter
	_player_entity = new Snake(*this, genID(), Vec2(0.0f, 0.0f), Data::ControlType::NPC);
	_snakes.push_back(_player_entity);

	float fwidth = (width - Dummy) / 2;
	Vec2 bl(-fwidth, -fwidth);
	Vec2 br(fwidth, -fwidth);
	Vec2 tl(-fwidth, fwidth);
	Vec2 tr(fwidth, fwidth );

	// Create hunters
	for (int i = 0; i < SnakeNum; ++i)
		createHunter(Vec2(random(-fwidth, fwidth), random(-fwidth, fwidth)));

	// Create Structures
	for (int i = 0; i < 10; i++)
	{
		int type = random(0, 4);
		
		type = 1;
		createStructure(Vec2(random(-fwidth, fwidth), random(-fwidth, fwidth)), random(10.0f, 20.0f), type);
	}


	for (int i = 0; i < ProjectileNum; i++)
	{
		float headingX = random(-1, 1);
		float headingY = 1 - sqrt(headingX * headingX);

		createProjectile(
			Vec2(random(-fwidth, fwidth), random(-fwidth, fwidth)),
			Vec2(headingX, headingY), 3);
	}

	// Create preys
	for (int i = 0; i < PreyNum; i++)
		createPrey(Vec2(random(-fwidth, fwidth), random(-fwidth, fwidth)));

	// Create walls
	std::vector<b2Vec2> walls =
	{
		b2Vec2(bl.x, bl.y),
		b2Vec2(br.x, br.y),
		b2Vec2(tr.x, tr.y),
		b2Vec2(tl.x, tl.y),
		b2Vec2(bl.x, bl.y)
	};

	_created_entities.emplace(Structure::createChain(*this, genID(), walls));

	// Set camera
	Vec2 heading = _player_entity->getHeading();
	Vec2 side = _player_entity->getSide();
	Vec2 pos = _player_entity->getPos();
	Camera2D::instance->setCamera(pos, heading, side, Camera2D::instance->getScale());
}


World::~World()
{}

void World::update()
{
	// If some entities are created, then we first have to push them into queue,
	// and move them to vector after iteration has finished.
	// If entities are inserted into vector when iterating,
	// then it will make a big problem.
	while (!_created_entities.empty())
	{
		Entity* ent = _created_entities.front();

		if (ent->getType() == Entity::kSnake)
			_snakes.push_back(static_cast<Snake*>(ent));

		else if (ent->getType() == Entity::kPrey)
			_preys.push_back(static_cast<Prey*>(ent));

		else if (ent->getType() == Entity::kProjectile)
			_projectiles.push_back(static_cast<Projectile*>(ent));

		else if (ent->getType() == Entity::kStructure)
			_structures.push_back(static_cast<Structure*>(ent));

		_created_entities.pop();
	}
	
	_physics->Step();

	// Update entities and delete them if set garbage.
	updateEntity();

	regenEntity();

	// Camera position setting
	if (_player_entity) 
		Camera2D::instance->setOrigin(_player_entity->getPos());
}



void World::render()
{
	for (auto e : _snakes)
		e->render();

	for (auto p : _projectiles)
		p->render();

	for (auto  p: _preys)
		p->render();

	for (auto s : _structures)
		s->render();

}


Snake* World::createPlayerPawn(const Vec2& pos, Data::UserData& user)
{
	Snake* snake = new Snake(*this, genID(), pos, Data::ControlType::Player);
	user.set_eid(snake->getID());
	_created_entities.emplace(snake);
	return snake;
}

void World::createHunter(const Vec2& pos)
{
	_created_entities.emplace(new Snake(*this, genID(), pos, Data::ControlType::AI));
}

void World::createProjectile(const Vec2& pos, const Vec2& heading, int proj_speed)
{
	_created_entities.emplace(new Projectile(*this, genID(), pos, heading));
}

void World::createPrey(const Vec2& pos)
{
	_created_entities.emplace(new Prey(*this, genID(), pos));
}


void World::createStructure(const Vec2& pos, float radius, int type)
{
	if (type == Structure::StructureType::kCircle)
		_created_entities.emplace(Structure::createCircle(*this, genID(), pos, radius));

	else if (type == Structure::StructureType::kPolygon)
		_created_entities.emplace(Structure::createPolygon(*this, genID(), pos));

	else if (type == Structure::StructureType::kAnchor)
		_created_entities.emplace(Structure::createAnchor(*this, genID(), pos, pos + Vec2(2.0f, 0)));
}