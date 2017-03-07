#include <chrono>
#include "Engine.h"
#include "WindowManager.h"
#include "GraphicsDriver.h"
#include "EntityManager.h"
#include "World.h"
#include "Camera2D.h"
#include "Utils.h"

#include "Entity/Snake.h"

#include <Common/Network/GamePacket.hpp>
#include "Server/PacketFactory.h"
#include "Server/Server.h"


Engine::Engine()
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
		if (player)
		{
			switch (inEvent->key.keysym.sym)
			{
			case SDLK_a:
					player->setHeading(left);
				break;

			case SDLK_d:
					player->setHeading(right);
				break;

			case SDLK_w:
					player->setHeading(up);
				break;

			case SDLK_s:
					player->setHeading(down);
				break;

			case SDLK_SPACE:
				break;

			default:
				break;
			}
		}
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

	//EntityManager::staticInit();
	
	

	server_.reset(new Server(8000));

	_world.reset(new World(server_->getRoom(), 30000));

	


	/*
	Data::ReplicateData rdata;

	PacketFactory::serializeReplicateData(_world.get(), rdata);
	auto packet = PacketFactory::createReplicatePacket(rdata);
	uint8_t buffer[100000];
	packet.serialize(buffer);
	//send

	// recv header
	uint8_t size = packet.getHeader().ByteSize();
	Data::HeaderData hdata;
	google::protobuf::io::CodedInputStream his(buffer, size);
	hdata.MergePartialFromCodedStream(&his);

	std::cout << "body size : " << hdata.size() << "   body type : " << hdata.type() << std::endl;

	// recv body
	Data::ReplicateData bdata;
	google::protobuf::io::CodedInputStream bis(buffer + GamePacket<int>::HeaderLength, hdata.size());
	bdata.MergePartialFromCodedStream(&bis);

	std::cout << bdata.DebugString() << std::endl;
	*/

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
	std::chrono::duration<double> start = std::chrono::system_clock::now().time_since_epoch();
	
	_world->update();

	std::chrono::duration<double> end = std::chrono::system_clock::now().time_since_epoch();
	
	// render
	GraphicsDriver::instance->clear();
	_world->render();
	GraphicsDriver::instance->render();
	GraphicsDriver::instance->present();

	std::chrono::duration<double> end2 = std::chrono::system_clock::now().time_since_epoch();
	//std::cout <<"u : "<< (end - start).count()<<"  r : "<< (end2 - end).count() << std::endl;
}
