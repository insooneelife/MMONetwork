#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "PhysicsManager.h"
#include <iostream>
#include "World.h"
#include "Entity/Entity.h"
#include "Entity/Snake.h"
#include "Entity/Prey.h"
#include "Entity/Projectile.h"


bool PhysicsManager::CheckContact(
	const b2Shape* shapeA, int32 indexA,
	const b2Shape* shapeB, int32 indexB,
	const b2Transform& xfA, const b2Transform& xfB,
	b2DistanceOutput& output)
{
	b2DistanceInput input;
	input.proxyA.Set(shapeA, indexA);
	input.proxyB.Set(shapeB, indexB);
	input.transformA = xfA;
	input.transformB = xfB;
	input.useRadii = true;

	b2SimplexCache cache;
	cache.count = 0;

	b2Distance(&output, &cache, &input);

	return output.distance < 10.0f * b2_epsilon;
}


bool PhysicsManager::ShapeCollide(
	b2Shape* shapeA, const b2Transform& xfA,
	b2Shape* shapeB, const b2Transform& xfB)
{
	b2DistanceOutput output;

	if (shapeA->GetType() == b2Shape::e_chain && shapeB->GetType() == b2Shape::e_chain)
	{
		auto chainA = static_cast<b2ChainShape*>(shapeA);
		auto chainB = static_cast<b2ChainShape*>(shapeB);
		for (int i = 0; i < chainA->GetChildCount(); i++)
		{
			for (int j = 0; j < chainB->GetChildCount(); j++)
			{
				b2EdgeShape edgeA;
				b2EdgeShape edgeB;
				chainA->GetChildEdge(&edgeA, i);
				chainB->GetChildEdge(&edgeB, j);
				if (CheckContact(&edgeA, i, &edgeB, j, xfA, xfB, output))
				{
					std::cout << "chain && chain" << std::endl;
					return true;
				}
			}
		}
	}
	else if (shapeA->GetType() == b2Shape::e_chain && shapeB->GetType() != b2Shape::e_chain)
	{
		auto chain = static_cast<b2ChainShape*>(shapeA);
		for (int i = 0; i < chain->GetChildCount(); i++)
		{
			b2EdgeShape edge;
			chain->GetChildEdge(&edge, i);
			if (CheckContact(&edge, i, shapeB, 0, xfA, xfB, output))
			{
				std::cout << "chain && !chain" << std::endl;
				//std::cout << xfA.p.x << " " << xfA.p.y << " " << xfB.q.c << " " << xfB.q.s << std::endl;
				
				std::cout << acos(xfB.q.c) << " " << asin(xfB.q.s) << std::endl;
				return true;
			}
		}
	}
	else if (shapeA->GetType() != b2Shape::e_chain && shapeB->GetType() == b2Shape::e_chain)
	{
		auto chain = static_cast<b2ChainShape*>(shapeB);
		for (int i = 0; i < chain->GetChildCount(); i++)
		{
			b2EdgeShape edge;
			chain->GetChildEdge(&edge, i);
			if (CheckContact(shapeA, 0, &edge, i, xfA, xfB, output))
			{
				std::cout << "!chain && chain" << std::endl;
				//std::cout << xfA.p.x << " " << xfA.p.y << " " << xfB.q.c << " " << xfB.q.s << std::endl;
				std::cout << acos(xfB.q.c) << " " << asin(xfB.q.s) << std::endl;
				return true;
			}
		}
	}
	else
	{
		if (CheckContact(shapeA, 0, shapeB, 0, xfA, xfB, output))
		{
			std::cout << "!chain && !chain" << std::endl;
			return true;
		}
	}
	return false;
}

