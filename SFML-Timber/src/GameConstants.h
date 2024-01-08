#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameConstants
{
	constexpr int WINDOW_WIDTH = 1920;
	constexpr int WINDOW_HEIGHT = 1080;


	// set the origin of the text to the centre of it
	static void centreTextOrigin(sf::Text& pText)
	{
		pText.setOrigin(pText.getLocalBounds().width / 2, pText.getLocalBounds().height / 2);
	}

	static sf::Vector2f roundVector2f(const sf::Vector2f pVector2f)
	{
		return sf::Vector2f(std::round(pVector2f.x), std::round(pVector2f.y));
	}
}

#endif