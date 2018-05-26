#include "bombMan.h"

bool bombMan::init()
{
	Sprite::init();
	
	Vector<SpriteFrame*>allFrames;
	char txt[100] = {};
	for (int i = 1; i < 4; i++) {
		sprintf_s(txt, "tex\\bombman\\bombman_runleft000%d.png", i);
		SpriteFrame *sf = SpriteFrame::create(txt, Rect(0, 0, 35, 48));
		sf->setAnchorPoint(Vec2(0.3f, 0.35f));//不知道为何 动画偏移 强改锚点。。。。
		allFrames.pushBack(sf);
	}

	auto sp = Sprite::create();
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1f);
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5f, 0.0f));
	addChild(sp);

	return true;
}

void bombMan::update(float dt)
{
	runleft(dt);
}

void bombMan::runleft(float dt)
{
	float d = dt * 200;
	setPositionX(getPositionX() - d);
}
