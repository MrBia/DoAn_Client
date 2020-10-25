#include "GamePlay2.h"
#include "ControlMusic.h"

cocos2d::Sprite* mPauseLayer2;
cocos2d::Sprite* mHeader2;
cocos2d::ui::Button *mBump2;
cocos2d::ui::Button *mJump2;
cocos2d::ui::Button *btnPause2;
int numDia = 0;

Scene * GamePlay2::createGame()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setSubsteps(8);

	// 'layer' is an autorelease object
	auto layer = GamePlay2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GamePlay2::init()
{
	//Create background music
	if (ControlMusic::GetInstance()->isMusic())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/angkor_wat.mp3", true);
	}

	//create Map
	createMap();

	//create physics for Map
	createMapPhysics();

	// initial state
	InitialState();

	//create Object
	createObject();

	// add dispatcher
	AddDispatcher();

	// add button
	InitialButton();

	//create pause layer
	createPauseLayer();

	//Create Joystick
	CreateJoystick(this);

	// update
	scheduleUpdate();

	// create fire
	vector<Vec2> v;

	fire_normal_1 = new Fire(this, false);
	((Fire*)(fire_normal_1))->setAI(false);
	((Fire*)(fire_normal_1))->setPos(Fire_Normal_1, _tileMap, v);

	fire_normal_2 = new Fire(this, false);
	((Fire*)(fire_normal_2))->setAI(false);
	((Fire*)(fire_normal_2))->setPos(Fire_Normal_2, _tileMap, v);

	fire_normal_3 = new Fire(this, false);
	((Fire*)(fire_normal_3))->setAI(false);
	((Fire*)(fire_normal_3))->setPos(Fire_Normal_3, _tileMap, v);

	return true;
}

void GamePlay2::createMap()
{
	_tileMap = new CCTMXTiledMap();
	_tileMap->initWithTMXFile("map2.tmx");
	_tileMap->setScale(2.0);
	_background = _tileMap->layerNamed("Background");
	_wall = _tileMap->layerNamed("MapLv2");
	_phy = _tileMap->layerNamed("physics");
	_phy->setVisible(false);
	mObjectGroup = _tileMap->getObjectGroup("Objects");
	mObjectGroup1 = _tileMap->getObjectGroup("Spiders");

	mObjects_line_down = _tileMap->getObjectGroup("Line_Down");
	mObjects_line_up = _tileMap->getObjectGroup("Line_Up");
	mObjectFire = _tileMap->getObjectGroup("Fire");

	this->addChild(_tileMap);
}

void GamePlay2::InitialState()
{
	// initial number diamon
	this->numDiamond2 = 0;

	// initial state
	fight = false;

	// initial direction
	moveLeft = false;
	moveRight = false;
	moveUp = false;
	moveDown = false;
	jump = false;
	fall = true;
}

