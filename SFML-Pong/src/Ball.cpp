#include "Ball.h"
#include "GameConstants.h"
#include "GameRandom.h"

// Constructors / Destructor
Ball::Ball()
{
	this->setPosition(0, 0);
	this->setRadius(15);
	mVelocity = sf::Vector2f(0, 0);

	// Set Origin to centre of circle
	this->setOrigin(getLocalBounds().getSize() / 2.f);
}

Ball::Ball(sf::Vector2f position, float radius)
{
	this->setPosition(position);
	this->setRadius(radius);
	mVelocity = sf::Vector2f(0, 0);

	// Set Origin to centre of circle
	this->setOrigin(getLocalBounds().getSize() / 2.f);
}

Ball::Ball(int x, int y, float radius) 
{
	this->setPosition(x, y);
	this->setRadius(radius);
	mVelocity = sf::Vector2f(0, 0);

	// Set Origin to centre of circle
	this->setOrigin(getLocalBounds().getSize() / 2.f);
}

Ball::~Ball() {}

void Ball::Serve(int side = 0)
{
	switch (side)
	{
	case 0:
	default:
		mVelocity = { -GameConstants::BALL_X_SPEED, GameRandom::RandFloat(-GameConstants::BALL_Y_SPEED, GameConstants::BALL_Y_SPEED) };
		break;
	case 1:
		mVelocity = { GameConstants::BALL_X_SPEED, GameRandom::RandFloat(-GameConstants::BALL_Y_SPEED, GameConstants::BALL_Y_SPEED) };
		break;
	}
}

void Ball::Update(sf::Time& deltaTime)
{
	sf::Vector2f tmpPos = this->getPosition();
	tmpPos += mVelocity * deltaTime.asSeconds();
	this->setPosition(tmpPos);
}

bool Ball::CheckBounds()
{
	sf::Vector2f tmpPos = this->getPosition();

	const float TOP_SCREEN = this->getRadius() / 2;
	const float LEFT_SCREEN = -TOP_SCREEN;
	const float BOTT_SCREEN = GameConstants::WINDOW_HEIGHT - (this->getRadius() / 2);

	// Check Y
	if (tmpPos.y > BOTT_SCREEN || tmpPos.y < TOP_SCREEN)
	{
		mVelocity.y = -mVelocity.y;
		return true;
	}

}


int Ball::CheckWin()
{
	sf::Vector2f tmpPos = this->getPosition();

	const float RIGHT_SCREEN = GameConstants::WINDOW_WIDTH - (this->getRadius() / 2);
	const float LEFT_SCREEN = -(this->getRadius() / 2);

	// Check for wins first.
	if (tmpPos.x > RIGHT_SCREEN)
	{
		// Player One wins.
		return 0;
	}
	else if (tmpPos.x < LEFT_SCREEN)
	{
		// Player Two wins.
		return 1;
	}

	return -1;
}
