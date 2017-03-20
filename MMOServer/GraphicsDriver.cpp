#include <array>
#include <iostream>
#include "GraphicsDriver.h"
#include "EntityManager.h"
#include "Camera2D.h"
#include <Common/Utils.h>

std::unique_ptr< GraphicsDriver > GraphicsDriver::instance = nullptr;

SDL_Color GraphicsDriver::red;
SDL_Color GraphicsDriver::blue;
SDL_Color GraphicsDriver::yellow;
SDL_Color GraphicsDriver::black;
SDL_Color GraphicsDriver::white;

SDL_Color GraphicsDriver::green;
SDL_Color GraphicsDriver::indigo;
SDL_Color GraphicsDriver::darkgray;
SDL_Color GraphicsDriver::orange;
SDL_Color GraphicsDriver::antiquewhite;
SDL_Color GraphicsDriver::lemon;
SDL_Color GraphicsDriver::darkgreen;



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
	// Set color
	red.r = 255;	red.g = 0;		red.b = 0;
	blue.r = 0;		blue.g = 0;		blue.b = 255;
	yellow.r = 255;	yellow.g = 255;	yellow.b = 0;
	black.r = 0;	black.g = 0;	black.b = 0;
	white.r = 255;	white.g = 255;	white.b = 255;

	green.r = 0;		green.g = 255;		green.b = 0;
	indigo.r = 75;		indigo.g = 0;		indigo.b = 130;
	darkgray.r = 169;	darkgray.g = 169;	darkgray.b = 169;
	orange.r = 238;		orange.g = 154;		orange.b = 0;

	antiquewhite.r = 255;	antiquewhite.g = 239;	antiquewhite.b = 219;
	lemon.r = 255;			lemon.g = 250;			lemon.b = 205;
	darkgreen.r = 162;		darkgreen.g = 205;		darkgreen.b = 90;

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

	for (auto e : text_cache_)
	{
		SDL_DestroyTexture(e.second.second);
		SDL_FreeSurface(e.second.first);
	}
}

void GraphicsDriver::render()
{}

void GraphicsDriver::clear()
{
	SDL_SetRenderDrawColor(_renderer, 100, 149, 237, SDL_ALPHA_OPAQUE);
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

void GraphicsDriver::drawLines(const std::vector<Vec2>& lines, SDL_Color color, bool on_ui)
{
	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
	std::array<SDL_Point, 100> rv;

	for (int i = 0; i < lines.size(); ++i)
	{
		Vec2 cp = Camera2D::instance->worldToScreen(lines[i]);
		rv[i].x = cp.x;
		rv[i].y = cp.y;
	}
	
	SDL_RenderDrawLines(_renderer, rv.data(), lines.size());
}

void GraphicsDriver::drawRect(Vec2 bot_left, Vec2 top_right, SDL_Color color, bool on_ui)
{
	if (!on_ui)
	{
		bot_left = Camera2D::instance->worldToScreen(bot_left);
		top_right = Camera2D::instance->worldToScreen(top_right);
	}

	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect;
	rect.x = static_cast<int>(bot_left.x);
	rect.y = static_cast<int>(bot_left.y);
	rect.w = static_cast<int>(top_right.x - bot_left.x);
	rect.h = static_cast<int>(top_right.y - bot_left.y);
	SDL_RenderDrawRect(_renderer, &rect);
}

void GraphicsDriver::drawRects(const std::vector<std::pair<Vec2, Vec2> >& rects, SDL_Color color, bool on_ui)
{
	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
	std::array<SDL_Rect, 10000> rv;

	for (int i = 0; i < rects.size(); ++i)
	{
		Vec2 bot_left = Camera2D::instance->worldToScreen(rects[i].first);
		Vec2 top_right = Camera2D::instance->worldToScreen(rects[i].second);
		rv[i].x = static_cast<int>(bot_left.x);
		rv[i].y = static_cast<int>(bot_left.y);
		rv[i].w = static_cast<int>(top_right.x - bot_left.x);
		rv[i].h = static_cast<int>(top_right.y - bot_left.y);
	}

	SDL_RenderDrawRects(_renderer, rv.data(), rects.size());
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
	auto key = std::make_tuple(inStr, inColor.r, inColor.g, inColor.b, inColor.a);
	auto it = text_cache_.find(key);
	if (it != std::end(text_cache_))
	{
		SDL_Texture* texture = it->second.second;

		SDL_Rect dstRect;
		dstRect.x = static_cast<int>(origin.x);
		dstRect.y = static_cast<int>(origin.y);
		SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);

		// Draw the texture
		SDL_RenderCopy(GraphicsDriver::instance->getRenderer(), texture, nullptr, &dstRect);
	}
	else
	{
		// Convert the color
		SDL_Color color;
		color.r = inColor.r;
		color.g = inColor.g;
		color.b = inColor.b;
		color.a = 255;

		// Draw to surface and create a texture
		SDL_Surface* surface = TTF_RenderText_Blended(_font, inStr.c_str(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(GraphicsDriver::instance->getRenderer(), surface);

		text_cache_.emplace(key, std::make_pair(surface, texture));

		// Setup the rect for the texture
		SDL_Rect dstRect;
		dstRect.x = static_cast<int>(origin.x);
		dstRect.y = static_cast<int>(origin.y);
		SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);

		// Draw the texture
		SDL_RenderCopy(GraphicsDriver::instance->getRenderer(), texture, nullptr, &dstRect);
	}	
}

void GraphicsDriver::drawBox2DShape(b2Shape* shape)
{
	if (shape->GetType() == b2Shape::e_chain)
	{
		auto chain = static_cast<b2ChainShape*>(shape);

		for (int i = 0; i < chain->GetChildCount(); i++)
		{
			b2EdgeShape edge;
			chain->GetChildEdge(&edge, i);
			drawLine(toVec(edge.m_vertex1), toVec(edge.m_vertex2));
		}
	}

	else if (shape->GetType() == b2Shape::e_circle)
	{
		auto circle = static_cast<b2CircleShape*>(shape);
		drawCircle(toVec(circle->m_p), circle->m_radius);
	}

	else if (shape->GetType() == b2Shape::e_edge)
	{
		auto edge = static_cast<b2EdgeShape*>(shape);
		drawLine(toVec(edge->m_vertex1), toVec(edge->m_vertex2));
	}

	else if (shape->GetType() == b2Shape::e_polygon)
	{
		auto polygon = static_cast<b2PolygonShape*>(shape);

		for (int i = 0; i < polygon->GetVertexCount(); i++)
		{
			int j = (i + 1) % polygon->GetVertexCount();
			b2Vec2 a = polygon->GetVertex(i);
			b2Vec2 b = polygon->GetVertex(j);
			drawLine(toVec(a), toVec(b));
		}
	}
}