#include "FightHammer.h"



Size FightHammer::getSize()
{
	return Size(x, y);
}

Sprite * FightHammer::getFrameFight()
{
	return this->sprite;
}

Sprite * FightHammer::clone(Sprite * sprite)
{
	return Sprite::createWithTexture(sprite->getTexture());
}

FightHammer::FightHammer(float x, float y, int tag)
{
	// create size
	this->x = x;
	this->y = y;
	this->tag = tag;

	// physic
	physic = PhysicsBody::createBox(Size(x, y));
	physic->setRotationEnable(false);
	physic->setContactTestBitmask(1);
	physic->setDynamic(false);
	this->sprite = Sprite::create();
	sprite->setPhysicsBody(physic);
	sprite->retain();
	sprite->setTag(tag);
}


FightHammer::~FightHammer()
{
}
