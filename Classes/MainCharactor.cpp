#include "MainCharactor.h"

MainCharactor::MainCharactor(Layer *layer)
{
	this->layer = layer;
	Init();
}

Sprite *MainCharactor::Clone(Sprite *sprite)
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	sprite_clone->retain();
	return sprite_clone;
}

MainCharactor::~MainCharactor()
{
}


void MainCharactor::Init()
{

	// initial state
	InitialState();

	// create sprite
	CreateSprite();

	// create animate action
	InitialAction();
}

void MainCharactor::InitialState()
{

	// check direction
	isLeft = false;
	isRight = true;


	// initial state
	push = false;
	fight = false;
	stun = false;

	// INIT DIRECTION
	isRotateLeft = false;
	isRotateRight = true;
	currentAnim = "";
}

void MainCharactor::CreateSprite()
{
	// initial blood
	this->SetBlood(BLOOD_CHARACTOR);

	// create sprite
	auto main = Clone(ResourceManager::GetInstance()->GetSpriteById(1));
	main->setScale(SCALE_CHARACTOR);

	//main->setPosition(550, 230);
	main->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->SetSprite(main);
	this->layer->addChild(this->GetSprite());

	// create physic
	physicbody = PhysicsBody::createBox(main->getContentSize());
	physicbody->setDynamic(true);
	main->setPhysicsBody(physicbody);
	physicbody->setRotationEnable(false);
	physicbody->setGravityEnable(false);
	physicbody->setMass(500);

	main->getPhysicsBody()->setContactTestBitmask(1);
	main->setTag(TAG_CHARACTOR); //tag dùng để xác định đối tượng va chạm
	this->GetSprite()->getPhysicsBody()->setLinearDamping(0.5f);

	// danh bua
	f = new FightHammer(30, 20, TAG_FIGHT);
	f->getFrameFight()->setPosition(-100, -100);
	this->layer->addChild(f->getFrameFight());
	f->getFrameFight()->getPhysicsBody()->setDynamic(false);
}

void MainCharactor::InitialAction()
{
	// push
	auto animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorPush(), SPEED_FRAME_CHARACTOR);
	action_push = Animate::create(animation);
	action_push->setTag(Actions::C_PUSH);
	action_push->retain();

	// wait
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorWait(), SPEED_FRAME_CHARACTOR);
	action_wait = Animate::create(animation);
	action_wait->setTag(Actions::C_WAIT);
	action_wait->retain();

	// run
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorRun(), SPEED_FRAME_CHARACTOR);
	action_run = RepeatForever::create(Animate::create(animation));
	action_run->setTag(Actions::C_RUN);
	action_run->retain();

	// fight
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorFight(), SPEED_FIGHT);
	action_fight = Animate::create(animation);
	action_fight->setTag(Actions::C_FIGHT);
	action_fight->retain();

	// stun
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorStun(), SPEED_FRAME_CHARACTOR);
	action_stun = Animate::create(animation);
	action_stun->setTag(Actions::C_STUN);
	action_stun->retain();
}

void MainCharactor::Update(float deltaTime)
{
	
}

void MainCharactor::Push()
{
	if (this->GetSprite()->getNumberOfRunningActionsByTag(Actions::C_PUSH) == 0)
	{
		this->GetSprite()->stopAllActions();
		this->GetSprite()->runAction(action_push);
	}
}

void MainCharactor::Fight()
{
	if (this->GetSprite()->getNumberOfRunningActions() > 0)
	{
		this->GetSprite()->stopAllActions();
	}
	if (this->GetSprite()->getNumberOfRunningActionsByTag(Actions::C_FIGHT) == 0)
		this->GetSprite()->runAction(action_fight);
	
	auto pos = this->GetSprite()->getPosition();
	if(isRight) f->getFrameFight()->setPosition(pos.x + 45, pos.y + 30);
	if(isLeft) f->getFrameFight()->setPosition(pos.x - 45, pos.y + 30);
}


void MainCharactor::Stun()
{
	if (this->GetSprite()->getNumberOfRunningActions() > 0)
	{
		this->GetSprite()->stopAllActions();
	}

	this->GetSprite()->runAction(action_stun);
}



Size MainCharactor::getSize()
{
	return this->GetSprite()->getContentSize() * SCALE_CHARACTOR;
}

void MainCharactor::mvLeft()
{
	// ROTATE
	if (this->isRotateLeft == false) {
		this->rotateLeft();

		this->isRotateLeft = true;
		this->isRotateRight = false;
	}

	// ACTION RUN
	if (this->currentAnim != "run") {
		this->GetSprite()->stopAllActions();
		this->currentAnim = "run";
	}
	else {
		if (this->GetSprite()->getNumberOfRunningActions() == 0) {
			this->GetSprite()->runAction(action_run);
		}
	}
}

void MainCharactor::mvRight()
{
	// ROTATE
	if (this->isRotateRight == false) {
		this->rotateRight();

		this->isRotateLeft = false;
		this->isRotateRight = true;
	}

	// ACTION RUN
	if (this->currentAnim != "run") {
		this->GetSprite()->stopAllActions();
		this->currentAnim = "run";
	}
	else {
		if (this->GetSprite()->getNumberOfRunningActions() == 0) {
			this->GetSprite()->runAction(action_run);
		}
	}
}

void MainCharactor::idle()
{
	if (this->currentAnim != "wait") {
		this->GetSprite()->stopAllActions();
		this->currentAnim = "wait";
	}
	else {
		if (this->GetSprite()->getNumberOfRunningActions() == 0) {
			this->GetSprite()->runAction(action_wait);
		}
	}
}

void MainCharactor::rotateLeft()
{
	this->GetSprite()->setFlipX(true);
}

void MainCharactor::rotateRight()
{
	this->GetSprite()->setFlipX(false);
}

void MainCharactor::setID(string id)
{
	this->id = id;
}

string MainCharactor::getID()
{
	return this->id;
}

void MainCharactor::setState(string state)
{
	this->state = state;
}

string MainCharactor::getState()
{
	return this->state;
}
