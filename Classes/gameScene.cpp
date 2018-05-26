#include "gameScene.h"
#include "SimpleAudioEngine.h"
#include "bullet.h"
#include "bombMan.h"
#define PI 3.1415926

USING_NS_CC;

Scene* gameScene::createScene()
{
	return gameScene::create();
}

// on "init" you need to initialize your instance
bool gameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景
	auto bg = Sprite::create("tex\\bg.jpg");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setScale(1.6f, 1.6f);
	this->addChild(bg);
	//角色
	hero = Hero::create();
	hero->setPosition(120, 190);
	hero->setScale(1.6f, 1.6f);
	this->addChild(hero);

	label = Label::createWithTTF("PRESS", "fonts/Marker Felt.ttf", 24);
	label->setAnchorPoint(Vec2(0, 0));
	label->setPosition(200, 20);
	addChild(label);

	//子弹相关
	isFiring = false;
	count = 0;
	//敌人相关
	maxBombman = 10;
	bombmanCount = 0;

	listenKeyboardEvent();
	this->scheduleUpdate();

	return true;
}

void gameScene::update(float dt)
{
	count++;

	hero->update(dt);

	if (isFiring&& count % 8 == 0)fire();
	moveBullets(dt);

	if (count % 90 == 0 && bombmanCount < maxBombman) newBmobman();
	moveBombman(dt);

}
//发射子弹
void gameScene::fire()
{
	auto b = bullet::create();
	b->setScale(1.6f, 1.6f);
	b->radian = hero->isLeft ? PI : 0;
	b->setPositionX(hero->getPositionX() + (hero->isLeft ? -32 : 32));
	b->setPositionY(hero->getPositionY() + (hero->isDown ? 16 : 36));
	addChild(b);
	bullets.pushBack(b);
}
//移动子弹
void gameScene::moveBullets(float dt)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		auto b = bullets.at(i);
		b->update(dt);
		if (outScreen(b)) {
			b->removeFromParent();
			bullets.eraseObject(b);
			i--;
		}
	}
}


void gameScene::newBmobman()
{
	bombmanCount++;
	auto bm = bombMan::create();
	bm->setPosition(535, 190);
	bm->setAnchorPoint(Vec2(0.5f, 0.0f));
	bm->setScale(1.6f, 1.6f);
	addChild(bm);
	bombMen.pushBack(bm);

}

void gameScene::moveBombman(float dt)
{
	for (int j = 0; j < bombMen.size(); j++)
	{
		auto bm = bombMen.at(j);
		bm->update(dt);
		if (outScreen(bm)) {
			bm->removeFromParent();
			bombMen.eraseObject(bm);
			j--;
		}
	}
}

void gameScene::listenKeyboardEvent()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(gameScene::onKeyPressed2, this);
	listener->onKeyReleased = CC_CALLBACK_2(gameScene::onKeyReleased2, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void gameScene::onKeyPressed2(EventKeyboard::KeyCode code, Event * evt)
{
		char txt[100] = {};
		sprintf_s(txt, "%d is Pressed", (int)code);
		label->setString(txt);

		switch ((int)code)
		{
		case 59:
			isFiring = true;
			break;
		default:
			break;
		}

}

void gameScene::onKeyReleased2(EventKeyboard::KeyCode code, Event * evt)
{
	switch ((int)code)
	{
	case 59:
		isFiring = false;
		break;
	default:
		break;
	}
}

bool gameScene::outScreen(Node * n)
{
	if (n->getPositionX() < -20 || n->getPositionX() > 550 ||
		n->getPositionY() < -20 || n->getPositionY() > 500)
		return true;
	return false;
}

