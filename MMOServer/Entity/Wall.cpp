#include <iostream>
#include <sstream>
#include "Wall.h"
#include "../GraphicsDriver.h"

Wall::Wall(
	World& world,
	unsigned int id,
	const Vec2& begin,
	const Vec2& end,
	const Vec2& heading)
	:
	Entity(world, id, (begin + end) / 2, 0.0f, Entity::Type::kWall, GraphicsDriver::black),
	_begin(begin),
	_end(end)
{
	setHeading(heading);
}

void Wall::render()
{
	GraphicsDriver::instance->drawLine(_begin, _end, _color);
}
