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
#include "Server/PacketFactory.h"


#include "EntityManager.h"

class Entity;
class Snake;
class Prey;
class Projectile;
class Wall;
class RigidBody;
class Room;
class NetworkManager;

class World
{
public:
	enum { InvalidateId = 0 };

	static const float OneStep;
	static const float SnakeSpeed;
	static const float Dummy;

	// Entity 조합에 맞는 충돌판별 및 처리
	static void collide(Snake& s1, Snake& s2);
	static void collide(Snake& s, Projectile& p);
	static void collide(Projectile& h, Prey& p);
	static void collide(Projectile& h, Wall& w);
	static void collide(Snake& s, Wall& w);
	static void collide(Snake& s, Prey& p);

	// 모든 entity의 update 및, garbage 수집
	template<class Container>
	static void updateEntity(Container& entities);

	// Entity 컨테이너 getter && setter
	inline const std::vector<Snake*>& getHunters() const			{ return _snakes; }
	inline const std::vector<Projectile*>& getProjectiles() const	{ return _projectiles; }
	inline const std::vector<Prey*>& getPreys() const				{ return _preys; }
	inline const std::vector<Wall*>& getWalls() const				{ return _walls; }

	inline CellSpacePartition<RigidBody*>& getCellSpace()			{ return _cell_space; }
	inline EntityManager& getEntityMgr()							{ return _entity_mgr; }

	// 플레이어의 entity를 참조하기 위한 getter
	inline Snake* getPlayerEntity() const							{ return _player_entity; }
	inline void setPlayerEntity(Snake* const hunter)				{ _player_entity = hunter; }
	
	// 유일한 id를 생성해 준다.
	inline unsigned int genID()										{ return _next_validate_id++; }
	inline int getLevel() const { return level_; }


	inline std::map<unsigned int, Data::UserData>& getUsers()		{ return _users; }
	inline std::vector<ModifyInfo>& getModifies() { return _modifies; }

	World(Room& room, float width);
	~World();
	
	void createHunter(const Vec2& pos);
	void createProjectile(const Vec2& pos, const Vec2& heading, int proj_speed);
	void createPrey(const Vec2& pos);
	void createWall(const Vec2& begin, const Vec2& end, const Vec2& heading);

	// world의 logic
	// 모든 entity의 update 호출
	void update();
	void solveCollide();

	void render();
	void renderGrid();
	void renderCellSpace();

private:
	// players
	std::map<unsigned int, Data::UserData> _users;
	std::vector<ModifyInfo> _modifies;

	// entities
	std::vector<Snake*> _snakes;
	std::vector<Projectile*> _projectiles;
	std::vector<Prey*> _preys;
	std::vector<Wall*> _walls;
	std::queue<Entity*> _created_entities;
	
	// for space query
	CellSpacePartition<RigidBody*> _cell_space;
	
	EntityManager _entity_mgr;

	std::unique_ptr<NetworkManager> _network_mgr;

	Snake* _player_entity;
	unsigned int _next_validate_id;

	float _width;
	int level_;
};