#include "Ball.h"

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

}
