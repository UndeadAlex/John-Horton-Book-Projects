#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameConstants
{
	// Its important for easiness to keep this as a 1:1 aspect ratio.
	constexpr int gWindowWidth = 1024;
	constexpr int gWindowHeight = 1024;

	constexpr int CELL_RES = 8;
	constexpr int CELL_SIZE = std::min(gWindowWidth, gWindowHeight) / CELL_RES;

	// set the origin of the text to the centre of it
	static void centreTextOrigin(sf::Text& pText)
	{
		pText.setOrigin(pText.getGlobalBounds().width / 2, 0);
	}

	static sf::Vector2f roundVector2f(const sf::Vector2f pVector2f)
	{
		return sf::Vector2f(std::round(pVector2f.x), std::round(pVector2f.y));
	}

	static sf::Font getFFFForwardFont()
	{
		sf::Font font;
		font.loadFromFile("assets/fonts/FFFFORWA.TTF");
		return font;
	}
}

#endif