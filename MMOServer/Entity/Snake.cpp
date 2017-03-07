#include <iostream>
#include <sstream>
#include "Snake.h"
#include "RigidBody.h"
#include "../World.h"
#include "../EntityManager.h"
#include "../GraphicsDriver.h"

Snake::Snake(World& world, unsigned int id, const Vec2& pos)
	:
	Entity(world, id, pos, 25.0f, Entity::Type::kSnake, GraphicsDriver::black),
	_state(kIdle),
	_experience(8),
	_is_player(true),
	_control_type(Data::ControlType::NPC)
{
	Vec2 arr[8] = 
	{
		Vec2(0, 0), Vec2(World::OneStep, 0), Vec2(World::OneStep, -World::OneStep),
		Vec2(0, -World::OneStep), Vec2(-World::OneStep, -World::OneStep),
		Vec2(-World::OneStep, 0), Vec2(-World::OneStep, World::OneStep), Vec2(0, World::OneStep)
	};

	for (int i = 0; i < _experience; ++i)
	{
		_body.push_back(new RigidBody(*this, Vec2(pos + arr[i]), _radius));
		_destinations.push_back(pos + arr[i]);
	}
}

Snake::~Snake()
{
	for (auto e : _body)
		delete e;
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
				_destinations[i] = _body[i - 1]->getPos();
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
			_pos += (_destination - _pos).getNormalized() * World::SnakeSpeed;

			for (int i = 0; i < _body.size(); ++i)
			{
				Vec2 pos = _body[i]->getPos();
				_body[i]->updateMovement((_destinations[i] - pos).getNormalized() * World::SnakeSpeed);
				//_body[i]->setPos(pos + (_destinations[i] - pos).getNormalized() * World::SnakeSpeed);
				//_body[i] += (_destinations[i] - _body[i]).getNormalized() * World::SnakeSpeed;
			}
		}
	}
}

void Snake::render()
{
	std::stringstream ss;
	ss << _id;
	//GraphicsDriver::instance->drawCircle(_pos, _radius, _color);
	GraphicsDriver::instance->drawText(ss.str(), _pos);

	Vec2 sidev = getSide() * _radius / 2;
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos - sidev, _color);
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos + _heading * _radius * 2, _color);
	GraphicsDriver::instance->drawLine(_pos - sidev, _pos + _heading * _radius * 2, _color);

	GraphicsDriver::instance->drawCircle(_pos, _radius, _color);
	for (auto e : _body)
		GraphicsDriver::instance->drawCircle(e->getPos(), _radius, _color);
}


bool Snake::handleMessage(const Message& msg) 
{
	switch (msg.getMsg())
	{
	case Message::kDamage:
		break;

	case Message::kIncrease:
		setExp(getExp() + Message::voidToType<int>(msg.getExtraInfo()));
		std::cout <<"exp : " << getExp() << std::endl;
		break;

	case Message::kDecrease:
		setExp(getExp() - 1);
		break;

	default:
		break;
	}
	return false; 
}

bool Snake::checkCollideCircleToBody(Vec2 pos, float radius, Vec2& cpos)
{
	/*for (auto e : _body)
	{
		if (e.distance(pos) < _radius + radius)
		{
			cpos = e;
			return true;
		}
	}*/
	return false;
}
