#ifndef C2DMATRIX_H
#define C2DMATRIX_H

//------------------------------------------------------------------------
//
//  Name:   C2DMatrix.h
//
//  Desc:   2D Matrix class 
//
//  Author: Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include <math.h>
#include <vector>
#include "Vec2.h"

class C2DMatrix
{
private:
	struct Matrix
	{
		double _11, _12, _13;
		double _21, _22, _23;
		double _31, _32, _33;

		Matrix()
		{
			_11 = 0.0; _12 = 0.0; _13 = 0.0;
			_21 = 0.0; _22 = 0.0; _23 = 0.0;
			_31 = 0.0; _32 = 0.0; _33 = 0.0;
		}

	};

	Matrix _mat;

	//multiplies _mat with mIn
	inline void  multiply(Matrix &mIn);


public:

	C2DMatrix()
	{
		//initialize the matrix to an identity matrix
		identity();
	}

	//create an identity matrix
	inline void identity();

	//create a transformation matrix
	inline void translate(double x, double y);

	//create a scale matrix
	inline void scale(double xScale, double yScale);

	//create a rotation matrix
	inline void  rotate(double rotation);

	//create a rotation matrix from a fwd and side 2D vector
	inline void  rotate(const Vec2 &fwd, const Vec2 &side);

	//applys a transformation matrix to a std::vector of points
	inline void transform(std::vector<Vec2>& vPoints);

	//applys a transformation matrix to a point
	inline void transform(Vec2& vPoint);

	//accessors to the matrix elements
	void _11(double val) { _mat._11 = val; }
	void _12(double val) { _mat._12 = val; }
	void _13(double val) { _mat._13 = val; }

	void _21(double val) { _mat._21 = val; }
	void _22(double val) { _mat._22 = val; }
	void _23(double val) { _mat._23 = val; }

	void _31(double val) { _mat._31 = val; }
	void _32(double val) { _mat._32 = val; }
	void _33(double val) { _mat._33 = val; }

};



//multiply two matrices together
inline void C2DMatrix::multiply(Matrix &mIn)
{
	C2DMatrix::Matrix mat_temp;

	//first row
	mat_temp._11 = (_mat._11*mIn._11) + (_mat._12*mIn._21) + (_mat._13*mIn._31);
	mat_temp._12 = (_mat._11*mIn._12) + (_mat._12*mIn._22) + (_mat._13*mIn._32);
	mat_temp._13 = (_mat._11*mIn._13) + (_mat._12*mIn._23) + (_mat._13*mIn._33);

	//second
	mat_temp._21 = (_mat._21*mIn._11) + (_mat._22*mIn._21) + (_mat._23*mIn._31);
	mat_temp._22 = (_mat._21*mIn._12) + (_mat._22*mIn._22) + (_mat._23*mIn._32);
	mat_temp._23 = (_mat._21*mIn._13) + (_mat._22*mIn._23) + (_mat._23*mIn._33);

	//third
	mat_temp._31 = (_mat._31*mIn._11) + (_mat._32*mIn._21) + (_mat._33*mIn._31);
	mat_temp._32 = (_mat._31*mIn._12) + (_mat._32*mIn._22) + (_mat._33*mIn._32);
	mat_temp._33 = (_mat._31*mIn._13) + (_mat._32*mIn._23) + (_mat._33*mIn._33);

	_mat = mat_temp;
}

//applies a 2D transformation matrix to a std::vector of Vector2Ds
inline void C2DMatrix::transform(std::vector<Vec2> &vPoint)
{
	for (unsigned int i = 0; i < vPoint.size(); ++i)
	{
		double tempX = (_mat._11*vPoint[i].x) + (_mat._21*vPoint[i].y) + (_mat._31);

		double tempY = (_mat._12*vPoint[i].x) + (_mat._22*vPoint[i].y) + (_mat._32);

		vPoint[i].x = tempX;

		vPoint[i].y = tempY;

	}
}

//applies a 2D transformation matrix to a single Vector2D
inline void C2DMatrix::transform(Vec2 &vPoint)
{

	double tempX = (_mat._11*vPoint.x) + (_mat._21*vPoint.y) + (_mat._31);

	double tempY = (_mat._12*vPoint.x) + (_mat._22*vPoint.y) + (_mat._32);

	vPoint.x = tempX;

	vPoint.y = tempY;
}



//create an identity matrix
inline void C2DMatrix::identity()
{
	_mat._11 = 1; _mat._12 = 0; _mat._13 = 0;

	_mat._21 = 0; _mat._22 = 1; _mat._23 = 0;

	_mat._31 = 0; _mat._32 = 0; _mat._33 = 1;

}

//create a transformation matrix
inline void C2DMatrix::translate(double x, double y)
{
	Matrix mat;

	mat._11 = 1; mat._12 = 0; mat._13 = 0;

	mat._21 = 0; mat._22 = 1; mat._23 = 0;

	mat._31 = x;    mat._32 = y;    mat._33 = 1;

	//and multiply
	multiply(mat);
}

//create a scale matrix
inline void C2DMatrix::scale(double xScale, double yScale)
{
	C2DMatrix::Matrix mat;

	mat._11 = xScale; mat._12 = 0; mat._13 = 0;

	mat._21 = 0; mat._22 = yScale; mat._23 = 0;

	mat._31 = 0; mat._32 = 0; mat._33 = 1;

	//and multiply
	multiply(mat);
}


//create a rotation matrix
inline void C2DMatrix::rotate(double rot)
{
	C2DMatrix::Matrix mat;

	double Sin = sin(rot);
	double Cos = cos(rot);

	mat._11 = Cos;  mat._12 = Sin; mat._13 = 0;

	mat._21 = -Sin; mat._22 = Cos; mat._23 = 0;

	mat._31 = 0; mat._32 = 0; mat._33 = 1;

	//and multiply
	multiply(mat);
}


//create a rotation matrix from a 2D vector
inline void C2DMatrix::rotate(const Vec2 &fwd, const Vec2 &side)
{
	C2DMatrix::Matrix mat;

	mat._11 = fwd.x;  mat._12 = fwd.y; mat._13 = 0;

	mat._21 = side.x; mat._22 = side.y; mat._23 = 0;

	mat._31 = 0; mat._32 = 0; mat._33 = 1;

	//and multiply
	multiply(mat);
}





#endif
