#include "Spider.h"

void Spider::Init()
{

	// initial sprite
	InitialSPider();

	// initial action
	InitialAction();
	goUp();
}

void Spider::Update(float deltaTime)
{
}

Size Spider::getSize()
{
	return this->GetSprite()->getContentSize() * SCALE_SPIDER;
}

void Spider::InitialSPider()
{
	// initial blood
	this->SetBlood(BLOOD_SPIDER);

	// initial sprite
	this->SetSprite(Sprite::create("spider_01.png"));
	this->GetSprite()->setPosition(this->getVisibleSize() / 2);
	this->GetSprite()->setScale(SCALE_SPIDER);
	this->GetSprite()->retain();
	this->layer->addChild(this->GetSprite(),0);
	this->GetSprite()->setTag(TAG_SPIDER);

	// physic
	auto physicbody = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physicbody->setDynamic(false);
	this->GetSprite()->setPhysicsBody(physicbody);
	physicbody->setRotationEnable(false);
	physicbody->setContactTestBitmask(1);
}

void Spider::InitialAction()
{
	// action up
	auto animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetSpiderUp(), SPEED_FRAME_SPIDER);
	auto animate = Animate::create(animation);
	auto delay = DelayTime::create(0.5f);

	auto move = MoveBy::create(1.0f,Vec2(0,this->GetSprite()->getPosition().y-380));
	auto seq = Sequence::create(move,delay,move->reverse(),nullptr);
	auto mySpawn = Spawn::createWithTwoActions(seq, animate);

	action_up = RepeatForever::create(mySpawn);
	action_up->setTag(actions_spider::GO_UP);
	action_up->retain();


	// action left
	auto move1 = MoveBy::create(1.0f, Vec2(0, this->GetSprite()->getPosition().x - 380));
	auto seq1 = Sequence::create(move1, delay, move1->reverse(), nullptr);
	auto mySpawn1 = Spawn::createWithTwoActions(seq1, animate);

	action_side = RepeatForever::create(mySpawn1);
	action_side->setTag(actions_spider::GO_LEFT);
	action_side->retain();
}

void Spider::goUp()
{
	this->GetSprite()->runAction(action_up);
}

void Spider::goDown()
{
	this->GetSprite()->runAction(action_down);

}

void Spider::goSide()
{
	this->GetSprite()->runAction(action_side);
}

void Spider::goLeft()
{
	this->GetSprite()->runAction(action_side);
	this->GetSprite()->setFlippedX(false);
}

void Spider::goRight()
{
	this->GetSprite()->setFlippedX(true);
	this->GetSprite()->runAction(action_side);
}

void Spider::setState(bool state)
{
	this->state = state;
}

bool Spider::isAlive()
{
	return this->state;
}

void Spider::setCatogory(bool cotogory)
{
	this->catogory = catogory;
}

bool Spider::isCatogory()
{
	return this->catogory;
}

void Spider::RotateLeft()
{
	if (!isLeft)
	{
		this->GetSprite()->setAnchorPoint(Vec2(0.5f, 0.0f));
		auto rotatecallback = [=](float value) {
			this->GetSprite()->setRotation3D(Vec3(0, value, 0));
		};
		auto runaction = ActionFloat::create(SPEED_ROTATE_SPIDER, 0.0f, 180.f, rotatecallback);

		//Run();
		this->GetSprite()->runAction(runaction);
	}
	isLeft = true;
	isRight = false;
}

void Spider::RotateRight()
{
	if (!isRight)
	{
		this->GetSprite()->setAnchorPoint(Vec2(0.5f, 0.0f));
		auto rotatecallback = [=](float value) {
			this->GetSprite()->setRotation3D(Vec3(0, value, 0));
		};
		auto runaction = ActionFloat::create(SPEED_ROTATE_SPIDER, 180.f, 0.0f, rotatecallback);

		this->GetSprite()->runAction(runaction);
	}
	isRight = true;
	isLeft = false;
}

Spider::Spider(Layer *layer)
{
	this->layer = layer;
	Init();
}

Spider::~Spider()
{
}
