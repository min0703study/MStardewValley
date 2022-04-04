#include "Stdafx.h"
#include "GameObject.h"
#include "Camera.h"

void GameObject::Init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	switch (xStandard) {
	case XS_LEFT:
		x = x + (width / 2.0f);
		break;
	case XS_RIGHT:
		x = x - (width / 2.0f);
		break;
	case XS_CENTER:
		break;
	}

	switch (yStandard) {
	case YS_TOP:
		y = y + (height / 2.0f);
		break;
	case YS_BOTTOM:
		y = y - (height / 2.0f);
		break;
	case YS_CENTER:
		break;
	}

	mCenterX = x;
	mCenterY = y;

	mWidth = width;
	mHeight = height;

	mRECT = RectMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);

	mId = id;
}

void GameObject::update(void)
{
}

void GameObject::render(void)
{
#if DEBUG_MODE
	//GDIPLUSMANAGER->drawRectF(getMemDc(), getRelRectF());
#endif
}

void GameObject::release(void)
{
}

void GameObject::draw()
{
}

void GameObject::animation()
{
}

void GameObject::move()
{
}

void GameObject::action()
{
}
