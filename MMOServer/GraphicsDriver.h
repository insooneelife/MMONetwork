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

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <tuple>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <memory>
#include <Common/Math/Vec2.h>
#include <Box2D/Box2D.h>


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

	static SDL_Color green;
	static SDL_Color indigo;
	static SDL_Color darkgray;
	static SDL_Color orange;
	static SDL_Color antiquewhite;
	static SDL_Color lemon;
	static SDL_Color darkgreen;

	void render();
	void clear();
	void present();
	SDL_Rect&		getLogicalViewport();
	SDL_Renderer*	getRenderer();

	void drawLine(Vec2 a, Vec2 b, SDL_Color color = red, bool on_ui = false);
	void drawLines(const std::vector<Vec2>& lines, SDL_Color color = red, bool on_ui = false);
	void drawRect(Vec2 bot_left, Vec2 top_right, SDL_Color color = red, bool on_ui = false);
	void drawRects(
		const std::vector<std::pair<Vec2, Vec2> >& rects,
		SDL_Color color = red,
		bool on_ui = false);

	void drawCircle(Vec2 p, float r, SDL_Color color = red, float fragment = 3, bool on_ui = false);
	void drawText(const std::string& inStr, Vec2 origin, const SDL_Color& inColor = red, bool on_ui = false);
	
	void drawBox2DShape(b2Shape* shape);
	
	~GraphicsDriver();

private:

	GraphicsDriver();
	bool init(SDL_Window* wnd);

	SDL_Renderer* _renderer;
	SDL_Rect _view_port;
	TTF_Font* _font;

	std::map<std::tuple<std::string, unsigned char, unsigned char, unsigned char, unsigned char>,
		std::pair<SDL_Surface*, SDL_Texture*> > text_cache_;
};
