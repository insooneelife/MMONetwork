#include "GraphicsDriver.h"
#include "EntityManager.h"
#include "Camera2D.h"
#include <iostream>

std::unique_ptr< GraphicsDriver > GraphicsDriver::instance = nullptr;

SDL_Color GraphicsDriver::red;
SDL_Color GraphicsDriver::blue;
SDL_Color GraphicsDriver::yellow;
SDL_Color GraphicsDriver::black;
SDL_Color GraphicsDriver::white;

bool GraphicsDriver::staticInit(SDL_Window* wnd)
{
	GraphicsDriver* new_graph_driver = new GraphicsDriver();
	bool result = new_graph_driver->init(wnd);

	if( !result )
	{
		delete new_graph_driver;
	}
	else
	{
		instance.reset(new_graph_driver);
	}

	// Set color
	red.r = 255;	red.g = 0;		red.b = 0;
	blue.r = 0;		blue.g = 0;		blue.b = 255;
	yellow.r = 255;	yellow.g = 237;	yellow.b = 0;
	black.r = 0;	black.g = 0;	black.b = 0;
	white.r = 255;	white.g = 255;	white.b = 255;

	return result;
}

bool GraphicsDriver::init(SDL_Window* wnd)
{
	_renderer = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED);
	if( _renderer == nullptr )
	{
		SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Failed to create hardware-accelerated renderer." );
		return false;
	}

	// Cornflower blue background, cause why not?
	SDL_SetRenderDrawColor(_renderer, 100, 149, 237, SDL_ALPHA_OPAQUE );

	// Set the logical size to 1280x720 so everything will just auto-scale
	SDL_RenderSetLogicalSize(_renderer, 1280, 720 );
	

	// Add font for use texts.
	TTF_Init();
	_font = TTF_OpenFont("Assets/Carlito-Regular.TTF", 24);

	if (_font == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load font.");
	}

	return true;
}

GraphicsDriver::GraphicsDriver()
	: _renderer( nullptr )
{}


GraphicsDriver::~GraphicsDriver()
{
	if(_renderer != nullptr )
	{
		SDL_DestroyRenderer(_renderer);
	}
}

void GraphicsDriver::render()
{}

void GraphicsDriver::clear()
{
	SDL_SetRenderDrawColor(_renderer, 100, 149, 237, SDL_ALPHA_OPAQUE );
	SDL_RenderClear(_renderer);
}

void GraphicsDriver::present()
{
	SDL_RenderPresent(_renderer);
}

SDL_Rect& GraphicsDriver::getLogicalViewport()
{
	SDL_RenderGetLogicalSize(_renderer, &_view_port.w, &_view_port.h );

	return _view_port;
}

SDL_Renderer* GraphicsDriver::getRenderer()
{
	return _renderer;
}


void GraphicsDriver::drawLine(Vec2 a, Vec2 b, SDL_Color color, bool on_ui)
{
	if (!on_ui)
	{
		a = Camera2D::instance->worldToScreen(a);
		b = Camera2D::instance->worldToScreen(b);
	}

	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(
		_renderer,
		static_cast<int>(a.x),
		static_cast<int>(a.y),
		static_cast<int>(b.x),
		static_cast<int>(b.y));
}

void GraphicsDriver::drawRect(Vec2 p, float w, float h, SDL_Color color, bool on_ui)
{
	if (!on_ui)
	{
		p = Camera2D::instance->worldToScreen(p);
	}

	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect;
	rect.x = static_cast<int>(p.x);
	rect.y = static_cast<int>(p.y);
	rect.w = static_cast<int>(w);
	rect.h = static_cast<int>(h);
	SDL_RenderDrawRect(_renderer, &rect);
}


void GraphicsDriver::drawCircle(Vec2 p, float r,  SDL_Color color, float fragment, bool on_ui)
{
	float add = 360 / fragment;
	Vec2 start = Vec2(r, 0) + p;
	Vec2 end(0, 0);

	for (float degree = 0; degree <= 360; degree += add)
	{
		float rad = MATH_DEG_TO_RAD(degree);
		end = Vec2(r*cos(rad), r*sin(rad)) + p;
		drawLine(start, end, color, on_ui);
		start = end;
	}
}

void GraphicsDriver::drawText(const std::string& inStr, Vec2 origin, const SDL_Color& inColor, bool on_ui)
{
	if (!on_ui)
	{
		origin = Camera2D::instance->worldToScreen(origin);
	}

	// Convert the color
	SDL_Color color;
	color.r = inColor.r;
	color.g = inColor.g;
	color.b = inColor.b;
	color.a = 255;

	
	// Draw to surface and create a texture
	SDL_Surface* surface = TTF_RenderText_Blended(_font, inStr.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(GraphicsDriver::instance->getRenderer(), surface);

	// Setup the rect for the texture
	SDL_Rect dstRect;
	dstRect.x = static_cast<int>(origin.x);
	dstRect.y = static_cast<int>(origin.y);
	SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);

	// Draw the texture
	SDL_RenderCopy(GraphicsDriver::instance->getRenderer(), texture, nullptr, &dstRect);

	// Destroy the surface/texture
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);

	
}