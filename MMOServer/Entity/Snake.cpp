#include <iostream>
#include <sstream>
#include <vector>
#include "Snake.h"
#include "../World.h"
#include "../EntityManager.h"
#include "../GraphicsDriver.h"
#include "../Server/NetworkManagerServer.h"


Snake::Snake(World& world, unsigned int id, const Vec2& pos, Data::ControlType ctype)
	:
	Entity(world, id, pos, World::SnakeRadius, Entity::Type::kSnake, GraphicsDriver::black),
	_state(kIdle),
	_experience(8),
	_is_player(true),
	_control_type(ctype)
{
	for (int i = 0; i < _experience; ++i)
	{
		b2CircleShape shape;
		shape.m_radius = World::SnakeRadius;

		auto body = _world->getPhysicsMgr()->CreateBody(pos.x, pos.y, b2BodyType::b2_kinematicBody, &shape, true);
		body->SetLinearDamping(2.0f);
		body->SetUserData(this);
		_bodies.emplace_back(body);

		_destinations.push_back(pos);
	}
}

Snake::Snake(Args* args)
	:
	Entity(args),
	_control_type(args->ctype),
	_state(kIdle),
	_experience(8),
	_is_player(true)
{
	for (int i = 0; i < _experience; ++i)
	{
		b2CircleShape shape;
		shape.m_radius = _radius;

		auto body = _world->getPhysicsMgr()->CreateBody(_pos.x, _pos.y, b2BodyType::b2_kinematicBody, &shape, true);
		body->SetLinearDamping(2.0f);
		body->SetUserData(this);
		_bodies.emplace_back(body);

		_destinations.push_back(_pos);
	}
}

Snake::~Snake()
{
	for (auto e : _bodies)
		_world->getPhysicsMgr()->RemoveBody(e);
}

void Snake::setPos(Vec2 pos)
{
	_pos = pos;
	_destination = pos;
	for (auto e : _bodies)
	{
		e->SetTransform(b2Vec2(pos.x, pos.y), 0);	
	}
	for (auto& e : _destinations)
	{
		e = pos;
	}
}

void Snake::update()
{
	if (_state == kIdle)
	{
		_destination = _pos + _heading * World::OneStep;
		_state = kMoving;

		for (int i = 0; i < _destinations.size(); ++i)
		{
			if (i == 0)
				_destinations[i] = _destination;
			else
				_destinations[i] = _bodies[i - 1]->GetPosition();
		}
	}
	else if (_state == kMoving)
	{
		if ((_destination - _pos).length() < World::SnakeSpeed)
		{
			_state = kIdle;
		}
		else
		{
			for (int i = 0; i < _bodies.size(); ++i)
			{
				Vec2 pos = _bodies[i]->GetPosition();
				Vec2 vel = (_destinations[i] - pos).getNormalized() * World::SnakeSpeed;
				_bodies[i]->SetLinearVelocity(b2Vec2(vel.x, vel.y));
			}
			_pos = _bodies[0]->GetPosition();
		}
	}
}

void Snake::render()
{
	std::stringstream ss;
	
	if (_control_type == Data::ControlType::Player)
	{
		Data::UserData user_data;
		_world->getNetworkMgr().queryUserDataByEID(_id, user_data);
		ss << user_data.name() << " " << _id;
		_color = GraphicsDriver::red;
	}
	else
	{
		ss << _id;
	}
	
	GraphicsDriver::instance->drawText(ss.str(), _pos, _color);
	
	Vec2 sidev = getSide() * _radius / 2;
	std::vector<Vec2> tri { _pos + sidev, _pos - sidev, _pos + _heading * _radius * 2, _pos + sidev };
	GraphicsDriver::instance->drawLines(tri, _color);

	std::vector<Vec2> lines(_bodies.size());
	for (int i = 0; i < _bodies.size(); ++i)
		lines[i] = _bodies[i]->GetPosition();

	GraphicsDriver::instance->drawLines(lines, _color);
}


bool Snake::handleMessage(const Message& msg) 
{
	switch (msg.getMsg())
	{
	case Message::kDamage:
		break;

	case Message::kIncrease:
		setExp(getExp() + Message::voidToType<int>(msg.getExtraInfo()));
		break;

	case Message::kDecrease:
		setExp(getExp() - 1);
		break;

	case Message::kCommand:
	{
		const Vec2 left(-1, 0);
		const Vec2 right(1, 0);
		const Vec2 up(0, 1);
		const Vec2 down(0, -1);

		Data::CommandType ctype = Message::voidToType<Data::CommandType>(msg.getExtraInfo());
		if (ctype == Data::CommandType::MoveDown)
		{
			setHeading(down);
		}
		else if (ctype == Data::CommandType::MoveLeft)
		{
			setHeading(left);
		}
		else if (ctype == Data::CommandType::MoveRight)
		{
			setHeading(right);
		}
		else if (ctype == Data::CommandType::MoveUp)
		{
			setHeading(up);
		}
	}
		break;

	default:
		break;
	}
	return false; 
}


Snake::Args::Args()
{
	class_id = typeid(Snake).hash_code();
	radius = World::SnakeRadius;
	type = Entity::Type::kSnake;
	color = GraphicsDriver::black;
}