#pragma once
//------------------------------------------------------------------------
//
//  Name:		World.h
//
//  Desc:		Class for define all interactive thing in the game world.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include <vector>
#include <memory>
#include <queue>
#include <Common/Math/Vec2.h>
#include "CellSpacePartition.h"
#include "Server/ProtobufServerUtils.h"


#include "EntityManager.h"

class Entity;
class Snake;
class Prey;
class Projectile;
class Wall;
class RigidBody;
class Room;
class NetworkManagerServer;

class World
{
public:
	enum { InvalidateId = 0 };

	static const float OneStep;
	static const float SnakeSpeed;
	static const float Dummy;
	static const float WorldSize;

	static const int SnakeNum;
	static const int ProjectileNum;
	static const int PreyNum;
	static const int CellNum;

	// Entity 조합에 맞는 충돌판별 및 처리
	static void collide(Snake& s1, Snake& s2);
	static void collide(Snake& s, Projectile& p);
	static void collide(Projectile& h, Prey& p);
	static void collide(Projectile& h, Wall& w);
	static void collide(Snake& s, Wall& w);
	static void collide(Snake& s, Prey& p);

	

	inline const std::vector<Snake*>& getHunters() const			{ return _snakes; }
	inline const std::vector<Projectile*>& getProjectiles() const	{ return _projectiles; }
	inline const std::vector<Prey*>& getPreys() const				{ return _preys; }
	inline const std::vector<Wall*>& getWalls() const				{ return _walls; }

	inline CellSpacePartition<RigidBody*>& getCellSpace()			{ return _cell_space; }
	inline EntityManager& getEntityMgr()							{ return _entity_mgr; }
	inline NetworkManagerServer& getNetworkMgr()					{ return *_network_mgr; }

	inline Snake* getPlayerEntity() const							{ return _player_entity; }
	inline void setPlayerEntity(Snake* const hunter)				{ _player_entity = hunter; }
	
	inline unsigned int genID()										{ return _next_validate_id++; }
	inline int getLevel() const										{ return level_; }
	inline float getWidth() const									{ return _width; }

	

	World(Room& room, float width);
	~World();
	
	Snake* createPlayerPawn(const Vec2& pos);
	void createHunter(const Vec2& pos);
	void createProjectile(const Vec2& pos, const Vec2& heading, int proj_speed);
	void createPrey(const Vec2& pos);
	void createWall(const Vec2& begin, const Vec2& end, const Vec2& heading);

	void update();
	void updateEntity();

	void regenEntity();

	void solveCollide();

	void render();
	void renderGrid();
	void renderCellSpace();

private:
	
	// entities
	std::vector<Snake*> _snakes;
	std::vector<Projectile*> _projectiles;
	std::vector<Prey*> _preys;
	std::vector<Wall*> _walls;
	std::queue<Entity*> _created_entities;
	
	// for space query
	CellSpacePartition<RigidBody*> _cell_space;
	
	EntityManager _entity_mgr;

	std::unique_ptr<NetworkManagerServer> _network_mgr;

	Snake* _player_entity;
	unsigned int _next_validate_id;

	float _width;
	int level_;
};