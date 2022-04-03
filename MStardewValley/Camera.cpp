#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init(float x, float y, float width, float height)
{
	mWidth = width;
	mHeight = height;

	mX = x;
	mY = y;

	return S_OK;
}

void Camera::release(void)
{

}
