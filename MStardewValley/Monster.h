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

	void draw(void) override;
	void animation(void)override;
	void move(void) override;
	void action(void) override;

private:
	MonsterAnimation* ani;
	eMonsterType mType;
};