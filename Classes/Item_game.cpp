#include "Item_game.h"


Item_game::Item_game(Layer* layer)
{
	this->layer = layer;
	Init();
}

bool Item_game::isCollect()
{
	return this->collect;
}


Item_game::~Item_game()
{
}


void Item_game::SetTouch(CCPoint touch)
{
	this->touch = touch;
}

void Item_game::Init()
{
	// is collect
	this->collect = false;

	this->SetSprite(Clone(ResourceManager::GetInstance()->GetSpriteById(0)));
	random(this);
	auto physicbody = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physicbody->setDynamic(true);
	physicbody->setVelocity(Vec2(1, 1));
	this->GetSprite()->setPhysicsBody(physicbody);
	this->layer->addChild(this->GetSprite());
}

void Item_game::Update(float deltaTime)
{
	this->collect = false;

	auto rect = new Rect(this->GetSprite()->getPosition().x, this->GetSprite()->getPosition().y,
		this->GetSprite()->getContentSize().width, this->GetSprite()->getContentSize().height);

	if (rect->containsPoint(touch)) {
		touch.x = 0;
		touch.y = 0;
		this->GetSprite()->getPhysicsBody()->setVelocity(Vec2(1, 1));
		this->collect = true;
		random(this);
	}
	else if (this->GetSprite()->getPosition().y < 0) {
		this->collect = false;
		this->GetSprite()->getPhysicsBody()->setVelocity(Vec2(1, 1));
		random(this);
	}
}


Sprite * Item_game::Clone(Sprite * sprite)
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	return sprite_clone;
}

void Item_game::random(Objject * object)
{
	float x = 10 + rand() % ((int)this->getVisibleSize().width + 10 - 1);
	object->GetSprite()->setPosition(x, this->getVisibleSize().height + 20);
}
