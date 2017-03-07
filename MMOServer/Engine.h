#pragma once
//------------------------------------------------------------------------
//
//  Name:		Engine.h
//
//  Desc:		It includes world and managers which are outside of world.
//				
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include <SDL/SDL.h>
#include <vector>
#include <memory>

class Entity;
class World;
class Server;

class Engine
{
public:
	Engine();

	~Engine();

	// Initialize all manager classes
	bool init();
	
	// Big loop for all, include world
	int run();

private:
	// Process event by type
	void handleEvent(SDL_Event* ev);

	// All updates, include world
	void update();

	// Takes one world instance
	std::unique_ptr<World> _world;

	std::unique_ptr<Server> server_;
};