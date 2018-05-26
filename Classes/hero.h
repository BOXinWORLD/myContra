#ifndef __Hero_H__
#define __Hero_H__
#include "cocos2d.h"
USING_NS_CC;

class Hero :public Sprite {
public:
	CREATE_FUNC(Hero);
	bool init();

	void update(float dt);

	void idle();//静止
	void down();//趴下
	void jump();//jump
	void runAnimation();//奔跑动画
	void runLeft(float dt);
	void runRight(float dt);

	bool isLeft;//是否面左
	bool isDown;
	bool isJump;
	bool keepLeft;
	bool keepRight;

	float vy;//起跳速度
	float g;//重力加速度
	float oy;//起跳y坐标

	Sprite* sp;
	Action* run;
	Action* jumpAction;

	//键盘监听
	void listenKeyboardEvent();
	void onKeyPressed2(EventKeyboard::KeyCode code, Event* evt);
	void onKeyReleased2(EventKeyboard::KeyCode code, Event* evt);
};

#endif // __Hero_H__


