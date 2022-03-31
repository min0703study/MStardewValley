#include "Stdafx.h"
#include "Player.h"

void Player::Init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init(id, x, y, width, height, xStandard, yStandard);

	ani = new PlayerAnimation;
	ani->init(PS_IDLE, eGameDirection::GD_DOWN);

	ani->setStatFrameSec(PS_IDLE, 10);
	ani->setStatFrameSec(PS_WALK, 10);
	ani->setStatFrameSec(PS_ATTACK_1, 10);
	ani->setStatFrameSec(PS_ATTACK_2, 10);
}

void Player::update(void)
{
	GameObject::update();
	ani->update();
	this->move();
	this->action();
}

void Player::render(void)
{
	GameObject::render();
	this->animation();
	this->draw();
}

void Player::release(void)
{
}

void Player::draw(void)
{
	ani->render(getMemDc(), getRelRectF());
}

void Player::animation(void)
{
	ani->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void Player::move(void)
{

}

void Player::move(eGameDirection direction)
{
	switch (direction)
	{
		case GD_LEFT:
			offsetX(-PLAYER_MOVE_SPEED);
			CAMERA->offsetX(-PLAYER_MOVE_SPEED);
			break;
		case GD_RIGHT:
			offsetX(+PLAYER_MOVE_SPEED);
			CAMERA->offsetX(+PLAYER_MOVE_SPEED);
			break;
		case GD_UP:
			offsetY(-PLAYER_MOVE_SPEED);
			CAMERA->offsetY(-PLAYER_MOVE_SPEED);
			break;
		case GD_DOWN:
			offsetY(+PLAYER_MOVE_SPEED);
			CAMERA->offsetY(+PLAYER_MOVE_SPEED);
			break;
		default:
			//DO NOTHING!
			break;
	}
}

void Player::action(void)
{
}

RectF Player::getTempMoveBoxRectF(eGameDirection changeDirection)
{
	float x = getAbsRectF().GetLeft();
	float y = getAbsRectF().GetTop() + getHalfHeight();
	switch (changeDirection)
	{
	case GD_LEFT:
		x += -PLAYER_MOVE_SPEED;
		break;
	case GD_RIGHT:
		x += +PLAYER_MOVE_SPEED;
		break;
	case GD_UP:
		y += (-PLAYER_MOVE_SPEED);
		break;
	case GD_DOWN:
		y += (+PLAYER_MOVE_SPEED);
		break;

	default:
		//DO NOTHING!
		break;
	}
	RectF tempMoveRectF = RectFMake(x, y, getWidth(), getHalfHeight());
	return tempMoveRectF;
}

void Player::changeActionStat(ePlayerStat changeStat)
{
	if (mCurActionStat != changeStat) {
		mCurActionStat = changeStat;
		ani->changeStatAni(changeStat);
	}
}

void Player::changeDirection(eGameDirection changeDirection)
{
	if (mCurDirection != changeDirection) {
		mCurDirection = changeDirection;
		ani->changeDirectionAni(changeDirection);
	}
}
