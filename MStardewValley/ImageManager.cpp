#include "Stdafx.h"
#include "ImageManager.h"
#include "ImageBase.h"

HRESULT ImageManager::init(void)
{
	return S_OK;
}

void ImageManager::release(void)
{
	this->deleteAll();
}

ImageBase* ImageManager::addImage(string strKey, int width, int height)
{
	ImageBase* img = findImage(strKey, true);

	if (img) return img;

	img = new ImageBase;
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

ImageBase* ImageManager::addImage(string strKey, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	ImageBase* img = findImage(strKey, true);
	if (img) return img;

	img = new ImageBase;
	LOG::d(LOG_IMG_GP_TAG, "== 이미지 생성 시작 : \t\t" + strKey + "\t\t ==");
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		LOG::e(LOG_IMG_GP_TAG, "ㄴ 실패 : " + strKey + " / PATH: " + fileName);
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

ImageBase* ImageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	ImageBase* img = findImage(strKey, true);

	if (img) return img;

	img = new ImageBase;
	LOG::d(LOG_IMG_GP_TAG, "== 이미지 생성 시작 : \t\t" + strKey + "\t\t ==");
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		LOG::e(LOG_IMG_GP_TAG, "ㄴ 실패 : " + strKey + " / PATH: " + fileName);
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

ImageBase* ImageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	ImageBase* img = findImage(strKey, true);

	if (img) return img;//있으면 반환
	img = new ImageBase;
	LOG::d(LOG_IMG_GP_TAG, "== 프레임 이미지 생성 시작 : \t\t" + strKey + "\t\t ==");
	if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))//없으면 생성
	{
		LOG::e(LOG_IMG_GP_TAG, "ㄴ 실패 : " + strKey + " / PATH: " + fileName);
		SAFE_DELETE(img);
		return NULL;
	}
	else

	_mImageList.insert(make_pair(strKey, img));//좀더 심플해짐

	return img;
}

ImageBase* ImageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	ImageBase* img = findImage(strKey, true);

	if (img) return img;//있으면 반환

	img = new ImageBase;
	LOG::d(LOG_IMG_GP_TAG, "== 프레임 이미지 생성 시작 : \t\t" + strKey + "\t\t ==");
	if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor)))//없으면 생성
	{
		LOG::e(LOG_IMG_GP_TAG, "ㄴ 실패 : " + strKey + " / PATH: " + fileName);
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

ImageBase * ImageManager::findImage(string strKey, bool isCreate)
{
	auto key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		return key->second;
	}
	else if(!isCreate) {
		LOG::d(LOG_IMG_BASE_TAG, "이미지 검색 실패 : " + strKey);
	}

	return nullptr;
}

bool ImageManager::deleteImage(string strKey)
{
	auto key = _mImageList.find(strKey);
	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}
	return false;
}

bool ImageManager::deleteAll()
{
	auto iter = _mImageList.begin();//   mapImageIter iter = _mImageList.begin();가 더 알아보기쉽다

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();//있을때만 지워주겠다
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mImageList.clear();
	return true;
}

////////////////////////
// 일반 렌더         //
/////////////////////
void ImageManager::render(string strKey, HDC hdc)
{
	ImageBase* img = findImage(strKey);
	if (img) img->render(hdc);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	ImageBase* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	ImageBase* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}
////////////////////////
// 알파 렌더         //
/////////////////////
void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	ImageBase* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	ImageBase* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	ImageBase* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}
////////////////////////
// 프레임 렌더         //
/////////////////////
void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	ImageBase* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	ImageBase* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	ImageBase* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void ImageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	ImageBase* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
}