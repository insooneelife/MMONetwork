#include <iostream>
#include <sstream>
#include "Snake.h"
#include "RigidBody.h"
#include "../World.h"
#include "../EntityManager.h"
#include "../GraphicsDriver.h"
#include "../Server/NetworkManagerServer.h"

Snake::Snake(World& world, unsigned int id, const Vec2& pos, Data::ControlType ctype)
	:
	Entity(world, id, pos, 25.0f, Entity::Type::kSnake, GraphicsDriver::black),
	_state(kIdle),
	_experience(8),
	_is_player(true),
	_control_type(ctype)
{
	for (int i = 0; i < _experience; ++i)
	{
		_body.push_back(new RigidBody(*this, pos, _radius));
		_destinations.push_back(pos);
	}
}

Snake::~Snake()
{
	for (auto e : _body)
		delete e;
}

void Snake::setPos(Vec2 pos)
{
	_pos = pos;
	_destination = pos;
	for (auto e : _body)
	{
		e->setPos(pos);
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
				_body[i]->setPos(pos + (_destinations[i] - pos).getNormalized() * World::SnakeSpeed);
				//_body[i]->updateMovement((_destinations[i] - pos).getNormalized() * World::SnakeSpeed);
				//_body[i]->setPos(pos + (_destinations[i] - pos).getNormalized() * World::SnakeSpeed);
				//_body[i] += (_destinations[i] - _body[i]).getNormalized() * World::SnakeSpeed;
			}
		}
	}
}

void Snake::render()
{
	std::stringstream ss;
	
	
	if (_control_type == Data::ControlType::Player)
	{
		ss << _user_data.name();
		_color = GraphicsDriver::red;
	}
	else
	{
		ss << _id;
	}
	
	
	//GraphicsDriver::instance->drawCircle(_pos, _radius, _color);
	GraphicsDriver::instance->drawText(ss.str(), _pos, _color);

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
