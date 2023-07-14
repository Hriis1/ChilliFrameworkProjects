#pragma once
#include "Vec2.h"
class RectF
{
public:
	enum class YMODE
	{
		INVERTED, STANDARD
	};

	RectF() = default;
	RectF(float left_, float right_, float top_, float bot_);
	RectF(const Vec2<float>& topLeft, const Vec2<float>& botRight);
	RectF(const Vec2<float>& topLeft, float width, float height); //Only used for rects which Y coordinate goes up as the rect goes down

	void moveBy(const Vec2<float>& amount);

	bool isOverlappingWith(const RectF& other) const;
	bool isContainedBy(const RectF& other, YMODE yMode = YMODE::INVERTED) const;

	RectF getExpanded(float offset, YMODE yMode = YMODE::INVERTED) const;

	//static
	static RectF fromCenter(const Vec2<float>& center, float halfWidth, float halfHeight, YMODE yMode = YMODE::INVERTED)
	{
		const Vec2<float> half(halfWidth, halfHeight);

		if (yMode == YMODE::INVERTED)
			return RectF(center - half, center + half);
		else
			return RectF(Vec2<float>(center._x - half._x, center._y + half._y), Vec2<float>(center._x + half._x, center._y - half._y));
	}

	//getters
	Vec2<float> getCenter() const { return Vec2<float>((left + right)/2.0f, (top + bot)/2.0f); }
	float getWidth() const { return abs(right - left); }
	float getHeight() const { return abs(top - bot);   }
public:
	float left = 0.0f;
	float right = 0.0f;
	float top = 0.0f;
	float bot = 0.0f;
};

