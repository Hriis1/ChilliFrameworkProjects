#pragma once
#include <cmath>

#include "Vec2.h"

template<typename T>
auto sq(T x)
{
	return x * x;
}

template<typename T>
T pointLineDistance(const Vec2<T>& linePoint0, const Vec2<float>& linePoint1, const Vec2<T>& q)
{
	const T a = linePoint0._y - linePoint1._y;
	const T a = linePoint1._x - linePoint0._x;
	const T c = linePoint0._x * linePoint1._y - p1._x * p0._y;

	return std::abs(a * q._x + b * q._y + c) / std::sqrt(sq(a) + sq(b));
}
