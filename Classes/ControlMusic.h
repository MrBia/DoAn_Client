#include"cocos2d.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

class ControlMusic
{
private:
	static ControlMusic *s_instance;

public:
	ControlMusic();
	~ControlMusic();

	bool music;
	bool sound;
	int volume;

	static ControlMusic* GetInstance();

	bool isMusic();
	void setMusic(bool music);
	bool isSound();
	void setSound(bool sound);
};