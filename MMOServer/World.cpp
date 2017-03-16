#include <iostream>
#include "World.h"
#include "EntityManager.h"
#include "Camera2D.h"
#include "GraphicsDriver.h"

#include <Common/Utils.h>
#include <Common/Math/Transformations.h>

#include "Entity/Snake.h"
#include "Entity/Prey.h"
#include "Entity/Projectile.h"
#include "Entity/Wall.h"
#include "Entity/RigidBody.h"

#include "Server/NetworkManagerServer.h"

using namespace std;

const float World::OneStep = 50.0f;
const float World::SnakeSpeed = 1.0f;
const float World::Dummy = 200;
const float World::WorldSize = 2000.0f;

const int World::SnakeNum = 20;
const int World::ProjectileNum = 20;
const int World::PreyNum = 20;
const int World::CellNum = 10;

void World::collide(Snake& s1, Snake& s2)
{
	//cout << "collide!  Snake && Snake" << endl;
}

void World::collide(Snake& s, Projectile& p)
{
	Vec2 collide_pos;
	//if(s.checkCollideCircleToBody(p.getPos(), p.getBRadius(), collide_pos))
	if ((s.getPos().distance(p.getPos()) < s.getBRadius() + p.getBRadius()))
	{
		//cout << "collide!  Snake && Projectile" << endl;
		p.reflectCircle(s.getPos(), s.getBRadius());
	}
}

void World::collide(Projectile& pro, Prey& prey)
{
	if ((pro.getPos().distance(prey.getPos()) < pro.getBRadius() + prey.getBRadius()))
	{
		//cout << "collide!  Projectile && Prey" << endl;
		pro.reflectCircle(prey.getPos(), prey.getBRadius());
	}
}

void World::collide(Projectile& p, Wall& w)
{
	if (segmentCircleOverlap(w.getBegin(), w.getEnd(), p.getPos(), p.getBRadius()))
	{
		//cout << "collide!  Projectile && Wall" << endl;

		float distance = sqrt(distToSegmentSq(w.getBegin(), w.getEnd(), p.getPos()));
		p.reflect(w.getBegin(), w.getEnd());
	}
}

void World::collide(Snake& s, Wall& w)
{
	if (segmentCircleOverlap(w.getBegin(), w.getEnd(), s.getPos(), s.getBRadius()))
	{
		//cout << "collide!  Snake && Wall" << endl;

		s.setGarbage(true);
	}
}

void World::collide(Snake& s, Prey& p)
{
	if ((s.getPos().distance(p.getPos()) < s.getBRadius() + p.getBRadius()))
	{
		//cout << "collide!  Snake && Prey" << endl;
		p.setGarbage(true);

		int increase = 1;
		
		p.getWorld().getEntityMgr().dispatchMsg(
			p.getID(), s.getID(), Message::kIncrease, &increase);
	}
}

void World::regenPlayerPawn(Snake* pawn)
{
	float fwidth = (getWidth() - World::Dummy) / 2;
	Snake* new_pawn = createPlayerPawn(
		Vec2(random(-fwidth, fwidth), random(-fwidth, fwidth)),
		pawn->getUserData());

	//pawn->setGarbage(false);
	_created_entities.emplace(new_pawn);
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
	_cell_space(width, width, CellNum, CellNum, 1000000),
	_network_mgr(new NetworkManagerServer(*this, room)),
	level_(0)
{
	// Create player with hunter
	_player_entity = new Snake(*this, genID(), Vec2(100.0f, 100.0f), Data::ControlType::NPC);
	_snakes.push_back(_player_entity);

	float fwidth = (width - Dummy) / 2;
	Vec2 bl(-fwidth, -fwidth);
	Vec2 br(fwidth, -fwidth);
	Vec2 tl(-fwidth, fwidth);
	Vec2 tr(fwidth, fwidth );

	// Create hunters
	for (int i = 0; i < SnakeNum; ++i)
		createHunter(Vec2(random(-fwidth, fwidth), random(-fwidth, fwidth)));

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
	createWall(bl, br, (br - bl).getNormalized().getPerp());
	createWall(br, tr, (tr - br).getNormalized().getPerp());
	createWall(tr, tl, (tl - tr).getNormalized().getPerp());
	createWall(tl, bl, (bl - tl).getNormalized().getPerp());

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

		else if (ent->getType() == Entity::kWall)
			_walls.push_back(static_cast<Wall*>(ent));

		_created_entities.pop();
	}
	
	// Update entities and delete them if set garbage.
	updateEntity();

	regenEntity();

	// Process collide between entities.
	solveCollide();

	// Camera position setting
	if (_player_entity) 
		Camera2D::instance->setOrigin(_player_entity->getPos());
}

