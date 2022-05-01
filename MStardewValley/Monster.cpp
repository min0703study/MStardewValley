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
	if (mAni->isOneTimeAniOver()) {
		if (!bIsDie) {
			mAni->playAniLoop(eMonsterStat::MSS_IDLE);
			changeActionStat(eMonsterStat::MSS_IDLE);
		}
	}

	RectF rcF;
	getAbsRectF().GetBounds(&rcF);
	rcF.Inflate(getWidth(), getHeight());

	if (rcF.Intersect(PLAYER->getAbsRectF())) {
		mStat = MSS_TO_PLAYER;
	}
	else {
		mStat = MSS_IDLE;
	}
}

void Monster::hit(int power)
{
	mHp -= power;
	if (mHp <= 0) {
		bIsDie = true;
		mAni->playAniOneTime(eMonsterStat::MSS_HIT);
	}
	else {
		mAni->playAniOneTime(eMonsterStat::MSS_HIT);
		changeActionStat(eMonsterStat::MSS_HIT);
		mHitDirection = PLAYER->getDirection();
	}
}

int Monster::attack()
{
	return mPower;
}

void Monster::changeActionStat(eMonsterStat changeStat)
{
	if (mStat != changeStat) {
		mStat = changeStat;
	}
}

RectF Monster::getCanMoveRectF()
{
	return RectF();
}

void Monster::movePatternChange()
{
}

void Monster::release(void)
{
	//mAni->release();
	//SAFE_DELETE(mAni);
}

/////////////////////////////////////////////////////////////////////////

void Grub::init(float x, float y, eXStandard xStandard, eYStandard yStandard)
{
	Monster::init(MST_GRUB, 10, 20,  x, y, TILE_SIZE, TILE_SIZE, xStandard, yStandard);
	mSpeed = 0.2f;
}

RectF Grub::getCanMoveRectF()
{
	float x = getAbsRectF().GetLeft();
	float y = getAbsRectF().GetTop();

	if (mStat == eMonsterStat::MSS_IDLE) {
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
	}
	else if(mStat == eMonsterStat::MSS_HIT) {
		switch (mHitDirection)
		{
		case GD_LEFT:
			x += -1;
			break;
		case GD_RIGHT:
			x += +1;
			break;
		case GD_UP:
			y += -1;
			break;
		case GD_DOWN:
			y += +1;
			break;

		default:
			//DO NOTHING!
			break;
		}
	}
	else if (mStat == eMonsterStat::MSS_TO_PLAYER) {
		x += (3.0f * (PLAYER->getAbsX() > getAbsX() ? 1 : -1));
		y += (3.0f *  (PLAYER->getAbsY() > getAbsY() ? 1 : -1));
	}

	RectF tempMoveRectF = RectFMake(x, y, getWidth(), getHeight());
	return tempMoveRectF;
}

void Grub::movePatternChange()
{
	if (mStat == eMonsterStat::MSS_IDLE) {
		int tempDirection = RND->getInt(eGameDirection::GD_END);
		while (mCurDirection == tempDirection) {
			tempDirection = RND->getInt(eGameDirection::GD_END);
		}

		mCurDirection = (eGameDirection)tempDirection;
	} 
}

void Grub::release()
{
	Monster::release();
}

void Grub::move()
{
	if (mStat == eMonsterStat::MSS_IDLE) {
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
	else if(mStat == eMonsterStat::MSS_HIT) {
		switch (mHitDirection)
		{
		case GD_LEFT:
			offsetX(-1);
			break;
		case GD_RIGHT:
			offsetX(+1);
			break;
		case GD_UP:
			offsetY(-1);
			break;
		case GD_DOWN:
			offsetY(+1);
			break;

		default:
			//DO NOTHING!
			break;
		}
	}
	else if (mStat == eMonsterStat::MSS_TO_PLAYER) {
		float x = (mSpeed * (PLAYER->getAbsX() >getAbsX() ? 1 : -1));
		float y = (mSpeed *  (PLAYER->getAbsY() > getAbsY() ? 1 : -1));
		
		offsetX(x);
		offsetY(y);
	}
}

//////////////////////////////////////////////////////////////////////////

void Slime::init(float x, float y, eXStandard xStandard, eYStandard yStandard)
{
	Monster::init(eMonsterType::MST_SLIME, 20, 20, x, y, TILE_SIZE, TILE_SIZE, xStandard, yStandard);
	mSpeed = 0.2f;
}

RectF Slime::getCanMoveRectF()
{
	float x = getAbsRectF().GetLeft();
	float y = getAbsRectF().GetTop();

	if (mStat == eMonsterStat::MSS_IDLE) {
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
	}
	else {
		switch (mHitDirection)
		{
		case GD_LEFT:
			x += -1;
			break;
		case GD_RIGHT:
			x += +1;
			break;
		case GD_UP:
			y += -1;
			break;
		case GD_DOWN:
			y += +1;
			break;

		default:
			//DO NOTHING!
			break;
		}
	}


	RectF tempMoveRectF = RectFMake(x, y, getWidth(), getHeight());
	return tempMoveRectF;
}

void Slime::movePatternChange()
{
	if (mStat == eMonsterStat::MSS_IDLE) {
		int tempDirection = RND->getInt(eGameDirection::GD_END);
		while (mCurDirection == tempDirection) {
			tempDirection = RND->getInt(eGameDirection::GD_END);
		}

		mCurDirection = (eGameDirection)tempDirection;
	}
}

void Slime::move()
{
	if (mStat == eMonsterStat::MSS_IDLE) {
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
	else {
		switch (mHitDirection)
		{
		case GD_LEFT:
			offsetX(-1);
			break;
		case GD_RIGHT:
			offsetX(+1);
			break;
		case GD_UP:
			offsetY(-1);
			break;
		case GD_DOWN:
			offsetY(+1);
			break;

		default:
			//DO NOTHING!
			break;
		}
	}
}

void Slime::release(void)
{
	Monster::release();
}