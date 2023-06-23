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

public:
	//[row][col]
	T cells[2][2];
};
