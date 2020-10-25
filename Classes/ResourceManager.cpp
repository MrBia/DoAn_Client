#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = NULL;

ResourceManager::ResourceManager()
{
}

ResourceManager * ResourceManager::GetInstance()
{
	if (!instance) {
		instance = new ResourceManager;
	}
	return instance;
}

void ResourceManager::Init(const string path)
{
	this->m_dataFolderPath = path;
	Load(m_dataFolderPath);
}

void ResourceManager::Load(std::string fileName)
{
	std::string s = FileUtils::getInstance()->getStringFromFile(fileName);
	vector<std::string> arr_source = Split(s, "\r\n");

	for (size_t i = 0; i < arr_source.size(); i++) {
		// get name and number
		vector<std::string> arr_name = Split(arr_source[i], " ");

		if (arr_name[0] == "#SPRITE") {
			// number 
			int number = atoi(arr_name[1].c_str());
			while (number > 0) {
				i++;                  // id
				int id = Get_ID(arr_source[i]);

				i++;                  // path
				std::string path = Get_Path(arr_source[i]);

				// create sprite
				auto sprite = Sprite::create(path);
				log("path sprite1: %s", path.c_str());
				sprite->retain();
				log("path sprite1 after retain: %s", path.c_str());

				// insert map
				m_sprites.insert(pair<int, Sprite*>(id, sprite));

				number--;
			}
		}
		
		
		else if (arr_name[0] == "#LOAD") {
			// number 
			int number = atoi(arr_name[1].c_str());
			while (number > 0) {
				i++;                  // id
				int id = Get_ID(arr_source[i]);

				i++;                  // path
				std::string path = Get_Path(arr_source[i]);

				// create sprite
				auto sprite = Sprite::create(path);
				sprite->retain();

				// insert map
				m_load.insert(pair<int, Sprite*>(id, sprite));

				number--;
			}
		}
		else if (arr_name[0] == "#BUTTON") {
			// number 
			int number = atoi(arr_name[1].c_str());
			while (number > 0) {
				i++;                  // id
				int id = Get_ID(arr_source[i]);

				i++;                  // path
				std::string path = Get_Path(arr_source[i]);

				// create sprite
				auto button = ui::Button::create(path, "");
				log("path button: %s", path.c_str());
				button->retain();
				log("path button after retain: %s", path.c_str());

				// insert map
				m_button.insert(pair<int, ui::Button*>(id, button));

				number--;
			}
		}
		else if (arr_name[0] == "#ITEM") {
			// number 
			int number = atoi(arr_name[1].c_str());
			while (number > 0) {
				i++;                  // id
				int id = Get_ID(arr_source[i]);
				i++;                  // path
				std::string path = Get_Path(arr_source[i]);
				// create sprite
				auto item = Sprite::create(path);
				item->retain();
				// insert map
				m_item.insert(pair<int, Sprite*>(id, item));
				number--;
			}
		}
		else if (arr_name[0] == "#ACTION_CHARACTOR") {
			// number 
			int number = atoi(arr_name[1].c_str());
			while (number > 0) {
				i++;                  // id
				int id = Get_ID(arr_source[i]);

				i++;                  // path plist
				std::string path_1 = Get_Path(arr_source[i]);

				i++;			      // path png
				std::string path_2 = Get_Path(arr_source[i]);

				// load plist
				SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path_1, path_2);
				
				
				// insert map
				if (id == 0) {
					Vector<SpriteFrame*> spriteFrames_push;
					spriteFrames_push.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1.png"));
					spriteFrames_push.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("2.png"));
					spriteFrames_push.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("3.png"));
					spriteFrames_push.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("4.png"));
					spriteFrames_push.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("5.png"));
					spriteFrames_push.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("6.png"));

					m_charactor_action.insert(pair<int, Vector<SpriteFrame*>>(Action_Charactor::CH_PUSH, spriteFrames_push));
				}
				else if (id == 1) {
					Vector<SpriteFrame*> spriteFrames_wait;
					spriteFrames_wait.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("7.png"));
					spriteFrames_wait.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("8.png"));
					spriteFrames_wait.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("9.png"));
					spriteFrames_wait.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("10.png"));
					spriteFrames_wait.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("11.png"));
					spriteFrames_wait.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("12.png"));

					m_charactor_action.insert(pair<int, Vector<SpriteFrame*>>(Action_Charactor::CH_WAIT, spriteFrames_wait));
				}
				else if (id == 2) {
					Vector<SpriteFrame*> spriteFrames_run;
					spriteFrames_run.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("13.png"));
					spriteFrames_run.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("14.png"));
					spriteFrames_run.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("15.png"));
					spriteFrames_run.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("16.png"));
					spriteFrames_run.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("17.png"));
					spriteFrames_run.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("18.png"));

					m_charactor_action.insert(pair<int, Vector<SpriteFrame*>>(Action_Charactor::CH_RUN, spriteFrames_run));
				}
				else if (id == 3) {
					Vector<SpriteFrame*> spriteFrames_fight;
					spriteFrames_fight.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fight_1.png"));
					spriteFrames_fight.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fight_2.png"));
					spriteFrames_fight.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fight_3.png"));

					m_charactor_action.insert(pair<int, Vector<SpriteFrame*>>(Action_Charactor::CH_FIGHT, spriteFrames_fight));
				}
				else if (id == 4) {
					Vector<SpriteFrame*> spriteFrames_stun;
					spriteFrames_stun.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("stun_1.png"));
					spriteFrames_stun.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("stun_2.png"));
					spriteFrames_stun.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("stun_3.png"));

					m_charactor_action.insert(pair<int, Vector<SpriteFrame*>>(Action_Charactor::CH_STUN, spriteFrames_stun));
				}
				number--;
			}
		}
		else if (arr_name[0] == "#ACTION_SPIDER") {
			// number 
			int number = atoi(arr_name[1].c_str());

			while (number > 0) {
				i++;                  // id
				int id = Get_ID(arr_source[i]);

				i++;                  // path 1
				std::string path_1 = Get_Path(arr_source[i]);

				i++;                  // path 2
				std::string path_2 = Get_Path(arr_source[i]);

				// load plist
				SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path_1, path_2);

				// insert map
				if (id == 0) {
					Vector<SpriteFrame*> spiderFrames_down;
					spiderFrames_down.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_01.png"));
					spiderFrames_down.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_02.png"));
					spiderFrames_down.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_03.png"));
					spiderFrames_down.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_04.png"));
					spiderFrames_down.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_05.png"));
					spiderFrames_down.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_06.png"));

					m_spider_action.insert(pair<int, Vector<SpriteFrame*>>(Action_Spider::S_DOWN, spiderFrames_down));
				}
				else if (id == 1) {
					Vector<SpriteFrame*> spiderFrames_up;
					spiderFrames_up.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_13.png"));
					spiderFrames_up.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_14.png"));
					spiderFrames_up.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_15.png"));
					spiderFrames_up.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_16.png"));
					spiderFrames_up.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_17.png"));
					spiderFrames_up.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_18.png"));

					m_spider_action.insert(pair<int, Vector<SpriteFrame*>>(Action_Spider::S_UP, spiderFrames_up));
				}
				else if (id == 2) {
					Vector<SpriteFrame*> spiderFrames_side;
					spiderFrames_side.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_07.png"));
					spiderFrames_side.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_08.png"));
					spiderFrames_side.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_09.png"));
					spiderFrames_side.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_10.png"));
					spiderFrames_side.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_11.png"));
					spiderFrames_side.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("spider_12.png"));

					m_spider_action.insert(pair<int, Vector<SpriteFrame*>>(Action_Spider::S_SIDE, spiderFrames_side));
				}

				number--;
			}
		}
		else if (arr_name[0] == "#ACTION_DIAMOND") {
			// number 
			int number = atoi(arr_name[1].c_str());
			while (number > 0) {
				i++;                  // id
				int id = Get_ID(arr_source[i]);

				i++;                  // path 1
				string path_1 = Get_Path(arr_source[i]);

				i++;                  // path 2
				string path_2 = Get_Path(arr_source[i]);

				// load plist
				SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path_1, path_2);

				Vector<SpriteFrame*> frame_diamond;
				frame_diamond.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_03.png"));
				frame_diamond.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_04.png"));
				frame_diamond.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_05.png"));
				frame_diamond.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_06.png"));
				frame_diamond.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_07.png"));
				frame_diamond.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_08.png"));
				frame_diamond.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_09.png"));
				frame_diamond.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_10.png"));
				frame_diamond.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_11.png"));
				frame_diamond.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_12.png"));
				frame_diamond.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_13.png"));
				frame_diamond.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_14.png"));

				m_diamond_action.insert(pair<int, Vector<SpriteFrame*>>(0, frame_diamond));

				number--;
			}
		}
		else if (arr_name[0] == "#ACTION_FIRE") {
			// number 
			int number = atoi(arr_name[1].c_str());
			while (number > 0) {
				i++;                  // id
				int id = Get_ID(arr_source[i]);

				i++;                  // path 1
				string path_1 = Get_Path(arr_source[i]);

				i++;                  // path 2
				string path_2 = Get_Path(arr_source[i]);

				// load plist
				SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path_1, path_2);

				Vector<SpriteFrame*> frame_fire;
				frame_fire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire1.png"));
				frame_fire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire2.png"));
				frame_fire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire3.png"));
				frame_fire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire4.png"));
				frame_fire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire5.png"));
				frame_fire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire6.png"));
				frame_fire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire7.png"));
				frame_fire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire8.png"));
				frame_fire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire9.png"));
				frame_fire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire10.png"));
				frame_fire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire11.png"));

				m_fire_action.insert(pair<int, Vector<SpriteFrame*>>(0, frame_fire));

				number--;
			}
		}

	}
}

