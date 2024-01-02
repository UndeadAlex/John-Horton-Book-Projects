#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <unordered_map>
#include <string>

class AudioManager
{
public:
	AudioManager();
	virtual ~AudioManager();

	static bool LoadAudio(std::string fileName, std::string clipName);
	static sf::Sound* GetAudio(std::string clipName);

private:
	static std::unordered_map<std::string, sf::Sound*> mAudio;
};

#endif