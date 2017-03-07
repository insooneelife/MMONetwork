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

#include "Entity.h"

class Prey : public Entity
{
public:
	
	Prey(World& world, unsigned int id, const Vec2& pos);

	virtual ~Prey() {}
	virtual void update() {}
	virtual void render();
};