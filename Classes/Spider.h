#pragma once
#include "Objject.h"

enum actions_spider {
	GO_UP,
	GO_DOWN,
	GO_LEFT,
	GO_RIGHT
};

class Spider : public Objject
{
private:
	bool isLeft;
	bool isRight;
	bool state = true;
	bool catogory = true;

	Scene* scene;
	Layer* layer;
	Action* action_up;
	Action* action_down;
	Action* action_side;
public:
	void Init();
	void InitialSPider();
	void InitialAction();
	void Update(float deltaTime);
	Size getSize();
	void goUp();
	void goDown();
	void goSide();
	void goLeft();
	void goRight();
	void setState(bool state);
	bool isAlive();
	void setCatogory(bool cotogory);
	bool isCatogory();

	void RotateLeft();
	void RotateRight();
	Spider(Layer* layer);
	~Spider();
};

