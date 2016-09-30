// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cSound.h"

cSound::cSound(void)
{
	FMOD::System_Create(&system);// create an instance of the game engine
	system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels
}

cSound::~cSound(void)
{
	for (int i = 0; i < NUM_SOUNDS; i++) sounds[i]->release();
	system->release();
}

bool cSound::Load()
{
	system->createStream("Sound/bg_music.wav", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT1]);
	system->createStream("Sound/blastershot.mp3", FMOD_SOFTWARE | FMOD_LOOP_OFF, 0, &sounds[SOUND_AMBIENT2]);
	system->createStream("Sound/explosion.wav", FMOD_SOFTWARE | FMOD_LOOP_OFF, 0, &sounds[SOUND_AMBIENT3]);
	return true;
}

void cSound::Play(int sound_id)
{
	if (sound_id == SOUND_AMBIENT1) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[SOUND_AMBIENT1], false, &ambient1Channel);
		ambient1Channel->setVolume(0.2f); //between 0 and 1
	}
	else if (sound_id == SOUND_AMBIENT2) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[SOUND_AMBIENT2], false, &ambient2Channel);
		ambient2Channel->setVolume(1.f); //between 0 and 1
	}
	else if (sound_id == SOUND_AMBIENT3) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[SOUND_AMBIENT3], false, &ambient3Channel);
		ambient2Channel->setVolume(0.8f); //between 0 and 1
	}
	else {
		system->playSound(FMOD_CHANNEL_FREE, sounds[sound_id], false, 0);
	}
}

void cSound::StopAll()
{
	ambient1Channel->stop();
	ambient2Channel->stop();
	ambient3Channel->stop();
}

void cSound::Update()
{
	system->update();
}