void GamePlay2::createObject() {
	auto objects1 = mObjectGroup1->getObjects();
	for (int i = 0; i < objects1.size(); i++)
	{
		auto object1 = objects1.at(i);
		auto properties = object1.asValueMap();
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object1.asValueMap().at("type").asInt();
		if (type == 2)//Create Spider
		{
			Spider *spider = new Spider(this);
			spider->GetSprite()->setPosition(Vec2(posX * 2, posY * 2));
			spider->setCatogory(true);
			spiders.push_back(spider);
		}
	}
	
	auto objects = mObjectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);
		auto properties = object.asValueMap();
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();

		if (type == 1)//Create Charactor
		{
			this->main_charactor = new MainCharactor(this);
			this->main_charactor->GetSprite()->setPosition(Vec2(posX * 2, posY * 2));
			this->setViewPointCenter(this->main_charactor->GetSprite()->getPosition());
			CreateBloodBar();
			CreateNumDiamon();
		}
		else if (type == 4) {//Create Glass
			Objject* glass2 = new Glass2(this);
			glass2->GetSprite()->setPosition(Vec2(posX*2, posY*2));
			glasss.push_back(glass2);
		}
		else if (type == 5) {//Create Diamond
			numDia++;
			Objject* diamon = new Diamond(this);
			diamon->GetSprite()->setPosition(Vec2(posX*2, posY*2));
			diamons.push_back(diamon);
		}
		else if (type == 6) {//Create Rock
			Objject* rock = new Rock(this);
			rock->GetSprite()->setPosition(Vec2(posX*2, posY*2));
			rocks.push_back(rock);
		}
	}

	// get object line down
	auto objects_line_down = mObjects_line_down->getObjects();
	for (int i = 0; i < objects_line_down.size(); i++) {
		auto object = objects_line_down.at(i);
		auto properties = object.asValueMap();

		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();

		if (type == 1) {
			_Line_Down_Pos_1.push_back(Vec2(posX, posY)*2);
		}
		else if (type == 2) {
			_Line_Down_Pos_2.push_back(Vec2(posX, posY) * 2);
		}
		else if (type == 3) {
			_Line_Down_Pos_3.push_back(Vec2(posX, posY) * 2);
		}
		else if (type == 4) {
			_Line_Down_Pos_4.push_back(Vec2(posX, posY) * 2);
		}
		else if (type == 5) {
			_Line_Down_Pos_5.push_back(Vec2(posX, posY) * 2);
		}
		else if (type == 6) {
			_Line_Down_Pos_6.push_back(Vec2(posX, posY) * 2);
		}
	}

	// get object line up
	auto objects_line_up = mObjects_line_up->getObjects();
	for (int i = 0; i < objects_line_up.size(); i++) {
		auto object = objects_line_up.at(i);
		auto properties = object.asValueMap();

		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();

		if (type == 1) {
			_Line_Up_Pos_1.push_back(Vec2(posX, posY) * 2);
		}
		else if (type == 2) {
			_Line_Up_Pos_2.push_back(Vec2(posX, posY) * 2);
		}
		else if (type == 3) {
			_Line_Up_Pos_3.push_back(Vec2(posX, posY) * 2);
		}
		else if (type == 4) {
			_Line_Up_Pos_4.push_back(Vec2(posX, posY) * 2);
		}
		else if (type == 5) {
			_Line_Up_Pos_5.push_back(Vec2(posX, posY) * 2);
		}
		else if (type == 6) {
			_Line_Up_Pos_6.push_back(Vec2(posX, posY) * 2);
		}
	}

	// get object fire
	auto objects_fire = mObjectFire->getObjects();
	for (int i = 0; i < objects_fire.size(); i++) {
		auto object = objects_fire.at(i);
		auto properties = object.asValueMap();

		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();

		if (type == 1) {
			Fire_Normal_1.push_back(Vec2(posX, posY));
		}
		else if (type == 2) {
			Fire_Normal_2.push_back(Vec2(posX, posY));
		}
		else if (type == 3) {
			Fire_Normal_3.push_back(Vec2(posX, posY));
		}
		else if (type == 20) {
			blood_1 = Sprite::create("blood.png");
			blood_1->setScale(SCALE_BLOOD);
			blood_1->setTag(TAG_BLOOD);
			blood_1->retain();
			blood_1->setPosition(Vec2(posX, posY) * 2);

			auto physic = PhysicsBody::createBox(blood_1->getContentSize());
			physic->setRotationEnable(false);
			physic->setContactTestBitmask(1);
			physic->setDynamic(false);
			blood_1->setPhysicsBody(physic);

			this->addChild(blood_1);
		}
		else if (type == 21) {
			blood_2 = Sprite::create("blood.png");
			blood_2->setScale(SCALE_BLOOD);
			blood_2->setTag(TAG_BLOOD);
			blood_2->retain();
			blood_2->setPosition(Vec2(posX, posY) * 2);

			auto physic = PhysicsBody::createBox(blood_2->getContentSize());
			physic->setRotationEnable(false);
			physic->setContactTestBitmask(1);
			physic->setDynamic(false);
			blood_2->setPhysicsBody(physic);

			this->addChild(blood_2);
		}
	}
}

void GamePlay2::AddDispatcher()
{
	// key board
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(GamePlay2::OnKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(GamePlay2::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	// listener contact
	auto contacListener = EventListenerPhysicsContact::create();
	contacListener->onContactBegin = CC_CALLBACK_1(GamePlay2::OnContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contacListener, this);

	// touch
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GamePlay2::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GamePlay2::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GamePlay2::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GamePlay2::InitialButton()
{
	//Button Fight
	mBump2 = ui::Button::create("Button/hammer_normal.png", "Button/hammer_pressed.png");
	mBump2->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 150, 100));
	mBump2->addTouchEventListener(CC_CALLBACK_2(GamePlay2::Fight, this));
	addChild(mBump2);

	//Button Pause
	btnPause2 = ui::Button::create("Button/pause_norrmal.png", "Button/pause_pressed.png");
	btnPause2->setAnchorPoint(Vec2(1, 1));
	btnPause2->setPosition(Director::getInstance()->getVisibleSize() - Size(3, 8));
	btnPause2->addTouchEventListener(CC_CALLBACK_2(GamePlay2::Pause, this));
	addChild(btnPause2, 2);
}

void GamePlay2::createMapPhysics()
{
	//ground
	Size layerSize = _phy->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = _phy->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physic = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
				physic->setCollisionBitmask(1);
				physic->setContactTestBitmask(true);
				physic->setDynamic(false);
				physic->setMass(100);
				tileSet->setPhysicsBody(physic);
				tileSet->setTag(TAG_MAP);
			}
		}
	}
}

