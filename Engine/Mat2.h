#pragma once

#include "Vec2.h"

template<typename T>
class Mat2
{
public:
	
	//operators
	Vec2<T> operator*(const Vec2<T>& vec) const
	{
		return Vec2<T>{ cells[0][0] * vec._x + cells[0][1] * vec._y,  cells[1][0] * vec._x + cells[1][1] * vec._y };
	}

	Mat2 operator*(const Mat2& rhs) const
	{
		Mat2 out;
		for (int row_left = 0; row_left < 2; row_left++)
		{
			for (int col_right = 0; col_right < 2; col_right++)
			{
				out.cells[row_left][col_right] = (T)0;
				for (int i = 0; i < 2; i++)
				{
					out.cells[row_left][col_right] += cells[row_left][i] * rhs.cells[i][col_right];
				}
			}
		}
		return out;
	}

	Mat2<T>& operator*=(const Mat2<T>& rhs) const
	{
		return *this = *this * rhs;
	}

	//static
	static Mat2<T> Identity()
	{
		return scale((T)1);
	}

	static Mat2 FlipY()
	{
		return {
			(T)1,	(T)0,
			(T)0,	(T)-1
		};
	}

	static Mat2<T> Scale(T factor)
	{
		return Mat2<T> {
			factor, (T)0,
			(T)0,    factor
		};
	}

	static Mat2<T> Rotation(T theta)
	{
		const auto sinTheta = sin(theta);
		const auto cosTheta = cos(theta);
		return Mat2<T> {
			(T)cosTheta, -(T)sinTheta,	
			(T)sinTheta, (T)cosTheta
		};
	}

	

public:
	//[row][col]
	T cells[2][2];
};
