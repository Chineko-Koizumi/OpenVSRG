#pragma once
#include <SFML/Audio.hpp>

using namespace sf;

class HitSound
{
private:
	SoundBuffer* Hit_Sound_Buffer;
	Sound*   Hit_Sound;

public:
	HitSound(String path);
	~HitSound();
	
	void TriggerHitSound();
	Sound* GetSOUND();
};




