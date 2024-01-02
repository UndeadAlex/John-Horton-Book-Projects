#include "AudioManager.h"

AudioManager::AudioManager()
{
	/*SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("assets/sounds/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setVolume(25);
	outOfTime.setBuffer(ootBuffer);*/
}

AudioManager::~AudioManager()
{

}

bool AudioManager::LoadAudio(std::string fileName, std::string clipName)
{
	// Haven't loaded it yet, time to create it
	sf::SoundBuffer* tmpSoundBuffer = new sf::SoundBuffer();
	sf::Sound* tmpSound = new sf::Sound(*tmpSoundBuffer);

	if (tmpSoundBuffer->loadFromFile(fileName))
	{
		mAudio[clipName] = tmpSound;
		return true;
	}
	else
	{
		delete tmpSound;
		delete tmpSoundBuffer;
		return false;
	}
}

sf::Sound* AudioManager::GetAudio(std::string clipName)
{
	if (mAudio.find(clipName) != mAudio.end())
	{
		return mAudio[clipName];
	}
	else
	{
		return nullptr;
	}
}

std::unordered_map<std::string, sf::Sound*> AudioManager::mAudio;
