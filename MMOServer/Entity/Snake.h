#pragma once
//------------------------------------------------------------------------
//
//  Name:   Snake.h
//
//  Desc:   The entity which intakes other entities and grows bigger.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include <Box2D/Box2D.h>
#include <vector>
#include <memory>
#include "Entity.h"
#include <Common/Protobuf/generated/Base.pb.h>
#include <Common/Protobuf/generated/UserData.pb.h>

class Snake : public Entity
{
public:
	enum State
	{
		kIdle,
		kMoving
	};

	struct Args : public Entity::Args
	{
		Args();
		Data::ControlType ctype;
	};

	CREATE_METHOD(typeid(Snake).hash_code(), Snake)

	

	inline int getExp() const			{ return _experience; }
	inline void setExp(int exp)			{ _experience = exp; }
	inline bool isPlayer() const		{ return _is_player; }

	inline Data::ControlType getControlType() const { return _control_type; }
	inline const std::vector<b2Body*>& getBodies() const { return _bodies; }

	Snake(World& world, unsigned int id, const Vec2& pos, Data::ControlType ctype);

	Snake(Args* args);

	virtual ~Snake();

	void setPos(Vec2 pos);

	virtual void update();
	virtual void render();
	virtual bool handleMessage(const Message& msg);


private:
	State _state;
	Vec2 _destination;

	std::vector<b2Body*> _bodies;
	std::vector<Vec2> _destinations;

	int _experience;
	bool _is_player;

	Data::ControlType _control_type;
};

