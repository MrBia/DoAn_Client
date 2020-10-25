#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include <MainMenu.h>
#include "ui/CocosGUI.h"
#include "ControlMusic.h"

using namespace CocosDenshion;
USING_NS_CC;

#define TIME_LOAD 3

class LoadingLogo : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	
	virtual bool init();
	
	void changeLoading(float dt);

	void update(float deltaTime);
	CREATE_FUNC(LoadingLogo);
};

#endif // __HELLOWORLD_SCENE_H__