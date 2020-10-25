#include "Glass2.h"

void Glass2::Init()
{
	// sprite
	this->SetSprite(Sprite::create("leaf2.png"));
	this->GetSprite()->retain();

	this->GetSprite()->setAnchorPoint(Vec2(0, 0));
	this->GetSprite()->setScale(SCALE_GLASS);
	this->layer->addChild(this->GetSprite());
	this->GetSprite()->setTag(TAG_GLASS2);

	// physic
	auto physicbody = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physicbody->setDynamic(false);
	this->GetSprite()->setPhysicsBody(physicbody);
	physicbody->setRotationEnable(false);
	physicbody->setContactTestBitmask(1);
}

void Glass2::Update(float deltaTime)
{
}

Glass2::Glass2(Layer* layer)
{
	this->layer = layer;
	Init();
}

Sprite * Glass2::Clone(Sprite * sprite)
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	sprite_clone->retain();
	return sprite_clone;
}

Size Glass2::getSize()
{
	return this->GetSprite()->getContentSize() * SCALE_GLASS;
}


Glass2::~Glass2()
{
	//delete this;
}
