#pragma once
//------------------------------------------------------------------------
//
//  Name:		GraphicsDriver.h
//
//  Desc:		Utility class for wrapping SDL graphic tools
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <memory>
#include <Common/Math/Vec2.h>

class GraphicsDriver
{
public:

	static bool staticInit(SDL_Window* wnd);

	static std::unique_ptr< GraphicsDriver > instance;

	static SDL_Color red;
	static SDL_Color blue;
	static SDL_Color yellow;
	static SDL_Color black;
	static SDL_Color white;


	void			render();
	void			clear();
	void			present();
	SDL_Rect&		getLogicalViewport();
	SDL_Renderer*	getRenderer();

	void			drawLine(Vec2 a, Vec2 b, SDL_Color color = red, bool on_ui = false);
	void			drawRect(Vec2 p, float w, float h, SDL_Color color = red, bool on_ui = false);
	void			drawCircle(Vec2 p, float r, SDL_Color color = red, float fragment = 3, bool on_ui = false);
	void			drawText(const std::string& inStr, Vec2 origin, const SDL_Color& inColor = red, bool on_ui = false);
	~GraphicsDriver();

private:

	GraphicsDriver();
	bool init(SDL_Window* wnd);

	SDL_Renderer*			_renderer;
	SDL_Rect				_view_port;
	TTF_Font*				_font;
};
