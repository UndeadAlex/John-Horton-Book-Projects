#include "Ball.h"
#include "GameConstants.h"
#include "GameRandom.h"

Ball::Ball() : mVelocity(0, 0)
{
	this->setPosition(0, 0);
	this->setSize(sf::Vector2f(15, 15));
	this->setOrigin(7.5f, 7.5f);
}

Ball::Ball(int x, int y, float size) : mVelocity(0, 0)
{
	this->setPosition(x, y);
	this->setSize(sf::Vector2f(size, size));
	this->setOrigin(size/2,size/2);
}

Ball::~Ball()
{

}

void Ball::Update(sf::Time& deltaTime)
{
	sf::Vector2f tmpPos = this->getPosition();

	tmpPos += mVelocity * (GameConstants::BALL_SPEED * deltaTime.asSeconds());
	
	this->setPosition(tmpPos);
}

void Ball::Serve(bool left)
{
	sf::Vector2f screenCenter = sf::Vector2f(GameConstants::WINDOW_WIDTH / 2, GameConstants::WINDOW_HEIGHT / 2);
	this->setPosition(screenCenter);

	float randomYVelocity = GameRandom::RandFloat(-0.5f, 0.5f);
	mVelocity = left ? sf::Vector2f(-1, randomYVelocity) : sf::Vector2f(1, randomYVelocity);
	GameConstants::NormalizeVector2f(mVelocity);
}

void Ball::Bounce(bool isPaddle)
{
	if (isPaddle)
	{
		mVelocity.x = -mVelocity.x;
		//mVelocity.y = GameRandom::RandFloat(-0.25f, 0.25f);
		GameConstants::NormalizeVector2f(mVelocity);
	}
	else
	{
		mVelocity.y = -mVelocity.y;
	}
}