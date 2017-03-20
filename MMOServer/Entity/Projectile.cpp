#include <iostream>
#include <sstream>
#include <array>
#include "Projectile.h"
#include "../GraphicsDriver.h"
#include <Common/Utils.h>

#include "../World.h"
//#include "RigidBody.h"

Projectile::Projectile(
	World& world,
	unsigned int id,
	const Vec2& pos,
	const Vec2& heading)
	:
	Entity(world, id, pos, World::ProjectileRadius, Entity::Type::kProjectile, GraphicsDriver::black),
	//_body(new RigidBody(*this, pos, World::ProjectileRadius))
	_body(nullptr)
{
	b2CircleShape shape;
	shape.m_radius = World::ProjectileRadius;

	_body = _world.getPhysicsMgr()->CreateBody(pos.x, pos.y, b2BodyType::b2_dynamicBody, &shape, true);
	_body->SetLinearDamping(2.0f);
	_body->SetUserData(this);


	setHeading(heading);
}

Projectile::~Projectile() 
{
	if (_body)
		_world.getPhysicsMgr()->RemoveBody(_body);
}

void Projectile::update()
{
	Vec2 vel = _heading * World::ProjectileSpeed;
	//_pos += vel;
	_body->SetLinearVelocity(b2Vec2(vel.x, vel.y));
	_pos = Vec2(_body->GetPosition().x, _body->GetPosition().y);
	//_body->setPos(_pos);
}

void Projectile::render()
{
	Vec2 sidev = getSide() * _radius / 2;
	//GraphicsDriver::instance->drawLine(_pos + sidev, _pos - sidev, _color);
	//GraphicsDriver::instance->drawLine(_pos + sidev, _pos + _heading * _radius * 2, _color);
	//GraphicsDriver::instance->drawLine(_pos - sidev, _pos + _heading * _radius * 2, _color);
	std::array<Vec2, 4> arr{ _pos + sidev, _pos - sidev, _pos + _heading * _radius * 2, _pos + sidev };
	std::vector<Vec2> tri(4);
	tri[0] = _pos + sidev;
	tri[1] = _pos - sidev;
	tri[2] = _pos + _heading * _radius * 2;
	tri[3] = _pos + sidev;
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