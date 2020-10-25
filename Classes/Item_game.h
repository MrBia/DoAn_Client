#pragma once
#include "Objject.h"
class Item_game : public Objject
{
private:
	Layer* layer;
	CCPoint touch;
	bool collect;
public:
	void SetTouch(CCPoint touch);
	void Init();
	void Update(float deltaTime);
	Item_game(Layer* layer);
	bool isCollect();
	~Item_game();
	Sprite* Clone(Sprite* sprite);
	void random(Objject* object);
};

