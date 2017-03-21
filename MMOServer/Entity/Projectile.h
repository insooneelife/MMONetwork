#pragma once
//------------------------------------------------------------------------
//
//  Name:   Projectile.h
//
//  Desc:   The entitiy which hunter shoots to other.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include <Box2D/Box2D.h>
#include <memory>
#include "Entity.h"

class RigidBody;
class Projectile : public Entity
{
public:
	inline b2Body* getBody() const { return _body; }

	Projectile(
		World& world,
		unsigned int id,
		const Vec2& pos,
		const Vec2& heading);


	virtual ~Projectile();
	virtual void update();
	virtual void render();

	void reflect(Vec2 begin, Vec2 end);
	void reflectCircle(Vec2 pos, float radius);

private:

	b2Body* _body;
};