#ifndef __main_Scene_H__
#define __main_Scene_H__

#include "cocos2d.h"
USING_NS_CC;

class mainScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(mainScene);

	Label *label;
	//¼üÅÌ¼àÌý
	void listenKeyboardEvent();
	void onKeyPressed2(EventKeyboard::KeyCode code, Event* evt);
	void onKeyReleased2(EventKeyboard::KeyCode code, Event* evt);
};

#endif 
