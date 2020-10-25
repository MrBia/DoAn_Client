#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "MapGame.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

class MainMenu : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float deltaTime);
	CREATE_FUNC(MainMenu);

	void createBackground();

	void createBackgroundMusic();

	void addButton();

	void createSetting();

	void activeSetting();

	
};

#endif // __MAINMENU_SCENE_H__
