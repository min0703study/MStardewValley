#pragma once

enum POSITION {
	TOP,
	BOTTOM, 
	RIGHT, 
	LEFT
};

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectMakeCenter(float x, float y, float width, float height)
{
	long left = FLOAT_TO_LONG(x - width / 2.0f);
	long top = FLOAT_TO_LONG(y - height / 2.0f);
	long right = FLOAT_TO_LONG(x + width / 2.0f);
	long bottom = FLOAT_TO_LONG(y + height / 2.0f);

	RECT rc = { left, top, right, bottom };

	return rc;
}


inline RECT RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
	return { x, y, x + width, y + height };
}


inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline void RectangleMake(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline void SetCenter(RECT& baseObject, RECT& setObject,int setObjectSizeW, int setObjectSizeH, POSITION position) {
	int baseObjectSizeW = baseObject.right - baseObject.left;
	int baseObjectSizeH = baseObject.bottom - baseObject.top;
	int baseObjectCenterX = baseObject.left + (baseObjectSizeW/2);
	int baseObjectCenterY = baseObject.top + (baseObjectSizeH/2);

	switch (position) {
	//위
	case TOP:
		setObject.left = baseObjectCenterX - (setObjectSizeW / 2);
		setObject.right = setObject.left + setObjectSizeW;
		setObject.top = baseObject.top - setObjectSizeH;
		setObject.bottom = baseObject.top;
		break;
	//왼쪽
	case LEFT:
		setObject.left = baseObject.right;
		setObject.right = baseObject.right + setObjectSizeW;
		setObject.top = baseObjectCenterY - (setObjectSizeH / 2);
		setObject.bottom = setObject.top + setObjectSizeH;
		break;
	//오른쪽
	case RIGHT:
		setObject.left = baseObject.left - setObjectSizeH;
		setObject.right = baseObject.left;
		setObject.top = baseObjectCenterY - (setObjectSizeH / 2);
		setObject.bottom = setObject.top + setObjectSizeH;
		break;
	}
}

inline RECT RectMakeWindowCenter(int windowWidth, int windowHeight, int width, int height)
{
	int left = (windowWidth / 2) - (width / 2);
	int top = (windowHeight / 2) - (height / 2);
	int right = (windowWidth / 2) + (width / 2);
	int bottom = (windowHeight / 2) + (height / 2);

	return { left, top, right, bottom };
}

inline RECT RectMakeWindowBottomCenter(int windowWidth, int windowHeight, int width, int height)
{
	int left = (windowWidth / 2) - (width / 2);
	int top = windowHeight - height - 40;
	int right = (windowWidth / 2) + (width / 2);
	int bottom = windowHeight - 40;

	return { left, top, right, bottom };
}

inline RECT RectMakeWindowCenter(int windowWidth, int windowHeight, int width, int height, int position)
{
	RECT returnRect;

	switch (position) {
	case 1:
		returnRect.left = 0;
		returnRect.top = (windowHeight / 2) - (height / 2);
		returnRect.right = width;
		returnRect.bottom = returnRect.top + height;
		break;
	case 2:
		returnRect.left = windowWidth - width - 15;
		returnRect.top = (windowHeight / 2) - (height / 2);
		returnRect.right = windowWidth - 15;
		returnRect.bottom = returnRect.top + height;
		break;
	}
	return returnRect;
}

inline RECT CollisionAreaResizing(RECT &rcDest, int width, int height)
{
	RECT rc = { rcDest.left + width / 2, rcDest.top + height / 2, rcDest.right - width / 2, rcDest.bottom - height / 2 };
	return rc;
}
