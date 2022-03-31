#include "Stdafx.h"
#include "Player.h"

void Player::Init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init(id, x, y, width, height, xStandard, yStandard);

	ani = new PlayerAnimation;
	ani->init(PS_WALK, eGameDirection::GD_RIGHT);

	ani->setStatFrameSec(PS_IDLE, 10);
	ani->setStatFrameSec(PS_WALK, 10);
	ani->setStatFrameSec(PS_ATTACK_1, 10);
}

void Player::update(void)
{
	this->move();
	this->action();
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
	ani->render(getMemDc(), getAbsRectF().GetLeft(), getAbsRectF().GetTop());
}

void Player::animation(void)
{
	ani->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void Player::move(void)
{
	if (KEYMANAGER->isStayTempKeyDown(VK_LEFT)) {
		if (KEYMANAGER->isOnceTempKeyDown(VK_LEFT)) {
			changeDirection(GD_LEFT);
			changeActionStat(PS_WALK);
		}
	}

	if (KEYMANAGER->isStayTempKeyDown(VK_RIGHT)) {
		if (KEYMANAGER->isOnceTempKeyDown(VK_RIGHT)) {
			changeDirection(GD_RIGHT);
			changeActionStat(PS_WALK);
		}
	}

	if (KEYMANAGER->isStayTempKeyDown(VK_UP)) {
		if (KEYMANAGER->isOnceTempKeyDown(VK_UP)) {
			if (KEYMANAGER->isStayTempKeyDown(VK_LEFT) || 
				KEYMANAGER->isStayTempKeyDown(VK_RIGHT)) {

			}
			else {
				changeDirection(GD_UP);
			}

			changeActionStat(PS_WALK);
		}
	}

	if (KEYMANAGER->isStayTempKeyDown(VK_DOWN)) {
		if (KEYMANAGER->isOnceTempKeyDown(VK_DOWN)) {
			if (KEYMANAGER->isStayTempKeyDown(VK_LEFT) ||
				KEYMANAGER->isStayTempKeyDown(VK_RIGHT)) {

			}
			else {
				changeDirection(GD_DOWN);
			}
			changeActionStat(PS_WALK);
		}
	}

	if (KEYMANAGER->isOnceTempKeyUp(VK_LEFT)) {
		changeActionStat(PS_IDLE);
	}


	if (KEYMANAGER->isOnceTempKeyUp(VK_RIGHT)) {
		changeActionStat(PS_IDLE);
	}


	if (KEYMANAGER->isOnceTempKeyUp(VK_DOWN)) {
		changeActionStat(PS_IDLE);
	}


	if (KEYMANAGER->isOnceTempKeyUp(VK_UP)) {
		changeActionStat(PS_IDLE);
	}

	if (KEYMANAGER->isOnceTempKeyDown(VK_LBUTTON)) {
		changeActionStat(PS_ATTACK_1);
	}
}

void Player::move(eGameDirection direction)
{
	switch (direction)
	{
		case GD_LEFT:
			offsetX(-PLAYER_MOVE_SPEED);
			break;
		case GD_RIGHT:
			offsetX(+PLAYER_MOVE_SPEED);
			break;
		case GD_UP:
			offsetY(-PLAYER_MOVE_SPEED);
			break;
		case GD_DOWN:
			offsetY(+PLAYER_MOVE_SPEED);
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
