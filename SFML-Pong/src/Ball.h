#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>

class Ball : public sf::RectangleShape
{
public:
	Ball();
	Ball(int x, int y, float size);
	virtual ~Ball();

	void Update(sf::Time& deltaTime);

private:
	sf::Vector2f mVelocity;
};

#endif