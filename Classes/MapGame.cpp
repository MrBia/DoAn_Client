#include "MapGame.h"
#include "ControlMusic.h"

Scene* MapGame::createScene()
{
    return MapGame::create();
}

bool MapGame::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	//create background
	createBackground();

	//create Button 
	createButton();
    return true;
}

void MapGame::update(float deltaTime)
{
}

void MapGame::createBackground()
{
	auto background = Sprite::create("selectmap.png");
	background->removeFromParent();
	background->setContentSize(Director::getInstance()->getVisibleSize());
	background->setPosition(Director::getInstance()->getVisibleSize() / 2);
	addChild(background);
}

void MapGame::createButton()
{
	//Button return Main Menu
	btnBack = ui::Button::create("Button/Resume.png");
	btnBack->setPosition(Vec2(50, 370));
	btnBack->setScale(0.8);
	addChild(btnBack);
	btnBack->addClickEventListener([&](Ref* event){
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MainMenu::create()));
	});

	//Button into Map1
	btnMap1 = ui::Button::create("TempleRuins.png", "TempleRuins_pressed.png");
	btnMap1->setPosition(Vec2(250, Director::getInstance()->getVisibleSize().height / 2.5));
	btnMap1->setScale(0.75);
	btnMap1->addClickEventListener([&](Ref* event){
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f,GamePlay::createGame()));
	});
	addChild(btnMap1);

	//Button into Map2
	btnMap2 = ui::Button::create("TuinpleRems.png", "TuinpleRems_pressed.png");
	btnMap2->setPosition(Vec2(550, Director::getInstance()->getVisibleSize().height / 2.5));
	btnMap2->setScale(0.75);
	btnMap2->addClickEventListener([&](Ref* event){
		if (ControlMusic::GetInstance()->isSound())
		{
		SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GamePlay2::createGame()));
	});
	addChild(btnMap2);
}
