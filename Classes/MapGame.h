#ifndef __MAPGAME_SCENE_H__
#define __MAPGAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MapGame.h"
#include "GamePlay.h"
#include "GamePlay2.h"
#include "MainMenu.h"

USING_NS_CC;
using namespace CocosDenshion;

class MapGame : public cocos2d::Scene
{
private:
	cocos2d::ui::Button* btnBack;
	cocos2d::ui::Button* btnMap1;
	cocos2d::ui::Button* btnMap2;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float deltaTime);
	CREATE_FUNC(MapGame);

	void createBackground();
	void createButton();
};

#endif // __MAPGAMEs_SCENE_H__
