#pragma once
//------------------------------------------------------------------------
//
//  Name:   ControllerBase.h
//
//  Desc:   Base class for controllers.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include <memory>

class Entity;
class ControllerBase 
{
public:
	ControllerBase() : _owner(nullptr) {}

	inline void setOwner(Entity* entity) { _owner = entity; }
	inline Entity* getOwner() const { return _owner; }

	virtual ~ControllerBase() {};
	virtual void execute() = 0;

private:
	Entity* _owner;
};