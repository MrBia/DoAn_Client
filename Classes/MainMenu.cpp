#include "MainMenu.h"
#include "ControlMusic.h"


ui::CheckBox* music_ui;
ui::CheckBox* sound_ui;
cocos2d::ui::Button* btnPlay;
cocos2d::ui::Button* btnSetting;
cocos2d::Sprite* mSettingLayer;

Scene* MainMenu::createScene()
{
	return MainMenu::create();
}

bool MainMenu::init()
{
	srand((unsigned)time(0));

	if (!Scene::init()) {
		return false;
	}

	//create Background
	createBackground();

	//create Background Music
	createBackgroundMusic();

	//create Settings Layer when click button setting
	createSetting();

	//create button play and button settings
	addButton();
	
    return true;
}

void MainMenu::addButton()
{
	//Button Play
	btnPlay = ui::Button::create("play_normal.png", "play_pressed.png");
	btnPlay->setPosition(Vec2(270, 300));
	btnPlay->setScale(0.4);
	btnPlay->addClickEventListener([&](Ref* event){ 
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f,MapGame::create()));
	});
	addChild(btnPlay);

	//Button Settings
	btnSetting = ui::Button::create("Button/setting.png", "Button/setting_pressed.png");
	btnSetting->setPosition(Vec2(740,40));
	btnSetting->setScale(0.5);
	btnSetting->addClickEventListener([&](Ref* event){  
	   btnPlay->setVisible(false);
	   btnSetting->setVisible(false);
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
		activeSetting();
	});
	addChild(btnSetting);

}

void MainMenu::createSetting()
{
	//Settings background table
	mSettingLayer = Sprite::create("setting/table.png");
	mSettingLayer->setContentSize(Size(400,400));
	mSettingLayer->setVisible(false);
	mSettingLayer->setPosition(Director::getInstance()->getVisibleSize() /2);
	addChild(mSettingLayer,2);
	
	//Button return Main Menu
	auto returnButton = ui::Button::create("setting/close_2.png", "");
	returnButton->setPosition(Vec2(360,367));
	returnButton->setScale(0.65f);
	mSettingLayer->addChild(returnButton, 3);
	returnButton->addClickEventListener([&](Ref* event)
	{
		btnPlay->setVisible(true);
		btnSetting->setVisible(true);
		if (ControlMusic::GetInstance()->isSound())
		{
		SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
		mSettingLayer->setVisible(false);
	});

	//Lable Name "Music"
	auto musiclb = Label::create("MUSIC", "fonts/MarkerFelt.ttf",22);
	musiclb->setPosition(120,250);
	musiclb->setColor(Color3B::BLACK);
	mSettingLayer->addChild(musiclb, 4);

	//Check box turn on/off background music
	music_ui = ui::CheckBox::create("setting/95.png", "setting/96.png");
	music_ui->setScale(0.588f);
	music_ui->setSelected(ControlMusic::GetInstance()->isMusic());
	music_ui->addClickEventListener([&](Ref* event){
		music_ui->isSelected();
		if (!music_ui->isSelected())
		{
			ControlMusic::GetInstance()->setMusic(true);
			SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/menu.mp3", true);
		}
		else
		{
			ControlMusic::GetInstance()->setMusic(false);   	
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
	});
	music_ui->setPosition(musiclb->getPosition() + Vec2(140, 0));
	music_ui->setEnabled(true);
	mSettingLayer->addChild(music_ui, 4);

	//Lable Name "Sound"
	auto soundlb = Label::create("SOUND","fonts/MarkerFelt.ttf", 22);
	soundlb->setPosition(120, 170);
	soundlb->setColor(Color3B::BLACK);
	mSettingLayer->addChild(soundlb, 4);
	
	//Check box turn on/off effect music
	sound_ui = ui::CheckBox::create("setting/95.png","setting/96.png");
	sound_ui->retain();
	sound_ui->setScale(0.58f);
	sound_ui->setSelected(ControlMusic::GetInstance()->isSound());
	sound_ui->addClickEventListener([&](Ref* event)
	{
		if (!sound_ui->isSelected())
		{
		ControlMusic::GetInstance()->setSound(true);
		}
		else
		{
		ControlMusic::GetInstance()->setSound(false);
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}
	});
	sound_ui->setPosition(soundlb->getPosition() + Vec2(140, 0));
	sound_ui->setEnabled(true);
	mSettingLayer->addChild(sound_ui,4);
}

void MainMenu::activeSetting() {
	if (!mSettingLayer->isVisible()) {
		mSettingLayer->setVisible(true);
	}
	else {
		mSettingLayer->setVisible(false);
	}
}

void MainMenu::update(float deltaTime)
{
}

void MainMenu::createBackground()
{
	auto background = Sprite::create("background1.png");
	background->removeFromParent();
	background->setContentSize(Director::getInstance()->getVisibleSize());
	background->setPosition(Director::getInstance()->getVisibleSize() / 2);
	addChild(background);
}

void MainMenu::createBackgroundMusic()
{
	if (ControlMusic::GetInstance()->isMusic())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/menu.mp3", true);
	}
}

