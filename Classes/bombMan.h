#pragma once
#include "cocos2d.h"
USING_NS_CC;

class bombMan :public Sprite {
public:
	CREATE_FUNC(bombMan);
	bool init();
	void update(float dt);
	void runleft(float dt);
};