#include "MiniGameScene.h"
#include "string.h"
#include "ControlMusic.h"

Scene* MiniGame::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, -500.0f));

	auto layer = MiniGame::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool MiniGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	if (ControlMusic::GetInstance()->isMusic())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/angkor_wat.mp3", true);
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// Read file
	s = FileUtils::getInstance()->getStringFromFile("life.txt");
	life = std::stoi(s);
	
	// ===============Background===============
	// 1) Create the CCParallaxNode
	_backgroundNode = CCParallaxNode::create(); //1
	this->addChild(_backgroundNode, -1);

	// 2) Create the sprites will be added to the CCParallaxNode
	_spacedust1 = CCSprite::create("bg_front_spacedust.png");
	_spacedust2 = CCSprite::create("bg_front_spacedust.png");
	_planetsunrise = CCSprite::create("bg_planetsunrise.png");
	_galaxy = CCSprite::create("bg_galaxy.png");
	_spacialanomaly = CCSprite::create("bg_spacialanomaly.png");
	_spacialanomaly2 = CCSprite::create("bg_spacialanomaly2.png");

	// 3) Determine relative movement speeds for space dust and background
	CCPoint dustSpeed = ccp(0.1, 0.1);
	CCPoint bgSpeed = ccp(0.05, 0.05);

	// 4) Add children to CCParallaxNode
	_backgroundNode->addChild(_spacedust1, 0, dustSpeed, ccp(0, visibleSize.height / 2)); // 2
	_backgroundNode->addChild(_spacedust2, 0, dustSpeed, ccp(_spacedust1->getContentSize().width, visibleSize.height / 2));
	_backgroundNode->addChild(_galaxy, -1, bgSpeed, ccp(0, visibleSize.height * 0.7));
	_backgroundNode->addChild(_planetsunrise, -1, bgSpeed, ccp(600, visibleSize.height * 0));
	_backgroundNode->addChild(_spacialanomaly, -1, bgSpeed, ccp(900, visibleSize.height * 0.3));
	_backgroundNode->addChild(_spacialanomaly2, -1, bgSpeed, ccp(1500, visibleSize.height * 0.9));

	// 5) Star
	addChild(CCParticleSystemQuad::create("Stars1.plist"));
	addChild(CCParticleSystemQuad::create("Stars2.plist"));
	addChild(CCParticleSystemQuad::create("Stars3.plist"));

	// ===============Meteor===============
	for (int i = 1; i <= 100; i++)
	{
		auto meteor = Sprite::create("rock/boulder.png");
		meteor->setPosition(cocos2d::random(150, (int)visibleSize.width - 150), cocos2d::random(visibleSize.height, (visibleSize.height * 30)));
		meteor->setTag(i);
		meteor->setScale(1.0f);
		auto meteorBody = PhysicsBody::createCircle(meteor->getContentSize().width / 2);
		meteor->setPhysicsBody(meteorBody);
		meteorBody->setDynamic(true);
		meteorBody->setVelocityLimit(cocos2d::random(250.0f, 400.0f));
		meteor->getPhysicsBody()->setContactTestBitmask(1);
		this->addChild(meteor);
	}

	// ===============Diamond===============
	for (int i = 101; i <= 160; i++)
	{
		diamond = Sprite::create("Diamond/1_14.png");
		diamond->setPosition(cocos2d::random(10, (int)visibleSize.width - 10), cocos2d::random(visibleSize.height, (visibleSize.height * 30)));
		//diamond->setPosition(50 + (i * 10), 270);
		diamond->setScale(0.5f);
		diamond->setTag(i);
		auto diamondBody = PhysicsBody::createCircle(diamond->getContentSize().width / 2);
		diamond->setPhysicsBody(diamondBody);
		diamondBody->setDynamic(true);
		diamondBody->setVelocityLimit(cocos2d::random(200.0f, 350.0f));
		diamond->getPhysicsBody()->setContactTestBitmask(1);
		this->addChild(diamond);
	}

	// ===============Bar===============
	auto edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(cocos2d::Size(visibleSize.width, 1), PhysicsMaterial(0.0f, 0.0f, 0.0f), 0);
	edgeSp->setPosition(Point(visibleSize.width / 2, -35));
	edgeSp->setPhysicsBody(boundBody);
	edgeSp->setTag(0);
	boundBody->setContactTestBitmask(1);
	this->addChild(edgeSp);

	// ===============Label score===============
	CCString *tempScore = CCString::createWithFormat("%i/20", score);
	scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", 24);
	scoreLabel->setColor(Color3B::WHITE);
	scoreLabel->setPosition(Point(15, visibleSize.height - 15));
	this->addChild(scoreLabel, 10000);

	// ===============Label life===============
	CCString *tempLife = CCString::createWithFormat("%i/3", life);
	lifeLabel = Label::createWithTTF(tempLife->getCString(), "fonts/Marker Felt.ttf", 24);
	lifeLabel->setColor(Color3B::WHITE);
	lifeLabel->setPosition(Point(15, 15));
	this->addChild(lifeLabel, 10000);

	//  ===============Event diamond===============
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MiniGame::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// ===============Event bar===============
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MiniGame::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool MiniGame::onTouchBegan(Touch* touch, Event* event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 1; i <= 100; i++)
	{
		if (event->getCurrentTarget()->getChildByTag(i)->getBoundingBox().containsPoint(touch->getLocation()))
		{
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_damage.mp3", false);
			}
			if (this->life > 0)
			{
				this->life--;
			}
			auto hide = Hide::create();
			event->getCurrentTarget()->getChildByTag(i)->getPhysicsBody()->setEnabled(false);
			event->getCurrentTarget()->getChildByTag(i)->runAction(hide);
		}
	}
	for (int i = 101; i <= 160; i++)
	{
		if (event->getCurrentTarget()->getChildByTag(i)->getBoundingBox().containsPoint(touch->getLocation()))
		{
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_ui_diamond_impact.mp3", false);
			}
			this->score++;
			event->getCurrentTarget()->getChildByTag(i)->getPhysicsBody()->setEnabled(false);
			//event->getCurrentTarget()->removeChildByTag(i, true);
			auto moveTo = MoveTo::create(2, Point(15, (int)visibleSize.height - 15));
			auto scaleBy = ScaleBy::create(2.0f, 0.3f);
			auto spawn = Spawn::createWithTwoActions(moveTo, scaleBy);
			auto hide = Hide::create();
			auto sequence = Sequence::create(spawn, hide, nullptr);
			event->getCurrentTarget()->getChildByTag(i)->runAction(sequence);
		}
	}
	return true;
}

