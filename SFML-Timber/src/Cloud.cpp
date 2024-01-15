#include "Cloud.h"
#include "TextureManager.h"

#include "GameRandom.h"
#include "GameConstants.h"

Cloud::Cloud(sf::RenderWindow& renderWindow, sf::Vector2f position) : mRenderWindow(renderWindow), mMoveSpeed(0.0f)
{
	mSprite.setTexture(*TextureManager::GetTexture("cloud"));
	mSprite.setPosition(position);
}

Cloud::~Cloud()
{

}

void Cloud::Init()
{
	// How fast is the cloud
	mMoveSpeed = GameRandom::RandFloat(100, 200);
	// How high is the cloud
	float height = GameRandom::RandInt(this->GetPosition().y - 100, this->GetPosition().y + 100);
	mSprite.setPosition(-mSprite.getLocalBounds().width, height);
}

void Cloud::Update(sf::Time& deltaTime)
{
	sf::Vector2f tempPos = this->GetPosition();
	tempPos.x = tempPos.x + (mMoveSpeed * deltaTime.asSeconds());
	this->SetPosition(tempPos);

	// Has the be reached the left of the screen?
	if (this->GetPosition().x > GameConstants::WINDOW_WIDTH)
	{
		this->Init();
	}
}

void Cloud::Render()
{
	mRenderWindow.draw(mSprite);
}

