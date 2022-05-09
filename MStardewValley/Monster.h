#pragma once
#include "GameObject.h"
#include "MonsterAnimation.h"

class Monster: public GameObject
{
public:
	typedef struct tagMonsterItem {
		string ItemId;
		int Count;
		tagMonsterItem(string itemId, int count) : ItemId(itemId), Count(count) {}
		tagMonsterItem() : ItemId(""), Count(-1) {}
	} MonsterItem;
public:
	void init(eMonsterType type, int power, int hp, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
	virtual void update(void);
	virtual void render(void);
	virtual void release(void);

	virtual void draw(void) override;
	virtual void animation(void)override;
	virtual void move(void) override;
	virtual void action(void) override;
	
	virtual void hit(int power);
	virtual int attack();

	void changeActionStat(eMonsterStat changeStat);
	void setDropItem(MonsterItem item) {mMonsterItem = item;};

	virtual RectF getCanMoveRectF();
	virtual void movePatternChange();

	bool isDie() { return bIsDie && !(mAni->isPlaying()); };

	inline MonsterItem getMonsterItem() { 
		bIsDropItem = true;
		return mMonsterItem; 
	};
	
	Monster() {};
	virtual ~Monster() {};
protected:
	float mSpeed;

	eGameDirection mCurDirection;
	eGameDirection mHitDirection;

	eMonsterStat mStat;
private:
	MonsterAnimation* mAni;
	MonsterItem mMonsterItem;

	eMonsterType mType;
	
	bool mAutoMoveMode;
	bool bIsDie;
	bool bIsDropItem;
	int mHp;
	int mPower;
};

class Grub: public Monster {
public:
	void init(float x, float y, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP);
	void release();

	RectF getCanMoveRectF() override;
	void movePatternChange() override;
	void move() override;
};

class Slime : public Monster {
public:
	void init(float x, float y, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP);
	void release();

	RectF getCanMoveRectF() override;
	void movePatternChange() override;
	void move() override;
	void action() override;
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
