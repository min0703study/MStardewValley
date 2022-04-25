#include "Stdafx.h"
#include "Monster.h"

void Monster::init(eMonsterType type, int power, int hp, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init("", x, y, width, height, xStandard, yStandard);

	mCurDirection = GD_UP;
	mAni = new MonsterAnimation;
	mAni->init(type, &mCurDirection);

	mHp = hp;
	mPower = power;

	bIsDie = false;
}

void Monster::update(void)
{
	this->action();
}

void Monster::render(void)
{
	this->animation();
	this->draw();
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

void Monster::hit(int power)
{
	mHp -= power;
	if (mHp <= 0) {
		//mAni->playAniOneTime(eRockAniStat::RA_CRASH);
		bIsDie = true;
	}
	else {
		LOG::d(to_string(mHp));
		//mAni->playAniOneTime(eRockAniStat::RA_HIT);
	}

}

void Monster::changeAction(int changeStat)
{
	if (mCurActionStat != changeStat) {
		mCurActionStat = changeStat;
		mAni->changeStatAni(changeStat);
	}
}

RectF Monster::getCanMoveRectF()
{
	return RectF();
}

RectF Monster::getRelCanMoveRectF()
{
	return RectF();
}

void Monster::movePatternChange()
{
}

void Monster::release(void)
{
	mAni->release();
	SAFE_DELETE(mAni);
}

/////////////////////////////////////////////////////////////////////////

void Grub::init(float x, float y, eXStandard xStandard, eYStandard yStandard)
{
	Monster::init(MST_GRUB, 10, 100,  x, y, TILE_SIZE, TILE_SIZE, xStandard, yStandard);
	mSpeed = 0.2f;
}

void Grub::release()
{
	Monster::release();
}

RectF Grub::getCanMoveRectF()
{
	float x = getAbsRectF().GetLeft();
	float y = getAbsRectF().GetTop();

	switch (mCurDirection)
	{
	case GD_LEFT:
		x += -mSpeed;
		break;
	case GD_RIGHT:
		x += +mSpeed;
		break;
	case GD_UP:
		y += -mSpeed;
		break;
	case GD_DOWN:
		y += +mSpeed;
		break;

	default:
		//DO NOTHING!
		break;
	}

	RectF tempMoveRectF = RectFMake(x, y, getWidth(), getHeight());
	return tempMoveRectF;
}

RectF Grub::getRelCanMoveRectF()
{
	float x = getRelRectF().GetLeft();
	float y = getRelRectF().GetTop();

	switch (mCurDirection)
	{
	case GD_LEFT:
		x += -mSpeed;
		break;
	case GD_RIGHT:
		x += +mSpeed;
		break;
	case GD_UP:
		y += -mSpeed;
		break;
	case GD_DOWN:
		y += +mSpeed;
		break;

	default:
		//DO NOTHING!
		break;
	}

	RectF tempMoveRectF = RectFMake(x, y, getWidth(), getHeight());
	return tempMoveRectF;
}

void Grub::movePatternChange()
{
	int tempDirection = RND->getInt(eGameDirection::GD_END);
	while (mCurDirection == tempDirection) {
		tempDirection = RND->getInt(eGameDirection::GD_END);
	}

	mCurDirection = (eGameDirection)tempDirection;
}

void Grub::move()
{
	switch (mCurDirection)
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

//////////////////////////////////////////////////////////////////////////

void Slime::init(float x, float y, eXStandard xStandard, eYStandard yStandard)
{
	Monster::init(eMonsterType::MST_SLIME, 20, 150, x, y, TILE_SIZE, TILE_SIZE, xStandard, yStandard);
	mSpeed = 0.2f;
}

RectF Slime::getCanMoveRectF()
{
	float x = getAbsRectF().GetLeft();
	float y = getAbsRectF().GetTop();

	switch (mCurDirection)
	{
	case GD_LEFT:
		x += -mSpeed;
		break;
	case GD_RIGHT:
		x += +mSpeed;
		break;
	case GD_UP:
		y += -mSpeed;
		break;
	case GD_DOWN:
		y += +mSpeed;
		break;

	default:
		//DO NOTHING!
		break;
	}

	RectF tempMoveRectF = RectFMake(x, y, getWidth(), getHeight());
	return tempMoveRectF;
}

RectF Slime::getRelCanMoveRectF()
{
	float x = getRelRectF().GetLeft();
	float y = getRelRectF().GetTop();

	switch (mCurDirection)
	{
	case GD_LEFT:
		x += -mSpeed;
		break;
	case GD_RIGHT:
		x += +mSpeed;
		break;
	case GD_UP:
		y += -mSpeed;
		break;
	case GD_DOWN:
		y += +mSpeed;
		break;

	default:
		//DO NOTHING!
		break;
	}

	RectF tempMoveRectF = RectFMake(x, y, getWidth(), getHeight());
	return tempMoveRectF;
}

void Slime::movePatternChange()
{
	int tempDirection = RND->getInt(eGameDirection::GD_END);
	while (mCurDirection == tempDirection) {
		tempDirection = RND->getInt(eGameDirection::GD_END);
	}

	mCurDirection = (eGameDirection)tempDirection;
}

void Slime::move()
{
	switch (mCurDirection)
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

void Slime::release(void)
{
	Monster::release();
}