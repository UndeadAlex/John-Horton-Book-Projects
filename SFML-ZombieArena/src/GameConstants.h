#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameConstants
{
	// Its important for easiness to keep this as a 1:1 aspect ratio.
	constexpr int WINDOW_WIDTH = 1920;
	constexpr int WINDOW_HEIGHT = 1080;

	// set the origin of the text to the centre of it
	// localBounds needs drawable, setOrigin is transformable, so i cant see a common parent to make this one universal function, the best i can do is shape.
	static void CentreTextOrigin(sf::Text& text)
	{
		text.setOrigin(text.getLocalBounds().getSize() / 2.0f);
	}

	static void CentreShapeOrigin(sf::Shape& shape)
	{
		shape.setOrigin(shape.getLocalBounds().getSize() / 2.0f);
	}

	static sf::Vector2f RoundVector2f(const sf::Vector2f pVector2f)
	{
		return sf::Vector2f(std::round(pVector2f.x), std::round(pVector2f.y));
	}

	static float GetVector2fMagnitude(const sf::Vector2f vec2f)
	{
		return sqrt(pow(vec2f.x, 2.0f) + pow(vec2f.y, 2.0f));
	}

	static sf::Vector2f NormalizeVector2f(sf::Vector2f& vec2f)
	{
		vec2f /= GetVector2fMagnitude(vec2f);
		return vec2f;
	}
}

#endif