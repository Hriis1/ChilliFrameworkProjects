#include "RectF.h"

RectF::RectF(float left_, float right_, float top_, float bot_)
	: left(left_), right(right_), top(top_), bot(bot_)
{
}

RectF::RectF(const Vec2<float>& topLeft, const Vec2<float>& botRight)
	: RectF(topLeft._x, botRight._x, topLeft._y, botRight._y)
{
}

RectF::RectF(const Vec2<float>& topLeft, float width, float height)
	: RectF(topLeft._x, topLeft._x + width, topLeft._y, topLeft._y + height)
{
}

bool RectF::isOverlappingWith(const RectF& other) const
{
	return right >= other.left && left <= other.right && bot >=other.top && top <= other.bot;
}

bool RectF::isContainedBy(const RectF& other) const
{
	return left >= other.left && right <= other.right && top >= other.top && bot <= other.bot;
}

RectF RectF::getExpanded(float offset) const
{
	return RectF(left - offset, right + offset, top - offset, bot + offset);
}
