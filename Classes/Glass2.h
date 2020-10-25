#pragma once
#include "Objject.h"
class Glass2 : public Objject
{
private:
	Layer* layer;
public:
	void Init();
	void Update(float deltaTime);
	Glass2(Layer* layer);
	Sprite *Clone(Sprite *sprite);
	Size getSize();
	~Glass2();
};

