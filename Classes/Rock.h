#pragma once
#include "Objject.h"

class Rock : public Objject
{
private:
	Layer* layer;
public:
	void Init();
	void Update(float deltaTime);
	Rock(Layer* layer);
	Sprite* Clone(Sprite* sprite);
	Size getSize();
	~Rock();
};

