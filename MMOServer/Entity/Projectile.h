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

#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(
		World& world,
		unsigned int id,
		const Vec2& pos,
		const Vec2& heading,
		int proj_speed);


	virtual ~Projectile() {}
	virtual void update();
	virtual void render();

	void reflect(Vec2 begin, Vec2 end);
	void reflectCircle(Vec2 pos, float radius);

private:

	int _proj_speed;
};