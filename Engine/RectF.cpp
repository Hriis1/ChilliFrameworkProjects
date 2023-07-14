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

void RectF::moveBy(const Vec2<float>& amount)
{
	left += amount._x;
	right += amount._x;
	top += amount._y;
	bot += amount._y;
}

bool RectF::isOverlappingWith(const RectF& other) const
{
	return right >= other.left && left <= other.right && ((bot >=other.top && top <= other.bot) || (bot <= other.top && top >= other.bot)); //this handles both Y cases seperetrly
}

bool RectF::isContainedBy(const RectF& other, YMODE yMode) const
{
	if(yMode == YMODE::INVERTED)
		return left >= other.left && right <= other.right && top >= other.top && bot <= other.bot; 
	else
		return left >= other.left && right <= other.right && top <= other.top && bot >= other.bot;
}

RectF RectF::getExpanded(float offset, YMODE yMode) const
{
	if (yMode == YMODE::INVERTED)
		return RectF(left - offset, right + offset, top - offset, bot + offset);
	else
		return RectF(left - offset, right + offset, top + offset, bot - offset);
}
