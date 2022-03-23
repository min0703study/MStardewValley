#include "Stdafx.h"
#include "GameObject.h"
#include "Camera.h"

void GameObject::Init(string id, float x, float y, float width, float height)
{
	mWidth = width;
	mHeight = height;

	mX = x;
	mY = y;

	mRc = RECT_MAKE_FUNCTION;
}

void GameObject::update(void)
{
}

void GameObject::render(void)
{
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
