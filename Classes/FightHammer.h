#pragma once
#include "cocos2d.h"

USING_NS_CC;
class FightHammer
{
private:
	float x, y;
	int tag;
	Sprite* sprite;
	PhysicsBody* physic;
public:
	Size getSize();
	Sprite* getFrameFight();
	Sprite* clone(Sprite* sprite);
	FightHammer(float x, float y, int tag);
	~FightHammer();
};

