#pragma once
#include "Objject.h"
class Glass : public Objject
{
private:
	Layer* layer;
public:
	void Init();
	void Update(float deltaTime);
	Glass(Layer* layer);
	Sprite *Clone(Sprite *sprite);
	Size getSize();
	~Glass();
};

