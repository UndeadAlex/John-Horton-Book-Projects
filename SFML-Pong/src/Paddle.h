#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

class Paddle : public sf::RectangleShape
{
public:
	Paddle();
	Paddle(int x, int y, int width, int height);
	Paddle(sf::Vector2f position, sf::Vector2f size);
	virtual ~Paddle();

	void SetupControls(const sf::Keyboard::Key upKey, const sf::Keyboard::Key downKey);

	void HandleEvents(const sf::Event& e);
	void Update(sf::Time& deltaTime);

private:

	int mInputDir = 0;

	sf::Keyboard::Key mMoveKeyDown;
	sf::Keyboard::Key mMoveKeyUp;
};

#endif