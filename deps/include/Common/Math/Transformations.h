#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
//------------------------------------------------------------------------
//
//  Name:   Transformations.h
//
//  Desc:   Functions for converting 2D vectors between World and Local
//          space.
//
//  Author: Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------
#include <vector>
#include "C2DMatrix.h"
#include "Vec2.h"

namespace
{
	//--------------------------- worldTransform -----------------------------
	//
	//  given a std::vector of 2D vectors, a position, orientation and scale,
	//  this function transforms the 2D vectors into the object's world space
	//------------------------------------------------------------------------
	inline std::vector<Vec2> worldTransform(
		std::vector<Vec2> &points,
		const Vec2   &pos,
		const Vec2   &forward,
		const Vec2   &side,
		const Vec2   &scale)
	{
		//copy the original vertices into the buffer about to be transformed
		std::vector<Vec2> TranVector2Ds = points;

		//create a transformation matrix
		C2DMatrix matTransform;

		//scale
		if ((scale.x != 1.0) || (scale.y != 1.0))
		{
			matTransform.scale(scale.x, scale.y);
		}

		//rotate
		matTransform.rotate(forward, side);

		//and translate
		matTransform.translate(pos.x, pos.y);

		//now transform the object's vertices
		matTransform.transform(TranVector2Ds);

		return TranVector2Ds;
	}

	//--------------------------- worldTransform -----------------------------
	//
	//  given a std::vector of 2D vectors, a position and  orientation
	//  this function transforms the 2D vectors into the object's world space
	//------------------------------------------------------------------------
	inline std::vector<Vec2> worldTransform(
		std::vector<Vec2> &points,
		const Vec2   &pos,
		const Vec2   &forward,
		const Vec2   &side)
	{
		//copy the original vertices into the buffer about to be transformed
		std::vector<Vec2> TranVector2Ds = points;

		//create a transformation matrix
		C2DMatrix matTransform;

		//rotate
		matTransform.rotate(forward, side);

		//and translate
		matTransform.translate(pos.x, pos.y);

		//now transform the object's vertices
		matTransform.transform(TranVector2Ds);

		return TranVector2Ds;
	}

	//--------------------- pointToWorldSpace --------------------------------
	//
	//  Transforms a point from the agent's local space into world space
	//------------------------------------------------------------------------
	inline Vec2 pointToWorldSpace(
		const Vec2 &point,
		const Vec2 &AgentHeading,
		const Vec2 &AgentSide,
		const Vec2 &AgentPosition)
	{
		//make a copy of the point
		Vec2 TransPoint = point;

		//create a transformation matrix
		C2DMatrix matTransform;

		//rotate
		matTransform.rotate(AgentHeading, AgentSide);

		//and translate
		matTransform.translate(AgentPosition.x, AgentPosition.y);

		//now transform the vertices
		matTransform.transform(TransPoint);

		return TransPoint;
	}

	//--------------------- vectorToWorldSpace --------------------------------
	//
	//  Transforms a vector from the agent's local space into world space
	//------------------------------------------------------------------------
	inline Vec2 vectorToWorldSpace(
		const Vec2 &vec,
		const Vec2 &AgentHeading,
		const Vec2 &AgentSide)
	{
		//make a copy of the point
		Vec2 TransVec = vec;

		//create a transformation matrix
		C2DMatrix matTransform;

		//rotate
		matTransform.rotate(AgentHeading, AgentSide);

		//now transform the vertices
		matTransform.transform(TransVec);
		return TransVec;
	}


	//--------------------- pointToLocalSpace --------------------------------
	//
	//------------------------------------------------------------------------
	inline Vec2 pointToLocalSpace(
		const Vec2 &point,
		const Vec2 &AgentHeading,
		const Vec2 &AgentSide,
		const Vec2 &AgentPosition)
	{

		//make a copy of the point
		Vec2 TransPoint = point;

		//create a transformation matrix
		C2DMatrix matTransform;

		double Tx = -AgentPosition.dot(AgentHeading);
		double Ty = -AgentPosition.dot(AgentSide);

		//create the transformation matrix
		matTransform._11(AgentHeading.x); matTransform._12(AgentSide.x);
		matTransform._21(AgentHeading.y); matTransform._22(AgentSide.y);
		matTransform._31(Tx);           matTransform._32(Ty);

		//now transform the vertices
		matTransform.transform(TransPoint);

		return TransPoint;
	}

	//--------------------- vectorToLocalSpace --------------------------------
	//
	//------------------------------------------------------------------------
	inline Vec2 vectorToLocalSpace(
		const Vec2 &vec,
		const Vec2 &AgentHeading,
		const Vec2 &AgentSide)
	{

		//make a copy of the point
		Vec2 TransPoint = vec;

		//create a transformation matrix
		C2DMatrix matTransform;

		//create the transformation matrix
		matTransform._11(AgentHeading.x); matTransform._12(AgentSide.x);
		matTransform._21(AgentHeading.y); matTransform._22(AgentSide.y);

		//now transform the vertices
		matTransform.transform(TransPoint);

		return TransPoint;
	}

	//-------------------------- vec2DRotateAroundOrigin --------------------------
	//
	//  rotates a vector ang rads around the origin
	//-----------------------------------------------------------------------------
	inline void vec2DRotateAroundOrigin(Vec2& v, double ang)
	{
		//create a transformation matrix
		C2DMatrix mat;

		//rotate
		mat.rotate(ang);

		//now transform the object's vertices
		mat.transform(v);
	}

	//------------------------ createWhiskers ------------------------------------
	//
	//  given an origin, a facing direction, a 'field of view' describing the 
	//  limit of the outer whiskers, a whisker length and the number of whiskers
	//  this method returns a vector containing the end positions of a series
	//  of whiskers radiating away from the origin and with equal distance between
	//  them. (like the spokes of a wheel clipped to a specific segment size)
	//----------------------------------------------------------------------------
	inline std::vector<Vec2> createWhiskers(
		unsigned int  NumWhiskers,
		double        WhiskerLength,
		double        fov,
		Vec2      facing,
		Vec2      origin)
	{
		//this is the magnitude of the angle separating each whisker
		double SectorSize = fov / (double)(NumWhiskers - 1);

		std::vector<Vec2> whiskers;
		Vec2 temp;
		double angle = -fov*0.5;

		for (unsigned int w = 0; w < NumWhiskers; ++w)
		{
			//create the whisker extending outwards at this angle
			temp = facing;
			vec2DRotateAroundOrigin(temp, angle);
			whiskers.push_back(origin + WhiskerLength * temp);

			angle += SectorSize;
		}

		return whiskers;
	}

}


#endif