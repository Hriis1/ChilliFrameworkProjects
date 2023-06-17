#pragma once
#include "Vec2.h"
class RectF
{
public:
	RectF() = default;
	RectF(float left_, float right_, float top_, float bot_);
	RectF(const Vec2<float>& topLeft, const Vec2<float>& botRight);
	RectF(const Vec2<float>& topLeft, float width, float height);

	bool isOverlappingWith(const RectF& other) const;
	bool isContainedBy(const RectF& other) const;

	RectF getExpanded(float offset) const;

	//static
	static RectF fromCenter(const Vec2<float>& center, float halfWidth, float halfHeight)
	{
		const Vec2<float> half(halfWidth, halfHeight);
		return RectF(center - half, center + half);
	}

	//getters
	Vec2<float> getCenter() const { return Vec2<float>((left + right)/2.0f, (top + bot)/2.0f); }
public:
	float left = 0.0f;
	float right = 0.0f;
	float top = 0.0f;
	float bot = 0.0f;
};

