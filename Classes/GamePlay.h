#pragma once
#include "2d\CCLayer.h"
#include "SneakyJoystickSkinnedBase.h"
#include "MainCharactor.h"
#include "Spider.h"
#include "Diamond.h"
#include "Rock.h"
#include "Glass.h"
#include "MainMenu.h"
#include "MapGame.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Fire.h"
#include "Keys.h"
#include "network\SocketIO.h"
#include <string>

using namespace CocosDenshion;
using namespace cocos2d::network;
USING_NS_CC;

class GamePlay : 
	public Layer, public SocketIO::SIODelegate
{
private:
	int numDiamond;
	Label* LabelNumDiamon;

	bool fight;
	bool push;
	bool moveLeft;
	bool moveRight;
	bool jump;
	bool stun;
	bool moveUp;
	bool moveDown;
	bool fall;

	// button
	cocos2d::ui::Button *mFireController;

	// map
	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;
	CCTMXLayer *_wall;
	CCTMXLayer *_phy;
	


	// main charactor
	Objject* main_charactor = NULL;
	ui::LoadingBar *bloodBar_1;
	ui::LoadingBar *bloodBar_2;
	int SPEED_CHARACTOR_RUN = 2;

	// fire
	cocos2d::TMXObjectGroup* mObjectFire;
	vector<Vec2> Fire_Normal_1;
	vector<Vec2> Fire_Normal_2;
	vector<Vec2> Fire_Normal_3;
	Objject* fire_normal_1;
	Objject* fire_normal_2;
	Objject* fire_normal_3;
	vector<Vec2> Fire_AI_1;
	Objject* fire_ai_1;
	vector<Vec2> AI_View;
	vector<Vec2> Keys_Pos;
	Objject* key;
	bool isKey = false;
	
	Sprite* blood_1;
	Sprite* blood_2;

	// fire dragon
	vector<Vec2> Fire_dragon_1;


	// state key
	cocos2d::EventKeyboard::KeyCode mCurrentKey;
	cocos2d::ui::Widget::TouchEventType mCurrentTouchState;
	cocos2d::Point mCurrentTouchPoint;

	// object map
	cocos2d::TMXObjectGroup* mObjectGroup;

	std::vector<Spider*> spiders;
	std::vector<Objject*> glasss;
	std::vector<Objject*> diamons;
	std::vector<Objject*> rocks;

	// collistion between map and charactor
	cocos2d::TMXObjectGroup* mObjectCollistion;
	int sizeTilemapWidth;
	int sizeTilemapHeight;

	// collistion cell
	std::map<int, list<int>> collistionCell;
	list<int> listCell;
	
	// TEST USING ARRAY TO SAVE POSITION OF OBJECT
	int **_arrayMap;
	int wid;
	int hei;
	int NONE = None1;
	int MAP = Map1;
	int PLAYER = Player1;
	int GRASS = Grass1;
	int ROCK = Rock1;
	int DIAMOND = Diamond1;
	// player pos
	float playerPosX;
	float playerPosY;

	// CONNECT TO SERVER
	SIOClient* _client = NULL;
	std::vector<MainCharactor*> players;
	std::vector<Diamond*> diamonds_1;
	std::vector<Glass*> grasses_1;
	std::vector<Rock*> rocks_1;

	string id;
	float xInit, yInit;
	string state = "idle";

	string idle = "idle";
	string left = "left";
	string right = "right";
	string up = "up";
	string down = "down";

public:
	static Scene *createGame();
	virtual bool init();
	void CreateMap();
	void InitialState();
	void InitialObject();
	void AddDispatcher();
	void InitialButton();
	void InitialPhysics();
	bool OnContactBegin(PhysicsContact &contact);
	void CreateBloodBar();
	void CreateNumDiamon();
	void createPauseLayer();
	void Fight(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void Pause(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	// push rock
	void push_rock();
	int check_push();
	float distance(float main, float rock);
	
	// update
	void update(float deltaTime);
	void updateUI();
	void updateArrayMap();
	void updatePositionItemByCell();

	// touch
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);


	// key
	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event *event);
	void setViewPointCenter(CCPoint position);


	// CONNECT TO SERVER

	/**
	* describe: send postion of player to server save
	*/
	void sendRequestInitToServer(SIOClient* client, const std::string &data);


	/**
	  * describe: receive the initialization command
	              if a player join, this func is used to init player
	  * @param: data: posX and posY to init player
	  */
	void receiveRequestInitFromServer(SIOClient* client, const std::string &data);

	// INIT OBJECT (DIAMOND, GRASS, ROCK)
	void initDiamonds(SIOClient* client, const std::string &data);
	void initGrasses(SIOClient* client, const std::string &data);
	void initRocks(SIOClient* client, const std::string &data);

	/**
	* describe: send state of player to the server
	*/
	void sendState();

	/**
	* describe: receive state from the server
	*/
	void receiveState(SIOClient* client, const std::string &data);

	/**
	* describe: update state of player
	*/
	void updateState();

	/**
	* describe: update position of player
	*/
	void updatePosition(SIOClient* client, const std::string &data);

	// camera
	void requestCamera();

	void receiveCamera(SIOClient* client, const std::string &data);

	/**
	* describe: update position of object etc diamon, rock,...
	* receive position from server
	*/
	void updateObject(SIOClient* client, const std::string &data);

	// test
	void updateObjectDiamond(SIOClient* client, const std::string &data);
	void updateObjectRock(SIOClient* client, const std::string &data);

	// sioDelegate

	virtual void onConnect(SIOClient* client);
	virtual void onMessage(SIOClient* client, const std::string& data);
	virtual void onClose(SIOClient* client);
	virtual void onError(SIOClient* client, const std::string& data);

	CREATE_FUNC(GamePlay);

	//Joystick
	void CreateJoystick(Layer * layer);
	void UpdateJoystick(float dt);
	SneakyJoystick *leftJoystick;
	SneakyJoystickSkinnedBase* joystickBase;
	float activeRunRange;

	GamePlay();
	~GamePlay();
};
