#pragma once

#include "Vec3.h"

template<typename T>
class Mat3
{
public:

	//operators
	Vec2<T> operator*(const Vec2<T>& vec) const
	{
		return operator Vec2<T>(*this * (Vec3<T>)v);
	}

	Vec3<T> operator*(const Vec3<T>& vec) const
	{
		Vec3<T> vout; 
		vout._x = cells[0][0] * vec._x + cells[0][1] * vec._y + cells[0][2] * vec._w;
		vout._y = cells[1][0] * vec._x + cells[1][1] * vec._y + cells[1][2] * vec._w;
		vout._w = cells[2][0] * vec._x + cells[2][1] * vec._y + cells[2][2] * vec._w;

		return vout;
	}

	Mat3 operator*(const Mat3& rhs) const
	{
		Mat3 out;
		for (int row_left = 0; row_left < 3; row_left++)
		{
			for (int col_right = 0; col_right < 3; col_right++)
			{
				out.cells[row_left][col_right] = (T)0;
				for (int i = 0; i < 3; i++)
				{
					out.cells[row_left][col_right] += cells[row_left][i] * rhs.cells[i][col_right];
				}
			}
		}
		return out;
	}

	Mat3<T>& operator*=(const Mat3<T>& rhs) const
	{
		return *this = *this * rhs;
	}

	//static
	static Mat3<T> Identity()
	{
		return scale((T)1);
	}

	static Mat3 FlipY()
	{
		return {
			(T)1,	(T)0,  (T)0,
			(T)0,	(T)-1, (T)0,
			(T)0,	(T)0,  (T)1
		};
	}

	static Mat3<T> Scale(T factor)
	{
		return Mat3<T> {
			factor, (T)0, (T)0,
			(T)0, factor, (T)0,
			(T)0, (T)0,   (T)1
		};
	}

	static Mat3<T> Rotation(T theta)
	{
		const auto sinTheta = sin(theta);
		const auto cosTheta = cos(theta);
		return Mat3<T> {
			(T)cosTheta, -(T)sinTheta, (T)0,
			(T)sinTheta, (T)cosTheta, (T)0,
			(T)0,		 (T)0,		  (T)1
		};
	}

	static Mat3<T> Translation(T x, T y)
	{
		return Mat3<T> {
			(T)1, (T)0, x,
			(T)0, (T)1, y,
			(T)0, (T)0, (T)1
		};
	}



public:
	//[row][col]
	T cells[3][3];
};
