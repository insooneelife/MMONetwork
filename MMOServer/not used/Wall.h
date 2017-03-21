#pragma once
//------------------------------------------------------------------------
//
//  Name:   Wall.h
//
//  Desc:   Boundary of map.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "Entity.h"

class Wall : public Entity
{
public:

	inline Vec2 getBegin() const	{ return _begin; }
	inline Vec2 getEnd() const		{ return _end; }

	Wall(
		World& world,
		unsigned int id,
		const Vec2& begin,
		const Vec2& end,
		const Vec2& heading);

	virtual ~Wall() {}
	virtual void update() {}
	virtual void render();

private:
	Vec2 _begin;
	Vec2 _end;
};