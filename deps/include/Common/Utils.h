#pragma once
//------------------------------------------------------------------------
//
//  Name:		Utils.h
//
//  Desc:		Some utility functions.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------
#include <random>
#include <cstdio>
#include <cassert>
#include "Math/Vec2.h"

#include <Box2D/Box2D.h>

namespace
{
	// random number generator
	template<unsigned int T = 0, unsigned int U = 1>
	static inline auto genRand() {
		static std::random_device rd;
		static std::mt19937 mt(rd());
		static std::uniform_real_distribution<double> dist(T, std::nextafter(U, DBL_MAX));

		return dist(mt);
	}

	// random number generator, range : [T , U)  
	template<typename T, typename U>
	static inline decltype(auto) random(T begin, U end) {
		double rand = genRand<0, 1>();
		return ((end - begin) * rand + begin);
	}
	
	// neighber1_key is clock-wise direction key of dir
	// neighber2_key is counter-clock-wise direction key of dir
	// ex)
	//		a =>	left	=> Vec2(-1, 0)
	//		s =>	down	=> Vec2(0, -1)
	//		d =>	right	=> Vec2(1, 0)
	//		w =>	up		=> Vec2(0, 1)
	//		 
	//		neighber1_key of 'a' is 'w'
	//		neighber2_key of 'a' is 's'
	//
	inline Vec2 directionFromMultiKey(bool neighber1_key, bool neighber2_key, Vec2 dir)
	{
		Vec2 dir1 = -dir.getPerp();
		Vec2 dir2 = dir.getPerp();
		if (neighber1_key)
			return (dir1 + dir).getNormalized();
		else if (neighber2_key)
			return (dir2 + dir).getNormalized();
		else
			return dir;
	}

	inline float distToSegmentSq(
		Vec2 A,
		Vec2 B,
		Vec2 P)
	{
		assert((A != B) && "invalid segment!");

		// if the angle is obtuse between PA and AB is obtuse then the closest vertex must be A
		float dotA = (P.x - A.x)*(B.x - A.x) + (P.y - A.y)*(B.y - A.y);

		if (dotA <= 0) return (P - A).getLengthSq();

		// if the angle is obtuse between PB and AB is obtuse then the closest vertex must be B
		float dotB = (P.x - B.x)*(A.x - B.x) + (P.y - B.y)*(A.y - B.y);

		if (dotB <= 0) return (P - B).getLengthSq();

		// calculate the point along AB that is the closest to P
		Vec2 Point = A + ((B - A) * dotA) / (dotA + dotB);

		// calculate the distance P-Point
		return (Point - P).getLengthSq();
	}

	inline bool segmentCircleOverlap(
		Vec2 A,
		Vec2 B,
		Vec2 P,
		float radius)
	{
		assert((A != B) && "invalid segment!");
		assert((radius > 0) && "invalid circle radius!");

		// first determine the distance from the center of the circle to
		// the line segment (working in distance squared space)
		float dist_to_line_sq = distToSegmentSq(A, B, P);

		if (dist_to_line_sq <= radius*radius)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	inline bool circlesAmountOfOverlap(
		Vec2 pos1, float radius1,
		Vec2 pos2, float radius2,
		Vec2& force)
	{
		force = Vec2::ZERO;
		float amount_of_overlap = radius1 + radius2 - (pos1 - pos2).getLength();

		if (amount_of_overlap < 0)
			return false;

		force = (pos1 - pos2).getNormalized() * amount_of_overlap;
		return true;
	}

	template<typename Point>
	static inline Vec2 toVec(const Point& p) { return Vec2(p.x, p.y); }

	template<typename Point>
	static inline b2Vec2 tob2Vec(const Point& p) { return b2Vec2(p.x, p.y); }

	template<typename Color>
	static inline b2Color tob2Color(const Color& sdl_color)
	{
		return b2Color(sdl_color.r, sdl_color.g, sdl_color.b, sdl_color.a);
	}
}