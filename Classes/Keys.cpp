#include "Keys.h"


void Keys::Init()
{
	this->SetSprite(Sprite::create("key.png"));
	this->GetSprite()->retain();

	if (map) {
		this->GetSprite()->setScale(SCALE_KEY);
	}
	else {
		//this->GetSprite()->setScale(SCALE_FIRE_2);
	}

	this->GetSprite()->setTag(TAG_KEY);

	// physics body
	auto physic = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physic->setRotationEnable(false);
	physic->setContactTestBitmask(1);
	physic->setDynamic(false);
	this->GetSprite()->setPhysicsBody(physic);
}

void Keys::Update(float deltaTime)
{
}

Size Keys::getSize()
{
	return Size();
}

Keys::Keys(Layer * layer, bool map)
{
	this->layer = layer;
	this->map = map;
	Init();
}

void Keys::setPos(vector<Vec2> Key_pos, CCTMXTiledMap * _tileMap)
{
	this->Key_pos = Key_pos;
	this->_tileMap = _tileMap;
	this->GetSprite()->setPosition(Key_pos.at(0));
	this->_tileMap->addChild(this->GetSprite(), 6);
}

Keys::~Keys()
{
}
