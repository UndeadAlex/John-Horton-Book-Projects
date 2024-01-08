#include "Bat.h"

#include "GameConstants.h"

// Constructors / Destructor
#pragma region Constructors
Bat::Bat() 
{
	this->setPosition(0, 0);
	this->setSize({ 10, 100 });
	this->setOrigin(getLocalBounds().getSize() / 2.f);
	mUpKey = sf::Keyboard::W;
	mDownKey = sf::Keyboard::S;
}

Bat::Bat(sf::Vector2f position, sf::Vector2f size, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey) : mUpKey(upKey), mDownKey(downKey)
{
	this->setPosition(0, 0);
	this->setSize({ 10, 100 });
	this->setOrigin(getLocalBounds().getSize() / 2.f);
}

Bat::Bat(int x, int y, int width, int height, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey) : mUpKey(upKey), mDownKey(downKey)
{
	this->setPosition(x, y);
	this->setSize(sf::Vector2f(width,height));
	this->setOrigin(getLocalBounds().getSize() / 2.f);
}

Bat::~Bat() {}
#pragma endregion Constructors

void Bat::Update(sf::Time& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(mUpKey))
	{
		// Keep current X, subtract from Y
		this->setPosition(this->getPosition().x, this->getPosition().y - (GameConstants::PADDLE_SPEED * deltaTime.asSeconds()));
	}
	else if (sf::Keyboard::isKeyPressed(mDownKey))
	{
		// Keep current X, add to Y
		this->setPosition(this->getPosition().x, this->getPosition().y + (GameConstants::PADDLE_SPEED * deltaTime.asSeconds()));
	}

	this->CheckBounds();
}

bool Bat::CheckBounds()
{
	sf::Vector2f tmpPos = this->getPosition();

	const float TOP_SCREEN = this->getSize().y / 2;
	const float BOTT_SCREEN = GameConstants::WINDOW_HEIGHT - (this->getSize().y / 2);

	// Check Y
	if (tmpPos.y > BOTT_SCREEN)
	{
		tmpPos.y = BOTT_SCREEN;
		this->setPosition(tmpPos);
		return true;
	}
	else if (tmpPos.y < TOP_SCREEN)
	{
		tmpPos.y = TOP_SCREEN;
		this->setPosition(tmpPos);
		return true;
	}

	return false; // Return false if within bounds.
}
