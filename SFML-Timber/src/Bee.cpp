#include "Bee.h"

#include "GameRandom.h"
#include "TextureManager.h"

#include <iostream>

Bee::Bee(sf::RenderWindow& renderWindow, sf::Vector2f position) : mRenderWindow(renderWindow), mMoveSpeed(0.0f)
{
	mSprite.setTexture(*TextureManager::GetTexture("bee"));
	mSprite.setPosition(position);
}

Bee::~Bee()
{

}

void Bee::Init()
{
	// How fast is the cloud
	mMoveSpeed = GameRandom::RandFloat(200, 400);
	// How high is the bee
	float height = GameRandom::RandFloat(400, 1000);
	this->SetPosition({2000, height});
}

void Bee::Update(sf::Time& deltaTime)
{
	sf::Vector2f tempPos = this->GetPosition();
	tempPos.x = tempPos.x - (mMoveSpeed * deltaTime.asSeconds());
	this->SetPosition(tempPos);

	// Has the be reached the left of the screen?
	if (this->GetPosition().x < -mSprite.getLocalBounds().width)
	{
		this->Init();
	}
}

void Bee::Render()
{
	mRenderWindow.draw(mSprite);
}

