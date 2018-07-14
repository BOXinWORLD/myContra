#include "hero.h"

bool Hero::init()
{
	Sprite::init();
	isLeft = false;
	isDown = false;
	isJump = false;
	keepLeft = false;
	keepRight = false;

	idle();
	listenKeyboardEvent();

	return true;
}

void Hero::update(float dt)
{
	if (keepLeft&&keepRight && isDown==false&&isJump==false)idle();
	if (keepLeft&& keepRight == false&& isDown == false)runLeft(dt);
	if (keepRight&& keepLeft == false&& isDown == false)runRight(dt);
	if (isJump) {
		setPositionY(getPositionY() + vy);
		vy += g;
		if (getPositionY() < oy) {
			setPositionY(oy);
			isJump = false;
			sp->stopAction(jumpAction);
			if ((keepLeft == true && keepRight == false) || (keepLeft == false && keepRight == true)) {
				isLeft = keepLeft;
				sp->setScaleX(isLeft ? 1 : -1);
				runAnimation();
			}
			else idle();
		}
	}
}

void Hero::idle()
{
	this->removeAllChildren();
	sp = Sprite::create("tex\\hero\\run_left0004.png");
	sp->setAnchorPoint(Vec2(0.61f, 0.0f));//锚点定脚下 用于左右翻转
	sp->setScaleX(isLeft ? 1 : -1);
	this->addChild(sp);

	

}

void Hero::down()
{
	this->removeAllChildren();
	sp = Sprite::create("tex\\hero\\down.png");
	sp->setAnchorPoint(Vec2(0.6f, 0.0f));//锚点定脚下 用于左右翻转
	sp->setScaleX(isLeft ? 1 : -1);
	this->addChild(sp);
}

void Hero::jump()
{
	sp->stopAllActions();
	Vector<SpriteFrame*>allFrames;
	char txt[100] = {};
	for (int i = 1; i < 4; i++) {
		sprintf_s(txt, "tex\\hero\\jump000%d.png", i);
		SpriteFrame *sf = SpriteFrame::create(txt, Rect(0, 0, 46, 46));
		allFrames.pushBack(sf);
	}

	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1f);
	jumpAction= sp->runAction(RepeatForever::create(Animate::create(ani)));
}

void Hero::runAnimation()
{
	sp->stopAllActions();
	Vector<SpriteFrame*>allFrames;
	char txt[100] = {};
	for (int i = 2; i < 5; i++) {
		sprintf_s(txt, "tex\\hero\\run_left000%d.png", i);
		SpriteFrame *sf = SpriteFrame::create(txt, Rect(0, 0, 55, 55));
		allFrames.pushBack(sf);
	}

	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1f);
	run = sp->runAction(RepeatForever::create(Animate::create(ani)));
	
}

void Hero::runLeft(float dt)
{
	float d = dt * 200;
	setPositionX(getPositionX() - d);
}

void Hero::runRight(float dt)
{
	float d = dt * 200;
	setPositionX(getPositionX() + d);
}

void Hero::listenKeyboardEvent()
{
	this->_eventDispatcher->removeAllEventListeners();

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed2, this);
	listener->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased2, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Hero::onKeyPressed2(EventKeyboard::KeyCode code, Event * evt)
{
	switch ((int)code)
	{
	case 26://left
		keepLeft = true;
		isLeft = true;
		if (isDown == true)break;
		if (isJump == true)break;
		runAnimation();
		
		break;
	case 27://right
		keepRight = true;
		isLeft = false;		
		if (isDown == true)break;
		if (isJump == true)break;
		runAnimation();
		
		break;
	case 29://down
		if (isJump == true)break;
		isDown = true;
		down();
		break;
	case 28://jump
		if (!isJump && !isDown)
		{
			jump();
			oy = getPositionY();
			vy = 6;
			g = -0.2f;
			isJump = true;
		}
		break;
	default:
		break;
	}
	sp->setScaleX(isLeft ? 1 : -1);
}

void Hero::onKeyReleased2(EventKeyboard::KeyCode code, Event * evt)
{
	switch ((int)code)
	{
	case 26://left
		keepLeft = false;
		if (!isJump) {
			if (keepRight == true) {
				isLeft = false;
				sp->setScaleX(isLeft ? 1 : -1);
				if (isDown == true)break;
				runAnimation();
			}
			if (isDown == true)break;
			if (keepRight == false) {
				sp->stopAction(run);
				idle();
			}
		}	
		break;
	case 27://right
		keepRight = false;
		if (!isJump) {
			if (keepLeft == true) {
				isLeft = true;
				sp->setScaleX(isLeft ? 1 : -1);
				if (isDown == true)break;
				runAnimation();
			}
			if (isDown == true)break;
			if (keepLeft == false) {
				sp->stopAction(run);
				idle();
			}
		}
		break;
	case 29://down
		if (!isJump) {
			isDown = false;
			if ((keepLeft == true && keepRight == false) || (keepLeft == false && keepRight == true)) {
				sp->setScaleX(isLeft ? 1 : -1);
				runAnimation();
			}
			else idle();
		}
		break;

	default:
		break;
	}
}
