#pragma once
//------------------------------------------------------------------------
//
//  Name:		Camera2D.h
//
//  Desc:		For view transform related with screen, world and player.
//			
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include <Common/Math/Transformations.h>
#include <iostream>

class Camera2D
{
public:
	static void staticInit(float screenX, float screenY);
	static std::unique_ptr<Camera2D> instance;

	inline Vec2 getOrigin() const { return _origin; }
	inline void setOrigin(const Vec2& origin) { _origin = origin; }
	inline Vec2 getAxisX() const { return _axisX; }
	inline Vec2 getAxisY() const { return _axisY; }
	inline Vec2 getScale() const { return _scale; }
	
	inline void setScale(Vec2 scale) 
	{
		if(scale.x > 0 && scale.y > 0)
		_scale = scale; 
	}

	inline void setCamera(const Vec2& origin, const Vec2& axisX, const Vec2& axisY, Vec2 scale)
	{
		_origin = origin;
		_axisX = axisX;
		_axisY = axisY;
		_scale = scale;
	}

	inline float getScreenX() const { return _screenX; }
	inline float getScreenY() const { return _screenY; }

	Camera2D(float screenX, float screenY);

	Vec2 worldToScreen(const Vec2& pos);
	Vec2 screenToWorld(const Vec2& mpos);


private:
	float _screenX;
	float _screenY;

	Vec2 _origin;
	Vec2 _axisX;
	Vec2 _axisY;
	Vec2 _scale;
};