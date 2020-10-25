#include "ControlMusic.h"

ControlMusic* ControlMusic::s_instance = NULL;

ControlMusic::ControlMusic()
{
	music = true;
	sound = true;
}

ControlMusic::~ControlMusic()
{
}

ControlMusic * ControlMusic::GetInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new ControlMusic();
	}
	return s_instance;
}

bool ControlMusic::isMusic()
{
	return music;
}

void ControlMusic::setMusic(bool music)
{
	this->music = music;
}

bool ControlMusic::isSound()
{
	return sound;
}

void ControlMusic::setSound(bool sound)
{
	this->sound = sound;
}