bool PhysicsManager::ShapeCollide(
	b2Shape* shapeA, const b2Vec2& posA, float rotateA,
	b2Shape* shapeB, const b2Vec2& posB, float rotateB)
{
	b2Transform tA;
	tA.p = posA;
	tA.q.c = cos(rotateA);
	tA.q.s = sin(rotateA);

	b2Transform tB;
	tB.p = posB;
	tB.q.c = cos(rotateB);
	tB.q.s = sin(rotateB);

	return ShapeCollide(shapeA, tA, shapeB, tB);
}


bool PhysicsManager::BodyCollide(b2Body* bodyA, b2Body* bodyB)
{
	for (auto hf = bodyA->GetFixtureList(); hf; hf = hf->GetNext())
		for (auto sf = bodyB->GetFixtureList(); sf; sf = sf->GetNext())
			if (ShapeCollide(
				hf->GetShape(), bodyA->GetTransform(),
				sf->GetShape(), bodyB->GetTransform()))
				return true;
	return false;
}

bool PhysicsManager::RayCast(
	b2Shape* shape, const b2Transform& trans,
	const b2Vec2& A, const b2Vec2& B, b2Vec2& hit)
{
	b2RayCastOutput output;
	b2RayCastInput input;
	input.p1 = A;
	input.p2 = B;
	input.maxFraction = 1.0f;

	if (shape->GetType() == b2Shape::e_chain)
	{
		b2ChainShape* chain = static_cast<b2ChainShape*>(shape);
		
		float distance = FLT_MAX;
		for (int i = 0; i < chain->GetChildCount(); i++)
		{
			b2EdgeShape edge;
			chain->GetChildEdge(&edge, i);
			if (edge.RayCast(&output, input, trans, i))
			{
				b2Vec2 tempHit = (A + output.fraction * (B - A));
				if (distance > (tempHit - A).Length())
				{
					distance = (tempHit - A).Length();
					hit = tempHit;
				}
			}
		}
		if (FLT_MAX - 0.01f > distance)
		{
			std::cout << hit.x << " " << hit.y << std::endl;
			return true;
		}
	}
	else
	{
		if (shape->RayCast(&output, input, trans, 0))
		{
			hit = (A + output.fraction * (B - A));
			return true;
		}
	}
	return false;
}

void PhysicsManager::ApplyBlastImpulse(
	b2Body* body,
	b2Vec2 blastCenter,
	b2Vec2 applyPoint,
	float blastPower)
{
	b2Vec2 blastDir = applyPoint - blastCenter;
	float distance = blastDir.Normalize();
	//ignore bodies exactly at the blast point - blast direction is undefined
	if (distance == 0)
		return;
	float invDistance = 1 / distance;
	float impulseMag = blastPower * invDistance * invDistance;
	body->ApplyLinearImpulse(impulseMag * blastDir, applyPoint, true);
}


PhysicsManager::PhysicsManager(float worldX, float worldY)
	:
	_pointCount(0)
{
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	_world = new b2World(gravity);
	_destruction_listener.physics = this;
	_world->SetDestructionListener(&_destruction_listener);
	_world->SetContactListener(this);
	//_world->SetDebugDraw(GraphicsDriver::instance.get());

	// Ground body
	{
		b2BodyDef bd;
		_ground = _world->CreateBody(&bd);

		b2Vec2 points[] =
		{
			b2Vec2(-worldX, -worldY),
			b2Vec2(worldX, -worldY),
			b2Vec2(worldX, worldY),
			b2Vec2(-worldX, worldY)
		};

		for (int i = 0; i < 4; i++)
		{
			int j = (i + 1) % 4;
			b2EdgeShape shape;
			shape.Set(points[i], points[j]);
			_ground->CreateFixture(&shape, 0.0f);
		}
	}
}

void PhysicsManager::Step()
{
	uint32 flags = 0;
	flags += _settings.drawShapes		* b2Draw::e_shapeBit;
	flags += _settings.drawJoints		* b2Draw::e_jointBit;
	flags += _settings.drawAABBs		* b2Draw::e_aabbBit;
	flags += _settings.drawCOMs			* b2Draw::e_centerOfMassBit;
	//GraphicsDriver::instance->SetFlags(flags);

	float32 timeStep = _settings.hz > 0.0f ? 1.0f / _settings.hz : float32(0.0f);
	_pointCount = 0;

	_world->Step(
		timeStep,
		_settings.velocityIterations,
		_settings.positionIterations);
}

