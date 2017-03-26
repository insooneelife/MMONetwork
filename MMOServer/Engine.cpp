#include <chrono>
#include <iomanip>
#include "Engine.h"
#include "WindowManager.h"
#include "GraphicsDriver.h"
#include "EntityManager.h"
#include "World.h"
#include "Server/NetworkManagerServer.h"
#include "Camera2D.h"
#include <Common/Utils.h>

#include "GenericFactory.h"
#include "Entity/Snake.h"
#include "Entity/Prey.h"
#include "Entity/Projectile.h"
#include "Entity/Structure.h"

#include <Common/Network/GamePacket.hpp>
#include "Server/ProtobufServerUtils.h"
#include "Server/Server.h"

const double Engine::MsPerUpdate = 0.02f;
const double Engine::ReplicateTerm = 0.2f;


Engine::Engine()
	:accum_delta_(0)
{}

Engine::~Engine()
{}

void Engine::handleEvent(SDL_Event* inEvent)
{
	Snake* player = _world->getPlayerEntity();
	Vec2 heading;

	static bool press[255] = { 0 };
	const float distance = 100;
	const Vec2 left(-1, 0);
	const Vec2 right(1, 0);
	const Vec2 up(0, 1);
	const Vec2 down(0, -1);

	int mx = 0;
	int my = 0;

	switch (inEvent->type)
	{
	case SDL_KEYDOWN:
		// Details
		//if (player)
		//{
			switch (inEvent->key.keysym.sym)
			{
			case SDLK_a:
				if (player)player->setHeading(left);
				break;

			case SDLK_d:
				if (player)player->setHeading(right);
				break;

			case SDLK_w:
				if (player)player->setHeading(up);
				break;

			case SDLK_s:
				if (player)player->setHeading(down);
				break;

			case SDLK_u:
				_world->getNetworkMgr().showAllUsers();
				break;

			case SDLK_SPACE:
				break;

			default:
				break;
			}
		//}
		break;

	case SDL_KEYUP:
		break;

	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&mx, &my);
		
		break;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mx, &my);
		break;
	case SDL_MOUSEWHEEL:
		if (inEvent->wheel.y > 0)
		{
			Camera2D::instance->setScale(Camera2D::instance->getScale() * 1.1f);
		}
		else
		{
			Camera2D::instance->setScale(Camera2D::instance->getScale() * 0.9f);
		}

	default:
		break;
	}
}

bool Engine::init()
{
	GenericFactory::addCreateMethods
		<Snake, Structure, Projectile, Prey>
		(nullptr, nullptr, nullptr, nullptr);

	prev_ = std::chrono::system_clock::now().time_since_epoch();

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	if (!WindowManager::staticInit())
	{
		return false;
	}

	if (!GraphicsDriver::staticInit(WindowManager::instance->getMainWindow()))
	{
		return false;
	}
	
	Camera2D::staticInit(1280, 720);

	server_.reset(new Server(8000));

	_world.reset(new World(server_->getRoom(), World::WorldSize));

	
	
	return true;
}

int Engine::run()
{
	// Main message loop
	bool quit = false;
	SDL_Event event;
	memset(&event, 0, sizeof(SDL_Event));

	while (!quit)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT ||
				(event.type == SDL_WINDOWEVENT &&
					event.window.event == SDL_WINDOWEVENT_CLOSE))
			{
				quit = true;
			}
			else
			{
				// process events
				handleEvent(&event);
			}
		}
		else
		{
			// process updates
			update();
		}
	}

	return event.type;
}



void Engine::update()
{
	using namespace std::chrono;

	duration<double> current = system_clock::now().time_since_epoch();
	delta_ = current - prev_;
	prev_ = current;
	lag_ += delta_;


	duration<double> u0 = system_clock::now().time_since_epoch();
	while (lag_.count() >= MsPerUpdate)
	{
		_world->update();
		lag_ -= duration<double>(MsPerUpdate);
	}
	duration<double> u1 = system_clock::now().time_since_epoch();



	duration<double> re0 = system_clock::now().time_since_epoch();

	// render
	GraphicsDriver::instance->clear();
	_world->render();
	GraphicsDriver::instance->render();
	GraphicsDriver::instance->present();

	duration<double> re1 = system_clock::now().time_since_epoch();
	

	duration<double> c0 = system_clock::now().time_since_epoch();

	server_->getRoom().copyPacketsTo(_world->getNetworkMgr());
	_world->getNetworkMgr().processQueuedPackets();

	duration<double> c1 = system_clock::now().time_since_epoch();

	accum_delta_ += delta_.count();
	if (accum_delta_ > ReplicateTerm)
	{
		duration<double> r0 = system_clock::now().time_since_epoch();
		_world->getNetworkMgr().replicateToClients();
		accum_delta_ = 0;
		duration<double> r1 = system_clock::now().time_since_epoch();


		std::cout
			<< "r : " << std::fixed << std::setprecision(6) << (r1 - r0).count()
			<< "  re : " << std::fixed << std::setprecision(6) << (re1 - re0).count()
			<< "  u : " << std::fixed << std::setprecision(6) << (u1 - u0).count()
			<< "  c : " << std::fixed << std::setprecision(6) << (c1 - c0).count()
			<< "  delta : " << std::fixed << std::setprecision(6) << delta_.count()
			<< std::endl;
	}
}