bool GamePlay2::OnContactBegin(PhysicsContact &contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		// charactor vs spider
		if (nodeA->getTag() == TAG_SPIDER && nodeB->getTag() == TAG_CHARACTOR)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - 15);
			
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_damage.mp3", false);
			}

			this->main_charactor->GetSprite()->stopAllActions();

			((MainCharactor *)(main_charactor))->Stun();
			
			if (this->main_charactor->GetBlood() <= 0)
			{
				log("die");
				if (ControlMusic::GetInstance()->isSound())
				{
					SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_die.mp3", false);
				}
				Director::getInstance()->replaceScene(TransitionFade::create(0.5,MainMenu::createScene()));
			}
		}
		else if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_SPIDER)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - 15);
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_damage.mp3", false);
			}
			this->main_charactor->GetSprite()->stopAllActions();
			((MainCharactor *)(main_charactor))->Stun();
			if (this->main_charactor->GetBlood() <= 0)
			{
				log("die");
				if (ControlMusic::GetInstance()->isSound())
				{
					SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_die.mp3", false);
				}
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainMenu::createScene()));
			}
		}
		
		// main charactor vs diamond
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_DIAMOND)
		{
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_ui_diamond_impact.mp3", false);
			}
			numDiamond2++;
			nodeB->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == TAG_DIAMOND && nodeB->getTag() == TAG_CHARACTOR)
		{
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_ui_diamond_impact.mp3", false);
			}
			numDiamond2++;
			nodeA->removeFromParentAndCleanup(true);
		}

		// main charactor vs glass
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_GLASS2) {
			nodeB->removeFromParentAndCleanup(true);
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_icespear_break.mp3", false);
			}
		}
		else if (nodeA->getTag() == TAG_GLASS2 && nodeB->getTag() == TAG_CHARACTOR) {
			nodeA->removeFromParentAndCleanup(true);
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_icespear_break.mp3", false);
			}
		}

		//spider vs rock
		if (nodeA->getTag() == TAG_SPIDER && nodeB->getTag() == TAG_ROCK) {
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_broken_stone.mp3.mp3", false);
			}
			nodeA->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == TAG_ROCK && nodeB->getTag() == TAG_SPIDER)
		{
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_broken_stone.mp3.mp3", false);
			}
			nodeB->removeFromParentAndCleanup(true);
		}

		//spider vs rock
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_FIRE) {
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - 20);
		}
		else if (nodeA->getTag() == TAG_FIRE && nodeB->getTag() == TAG_CHARACTOR)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - 20);
		}

		// fight
		if (nodeA->getTag() == TAG_FIGHT && nodeB->getTag() == TAG_SPIDER) {
			nodeB->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == TAG_SPIDER && nodeB->getTag() == TAG_FIGHT) {
			nodeA->removeFromParentAndCleanup(true);
		}

		// main charactor vs blood
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_BLOOD) {
			nodeB->removeFromParentAndCleanup(true);
			if (this->main_charactor->GetBlood() < 100)
				this->main_charactor->SetBlood(this->main_charactor->GetBlood() + 20);

			if (this->main_charactor->GetBlood() >= 100)
				this->main_charactor->SetBlood(100);
		}
		else if (nodeA->getTag() == TAG_BLOOD && nodeB->getTag() == TAG_CHARACTOR) {
			nodeA->removeFromParentAndCleanup(true);
			if (this->main_charactor->GetBlood() < 100)
				this->main_charactor->SetBlood(this->main_charactor->GetBlood() + 20);

			if (this->main_charactor->GetBlood() >= 100)
				this->main_charactor->SetBlood(100);
		}

	}

	return true;
}

void GamePlay2::CreateBloodBar()
{
	auto posY = Director::getInstance()->getVisibleSize().height;

	mHeader2 = Sprite::create("header.png");
	mHeader2->setFlippedX(true);
	mHeader2->setAnchorPoint(Vec2(1, 1));
	mHeader2->setPosition(Director::getInstance()->getVisibleSize());
	mHeader2->setVisible(true);
	addChild(mHeader2, 2);

	Layer *layer_1 = Layer::create();
	auto bloodBar_bg = ui::LoadingBar::create("Load/bloodbar_bg.png");
	bloodBar_bg->setDirection(ui::LoadingBar::Direction::RIGHT);
	bloodBar_bg->setPercent(100);
	bloodBar_bg->setPosition(Director::getInstance()->getVisibleSize() - Size(230, 30));

	bloodBar = ui::LoadingBar::create("Load/bloodbar.png");
	bloodBar->setDirection(ui::LoadingBar::Direction::LEFT);
	bloodBar->setPercent(100);
	bloodBar->setPosition(bloodBar_bg->getPosition());

	this->addChild(bloodBar_bg, 3);
	this->addChild(bloodBar, 2);
}

void GamePlay2::CreateNumDiamon()
{
	// sprite diamon
	auto NumDiamon = ResourceManager::GetInstance()->GetSpriteById(3);
	NumDiamon->setScale(0.35);
	NumDiamon->setPosition(bloodBar->getPosition() - Vec2(250, 0));
	this->addChild(NumDiamon, 2);

	// label number
	CCString *num = CCString::createWithFormat("%i/20", numDiamond2);
	LabelNumDiamon = Label::createWithTTF(num->getCString(), "fonts/Marker Felt.ttf", 30);
	LabelNumDiamon->setPosition(NumDiamon->getPosition() + Vec2(50, 0));
	this->addChild(LabelNumDiamon, 2);
}

