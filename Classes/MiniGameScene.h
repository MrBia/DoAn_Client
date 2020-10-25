#ifndef __MINIGAME_SCENE_H__
#define __MINIGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MiniGame : public cocos2d::Layer
{
private:
	int score = 0;
	int life;
	std::string s;
	Sprite* diamond;
	PhysicsWorld* m_world;
	Label* scoreLabel;
	Label* lifeLabel;
	Label* lifeS;
	CCParallaxNode *_backgroundNode;
	CCSprite *_spacedust1;
	CCSprite *_spacedust2;
	CCSprite *_planetsunrise;
	CCSprite *_galaxy;
	CCSprite *_spacialanomaly;
	CCSprite *_spacialanomaly2;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float deltaTime);

	void setScore(int score) { this->score = score; };
	void setPhyWorld(PhysicsWorld* world) { m_world = world; };

	bool onContactBegin(PhysicsContact &contact);
	bool onTouchBegan(Touch *touch, Event *event);

	// implement the "static create()" method manually
	CREATE_FUNC(MiniGame);
};

#endif // __MINIGAME_SCENE_H__