#pragma once
#include "SingletonBase.h"
#include "GameObject.h"
#include "PlayerAnimation.h"
#include "PlayerSprite.h"

class Player: public GameObject, public SingletonBase<Player>
{
public:
	enum eActionStat {
		IDLE,
		WALK,
		ATTACK
	};

	void Init(string id, float x, float y, float width, float height);
	
	virtual void update(void);
	virtual void render(void);
	virtual void release(void);

	virtual void draw(void);
	virtual void animation(void);
	virtual void move(void);
	virtual void action(void);

private:
	PlayerAnimation* ani;
};

