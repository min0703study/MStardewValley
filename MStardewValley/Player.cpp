#include "Stdafx.h"
#include "Player.h"

void Player::Init(string id, float x, float y, float width, float height)
{
	GameObject::Init(id, x, y, width, height);
}

void Player::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)){
		CAMERA->offSetX(+4.0f);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		CAMERA->offSetX(-4.0f);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		CAMERA->offSetY(-4.0f);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		CAMERA->offSetY(+4.0f);
	}
}

void Player::render(void)
{
}

void Player::release(void)
{
}

void Player::draw(void)
{
}

void Player::animation(void)
{
}

void Player::move(void)
{
}

void Player::action(void)
{
}