Sprite * ResourceManager::GetBackgroundById(int id)
{
	return m_background.at(id);
}
Sprite * ResourceManager::GetSpriteById(int id)
{
	return m_sprites.at(id);
}

Sprite * ResourceManager::GetItemById(int id)
{
	return m_item.at(id);
}

ui::Button * ResourceManager::GetButtonById(int id)
{
	return m_button.at(id);
}

Vector<SpriteFrame*> ResourceManager::GetSpiderUp()
{
	return m_spider_action.at(Action_Spider::S_UP);
}

Vector<SpriteFrame*> ResourceManager::GetSpiderDown()
{
	return m_spider_action.at(Action_Spider::S_DOWN);
}

Vector<SpriteFrame*> ResourceManager::GetSpiderSide()
{
	return m_spider_action.at(Action_Spider::S_SIDE);
}


std::vector<std::string> ResourceManager::Split(std::string str1, std::string str2)
{

	vector<std::string> arr;

	char *c = const_cast<char*>(str1.c_str());
	char* s1 = strtok(c, str2.c_str());

	while (s1 != NULL) {
		arr.push_back(s1);
		s1 = strtok(NULL, str2.c_str());
	}


	return arr;
}

std::string ResourceManager::formatData(std::string data)
{
	std::string result = "";
	data = data.c_str();

	for (int i = 1; i < data.length() - 1; i++) {
		result += data[i];
	}
	return result;
}

