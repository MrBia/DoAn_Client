#pragma once
#include "ResourceManager.h"
#include "cocos2d.h"
#include "Defines.h"

USING_NS_CC;
class Objject
{
private:
	int blood;
	Sprite* sprite;
	CCSize visibleSize;
public:
	CCSize getVisibleSize();
	void SetBlood(int blood);
	int GetBlood();
	void SetSprite(Sprite* sprite);
	Sprite* GetSprite();
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual Size getSize() = 0;

	// TEST BY MR BIA
	virtual void mvLeft();
	virtual void mvRight();
	virtual void idle();

	Objject();
	~Objject();
	void UpdateVelocity(Point velocity);

};

