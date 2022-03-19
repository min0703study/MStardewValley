#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init(float x, float y, float width, float height)
{
	mWidth = width;
	mHeight = height;

	mX = x;
	mY = y;

	mlpRc = new RECT(RectMake(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height)));

	return S_OK;
}

void Camera::release(void)
{
	SAFE_DELETE(mlpRc);
}
