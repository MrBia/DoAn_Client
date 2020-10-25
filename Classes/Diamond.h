#pragma once
#include "Objject.h"

class Diamond :
	public Objject
{
private:
	cocos2d::Layer* layer;
public:
	Diamond(cocos2d::Layer* layer);
	Sprite* Clone(cocos2d::Sprite* sprite);
	~Diamond();
	void Init();
	void Update(float deltaTime);
	Size getSize();
};

