#pragma once
//------------------------------------------------------------------------
//
//  Name:		WindowManager.h
//
//  Desc:		Utility class for wrapping SDL window API.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include <memory>
#include <iostream>
#include <SDL/SDL.h>

class WindowManager
{
public:
	
	static bool staticInit();
	static std::unique_ptr<WindowManager> instance;

	SDL_Window*		getMainWindow()	const	{ return _main_window; }

	~WindowManager();

private:
	WindowManager( SDL_Window* main_window );

	SDL_Window*				_main_window;
};