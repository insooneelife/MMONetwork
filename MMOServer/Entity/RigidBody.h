#pragma once
//------------------------------------------------------------------------
//
//  Name:   RigidBody.h
//
//  Desc:   Base colliding shape.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include <Common/Math/Vec2.h>
#include "../Engine.h"

class Entity;
class RigidBody
{
public:
	RigidBody(Entity& owner, Vec2 pos, float radius);
	~RigidBody();

	inline Entity& getEntity() const	{ return _owner; }
	inline Vec2 getPos() const			{ return _pos; }
	void setPos(Vec2 pos);
	inline float getRadius() const		{ return _radius; }

	//void updateMovement(Vec2 velocity);

protected:
	Entity& _owner;
	Vec2 _pos;
	float _radius;
};