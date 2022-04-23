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
	void init(float x, float y, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP);
	void release();

	RectF getCanMoveRectF() override;
	RectF getRelCanMoveRectF() override;
	void movePatternChange() override;
	void move() override;
};

class Slime : public Monster {
public:
	void init(float x, float y, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP);
	void release();

	RectF getCanMoveRectF() override;
	RectF getRelCanMoveRectF() override;
	void movePatternChange() override;
	void move() override;
};

class MonsterFactory {
public:
	static Monster* getMonster(eMonsterType type, float x, float y) {
		switch (type) {
		case MST_GRUB: {
			Grub* monster = new Grub();
			monster->init(x, y);
			return monster;
		}

		case MST_SLIME: {
			Slime* monster = new Slime();
			monster->init(x, y);
			return monster;
		}
		}
	}

};
