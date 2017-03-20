#include <iostream>
#include <sstream>

#include <Box2D/Box2D.h>
#include "../World.h"
#include "../PhysicsManager.h"

#include "Prey.h"
//#include "RigidBody.h"
#include "../GraphicsDriver.h"

Prey::Prey(World& world, unsigned int id, const Vec2& pos)
	:
	Entity(world, id, pos, World::PreyRadius, Entity::Type::kPrey, GraphicsDriver::red),
	_body(nullptr)
	//_body(new RigidBody(*this, pos, 20.0f))
{
	b2CircleShape shape;
	shape.m_radius = World::PreyRadius;

	_body = _world.getPhysicsMgr()->CreateBody(pos.x, pos.y, b2BodyType::b2_dynamicBody, &shape, true);
	_body->SetLinearDamping(2.0f);
	_body->SetUserData(this);
}

void Prey::render()
{
	GraphicsDriver::instance->drawCircle(_pos, _radius, _color);
}

