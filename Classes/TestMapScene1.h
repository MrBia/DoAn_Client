#pragma once
#include "2d\CCLayer.h"
#include "cocos2d.h"
#include "Objject.h"
#include "MainCharactor.h"
#include "ResourceManager.h"


USING_NS_CC;

class TestMapScene1 :
	public Layer
{
private:
	TMXTiledMap* map;
	TMXLayer* background;
	TMXLayer* wall;
	TMXLayer* meta;
	Sprite* mainCh;

	PhysicsBody* physicsBody;

	Objject* Main_Charactor;

public:
	static Scene* createMap();
	bool init() override;
	void update(float deltaTime);

	

	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void setViewPointCenter(CCPoint position);
	void setPlayerPosition(CCPoint position);
	CCPoint tileCoorforposition(CCPoint position);

	CREATE_FUNC(TestMapScene1);

	TestMapScene1();
	~TestMapScene1();
};

