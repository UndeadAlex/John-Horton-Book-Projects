#ifndef BAT_H
#define BAT_H

#include <SFML/System/Vector2.hpp>
#include <sfml/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>


class Bat : public sf::RectangleShape
{
public:
	Bat();
	Bat(sf::Vector2f position, sf::Vector2f size, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);
	Bat(int x, int y, int width, int height, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);
	virtual ~Bat();

	void Update(sf::Time& deltaTime);

private:
	bool CheckBounds();

	// Keys for movement
	sf::Keyboard::Key mUpKey;
	sf::Keyboard::Key mDownKey;
};

#endif