void World::solveCollide()
{
	for (auto s1 : _snakes)
	{
		_cell_space.calculateNeighborsForOne(s1->getPos());

		for (int i = 0; i < _cell_space.getNeighborsCnt(); ++i)
		{
			if (s1->getID() == _cell_space.getNeighbors()[i]->getEntity().getID())
				continue;

			if (_cell_space.getNeighbors()[i]->getEntity().getType() != Entity::kSnake)
				continue;

			// check if snake head collides with body piece
			Vec2 bpos = _cell_space.getNeighbors()[i]->getPos();
			float brad = _cell_space.getNeighbors()[i]->getRadius();

			if (s1->getPos().distance(bpos) < s1->getBRadius() + brad)
			{
				Snake* s2 = static_cast<Snake*>(&_cell_space.getNeighbors()[i]->getEntity());
				collide(*s1, *s2);
			}
		}
	}

	for (auto s : _snakes)
		for (auto p : _projectiles)
			collide(*s, *p);

	for (auto pro : _projectiles)
		for (auto p : _preys)
			collide(*pro, *p);

	for (auto p : _projectiles)
		for (auto w : _walls)
			collide(*p, *w);

	for (auto s : _snakes)
		for (auto w : _walls)
			collide(*s, *w);

	for (auto s : _snakes)
		for (auto p : _preys)
			collide(*s, *p);
}


void World::render()
{
	for (auto e : _snakes)
		e->render();

	for (auto p : _projectiles)
		p->render();

	for (auto  p: _preys)
		p->render();

	for (auto p : _walls)
		p->render();

	//renderGrid();
	renderCellSpace();
}

void World::renderGrid()
{
	for (float x = -_width; x < _width; x += OneStep)
	{
		GraphicsDriver::instance->drawLine(Vec2(x, -_width), Vec2(x, _width));
	}

	for (float y = -_width; y < _width; y += OneStep)
	{
		GraphicsDriver::instance->drawLine(Vec2(-_width, y), Vec2(_width, y));
	}
}

void World::renderCellSpace()
{
	for (auto c = std::begin(_cell_space.getCells()); c != std::end(_cell_space.getCells()); ++c)
	{
		Vec2 bl = _cell_space.toWorldPos((*c)->bounding_box.getBottomLeft());
		Vec2 br = _cell_space.toWorldPos((*c)->bounding_box.getBottomRight());
		Vec2 tr = _cell_space.toWorldPos((*c)->bounding_box.getTopRight());
		Vec2 tl = _cell_space.toWorldPos((*c)->bounding_box.getTopLeft());
		Vec2 center = _cell_space.toWorldPos((*c)->bounding_box.getCenter());

		GraphicsDriver::instance->drawLine(bl, br);
		GraphicsDriver::instance->drawLine(br, tr);
		GraphicsDriver::instance->drawLine(tr, tl);
		GraphicsDriver::instance->drawLine(tl, bl);

		std::stringstream ss;
		ss << (*c)->members.size();
		GraphicsDriver::instance->drawText(ss.str(), center, GraphicsDriver::blue);
	}	
}

Snake* World::createPlayerPawn(const Vec2& pos, Data::UserData& user)
{
	Snake* snake = new Snake(*this, genID(), pos, Data::ControlType::Player);
	user.set_eid(snake->getID());
	snake->setUserData(user);
	_created_entities.emplace(snake);
	return snake;
}

void World::createHunter(const Vec2& pos)
{
	_created_entities.emplace(new Snake(*this, genID(), pos, Data::ControlType::AI));
}

void World::createProjectile(const Vec2& pos, const Vec2& heading, int proj_speed)
{
	_created_entities.emplace(new Projectile(*this, genID(), pos, heading, proj_speed));
}

void World::createPrey(const Vec2& pos)
{
	_created_entities.emplace(new Prey(*this, genID(), pos));
}

void World::createWall(const Vec2& begin, const Vec2& end, const Vec2& heading)
{
	_created_entities.emplace(new Wall(*this, genID(), begin, end, heading));
}