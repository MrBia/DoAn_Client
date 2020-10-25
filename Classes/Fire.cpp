#include "Fire.h"



void Fire::Init()
{
	this->SetSprite(Sprite::create("Fire/fire10.png"));
	this->GetSprite()->retain();

	// run action
	auto animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetActionFire(), 0.2);
	auto animate = Animate::create(animation);
	animate->retain();
	this->GetSprite()->runAction(RepeatForever::create(animate));
	if (map) {
		this->GetSprite()->setScale(SCALE_FIRE);
	}
	else {
		this->GetSprite()->setScale(SCALE_FIRE_2);
	}
	this->GetSprite()->setTag(TAG_FIRE);
	this->GetSprite()->setAnchorPoint(Vec2(0, 0));

	// physics body
	physic = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physic->setRotationEnable(false);
	physic->setContactTestBitmask(1);
	physic->setDynamic(false);
	//physic->setGravityEnable(false);
	this->GetSprite()->setPhysicsBody(physic);
}

void Fire::Update(float deltaTime)
{
	if (isAI()) {
		runAI();
	}
}

Fire::Fire(Layer* layer, bool map)
{
	this->layer = layer;
	this->map = map;
	Init();
}

Size Fire::getSize()
{
	return Size();
}

void Fire::setPos(vector<Vec2> Fire_pos, CCTMXTiledMap *_tileMap, vector<Vec2> AI_View)
{
	this->Fire_pos = Fire_pos;
	this->_tileMap = _tileMap;
	this->AI_View = AI_View;
	this->GetSprite()->setPosition(Fire_pos.at(0));
	this->_tileMap->addChild(this->GetSprite(), 5);

	if (!isAI()) {
		auto moveTo_1 = MoveTo::create(1, Fire_pos.at(1));
		auto moveTo_2 = MoveTo::create(1, Fire_pos.at(2));
		auto moveTo_3 = MoveTo::create(1, Fire_pos.at(3));
		auto moveTo_4 = MoveTo::create(1, Fire_pos.at(0));
		auto sq = Sequence::create(moveTo_1, moveTo_2, moveTo_3, moveTo_4, nullptr);

		this->GetSprite()->runAction(RepeatForever::create(sq));
	}

	if (isAI()) {
		AI_pos = this->GetSprite()->getPosition();
	}
}

void Fire::setPosMain(Vec2 pos_main)
{
	this->pos_main = pos_main;
}

void Fire::setAI(bool c)
{
	this->AI = c;
}

bool Fire::isAI()
{
	return AI;
}

void Fire::runAI()
{
	Vec2 pos_AI = this->GetSprite()->getPosition();
	auto mapPOS = _tileMap->getPosition();
	float pos_main_x = pos_main.x + (0 - mapPOS.x);
	float pos_main_y = pos_main.y + (0 - mapPOS.y);

	if (!isKey) {
		if (pos_main_y > AI_View.at(0).y) {
			auto tl = getMove(Vec2(pos_main_x, pos_main_y), isKey);
			this->GetSprite()->setPosition(Vec2(pos_AI.x + tl.x, pos_AI.y + tl.y));
		}
	}
	else if (isKey) {
		if (pos_main_y > AI_View.at(1).y) {
			auto tl = getMove(Vec2(pos_main_x, pos_main_y), isKey);
			this->GetSprite()->setPosition(Vec2(pos_AI.x + tl.x, pos_AI.y + tl.y));
		}
	}

	if (pos_AI.x <= AI_pos.x + 5 && pos_AI.x >= AI_pos.x - 5 &&
		pos_AI.y <= AI_pos.y + 5 && pos_AI.y >= AI_pos.y - 5) {
		// not do
	}
	else {
		if (!isKey) {
			if (pos_main_y < AI_View.at(0).y) {
				auto tl = getMove(AI_pos, isKey);
				this->GetSprite()->setPosition(Vec2(pos_AI.x + tl.x, pos_AI.y + tl.y));
			}
		}
		else if (isKey) {
			if (pos_main_y < AI_View.at(1).y) {
				auto tl = getMove(AI_pos, isKey);
				this->GetSprite()->setPosition(Vec2(pos_AI.x + tl.x, pos_AI.y + tl.y));
			}
		}
	}
}

Vec2 Fire::getMove(Vec2 head, bool isKey)
{
	auto pos_main_x = head.x;
	auto pos_main_y = head.y;
	float speedAI;
	if (!isKey) {
		speedAI = RUN_1;
	}
	else {
		speedAI = RUN_2;
	}
	Vec2 pos_AI = this->GetSprite()->getPosition();

	// angle
	float alpha = atan((pos_main_y - pos_AI.y) / (pos_main_x - pos_AI.x))*(180 / M_PI);

	// x move   y move
	auto tlx = speedAI * cos(alpha*(M_PI / 180));
	auto tly = speedAI * sin(alpha*(M_PI / 180));

	if (tly > 0 && pos_main_x < pos_AI.x && pos_main_y < pos_AI.y) {
		tlx = -tlx;
		tly = -tly;
	}
	else if (tly < 0) {
		if (pos_main_x < pos_AI.x) {
			tlx = -tlx;
			tly = -tly;
		}
		else if (pos_main_y < pos_AI.y) {
			//tly = -tly;
		}
	}

	return Vec2(tlx, tly);
}

float Fire::distance(Vec2 main, Vec2 AI)
{
	auto mapPOS = _tileMap->getPosition();
	float dis = sqrt((main.x - AI.x)*(main.x - AI.x) +
		(main.y - AI.y)*(main.y - AI.y));

	return dis;
}

void Fire::setKey(bool isKey)
{
	this->isKey = isKey;
}

Fire::~Fire()
{
}
