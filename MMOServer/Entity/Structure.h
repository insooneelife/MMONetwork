#pragma once
//------------------------------------------------------------------------
//
//  Name:   Structure.h
//
//  Desc:   
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include <Box2D/Box2D.h>
#include "Entity.h"

class Structure : public Entity
{
public:
	enum StructureType
	{
		kCircle,
		kPolygon,
		kChain,
		kAnchor
	};

	struct Args : public Entity::Args
	{
		Args();
		StructureType structure_type;
		b2Body* body;
	};

	CREATE_METHOD(typeid(Structure).hash_code(), Structure)

	static b2Body* createCircle(World& world, const Vec2& pos, float radius);
	static b2Body* createPolygon(World& world, const Vec2& pos);
	static b2Body* createChain(World& world, const std::vector<b2Vec2>& points);
	static b2Body* createAnchor(World& world, const Vec2& begin, const Vec2& end);

	inline StructureType getStructureType() const { return _structure_type; }

	Structure(Args* args);

	virtual ~Structure();
	virtual void update();
	virtual void render();

private:

	Structure(
		World& world,
		unsigned int id,
		const Vec2& pos,
		StructureType type,
		b2Body* body);

	

	StructureType _structure_type;
	b2Body* _body;
};


