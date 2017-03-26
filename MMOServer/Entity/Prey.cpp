#include <iostream>
#include <sstream>
#include <Box2D/Box2D.h>

#include "Prey.h"
#include "../World.h"
#include "../PhysicsManager.h"
#include "../GraphicsDriver.h"


Prey::Prey(World& world, unsigned int id, const Vec2& pos)
	:
	Entity(world, id, pos, World::PreyRadius, Entity::Type::kPrey, GraphicsDriver::red),
	_body(nullptr)
{
	b2CircleShape shape;
	shape.m_radius = World::PreyRadius;

	_body = _world->getPhysicsMgr()->CreateBody(pos.x, pos.y, b2BodyType::b2_dynamicBody, &shape, true);
	_body->SetLinearDamping(2.0f);
	_body->SetUserData(this);
}

Prey::Prey(Args* args)
	:
	Entity(args)
{

}

void Prey::render()
{
	GraphicsDriver::instance->drawCircle(_pos, _radius, _color);
}

Prey::Args::Args()
{
	class_id = typeid(Prey).hash_code();
	radius = World::PreyRadius;
	type = Entity::Type::kPrey;
	color = GraphicsDriver::red;
}