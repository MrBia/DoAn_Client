#pragma once
#include "2d\CCLayer.h"
#include "cocos2d.h"
#include "Objject.h"
#include "MainCharactor.h"
#include "SneakyJoystickSkinnedBase.h"
#include "Rock.h"
#include "Glass2.h"
#include "Diamond.h"
#include "Spider.h"
#include "MapGame.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

class GamePlay2 :
	public Layer
{
private:
	//Object
	Objject* main_charactor;
	std::vector<Spider*> spiders;
	std::vector<Objject*> glasss;
	std::vector<Objject*> diamons;
	std::vector<Objject*> rocks;
	
	// fire
	cocos2d::TMXObjectGroup* mObjectFire;
	vector<Vec2> Fire_Normal_1;
	vector<Vec2> Fire_Normal_2;
	vector<Vec2> Fire_Normal_3;
	Objject* fire_normal_1;
	Objject* fire_normal_2;
	Objject* fire_normal_3;
	Sprite* blood_1;
	Sprite* blood_2;

	// collistion
	void checkGround();
	cocos2d::TMXObjectGroup* mObjects_line_down;
	vector<Vec2> _Line_Down_Pos_1;
	vector<Vec2> _Line_Down_Pos_2;
	vector<Vec2> _Line_Down_Pos_3;
	vector<Vec2> _Line_Down_Pos_4;
	vector<Vec2> _Line_Down_Pos_5;
	vector<Vec2> _Line_Down_Pos_6;
	cocos2d::TMXObjectGroup* mObjects_line_up;
	vector<Vec2> _Line_Up_Pos_1;
	vector<Vec2> _Line_Up_Pos_2;
	vector<Vec2> _Line_Up_Pos_3;
	vector<Vec2> _Line_Up_Pos_4;
	vector<Vec2> _Line_Up_Pos_5;
	vector<Vec2> _Line_Up_Pos_6;

	//State Move of Charactor
	bool moveLeft;
	bool moveRight;
	bool jump;
	bool moveUp;
	bool moveDown;
	int SPEED_CHARACTOR_RUN = 4;

	//State Action of Charactor
	bool fight;
	bool push;
	bool stun;
	bool fall;

	//Map
	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;
	CCTMXLayer *_wall;
	CCTMXLayer *_phy;
	cocos2d::TMXObjectGroup* mObjectGroup;
	cocos2d::TMXObjectGroup* mObjectGroup1;

	//Button
	cocos2d::ui::Button *mFireController;

	
	//Header bar
	int numDiamond2;
	Label* LabelNumDiamon;
	ui::LoadingBar *bloodBar;
	
	//
	cocos2d::EventKeyboard::KeyCode mCurrentKey;
	cocos2d::ui::Widget::TouchEventType mCurrentTouchState;
	cocos2d::Point mCurrentTouchPoint;

	Vec2 _thang_1;
	Vec2 _thang_2;

	/////////// test ground not physic
	Vec2 _ground_Pos;
	Vec2 _ground_Pos_1;
	Vec2 _ground_Pos_2;
	bool _collistionGround = false;
	float distance_1(float p_1, float p_2);

	//////////////////////////////// test tiep
	Vec2 _ground_Pos_12;
	Vec2 _ground_Pos_13;
	Vec2 _ground_Pos_14;
	Vec2 _ground_Pos_15;
	Vec2 _ground_Pos_16;
	Vec2 _ground_Pos_17;
	Vec2 _ground_Pos_18;
	Vec2 _ground_Pos_19;
	Vec2 _ground_Pos_20;
	Vec2 _ground_Pos_21;
	Vec2 _ground_Pos_22;
	Vec2 _ground_Pos_23;
	Vec2 _ground_Pos_24;

public:
	GamePlay2();
	~GamePlay2();

	static Scene *createGame();
	virtual bool init();
	// update
	void update(float deltaTime);
	CREATE_FUNC(GamePlay2);

	void createMap();
	void createMapPhysics();
	void createObject();
	void InitialState();
	void AddDispatcher();
	void setViewPointCenter(CCPoint position);
	void push_rock();
	int check_push();
	float distance(float main, float rock);
	bool OnContactBegin(PhysicsContact &contact);
	void CreateBloodBar();
	void CreateNumDiamon();
	void createPauseLayer();
	void Fight(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void Jump(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void climb();
	void Pause(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void InitialButton();


	// touch
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	
	//key
	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event *event);

	//Joystick
	void CreateJoystick(Layer * layer);
	void UpdateJoystick(float dt);
	SneakyJoystick *leftJoystick;
	SneakyJoystickSkinnedBase* joystickBase;
	float activeRunRange;
};

