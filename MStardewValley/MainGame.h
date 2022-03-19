#pragma once
#include "GameNode.h"

class MainGame: public GameNode
{
private:
	GameUI* mCursor;
public:
	HRESULT init(void);
	virtual void update(void);
	virtual void release(void);
	virtual void render(void);
};

