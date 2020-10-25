#include "LoadingLogo.h"

Scene* LoadingLogo::createScene()
{
	return LoadingLogo::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool LoadingLogo::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//LOGO
	auto logo = Sprite::create("play_pressed.png");
	logo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height /1.65);
	logo->setScale(0.33);
	addChild(logo);


	//LOADING BAR
	auto loadingBarGB = Sprite::create("Load/bloodbar_bg.png");
	loadingBarGB->setPosition(Vec2(430, 150));
	loadingBarGB->setFlippedX(true);
	loadingBarGB->setScale(1.3);
	addChild(loadingBarGB,1);

	static auto loadingbar = ui::LoadingBar::create("Load/bloodbar.png");
	loadingbar->setPosition(loadingBarGB->getPosition());
	loadingbar->setScale(1.28);
	loadingbar->setPercent(0);
	loadingbar->setDirection(ui::LoadingBar::Direction::LEFT);
	addChild(loadingbar,0);

	auto updateLoadingBar = CallFunc::create([]() {
		if (loadingbar->getPercent() < 100)
		{
			loadingbar->setPercent(loadingbar->getPercent() + 1);
		}
	});

	auto sequenceRunUpdateLoadingBar = Sequence::createWithTwoActions(updateLoadingBar, DelayTime::create(0.08f));
	auto repeat = Repeat::create(sequenceRunUpdateLoadingBar, 100);
	loadingbar->runAction(repeat);

	this->schedule(schedule_selector(LoadingLogo::changeLoading), 8.0f);
	return true;
}

void LoadingLogo::changeLoading(float dt) {
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainMenu::createScene()));
}

void LoadingLogo::update(float deltaTime)
{
}
