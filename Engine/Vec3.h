#pragma once

#include <cmath>

#include "Vec2.h"

//This class always has the _w component set to 1 - it should only be used for 2d, it isn't actually a vector with 3 modifiable components
template<typename T>
class Vec3
{
public:
	Vec3()
	{
	}

	Vec3(T x, T y)
		: _x(x), _y(y)
	{
	}
	Vec3(const Vec3& other)
	{
		_x = other._x;
		_y = other._y;
	}

	explicit Vec3(const Vec2<T>& v2)
		: Vec3(v2._x, v2._y)
	{

	}

	template<typename Type>
	explicit Vec3(const Vec3<Type>& other)
		: _x((T)other._x), _y((T)other._y)
	{

	}

	~Vec3()
	{
	}

	Vec3& Rotate(T angle)
	{
		const T cosTheta = cos(angle);
		const T sinTheta = sin(angle);

		const T newX = _x * cosTheta - _y * sinTheta;
		_y = _x * sinTheta + _y * cosTheta;
		_x = newX;

		return *this;
	}

	Vec3& Rotate(T sinTheta, T cosTheta)
	{
		const T newX = _x * cosTheta - _y * sinTheta;
		_y = _x * sinTheta + _y * cosTheta;
		_x = newX;

		return *this;
	}

	Vec3& normalize()
	{
		*this = getNormalized();
		return *this;
	}

	T dot(const Vec3<T>& other) const
	{
		return _x * other._x + _y * other._y;
	}

	//getters
	T getLenghtSqrt() const { return _x * _x + _y * _y; }
	T getLenght() const { return  (T)std::sqrt(getLenghtSqrt()); }

	Vec3 getNormalized() const {
		const T len = getLenght();
		if (len == (T)0)
			return *this;

		return *this * ((T)1 / len);
	}

	Vec3 getRotated(T angle) const
	{
		return Vec3<T>(*this).Rotate(angle);
	}

	Vec3 getRotatedPositive90Degrees() const
	{
		return Vec3<T> {-_y, _x};
	}
	Vec3 getRotatedNegative90Degrees() const
	{
		return Vec3<T> {_y, -_x};
	}

	//operators
	bool operator==(const Vec3& other) const
	{
		return _x == other._x && _y == other._y && _w == other._w;
	}

	bool operator!=(const Vec3& other) const
	{
		return !(operator==(other));
	}



	Vec3 operator+(const Vec3& other) const
	{
		return Vec3(_x + other._x, _y + other._y);
	}

	Vec3& operator+=(const Vec3& other)
	{
		*this = *this + other;
		return *this;
	}

	Vec3 operator-(const Vec3& other) const
	{
		return Vec3(_x - other._x, _y - other._y);
	}

	Vec3 operator-() const
	{
		return Vec3(-_x, -_y);
	}

	Vec3& operator=(const Vec3& other)
	{
		if (this != &other)
		{
			_x = other._x;
			_y = other._y;
			_w = other._w;
		}
		return *this;
	}

	Vec3& operator-=(const Vec3& other)
	{
		*this = *this - other;
		return *this;
	}

	Vec3 operator*(T val) const
	{
		return Vec3(_x * val, _y * val);
	}

	Vec3& operator*=(T val)
	{
		*this = *this * val;
		return *this;
	}

	Vec3 operator/(T val) const
	{
		return Vec3(_x / val, _y / val);
	}

	Vec3& operator/=(T val)
	{
		*this = *this / val;
		return *this;
	}

	explicit operator Vec2<T>() const
	{
		return Vec2<T>(_x, _y);
	}
public:
	T _x = 0;
	T _y = 0;
	T _w = (T)1;
};
