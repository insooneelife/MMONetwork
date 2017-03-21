#include <iostream>
#include <sstream>
#include "Structure.h"
#include "../GraphicsDriver.h"
#include "../World.h"
#include "../PhysicsManager.h"


Structure* Structure::createCircle(World& world, unsigned int id, const Vec2& pos, float radius)
{
	auto physics = world.getPhysicsMgr()->GetPhysicsWorld();

	b2BodyDef bd;
	bd.position.Set(pos.x, pos.y);
	b2Body* body = physics->CreateBody(&bd);

	b2CircleShape shape;
	shape.m_radius = radius;
	body->CreateFixture(&shape, 0.0f);

	return new Structure(world, id, pos, StructureType::kCircle, body);
}

Structure* Structure::createPolygon(World& world, unsigned int id, const Vec2& pos)
{
	b2Vec2 points[] =
	{
		b2Vec2(-1.0f, -1.0f),
		b2Vec2(3.0f, 0.0f),
		b2Vec2(2.0f, 2.0f),
		b2Vec2(0.0f, 3.0f),
		b2Vec2(-3.0f, 1.5f),
		b2Vec2(-1.0f, -1.0f)
	};

	auto physics = world.getPhysicsMgr()->GetPhysicsWorld();

	b2BodyDef bd;
	bd.position.Set(pos.x, pos.y);
	b2Body* body = physics->CreateBody(&bd);

	//b2ChainShape chain;
	//chain.CreateChain(points, 6);

	b2PolygonShape poly;
	poly.Set(points, 6);

	b2FixtureDef groundFixture;
	groundFixture.shape = &poly;
	groundFixture.restitution = 0.1f;
	groundFixture.friction = 0.0f;

	body->CreateFixture(&groundFixture);

	return new Structure(world, id, pos, StructureType::kPolygon, body);
}


Structure* Structure::createChain(World& world, unsigned int id, const std::vector<b2Vec2>& points)
{
	Vec2 pos = Vec2();
	auto physics = world.getPhysicsMgr()->GetPhysicsWorld();

	b2BodyDef bd;
	b2Body* body = physics->CreateBody(&bd);

	b2ChainShape chain;
	chain.CreateChain(points.data(), points.size());

	b2FixtureDef groundFixture;
	groundFixture.shape = &chain;
	groundFixture.restitution = 0.1f;
	groundFixture.friction = 0.0f;

	body->CreateFixture(&groundFixture);

	return new Structure(world, id, pos, StructureType::kPolygon, body);
}


Structure* Structure::createAnchor(World& world, unsigned int id, const Vec2& begin, const Vec2& end)
{
	auto physics = world.getPhysicsMgr()->GetPhysicsWorld();
	b2Body* prevBody = world.getPhysicsMgr()->GetGround();
	Vec2 pos((begin + end) / 2);

	b2PolygonShape shape;
	shape.SetAsBox(end.x - begin.x - 0.25f, end.y - begin.y + 0.25f);

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(pos.x, pos.y);
	b2Body* body = physics->CreateBody(&bd);
	body->CreateFixture(&shape, 2.0f);

	b2RevoluteJointDef rjd;
	rjd.Initialize(prevBody, body, b2Vec2(begin.x, begin.y));
	rjd.motorSpeed = 1.0f * b2_pi;
	rjd.maxMotorTorque = 10000.0f;
	rjd.enableMotor = false;
	physics->CreateJoint(&rjd);

	return new Structure(world, id, pos, StructureType::kAnchor, body);
}


Structure::Structure(
	World& world,
	unsigned int id,
	const Vec2& pos,
	StructureType type,
	b2Body* body)
	:
	Entity(world, id, pos, 0.0f, Entity::Type::kStructure, GraphicsDriver::black),
	_structure_type(type)
{
	_body = body;
	_body->SetUserData(this);
}

Structure::~Structure()
{}

void Structure::update()
{}

void Structure::render()
{
	std::stringstream ss;
	ss << _id;

	GraphicsDriver::instance->drawText(ss.str(), _pos);

	for (auto f = _body->GetFixtureList(); f; f = f->GetNext())
	{
		GraphicsDriver::instance->drawBox2DShape(_pos, f->GetShape());
	}

}