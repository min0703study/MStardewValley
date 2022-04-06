#include "Stdafx.h"
#include "Monster.h"

void Monster::init(string id, eMonsterType type, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init(id, x, y, width, height, xStandard, yStandard);
	mAni = new MonsterAnimation;
	mAni->init(type);
}

void Monster::update(void)
{
	this->action();
	this->move();
}

void Monster::render(void)
{
	this->animation();
	this->draw();
}

void Monster::release(void)
{
}

void Monster::draw(void)
{
	mAni->render(getMemDc(), getRelRectF());
}

void Monster::animation(void)
{
	mAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void Monster::move(void)
{
}

void Monster::action(void)
{
}

void Monster::changeAction(int changeStat)
{
	if (mCurActionStat != changeStat) {
		mCurActionStat = changeStat;
		mAni->changeStatAni(changeStat);
	}
}

void Monster::move(eGameDirection direction)
{
	switch (direction)
	{
	case GD_LEFT:
		offsetX(-mSpeed);
		break;
	case GD_RIGHT:
		offsetX(+mSpeed);
		break;
	case GD_UP:
		offsetY(-mSpeed);
		break;
	case GD_DOWN:
		offsetY(+mSpeed);
		break;
	default:
		//DO NOTHING!
		break;
	}
}

///////////////////////////////////////////////

void Grub::init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	Monster::init(id,eMonsterType::MST_GRUB, x, y, width, height, xStandard, yStandard);
	mSpeed = 0.5f;
}