#ifndef GAME_RANDOM_H
#define GAME_RANDOM_H

#include <random>
#include <ctime>
#include <SFML/System/Vector2.hpp>

namespace GameRandom
{
	inline int randint(int pMin, int pMax)
	{
		static std::default_random_engine ran((unsigned int)std::time(0));
		return std::uniform_int_distribution<>{pMin, pMax}(ran);
	}

	inline int randint(int pMax) { return randint(0, pMax); }

	inline float randFloat(float pMin, float pMax)
	{
		static std::default_random_engine ran((unsigned int)std::time(0));
		return static_cast<float>(std::uniform_real_distribution<>{pMin, pMax}(ran));
	}

	inline float randFloat(float pMax) { return randFloat(0.f, pMax); }

	inline sf::Vector2f randVector2f(sf::Vector2f pMin, sf::Vector2f pMax)
	{
		float x = randFloat(pMin.x, pMax.x);
		float y = randFloat(pMin.y, pMax.y);
		return sf::Vector2f(x, y);
	}

	inline sf::Vector2f randVector2f(sf::Vector2f pMax)
	{
		float x = randFloat(pMax.x);
		float y = randFloat(pMax.y);
		return sf::Vector2f(x, y);
	}
}

#endif