#pragma once
#include "GameObject.h"
#include "MonsterAnimation.h"

class Monster: public GameObject
{
public:
	void init(eMonsterType type, int power, int hp, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);

	void update(void) override;
	void render(void) override;
	void release(void) override;

	virtual void draw(void) override;
	virtual void animation(void)override;
	virtual void move(void) override;
	virtual void action(void) override;
	
	virtual void hit(int power);
	void changeAction(int changeStat);

	virtual RectF getCanMoveRectF();
	virtual RectF getRelCanMoveRectF();
	virtual void movePatternChange();
	
	Monster() {};
	virtual ~Monster() {};
protected:
	float mSpeed;
	eGameDirection mCurDirection;
private:
	MonsterAnimation* mAni;
	eMonsterType mType;
	bool bIsDie;
	int mCurActionStat;
	int mHp;
	int mPower;
};

class Grub: public Monster {
public:
	void init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
	void release();

	RectF getCanMoveRectF() override;
	RectF getRelCanMoveRectF() override;
	void movePatternChange() override;
	void move() override;
};

class Slime : public Monster {
public:
	void init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
	void release();

	RectF getCanMoveRectF() override;
	RectF getRelCanMoveRectF() override;
	void movePatternChange() override;
	void move() override;
};