void GamePlay2::createPauseLayer()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//create pause layer
	mPauseLayer2 = Sprite::create("pause.png");
	mPauseLayer2->setPosition(visibleSize / 2);
	mPauseLayer2->setContentSize(visibleSize);
	mPauseLayer2->setVisible(false);
	addChild(mPauseLayer2, 2);

	//Button Go to Map
	auto btnHome = ui::Button::create("Button/home_normal.png", "Button/home_pressed.png");
	btnHome->setScale(SCALE_BUTTON);
	btnHome->setPosition(Vec2(visibleSize / 2 - Size(0, 80)));
	btnHome->addClickEventListener([](Ref* event) {
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainMenu::createScene()));
	});
	mPauseLayer2->addChild(btnHome);

	//Button Restart
	auto btnRestart = ui::Button::create("Button/restart_normal.png", "Button/restart_pressed.png");
	btnRestart->setScale(SCALE_BUTTON);
	btnRestart->setPosition(btnHome->getPosition() + Size(0, 70));
	btnRestart->addClickEventListener([](Ref* event) {
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
	});
	mPauseLayer2->addChild(btnRestart);

	//Button Resume
	auto btnResume = ui::Button::create("Button/resume_normal.png", "Button/resume_pressed.png");
	btnResume->setScale(SCALE_BUTTON);
	btnResume->setPosition(btnRestart->getPosition() + Size(0, 70));
	btnResume->addClickEventListener([](Ref* event) {
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		btnPause2->setVisible(true);
		mBump2->setVisible(true);
		mPauseLayer2->setVisible(false);
	});
	mPauseLayer2->addChild(btnResume);
}

void GamePlay2::push_rock()
{
	push = false;
	int index = -1;
	index = check_push();
	if (index != -1) {
		push = true;

		Vec2 p_rock = rocks.at(index)->GetSprite()->getPosition();
		Vec2 p_main = main_charactor->GetSprite()->getPosition();

		if (p_rock.x < p_main.x) {
			rocks.at(index)->GetSprite()->setPosition(rocks.at(index)->GetSprite()->getPosition() -
				Vec2(SPEED_CHARACTOR_RUN, 0));
		}
		else if (p_rock.x > p_main.x) {
			rocks.at(index)->GetSprite()->setPosition(rocks.at(index)->GetSprite()->getPosition() +
				Vec2(SPEED_CHARACTOR_RUN, 0));
		}

		((MainCharactor*)(main_charactor))->Push();
	}
}

int GamePlay2::check_push()
{
	int index = 0;
	Vec2 p_main = main_charactor->GetSprite()->getPosition();
	Vec2 p_rock = rocks.at(0)->GetSprite()->getPosition();
	float min_horizontal = distance(p_main.x, p_rock.x);

	float _dis_horizontal = main_charactor->getSize().width / 2 + rocks.at(0)->getSize().width / 2;

	for (int i = 1; i < rocks.size(); i++) {
		float dis = distance(p_main.x, rocks.at(i)->GetSprite()->getPosition().x);
		if (dis < min_horizontal) {
			min_horizontal = dis;
			index = i;
		}
	}

	p_rock = rocks.at(index)->GetSprite()->getPosition();

	if (p_main.y > p_rock.y - 5 && p_main.y < p_rock.y + 5) {
		if (p_rock.x < p_main.x) {
			if ((min_horizontal - rocks.at(0)->getSize().width / 2 - 60) <= _dis_horizontal) {
				return index;
			}
		}
		else if (p_rock.x > p_main.x) {
			if ((min_horizontal + rocks.at(0)->getSize().width / 2) <= _dis_horizontal) {
				return index;
			}
		}
	}
	return -1;
}

float GamePlay2::distance_1(float p_1, float p_2)
{
	return p_1 - p_2;
}

float GamePlay2::distance(float main, float rock)
{
	//Vec2 P_main = main->GetSprite()->getPosition();
	//Vec2 P_rock = rock->GetSprite()->getPosition();

	//float dis = sqrt((P_main.x - P_rock.x)*(P_main.x - P_rock.x) + (P_main.y - P_rock.y)*(P_main.y - P_rock.y));
	float dis = abs(main - rock);

	return dis;
}

void GamePlay2::Fight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
	{
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_icehammer.mp3", false);
		}
		fight = true;
		break;
	}
	case ui::Widget::TouchEventType::ENDED:
		fight = false;
		break;
	}
}

void GamePlay2::Jump(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
	{
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_hammer.mp3", false);
		}
		
		if (!moveUp && fall)
		{
			fall = false;
			moveUp = true;
		}
		break;
	}
	case ui::Widget::TouchEventType::MOVED:
		if (!moveUp && fall)
		{
			fall = false;
			moveUp = true;
		}
		break;
	case ui::Widget::TouchEventType::ENDED:
		fall = true;
		moveUp = false;
		break;
	}
}

