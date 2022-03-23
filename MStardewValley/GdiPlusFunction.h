#pragma once
inline Gdiplus::RectF RectFMakeCenter(float x, float y, float width, float height)
{
	REAL realX = x - (width / 2.0f);
	REAL realY = y - (height / 2.0f);

	RectF rcF = RectF(realX, realY, width, height);

	return rcF;
}

inline Gdiplus::RectF RectFMake(float x, float y, float width, float height)
{
	RectF rcF = RectF(x, y, width, height);

	return rcF;
}

inline PointF GetCenterPtF(float x, float y, float width, float height)
{
	REAL realX = x + (width / 2.0f);
	REAL realY = y + (height / 2.0f);

	return PointF(realX, realY);
}