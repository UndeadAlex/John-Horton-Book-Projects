#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

class Ball : public sf::CircleShape
{
public:
	Ball();
	Ball(sf::Vector2f position, float radius);
	Ball(int x, int y, float radius);
	virtual ~Ball();

	void Serve(int side);
	void Update(sf::Time& deltaTime);

	// -1* == Null, 0 == Player One, 1 == Player Two.
	int CheckWin();

private:
	bool CheckBounds();

	sf::Vector2f mVelocity;
};

#endif