bool MiniGame::onContactBegin(PhysicsContact &contact)
{
	auto hide = Hide::create();
	auto ObjA = contact.getShapeA()->getBody()->getNode();
	auto ObjB = contact.getShapeB()->getBody()->getNode();

	if (ObjA && ObjB)
	{
			if (ObjA->getTag() == 0)
			{
				//ObjB->runAction(hide);
				//ObjB->getPhysicsBody()->setEnabled(false);
			}
			else if (ObjB->getTag() == 0)
			{
				ObjA->runAction(hide);
				ObjA->getPhysicsBody()->setEnabled(false);
			}
	}

	//this->removeChild(ObjB, true);

	//this->removeChild(ObjA, true);

	return true;
}

void MiniGame::update(float deltaTime)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto hide = Hide::create();

	//===========Update score===============
	CCString *tempScore = CCString::createWithFormat("%i/20", score);
	scoreLabel->setString(tempScore->getCString());

	//===========Update life=======================
	CCString *tempLife = CCString::createWithFormat("%i/3", life);
	lifeLabel->setString(tempLife->getCString());

	if (score == 20)
	{
		for (int i = 1; i <= 160; i++)
		{
			if (this->getChildByTag(i))
			{
				_eventDispatcher->removeAllEventListeners();
				this->removeChildByTag(i);
			}
		}

		auto winLabel = Label::createWithTTF("YOU WIN!", "fonts/Marker Felt.ttf", 54);
		winLabel->setColor(Color3B::WHITE);
		winLabel->setPosition(visibleSize / 2);
		this->addChild(winLabel, 10000);	
		auto delay = DelayTime::create(5.0f);

	}
}
