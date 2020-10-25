#pragma once
#include "Objject.h"
#include "FightHammer.h"
#include "ui/CocosGUI.h"

enum Actions
{
	C_PUSH,
	C_FIGHT,
	C_WAIT,
	C_RUN,
	C_STUN
};

class MainCharactor : public Objject
{
private:
	bool isLeft;
	bool isRight;

	bool push;
	bool fight;
	bool fight_1 = false;
	bool stun;


	Layer *layer;

	Action *action_stun;
	Action *action_push;
	Action *action_fight;
	Action *action_wait;
	Action *action_run;
	cocos2d::PhysicsBody* physicbody;

	FightHammer* f;

	// ID
	string id;

	// STATE
	string state = "idle";
public:
	void Init();
	void InitialState();
	void CreateSprite();
	void InitialAction();

	void Update(float deltaTime);
	void Push();
	void Fight();
	void Stun();
	
	Size getSize();

	// TEST BY MR BIA
	void mvLeft();
	void mvRight();
	void idle();
	void rotateLeft();
	void rotateRight();
	bool isRotateLeft;
	bool isRotateRight;
	string currentAnim;

	// ID
	void setID(string id);
	string getID();

	// STATE
	void setState(string state);
	string getState();

	void RotateLeft();
	void RotateRight();
	MainCharactor(Layer *layer);
	Sprite *Clone(Sprite *sprite);
	~MainCharactor();

	void UpdateVelocity(Point velocity);
};
