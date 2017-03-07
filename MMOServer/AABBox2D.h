#ifndef INVAABBOX2D_H
#define INVAABBOX2D_H
//-----------------------------------------------------------------------------
//
//  Name:   AABBox2D.h
//
//  Author: Insub Im (www.ai-junkie.com)
//
//  Desc:   A simple inverted (y increases down screen) axis aligned bounding
//          box class
//-----------------------------------------------------------------------------

#include <Common/Math/Vec2.h>

class AABBox2D
{
private:
	Vec2 _bottom_left;
	Vec2 _top_right;
	Vec2 _center;

public:
	AABBox2D(Vec2 bl, Vec2 tr)
		:
		_bottom_left(bl),
		_top_right(tr),
		_center((bl + tr) / 2.0)
	{}

	// returns true if the bbox described by other intersects with this one
	inline bool isOverlappedWith(const AABBox2D& other) const
	{
		return !((other.getTop() < this->getBottom()) ||
				(other.getBottom() > this->getTop()) ||
				(other.getLeft() > this->getRight()) ||
				(other.getRight() < this->getLeft()));
	}

	inline bool containsPoint(Vec2 p) const
	{
		return 
			getLeft() <= p.x && p.x <= getRight() &&
			getBottom() <= p.y && p.y <= getTop();
	}

	inline Vec2 getTopRight()		const { return _top_right; }
	inline Vec2 getTopLeft()		const { return Vec2(getLeft(), getTop()); }
	inline Vec2 getBottomLeft()		const { return _bottom_left; }
	inline Vec2 getBottomRight()	const { return Vec2(getRight(), getBottom()); }
	inline Vec2 getCenter()			const { return _center; }

	inline double getTop()		const { return _top_right.y; }
	inline double getLeft()		const { return _bottom_left.x; }
	inline double getBottom()	const { return _bottom_left.y; }
	inline double getRight()	const { return _top_right.x; }

};

#endif