void PhysicsManager::Render()
{
	/*_world->DrawDebugData();

	if (_settings.drawContactPoints)
	{
		const float32 k_impulseScale = 0.1f;
		const float32 k_axisScale = 0.3f;

		for (int32 i = 0; i < _pointCount; ++i)
		{
			ContactPoint* point = _points + i;

			if (point->state == b2_addState)
			{
				GraphicsDriver::instance->DrawPoint(point->position, 10.0f, b2Color(0.3f, 0.95f, 0.3f));
			}
			else if (point->state == b2_persistState)
			{
				GraphicsDriver::instance->DrawPoint(point->position, 5.0f, b2Color(0.3f, 0.3f, 0.95f));
			}

			if (_settings.drawContactNormals)
			{
				b2Vec2 p1 = point->position;
				b2Vec2 p2 = p1 + k_axisScale * point->normal;
				GraphicsDriver::instance->DrawSegment(p1, p2, b2Color(0.9f, 0.9f, 0.9f));
			}
			else if (_settings.drawContactImpulse)
			{
				b2Vec2 p1 = point->position;
				b2Vec2 p2 = p1 + k_impulseScale * point->normalImpulse * point->normal;
				GraphicsDriver::instance->DrawSegment(p1, p2, b2Color(0.9f, 0.9f, 0.3f));
			}

			if (_settings.drawFrictionImpulse)
			{
				b2Vec2 tangent = b2Cross(point->normal, 1.0f);
				b2Vec2 p1 = point->position;
				b2Vec2 p2 = p1 + k_impulseScale * point->tangentImpulse * tangent;
				GraphicsDriver::instance->DrawSegment(p1, p2, b2Color(0.9f, 0.9f, 0.3f));
			}
		}
	}*/
}


void PhysicsManager::BeginContact(b2Contact* contact)
{
	//check if both fixtures were balls
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserDataA && bodyUserDataB)
	{
		Entity* entA = static_cast<Entity*>(bodyUserDataA);
		Entity* entB = static_cast<Entity*>(bodyUserDataB);

		if (entA->getType() == Entity::Type::kSnake && entB->getType() == Entity::Type::kSnake)
			World::collide(*static_cast<Snake*>(entA), *static_cast<Snake*>(entB));

		else if (entA->getType() == Entity::Type::kSnake && entB->getType() == Entity::Type::kProjectile)
			World::collide(*static_cast<Snake*>(entA), *static_cast<Projectile*>(entB));

		else if (entA->getType() == Entity::Type::kProjectile && entB->getType() == Entity::Type::kSnake)
			World::collide(*static_cast<Snake*>(entB), *static_cast<Projectile*>(entA));

		else if (entA->getType() == Entity::Type::kProjectile && entB->getType() == Entity::Type::kPrey)
			World::collide(*static_cast<Projectile*>(entA), *static_cast<Prey*>(entB));

		else if (entA->getType() == Entity::Type::kPrey && entB->getType() == Entity::Type::kProjectile)
			World::collide(*static_cast<Projectile*>(entB), *static_cast<Prey*>(entA));

	}
}

void PhysicsManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	const b2Manifold* manifold = contact->GetManifold();

	if (manifold->pointCount == 0)
	{
		return;
	}

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
	b2GetPointStates(state1, state2, oldManifold, manifold);

	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	for (int32 i = 0; i < manifold->pointCount && _pointCount < 2048; ++i)
	{
		ContactPoint* cp = _points + _pointCount;
		cp->fixtureA = fixtureA;
		cp->fixtureB = fixtureB;
		cp->position = worldManifold.points[i];
		cp->normal = worldManifold.normal;
		cp->state = state2[i];
		cp->normalImpulse = manifold->points[i].normalImpulse;
		cp->tangentImpulse = manifold->points[i].tangentImpulse;
		cp->separation = worldManifold.separations[i];
		++_pointCount;
	}
}


