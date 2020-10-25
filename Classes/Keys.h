#pragma once
#include "Objject.h"
class Keys : public Objject
{
private:
	bool map;
	Layer* layer;
	CCTMXTiledMap *_tileMap;
	vector<Vec2> Key_pos;
public:
	void Init();
	void Update(float deltaTime);
	Size getSize();
	Keys(Layer* layer, bool map);
	void setPos(vector<Vec2> Key_pos, CCTMXTiledMap *_tileMap);
	~Keys();
};

