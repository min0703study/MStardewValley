#pragma once
#include "SingletonBase.h"
class AnimationManager: public SingletonBase<AnimationManager>
{
private:
	typedef map<int, ImageBase*> mapImageList;
	typedef map<int, ImageBase*>::iterator mapImageIter;;
};

