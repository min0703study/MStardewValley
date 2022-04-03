#include "Stdafx.h"
#include "Monster.h"

void Monster::init(string id, eMonsterType type, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init(id, x, y, width, height, xStandard, yStandard);

	ani = new MonsterAnimation;
	ani->init(type);
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
	ani->render(getMemDc(), getRelRectF());
}

void Monster::animation(void)
{
	ani->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void Monster::move(void)
{
}

void Monster::action(void)
{
}