std::vector<std::string> ResourceManager::formatDataObject(std::string str1)
{
	vector<std::string> arr;
	//[{"x":6,"y":5,"alive":true},{"x":7,"y":5,"alive":true},{"x":8,"y":5,"alive":true},{"x":9,"y":5,"alive":true},{"x":10,"y":5,"alive":true},{"x":11,"y":5,"alive":true},{"x":12,"y":5,"alive":true},{"x":13,"y":5,"alive":true},{"x":14,"y":5,"alive":true}]
	string sGet = "";
	bool check = false;
	str1 = str1.c_str();

	for (int i = 0; i < str1.length(); i++) {
		if (str1[i] == '{') {
			i += 1;
			check = true;
		}
		else if (str1[i] == '}') {
			check = false;
			arr.push_back(sGet);
			sGet = "";
		}

		if (check) {
			sGet += str1[i];
		}
	}
	return arr;
}

int ResourceManager::Get_ID(std::string s)
{
	int id;
	std::vector<std::string> arr_id = Split(s, " ");
	id = atoi(arr_id[1].c_str());

	return id;
}

std::string ResourceManager::Get_Path(std::string s)
{
	std::string path = "";
	std::vector<std::string> arr_path = Split(s, " ");
	path = arr_path[1];

	return path;
}


ResourceManager::~ResourceManager()
{
}

Vector<SpriteFrame*> ResourceManager::GetCharactorPush()
{
	return m_charactor_action.at(Action_Charactor::CH_PUSH);
}

Vector<SpriteFrame*> ResourceManager::GetCharactorFight()
{
	return m_charactor_action.at(Action_Charactor::CH_FIGHT);
}

Vector<SpriteFrame*> ResourceManager::GetCharactorWait()
{
	return m_charactor_action.at(Action_Charactor::CH_WAIT);
}

Vector<SpriteFrame*> ResourceManager::GetCharactorRun()
{
	return m_charactor_action.at(Action_Charactor::CH_RUN);
}

Vector<SpriteFrame*> ResourceManager::GetCharactorStun()
{
	return m_charactor_action.at(Action_Charactor::CH_STUN);
}

Vector<SpriteFrame*> ResourceManager::GetFrameDiamond()
{
	return m_diamond_action.at(0);
}

Vector<SpriteFrame*> ResourceManager::GetActionFire()
{
	return m_fire_action.at(0);
}
