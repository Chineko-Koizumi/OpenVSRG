#include "Sound.h"
#include <SFML/Audio.hpp>

using namespace sf;

#pragma region HitSound

HitSound::HitSound(String path)
{
	Hit_Sound_Buffer = new SoundBuffer;
	Hit_Sound = new Sound;

	Hit_Sound_Buffer->loadFromFile(path);
	Hit_Sound->setBuffer(*Hit_Sound_Buffer);
}

HitSound::~HitSound()
{
}

void HitSound::TriggerHitSound()
{
	Hit_Sound->play();
}

Sound* HitSound::GetSOUND()
{
	return Hit_Sound;
}

#pragma endregion

