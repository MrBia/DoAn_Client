#include "Objject.h"



CCSize Objject::getVisibleSize()
{

	return this->visibleSize;
}

void Objject::SetBlood(int blood)
{
	this->blood = blood;
}

int Objject::GetBlood()
{
	return this->blood;
}

void Objject::SetSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

Sprite * Objject::GetSprite()
{
	return this->sprite;
}

void Objject::mvLeft()
{
	log("move left");
}

void Objject::mvRight()
{
}

void Objject::idle()
{
}

Objject::Objject()
{
	visibleSize = Director::getInstance()->getVisibleSize();
}


Objject::~Objject()
{
}

void Objject::UpdateVelocity(Point velocity) {}
