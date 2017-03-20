#pragma once
//------------------------------------------------------------------------
//
//  Name:   Prey.h
//
//  Desc:   The entity which hunter intakes.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------
#include <Box2D/Box2D.h>
#include "Entity.h"
//class RigidBody;
class Prey : public Entity
{
public:
	
	Prey(World& world, unsigned int id, const Vec2& pos);

	virtual ~Prey() {}
	virtual void update() {}
	virtual void render();

private:
	//std::unique_ptr<RigidBody> _body;
	b2Body* _body;
};