#include "Glass.h"

void Glass::Init()
{
	// sprite
	this->SetSprite(Clone(ResourceManager::GetInstance()->GetSpriteById(2)));
	this->GetSprite()->retain();
	this->GetSprite()->setAnchorPoint(Vec2(0, 0));
	this->GetSprite()->setScale(SCALE_GLASS);
	this->layer->addChild(this->GetSprite());
	this->GetSprite()->setTag(TAG_GLASS);

	// physic
	auto physicbody = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physicbody->setDynamic(false);
	this->GetSprite()->setPhysicsBody(physicbody);
	physicbody->setRotationEnable(false);
	physicbody->setContactTestBitmask(1);
}

void Glass::Update(float deltaTime)
{
}

Glass::Glass(Layer* layer)
{
	this->layer = layer;
	Init();
}

Sprite * Glass::Clone(Sprite * sprite)
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	sprite_clone->retain();
	return sprite_clone;
}

Size Glass::getSize()
{
	return this->GetSprite()->getContentSize() * SCALE_GLASS;
}


Glass::~Glass()
{
	//delete this;
}
