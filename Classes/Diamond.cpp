#include "Diamond.h"



Diamond::Diamond(cocos2d::Layer* layer)
{
	this->layer = layer;
	this->Init();
}


Diamond::~Diamond()
{
}

Sprite* Diamond::Clone(cocos2d::Sprite* sprite)
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	sprite_clone->retain();
	return sprite_clone;
}

void Diamond::Init()
{
	//create sprite
	this->SetSprite(Clone(ResourceManager::GetInstance()->GetSpriteById(3)));
	this->GetSprite()->setScale(SCALE_DIAMOND);
	this->GetSprite()->setAnchorPoint(Vec2(0, 0));
	this->layer->addChild(this->GetSprite());

	// run action
	auto animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetFrameDiamond(), 0.2);
	auto animate = Animate::create(animation);
	animate->retain();
	this->GetSprite()->runAction(RepeatForever::create(animate));

	//add physic
	auto physicsBody1 = PhysicsBody::createCircle(this->GetSprite()->getContentSize().width/2);
	physicsBody1->setDynamic(false);
	physicsBody1->setRotationEnable(false);
	this->GetSprite()->setPhysicsBody(physicsBody1);
	this->GetSprite()->getPhysicsBody()->setContactTestBitmask(1);
	this->GetSprite()->setTag(TAG_DIAMOND);
}
void Diamond::Update(float deltaTime) 
{
}

Size Diamond::getSize()
{
	return this->GetSprite()->getContentSize() * SCALE_DIAMOND;
}
