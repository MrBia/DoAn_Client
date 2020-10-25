#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <map>
#include <string.h>

using namespace std;
USING_NS_CC;

enum Action_Spider {
	S_UP,
	S_DOWN,
	S_SIDE
};

enum Action_Charactor {
	CH_UP,
	CH_RUN,
	CH_DOWN,
	CH_LEFT,
	CH_RIGHT,
	CH_PUSH,
	CH_FIGHT,
	CH_WAIT,
	CH_STUN
};


class ResourceManager
{
private:
	string m_dataFolderPath;
	map<int, Sprite*> m_sprites;
	map<int, Sprite*> m_load;
	map<int, Sprite*> m_item;
	map<int, ui::Button*> m_button;
	map<int, Vector<SpriteFrame*>> m_spider_action;
	map<int, Vector<SpriteFrame*>> m_charactor_action;
	map<int, Sprite*> m_background;
	map<int, Vector<SpriteFrame*>> m_diamond_action;
	map<int, Vector<SpriteFrame*>> m_fire_action;   // lua

	ResourceManager();
	static ResourceManager* instance;
public:
	static ResourceManager* GetInstance();
	void Init(const string path);
	void Load(string fileName);
	Sprite* GetSpriteById(int id);
	Sprite * GetBackgroundById(int id);
	Sprite* GetLoadById(int id);
	Sprite* GetItemById(int id);
	ui::Button* GetButtonById(int id);
	Vector<SpriteFrame*> GetSpiderUp();
	Vector<SpriteFrame*> GetSpiderDown();
	Vector<SpriteFrame*> GetSpiderSide();
	
	Vector<SpriteFrame*> GetCharactorUp();
	Vector<SpriteFrame*> GetCharactorDown();
	Vector<SpriteFrame*> GetCharactorLeft();
	Vector<SpriteFrame*> GetCharactorRight();
	Vector<SpriteFrame*> GetCharactorPush();
	Vector<SpriteFrame*> GetCharactorFight();
	Vector<SpriteFrame*> GetCharactorWait();
	Vector<SpriteFrame*> GetCharactorRun();
	Vector<SpriteFrame*> GetCharactorStun();
	Vector<SpriteFrame*> GetFrameDiamond();

	Vector<SpriteFrame*> GetActionFire();

	/**
	*  discribe: return a vector contain arr value after split
	*  @param 1: string to split
	*  @param 2: charactor
	*/
	std::vector<std::string> Split(std::string str1, std::string str2);

	/**
	*  discribe: delete " " in data received from server
	*  @param: string  data
	*  @return: data format
	*/
	std::string formatData(std::string data);

	/**
	*  discribe: get x and y in data
	*  @param: string  data
	*  @return: data format
	*/
	std::vector<std::string> formatDataObject(std::string str1);

	int Get_ID(string s);
	std::string Get_Path(string s);
	~ResourceManager();
};

