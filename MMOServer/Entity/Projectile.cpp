#include <iostream>
#include <sstream>
#include "Projectile.h"
#include "../GraphicsDriver.h"
#include "../Utils.h"

Projectile::Projectile(
	World& world,
	unsigned int id,
	const Vec2& pos,
	const Vec2& heading,
	int proj_speed)
	:
	Entity(world, id, pos, 15.0f, Entity::Type::kProjectile, GraphicsDriver::black),
	_proj_speed(proj_speed)
{
	setHeading(heading);
}

void Projectile::update()
{
	_pos += _heading * (float)_proj_speed;
}

void Projectile::render()
{
	Vec2 sidev = getSide() * _radius / 2;
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos - sidev, _color);
	GraphicsDriver::instance->drawLine(_pos + sidev, _pos + _heading * _radius * 2, _color);
	GraphicsDriver::instance->drawLine(_pos - sidev, _pos + _heading * _radius * 2, _color);
}

void Projectile::reflect(Vec2 begin, Vec2 end)
{
	Vec2 n = (end - begin).getNormalized().getPerp();
	_heading = _heading - 2 * _heading.dot(n) * n;
}

void Projectile::reflectCircle(Vec2 pos, float radius)
{
	Vec2 force;
	circlesAmountOfOverlap(_pos, _radius, pos, radius, force);

	Vec2 side1 = force.getPerp();
	Vec2 side2 = -force.getPerp();

	_heading = (side2 - side1).getPerp().getNormalized();
}