b2Body* PhysicsManager::CreateApplyForceBody(float x, float y, b2Shape* shape)
{
	// Create body
	b2BodyDef bd;
	bd.position.Set(x, y);
	bd.type = b2BodyType::b2_dynamicBody;
	bd.allowSleep = false;

	b2Body* body = _world->CreateBody(&bd);

	b2FixtureDef fd;
	fd.shape = shape;
	fd.density = 1.0f;
	fd.friction = 0.0f;
	fd.restitution = 0.0f;
	body->CreateFixture(&fd);

	// Apply force
	float32 gravity = 10.0f;
	float32 I = body->GetInertia();
	float32 mass = body->GetMass();

	// For a circle: I = 0.5 * m * r * r ==> r = sqrt(2 * I / m)
	float32 radius = b2Sqrt(2.0f * I / mass);

	b2FrictionJointDef jd;
	jd.localAnchorA.SetZero();
	jd.localAnchorB.SetZero();
	jd.bodyA = _ground;
	jd.bodyB = body;
	jd.collideConnected = true;
	jd.maxForce = mass * gravity;
	jd.maxTorque = mass * radius * gravity;

	_world->CreateJoint(&jd);

	return body;
}

b2Body* PhysicsManager::CreateBody(float x, float y, b2BodyType type, b2Shape* shape, bool sensor)
{
	b2BodyDef bd;
	bd.position.Set(x, y);
	bd.type = type;
	bd.allowSleep = false;

	b2Body* body = _world->CreateBody(&bd);

	b2FixtureDef fd;
	fd.shape = shape;
	fd.density = 20.0f;
	fd.friction = 0.0f;
	fd.restitution = 0.0f;
	fd.isSensor = sensor;
	body->CreateFixture(&fd);
	return body;
}

void PhysicsManager::RemoveBody(b2Body* body)
{
	body->GetWorld()->DestroyBody(body);
}

void PhysicsManager::Explosion(const b2Vec2& center, float blastRadius, float blastPower)
{
	//find all bodies with fixtures in blast radius AABB
	EntityQueryCallback queryCallback; //see "World querying topic"
	b2AABB aabb;
	aabb.lowerBound = center - b2Vec2(blastRadius, blastRadius);
	aabb.upperBound = center + b2Vec2(blastRadius, blastRadius);
	
	_world->QueryAABB(&queryCallback, aabb);

	//check which of these bodies have their center of mass within the blast radius
	/*for (int i = 0; i < queryCallback.foundEntities.size(); i++)
	{
		Entity* ent = queryCallback.foundEntities[i];
		b2Vec2 bodyCom = ent->getBody()->GetWorldCenter();

		//ignore bodies outside the blast range
		if ((bodyCom - center).Length() >= blastRadius)
			continue;

		ApplyBlastImpulse(ent->getBody(), center, bodyCom, blastPower);
	}*/
}


void PhysicsManager::QueryAABB(
	const Vec2& center,
	float halfWidth,
	float halfHeight,
	b2QueryCallback* callback)
{
	b2AABB aabb;
	aabb.lowerBound = b2Vec2(center.x, center.y) - b2Vec2(halfWidth, halfHeight);
	aabb.upperBound = b2Vec2(center.x, center.y) + b2Vec2(halfWidth, halfHeight);
	_world->QueryAABB(callback, aabb);
}


void PhysicsManager::QueryRayCast(
	const Vec2& begin,
	const Vec2& end,
	b2RayCastCallback* callback)
{
	_world->RayCast(callback, b2Vec2(begin.x, begin.y), b2Vec2(end.x, end.y));
}

