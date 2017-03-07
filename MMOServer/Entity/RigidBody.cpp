#include "RigidBody.h"
#include "../World.h"
#include "Entity.h"

RigidBody::RigidBody(Entity& owner, Vec2 pos, float radius)
	:
	_owner(owner),
	_pos(pos),
	_radius(radius)
{
	_owner.getWorld().getCellSpace().addEntity(this);
}

RigidBody::~RigidBody()
{
	_owner.getWorld().getCellSpace().removeEntity(this);
}

void RigidBody::updateMovement(Vec2 velocity)
{
	Vec2 old_pos = _pos;
	_pos = _pos + velocity;
	_owner.getWorld().getCellSpace().updateEntity(this, old_pos);
}