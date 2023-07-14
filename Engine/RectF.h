#pragma once
#include "Vec2.h"
class RectF
{
public:
	enum class RECTF_POSITION_MODE
	{
		SCREEN_POS, COORD_SYSTEM_POS
	};
	RectF() = default;
	RectF(float left_, float right_, float top_, float bot_, RECTF_POSITION_MODE mode = RECTF_POSITION_MODE::SCREEN_POS);
	RectF(const Vec2<float>& topLeft, const Vec2<float>& botRight, RECTF_POSITION_MODE mode = RECTF_POSITION_MODE::SCREEN_POS);
	RectF(const Vec2<float>& topLeft, float width, float height, RECTF_POSITION_MODE mode = RECTF_POSITION_MODE::SCREEN_POS);

	void moveBy(const Vec2<float>& amount);

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
	float getWidth() const { return abs(right - left); }
	float getHeight() const { return abs(top - bot);   }
public:
	float left = 0.0f;
	float right = 0.0f;
	float top = 0.0f;
	float bot = 0.0f;

private:
	RECTF_POSITION_MODE _mode;
};

