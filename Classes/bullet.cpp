#include "bullet.h"
#include "math.h"
bool bullet::init()
{
	Sprite::init();

	auto b = Sprite::create("tex\\bullet.png");
	addChild(b);

	speed = 10;
	radian = 0;
	return true;
}

void bullet::update(float dt)
{
	float vx = speed*cos(radian);
	float vy = speed*sin(radian);
	setPosition(getPositionX() + vx, getPositionY() + vy);
}
