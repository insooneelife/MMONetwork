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

class Prey : public Entity
{
public:
	
	struct Args : Entity::Args
	{
		Args();
	};
	
	CREATE_METHOD(typeid(Prey).hash_code(), Prey)


	Prey(World& world, unsigned int id, const Vec2& pos);
	Prey(Args* args);

	virtual ~Prey() {}
	virtual void update() {}
	virtual void render();

private:
	b2Body* _body;
};

