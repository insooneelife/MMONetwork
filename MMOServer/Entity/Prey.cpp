#include <iostream>
#include <sstream>
#include "Prey.h"
#include "../GraphicsDriver.h"

Prey::Prey(World& world, unsigned int id, const Vec2& pos)
	:
	Entity(world, id, pos, 20.0f, Entity::Type::kPrey, GraphicsDriver::red)
{}

void Prey::render()
{
	GraphicsDriver::instance->drawCircle(_pos, _radius, _color);
}

