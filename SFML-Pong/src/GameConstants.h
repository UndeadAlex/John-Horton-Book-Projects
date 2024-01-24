#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameConstants
{
	constexpr int WINDOW_WIDTH = 1920;
	constexpr int WINDOW_HEIGHT = 1080;

	constexpr int PLAYERONESCORE_TEXTOFFSET = (WINDOW_WIDTH / 2) / 2;
	constexpr int PLAYERTWOSCORE_TEXTOFFSET = (WINDOW_WIDTH / 2) + PLAYERONESCORE_TEXTOFFSET;

	constexpr float PADDLE_SPEED = 350.0f;
	constexpr float BALL_X_SPEED = 350.0f;
	constexpr float BALL_Y_SPEED = 50.0f;

	static sf::Vector2f GetWindowCentre()
	{
		return sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}

	// set the origin of the text to the centre of it
	static void CentreTextOrigin(sf::Text& pText)
	{
		pText.setOrigin(pText.getGlobalBounds().width / 2, 0);
	}

	static sf::Vector2f RoundVector2f(const sf::Vector2f pVector2f)
	{
		return sf::Vector2f(std::round(pVector2f.x), std::round(pVector2f.y));
	}
}

#endif