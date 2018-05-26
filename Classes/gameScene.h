#ifndef __game_Scene_H__
#define __game_Scene_H__

#include "cocos2d.h"
#include "hero.h"
#include "bullet.h"
#include "bombMan.h"

class gameScene : public cocos2d::Scene
{
public:	
	// implement the "static create()" method manually
	CREATE_FUNC(gameScene);
	static cocos2d::Scene* createScene();
	virtual bool init();

	void update(float dt);

	Hero* hero;
	
	//子弹处理
	bool isFiring;
	void fire();
	void moveBullets(float dt);
	Vector<bullet*>bullets;
	int count;
	
	//敌人处理
	int maxBombman;
	int bombmanCount;
	void newBmobman();
	void moveBombman(float dt);
	Vector<bombMan*>bombMen;

	//键盘监听
	Label *label;
	void listenKeyboardEvent();
	void onKeyPressed2(EventKeyboard::KeyCode code, Event* evt);
	void onKeyReleased2(EventKeyboard::KeyCode code, Event* evt);

	//判断出屏
	bool outScreen(Node* n);
};

#endif 
#pragma once
