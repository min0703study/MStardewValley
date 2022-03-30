#include "Stdafx.h"
#include "Player.h"

void Player::Init(string id, float x, float y, float width, float height)
{
	GameObject::Init(id, x, y, PLAYER_WIDTH, PLAYER_HEIGHT);

	ani = new PlayerAnimation;
	ani->init();
	ani->setAniInfo(Player::eActionStat::WALK, 10, 5, 15);
	ani->setAniInfo(Player::eActionStat::WALK, 10, 5, 15);
	ani->setAniInfo(Player::eActionStat::ATTACK, 10, 5, 15);
	
	ani->changeAni(eGameDirection::GD_RIGHT, WALK);
}

void Player::update(void)
{
	move();
	action();
}

void Player::render(void)
{
	this->animation();
	this->draw();
}

void Player::release(void)
{
}

void Player::draw(void)
{
	ani->render(getMemDc(), CAMERA_X / 2, CAMERA_Y / 2);
}

void Player::animation(void)
{
	ani->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void Player::move(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		offsetX(+PLAYER_MOVE_SPEED);
		CAMERA->offSetX(+PLAYER_MOVE_SPEED);
		ani->changeAni(GD_RIGHT, WALK);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		offsetX(-PLAYER_MOVE_SPEED);
		CAMERA->offSetX(-PLAYER_MOVE_SPEED);
		ani->changeAni(GD_LEFT, WALK);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		offsetY(-PLAYER_MOVE_SPEED);
		CAMERA->offSetY(-PLAYER_MOVE_SPEED);
		ani->changeAni(GD_UP, WALK);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		offsetY(+PLAYER_MOVE_SPEED);
		CAMERA->offSetY(+PLAYER_MOVE_SPEED);
		ani->changeAni(GD_DOWN, WALK);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		ani->changeAni(GD_DOWN, ATTACK);
	}
}

void Player::action(void)
{
	ani->update();
}
