#pragma once
#include "cocos2d.h"
USING_NS_CC;

class bullet:public Sprite {
public:
	CREATE_FUNC(bullet);
	bool init();
	void update(float dt);
	float speed;
	float radian;
};