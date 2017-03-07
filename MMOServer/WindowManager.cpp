#include "WindowManager.h"
#include "SDL/SDL.h"

std::unique_ptr< WindowManager > WindowManager::instance = nullptr;

bool WindowManager::staticInit()
{
	int screenW = static_cast<int>( 1280 );
	int screenH = static_cast<int>( 720 );
	SDL_Window* wnd = SDL_CreateWindow( "Hello Game World", 100, 100, screenW, screenH, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	
	std::cout << "window size : " << screenW << " " << screenH << std::endl;

	if (wnd == nullptr)
	{
		SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Failed to create window." );
		return false;
	}

 	instance.reset(new WindowManager( wnd ));

	return true;
}


WindowManager::WindowManager( SDL_Window* main_window )
{
	_main_window = main_window;
}

WindowManager::~WindowManager()
{
	SDL_DestroyWindow(_main_window);
}
