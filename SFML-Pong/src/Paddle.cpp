#include "Paddle.h"
#include "GameConstants.h"

Paddle::Paddle()
{
	this->setPosition(0, 0);
	this->setSize(sf::Vector2f(100, 10));
	this->setOrigin(50,5);
}

Paddle::Paddle(int x, int y, int width, int height)
{
	this->setPosition(x, y);
	this->setSize(sf::Vector2f(width, height));
	this->setOrigin(this->getSize() / 2.0f);
}

Paddle::Paddle(sf::Vector2f position, sf::Vector2f size)
{
	this->setPosition(position);
	this->setSize(size);
	this->setOrigin(size / 2.0f);
}

Paddle::~Paddle()
{

}

void Paddle::SetupControls(const sf::Keyboard::Key upKey, const sf::Keyboard::Key downKey)
{

}

void Paddle::HandleEvents(const sf::Event& e)
{
	// Didn't call Setup controls or it was somehow invalid.
	if (!mMoveKeyDown || !mMoveKeyUp)
	{
		mMoveKeyUp = sf::Keyboard::W;
		mMoveKeyDown = sf::Keyboard::S;
	}

	if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code == mMoveKeyUp)
			mInputDir = -1;
		else if (e.key.code == mMoveKeyDown)
			mInputDir = 1;
	}
	if (e.type == sf::Event::KeyReleased)
	{
		if (e.key.code == mMoveKeyUp || e.key.code == mMoveKeyDown)
			mInputDir = 0;
	}
}

void Paddle::Update(sf::Time& deltaTime)
{
	sf::Vector2f tmpPos = this->getPosition();
	tmpPos.y = tmpPos.y + (mInputDir * GameConstants::PADDLE_SPEED) * deltaTime.asSeconds();

	// TODO: Check for boundaries

	this->setPosition(tmpPos);
}