void GamePlay2::checkGround()
{
	Vec2 _mapPos = _tileMap->getPosition();

	// down
	for (int i = 0; i < _Line_Down_Pos_1.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		// ngang
		if (_Line_Down_Pos_1.at(i).y == _Line_Down_Pos_1.at(i + 1).y) {
			if ((_main_pos.y <= _Line_Down_Pos_1.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_1.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.x >= _Line_Down_Pos_1.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Down_Pos_1.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Down_Pos_1.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Down_Pos_1.at(i).x == _Line_Down_Pos_1.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Down_Pos_1.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Down_Pos_1.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y <= _Line_Down_Pos_1.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_1.at(i + 1).y - (0 - _mapPos.y) - 5)) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_1.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Down_Pos_1.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Down_Pos_1.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y >= _Line_Down_Pos_1.at(i).y - (0 - _mapPos.y) - 5) &&
				(_main_pos.y <= _Line_Down_Pos_1.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_1.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}
	for (int i = 0; i < _Line_Down_Pos_2.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		// ngang
		if (_Line_Down_Pos_2.at(i).y == _Line_Down_Pos_2.at(i + 1).y) {
			if ((_main_pos.y <= _Line_Down_Pos_2.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_2.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.x >= _Line_Down_Pos_2.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Down_Pos_2.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Down_Pos_2.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Down_Pos_2.at(i).x == _Line_Down_Pos_2.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Down_Pos_2.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Down_Pos_2.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y <= _Line_Down_Pos_2.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_2.at(i + 1).y - (0 - _mapPos.y) - 5)) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_2.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Down_Pos_2.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Down_Pos_2.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y >= _Line_Down_Pos_2.at(i).y - (0 - _mapPos.y) - 5) &&
				(_main_pos.y <= _Line_Down_Pos_2.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_2.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}
	for (int i = 0; i < _Line_Down_Pos_3.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		// ngang
		if (_Line_Down_Pos_3.at(i).y == _Line_Down_Pos_3.at(i + 1).y) {
			if ((_main_pos.y <= _Line_Down_Pos_3.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_3.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.x >= _Line_Down_Pos_3.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Down_Pos_3.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Down_Pos_3.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Down_Pos_3.at(i).x == _Line_Down_Pos_3.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Down_Pos_3.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Down_Pos_3.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y <= _Line_Down_Pos_3.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_3.at(i + 1).y - (0 - _mapPos.y) - 5)) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_3.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Down_Pos_3.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Down_Pos_3.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y >= _Line_Down_Pos_3.at(i).y - (0 - _mapPos.y) - 5) &&
				(_main_pos.y <= _Line_Down_Pos_3.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_3.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}
	for (int i = 0; i < _Line_Down_Pos_4.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		// ngang
		if (_Line_Down_Pos_4.at(i).y == _Line_Down_Pos_4.at(i + 1).y) {
			if ((_main_pos.y <= _Line_Down_Pos_4.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_4.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.x >= _Line_Down_Pos_4.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Down_Pos_4.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Down_Pos_4.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Down_Pos_4.at(i).x == _Line_Down_Pos_4.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Down_Pos_4.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Down_Pos_4.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y <= _Line_Down_Pos_4.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_4.at(i + 1).y - (0 - _mapPos.y) - 5)) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_4.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Down_Pos_4.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Down_Pos_4.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y >= _Line_Down_Pos_4.at(i).y - (0 - _mapPos.y) - 5) &&
				(_main_pos.y <= _Line_Down_Pos_4.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_4.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}
	for (int i = 0; i < _Line_Down_Pos_5.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		// ngang
		if (_Line_Down_Pos_5.at(i).y == _Line_Down_Pos_5.at(i + 1).y) {
			if ((_main_pos.y <= _Line_Down_Pos_5.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_5.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.x >= _Line_Down_Pos_5.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Down_Pos_5.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Down_Pos_5.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Down_Pos_5.at(i).x == _Line_Down_Pos_5.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Down_Pos_5.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Down_Pos_5.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y <= _Line_Down_Pos_5.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_5.at(i + 1).y - (0 - _mapPos.y) - 5)) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_5.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Down_Pos_5.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Down_Pos_5.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y >= _Line_Down_Pos_5.at(i).y - (0 - _mapPos.y) - 5) &&
				(_main_pos.y <= _Line_Down_Pos_5.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_5.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}
	for (int i = 0; i < _Line_Down_Pos_6.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		// ngang
		if (_Line_Down_Pos_6.at(i).y == _Line_Down_Pos_6.at(i + 1).y) {
			if ((_main_pos.y <= _Line_Down_Pos_6.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_6.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.x >= _Line_Down_Pos_6.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Down_Pos_6.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Down_Pos_6.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Down_Pos_6.at(i).x == _Line_Down_Pos_6.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Down_Pos_6.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Down_Pos_6.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y <= _Line_Down_Pos_6.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_6.at(i + 1).y - (0 - _mapPos.y) - 5)) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_6.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Down_Pos_6.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Down_Pos_6.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y >= _Line_Down_Pos_6.at(i).y - (0 - _mapPos.y) - 5) &&
				(_main_pos.y <= _Line_Down_Pos_6.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_6.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	// up
	for (int i = 0; i < _Line_Up_Pos_1.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		if (_Line_Up_Pos_1.at(i).y == _Line_Up_Pos_1.at(i + 1).y) {
			if ((_main_pos.y >= _Line_Up_Pos_1.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_1.at(i).y - (0 - _mapPos.y) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_1.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Up_Pos_1.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Up_Pos_1.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Up_Pos_1.at(i).x == _Line_Up_Pos_1.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Up_Pos_1.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Up_Pos_1.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y >= _Line_Up_Pos_1.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_1.at(i + 1).y - (0 - _mapPos.y) + 5)) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_1.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Up_Pos_1.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_1.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y <= _Line_Up_Pos_1.at(i).y - (0 - _mapPos.y) + 5) &&
				(_main_pos.y >= _Line_Up_Pos_1.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_1.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	for (int i = 0; i < _Line_Up_Pos_2.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		if (_Line_Up_Pos_2.at(i).y == _Line_Up_Pos_2.at(i + 1).y) {
			if ((_main_pos.y >= _Line_Up_Pos_2.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_2.at(i).y - (0 - _mapPos.y) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_2.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Up_Pos_2.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Up_Pos_2.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Up_Pos_2.at(i).x == _Line_Up_Pos_2.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Up_Pos_2.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Up_Pos_2.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y >= _Line_Up_Pos_2.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_2.at(i + 1).y - (0 - _mapPos.y) + 5)) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_2.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Up_Pos_2.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_2.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y <= _Line_Up_Pos_2.at(i).y - (0 - _mapPos.y) + 5) &&
				(_main_pos.y >= _Line_Up_Pos_2.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_2.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	for (int i = 0; i < _Line_Up_Pos_3.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		if (_Line_Up_Pos_3.at(i).y == _Line_Up_Pos_3.at(i + 1).y) {
			if ((_main_pos.y >= _Line_Up_Pos_3.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_3.at(i).y - (0 - _mapPos.y) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_3.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Up_Pos_3.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Up_Pos_3.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Up_Pos_3.at(i).x == _Line_Up_Pos_3.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Up_Pos_3.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Up_Pos_3.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y >= _Line_Up_Pos_3.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_3.at(i + 1).y - (0 - _mapPos.y) + 5)) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_3.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Up_Pos_3.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_3.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y <= _Line_Up_Pos_3.at(i).y - (0 - _mapPos.y) + 5) &&
				(_main_pos.y >= _Line_Up_Pos_3.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_3.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	for (int i = 0; i < _Line_Up_Pos_4.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		if (_Line_Up_Pos_4.at(i).y == _Line_Up_Pos_4.at(i + 1).y) {
			if ((_main_pos.y >= _Line_Up_Pos_4.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_4.at(i).y - (0 - _mapPos.y) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_4.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Up_Pos_4.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Up_Pos_4.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Up_Pos_4.at(i).x == _Line_Up_Pos_4.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Up_Pos_4.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Up_Pos_4.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y >= _Line_Up_Pos_4.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_4.at(i + 1).y - (0 - _mapPos.y) + 5)) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_4.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Up_Pos_4.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_4.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y <= _Line_Up_Pos_4.at(i).y - (0 - _mapPos.y) + 5) &&
				(_main_pos.y >= _Line_Up_Pos_4.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_4.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	for (int i = 0; i < _Line_Up_Pos_5.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		if (_Line_Up_Pos_5.at(i).y == _Line_Up_Pos_5.at(i + 1).y) {
			if ((_main_pos.y >= _Line_Up_Pos_5.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_5.at(i).y - (0 - _mapPos.y) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_5.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Up_Pos_5.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Up_Pos_5.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Up_Pos_5.at(i).x == _Line_Up_Pos_5.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Up_Pos_5.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Up_Pos_5.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y >= _Line_Up_Pos_5.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_5.at(i + 1).y - (0 - _mapPos.y) + 5)) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_5.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Up_Pos_5.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_5.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y <= _Line_Up_Pos_5.at(i).y - (0 - _mapPos.y) + 5) &&
				(_main_pos.y >= _Line_Up_Pos_5.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_5.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	for (int i = 0; i < _Line_Up_Pos_6.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		if (_Line_Up_Pos_6.at(i).y == _Line_Up_Pos_6.at(i + 1).y) {
			if ((_main_pos.y >= _Line_Up_Pos_6.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_6.at(i).y - (0 - _mapPos.y) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_6.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Up_Pos_6.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Up_Pos_6.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Up_Pos_6.at(i).x == _Line_Up_Pos_6.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Up_Pos_6.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Up_Pos_6.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y >= _Line_Up_Pos_6.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_6.at(i + 1).y - (0 - _mapPos.y) + 5)) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_6.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Up_Pos_6.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_6.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y <= _Line_Up_Pos_6.at(i).y - (0 - _mapPos.y) + 5) &&
				(_main_pos.y >= _Line_Up_Pos_6.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_6.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}
}

void GamePlay2::Pause(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::ENDED:
		auto funcPause = CallFunc::create([]() {
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
			}
			Director::getInstance()->pause();
			//SimpleAudioEngine::getInstance()->pauseAllEffects();
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		});
		btnPause2->setVisible(false);
		mBump2->setVisible(false);
		mPauseLayer2->setOpacity(0);
		mPauseLayer2->setVisible(true);
		auto fadeIn = FadeIn::create(0.3f);
		mPauseLayer2->runAction(Sequence::create(fadeIn, funcPause, nullptr));
		break;
	}
}

void GamePlay2::update(float deltaTime)
{
	main_charactor->Update(deltaTime);

	// set view
	this->setViewPointCenter(main_charactor->GetSprite()->getPosition());


	// update blood
	bloodBar->setPercent(this->main_charactor->GetBlood());

	// update number diamond
	CCString *num = CCString::createWithFormat("%i/20", numDiamond2);
	LabelNumDiamon->setString(num->getCString());

	// push rock
	push_rock();

	////////////// ground
	checkGround();

	//Update Joystick
	UpdateJoystick(deltaTime);
}

void GamePlay2::setViewPointCenter(CCPoint position)
{
	CCSize winSize = Director::getInstance()->getVisibleSize();

	Vec2 mapMoveDistance = Vec2(0, 0);
	Vec2 mcMoveDistance = Vec2(0, 0);
	if (moveRight)
	{
		if (main_charactor->GetSprite()->getPosition().x < winSize.width / 2)
		{
			mcMoveDistance = Vec2(SPEED_CHARACTOR_RUN, 0);
		}
		else
		{
			float mapWidth = _tileMap->getMapSize().width * _tileMap->getTileSize().width * 2;
			if (_tileMap->getPosition().x > -(mapWidth - winSize.width - SPEED_CHARACTOR_RUN))
			{
				mapMoveDistance = -Vec2(SPEED_CHARACTOR_RUN, 0);
			}
			else if (main_charactor->GetSprite()->getPosition().x <= (winSize.width - SPEED_CHARACTOR_RUN))
			{
				mcMoveDistance = Vec2(SPEED_CHARACTOR_RUN, 0);
			}
		}
	}
	else if (moveLeft)
	{
		if (main_charactor->GetSprite()->getPosition().x > winSize.width / 2)
		{
			mcMoveDistance = -Vec2(SPEED_CHARACTOR_RUN, 0);
		}
		else
		{
			if (_tileMap->getPosition().x <= -SPEED_CHARACTOR_RUN)
			{
				mapMoveDistance = Vec2(SPEED_CHARACTOR_RUN, 0);
			}
			else if (main_charactor->GetSprite()->getPosition().x >= SPEED_CHARACTOR_RUN)
			{
				mcMoveDistance = -Vec2(SPEED_CHARACTOR_RUN, 0);
			}
		}
	}
	else if (moveUp || jump)
	{

		if (main_charactor->GetSprite()->getPosition().y < winSize.height / 2)
		{
			mcMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN + 5);
		}
		else
		{
			float mapHeight = _tileMap->getMapSize().height * _tileMap->getTileSize().height * 2;
			if (_tileMap->getPosition().y > -(mapHeight - winSize.height - SPEED_CHARACTOR_RUN))
			{
				mapMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN);
			}
			else if (main_charactor->GetSprite()->getPosition().y <= (winSize.height))
			{
				mcMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN);
			}
		}
	}
	else if (moveDown)
	{
		if (main_charactor->GetSprite()->getPosition().y > winSize.height / 2)
		{
			mcMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN);
		}
		else
		{
			if (_tileMap->getPosition().y <= -SPEED_CHARACTOR_RUN)
			{
				mapMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN);
			}
			else if (main_charactor->GetSprite()->getPosition().y >= SPEED_CHARACTOR_RUN)
			{
				mcMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN);
			}
		}
	}

	else if (main_charactor->GetSprite()->getPosition().y < Director::getInstance()->getWinSize().height / 2 &&
		_tileMap->getPosition().y < 0) {
		if (main_charactor->GetSprite()->getPosition().y > winSize.height / 2)
		{
			//mcMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN);
		}
		else
		{
			if (_tileMap->getPosition().y <= -SPEED_CHARACTOR_RUN)
			{
				mapMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN);
			}
		}
		if (moveLeft) {
			mcMoveDistance = -Vec2(SPEED_CHARACTOR_RUN, 0);
		}
		if (moveRight) {
			mcMoveDistance = Vec2(SPEED_CHARACTOR_RUN, 0);
		}
	}


	if (mcMoveDistance != Vec2(0, 0))
	{
		main_charactor->GetSprite()->setPosition(main_charactor->GetSprite()->getPosition() + mcMoveDistance);
	}

	if (mapMoveDistance != Vec2(0, 0))
	{
		// update map
		_tileMap->setPosition(_tileMap->getPosition() + mapMoveDistance);

		// update spider
		for (int i = 0; i < spiders.size(); i++)
		{
			spiders.at(i)->GetSprite()->setPosition(spiders.at(i)->GetSprite()->getPosition() + mapMoveDistance);
		}

		// update glass
		for (int i = 0; i < glasss.size(); i++)
		{
			glasss.at(i)->GetSprite()->setPosition(glasss.at(i)->GetSprite()->getPosition() + mapMoveDistance);
		}

		// update diamon
		for (int i = 0; i < diamons.size(); i++)
		{
			diamons.at(i)->GetSprite()->setPosition(diamons.at(i)->GetSprite()->getPosition() + mapMoveDistance);
		}

		// update rock
		for (int i = 0; i < rocks.size(); i++)
		{
			rocks.at(i)->GetSprite()->setPosition(rocks.at(i)->GetSprite()->getPosition() + mapMoveDistance);
		}

		// update blood
		blood_1->setPosition(blood_1->getPosition() + mapMoveDistance);
		blood_2->setPosition(blood_2->getPosition() + mapMoveDistance);
	}
}

void GamePlay2::CreateJoystick(Layer * layer)
{
	auto thumb = Sprite::create("thumb.png");
	auto joystick = Sprite::create("joystick.png");
	Rect joystickBaseDimensions = Rect(0, 0, 40.f, 40.0f);
	Point joystickBasePosition;
	joystickBasePosition = Vec2(MARGIN_JOYSTICK + thumb->getBoundingBox().size.width / 2 + joystick->getBoundingBox().size.width / 2
		, MARGIN_JOYSTICK + thumb->getBoundingBox().size.height / 2 + joystick->getBoundingBox().size.height / 2);

	joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(Vec2(100, 100));
	joystickBase->setBackgroundSprite(thumb);
	joystickBase->setAnchorPoint(Vec2(0, 0));
	joystickBase->setThumbSprite(joystick);
	joystickBase->getThumbSprite()->setScale(0.2f);
	joystickBase->setScale(1.0f);
	joystick->setScale(0.5f);
	SneakyJoystick *aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);
	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(Vec2(100, 100));

	leftJoystick = joystickBase->getJoystick();
	activeRunRange = thumb->getBoundingBox().size.height / 2;
	layer->addChild(joystickBase);
}

void GamePlay2::UpdateJoystick(float dt)
{

	Point pos = leftJoystick->getStickPosition();
	float radius = std::sqrt(pos.x*pos.x + pos.y*pos.y);
	if (radius > 0)
	{
		float degree = std::atan2f(pos.y, pos.x) * 180 / 3.141593;
		if (degree > 135 && degree < 180 || degree > -180 && degree < -135)//MoveLeft
		{
			moveRight = false;
			moveLeft = true;
			moveUp = false;
			moveDown = false;
		}
		if (degree > -135 && degree < -45)//Move Down
		{
			moveRight = false;
			moveLeft = false;
			moveUp = false;
			moveDown = true;
		}
		if (degree > -45 && degree < 45)//Move Right
		{
			moveRight = true;
			moveLeft = false;
			moveUp = false;
			moveDown = false;
		}
		if (degree > 45 && degree < 135)//Move Up
		{
			moveRight = false;
			moveLeft = false;
			moveUp = true;
			moveDown = false;
		}
	}
	else
	{
		moveRight = false;
		moveLeft = false;
		moveUp = false;
		moveDown = false;
	}
}

GamePlay2::GamePlay2()
{
}

GamePlay2::~GamePlay2()
{
}

bool GamePlay2::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::BEGAN;
	mCurrentTouchPoint = touch->getLocation();
	return true;
}

void GamePlay2::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
}

void GamePlay2::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::ENDED;
	mCurrentTouchPoint = Point(-1, -1);
}

void GamePlay2::OnKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_Q:
	{
		if (moveLeft || moveRight)
		{
			fight = false;
		}
		else
		{
			fight = true;
		}

		break;
	}

	case EventKeyboard::KeyCode::KEY_A:
	{
		moveLeft = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	{
		moveRight = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_W:
	{
		moveUp = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_S:
	{
		moveDown = true;
		break;
	}
	default:
		break;
	}
}

void GamePlay2::OnKeyReleased(EventKeyboard::KeyCode keycode, Event * event)

{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_Q:
	{
		fight = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_A:
	{
		moveLeft = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	{
		moveRight = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_W:
	{
		moveUp = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_S:
	{
		moveDown = false;
		break;
	}
	default:
		break;
	}
}
