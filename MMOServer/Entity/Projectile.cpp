#include <iostream>
#include <sstream>
#include <array>
#include <Common/Utils.h>
#include "Projectile.h"
#include "../GraphicsDriver.h"
#include "../World.h"


Projectile::Projectile(
	World& world,
	unsigned int id,
	const Vec2& pos,
	const Vec2& heading)
	:
	Entity(world, id, pos, World::ProjectileRadius, Entity::Type::kProjectile, GraphicsDriver::black),
	_body(nullptr)
{
	b2CircleShape shape;
	shape.m_radius = World::ProjectileRadius;

	_body = _world.getPhysicsMgr()->CreateBody(pos.x, pos.y, b2BodyType::b2_dynamicBody, &shape, false, 1.0f);
	_body->SetUserData(this);

	setHeading(heading);
	Vec2 vel = _heading * World::ProjectileSpeed;
	_body->SetLinearVelocity(b2Vec2(vel.x, vel.y));
}

Projectile::~Projectile() 
{
	if (_body)
		_world.getPhysicsMgr()->RemoveBody(_body);
}

void Projectile::update()
{
	_pos = _body->GetPosition();
	
}

void Projectile::render()
{
	Vec2 sidev = getSide() * _radius / 2;
	std::vector<Vec2> tri { _pos + sidev, _pos - sidev, _pos + _heading * _radius * 2, _pos + sidev };
	GraphicsDriver::instance->drawLines(tri, _color);
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