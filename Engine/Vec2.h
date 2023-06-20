#pragma once
#include <cmath>

template<typename T>
class Vec2
{
public:
	Vec2()
	{
	}

	Vec2(T x, T y)
		: _x(x), _y(y)
	{
	}
	Vec2(const Vec2& other)
	{
		_x = other._x;
		_y = other._y;
	}

	template<typename Type>
	explicit Vec2(const Vec2<Type>& other)
		: _x((T)other._x), _y((T)other._y)
	{

	}

	~Vec2()
	{
	}

	Vec2& normalize()
	{
		*this = getNormalized();
		return *this;
	}

	T dot(Vec2<T>& other) const
	{
		return _x * other._x + _y * other._y;
	}

	//getters
	T getLenghtSqrt() const { return _x * _x + _y * _y; }
	T getLenght() const { return  (T)std::sqrt(getLenghtSqrt()); }

	Vec2 getNormalized() const {
		const T len = getLenght();
		if (len == (T)0)
			return *this;

		return *this * ((T)1/ len);
	}

	//operators
	bool operator==(const Vec2& other) const
	{
		return _x == other._x && _y == other._y;
	}

	bool operator!=(const Vec2& other) const
	{
		return !(operator==(other));
	}



	Vec2 operator+(const Vec2& other) const
	{
		return Vec2(_x + other._x, _y + other._y);
	}

	Vec2& operator+=(const Vec2& other)
	{
		*this = *this + other;
		return *this;
	}

	Vec2 operator-(const Vec2& other) const
	{
		return Vec2(_x - other._x, _y - other._y);
	}

	Vec2 operator-() const
	{
		return Vec2(-_x, -_y);
	}

	Vec2& operator=(const Vec2& other)
	{
		if (this != &other)
		{
			_x = other._x;
			_y = other._y;
		}
		return *this;
	}

	Vec2& operator-=(const Vec2& other)
	{
		*this = *this - other;
		return *this;
	}

	Vec2 operator*(T val) const
	{
		return Vec2(_x * val, _y * val);
	}

	Vec2& operator*=(T val)
	{
		*this = *this * val;
		return *this;
	}

	Vec2 operator/(T val) const
	{
		return Vec2(_x / val, _y / val);
	}

	Vec2& operator/=(T val)
	{
		*this = *this / val;
		return *this;
	}
public:
	T _x = 0;
	T _y = 0;
};

