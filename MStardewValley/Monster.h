#pragma once
#include "GameObject.h"
#include "MonsterAnimation.h"

class Monster: public GameObject
{
public:
	void init(string id, eMonsterType type, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);

	void update(void) override;
	void render(void) override;
	void release(void) override;

	virtual void draw(void) override;
	virtual void animation(void)override;
	virtual void move(void);
	virtual void action(void) override;

	void move(eGameDirection direction);
	void changeAction(int changeStat);

	virtual RectF getTempMoveAbsRectF();

	Monster() {};
	virtual ~Monster() {};
protected:
	float mSpeed;
	eGameDirection mCurDirection;
private:
	MonsterAnimation* mAni;
	eMonsterType mType;
	int mCurActionStat;
};

class Grub: public Monster {
public:
	void init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
	RectF getTempMoveAbsRectF() override;
};