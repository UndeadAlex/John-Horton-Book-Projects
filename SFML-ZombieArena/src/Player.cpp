#include "Player.h"

Player::Player()
{
	mSpeed = START_SPEED;
	mHealth = START_HEALTH;
	mMaxHealth = START_HEALTH;

	mTexture.loadFromFile("assets/graphics/player.png");
	mSprite.setTexture(mTexture);

	mSprite.setOrigin(25, 25);
}

Player::~Player()
{

}

void Player::Spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize)
{
	mPosition.x = arena.width / 2;
	mPosition.y = arena.height / 2;

	mArena.left = arena.left;
	mArena.width = arena.width;
	mArena.top = arena.top;
	mArena.height = arena.height;

	mTileSize = tileSize;

	mResolution.x = resolution.x;
	mResolution.y = resolution.y;
}

void Player::ResetPlayerStats()
{
	mSpeed = START_SPEED;
	mHealth = START_HEALTH;
	mMaxHealth = START_HEALTH;
}

bool Player::Hit(sf::Time timeHit)
{
	if (timeHit.asMilliseconds() - mLastHit.asMilliseconds() > 200)
	{
		mLastHit = timeHit;
		mHealth -= 10;
		return true;
	}
	return false;
}

sf::Time Player::GetLastHitTime()
{
	return mLastHit;
}

sf::FloatRect Player::GetPosition()
{
	return mSprite.getGlobalBounds();
}

sf::Vector2f Player::GetCenter()
{
	return mPosition;
}

float Player::GetRotation()
{
	return mSprite.getRotation();
}

sf::Sprite Player::GetSprite()
{
	return mSprite;
}

void Player::MoveLeft()
{
	mLeftPressed = true;
}

void Player::MoveRight()
{
	mRightPressed = true;
}

void Player::MoveUp()
{
	mUpPressed = true;
}

void Player::MoveDown()
{
	mDownPressed = true;
}

void Player::StopLeft()
{
	mLeftPressed = false;
}

void Player::StopRight()
{
	mRightPressed = false;
}

void Player::StopUp()
{
	mUpPressed = false;
}

void Player::StopDown()
{
	mDownPressed = false;
}

void Player::Update(float elapsedTime, sf::Vector2i mousePosition)
{
	if (mUpPressed)
	{
		mPosition.y -= mSpeed * elapsedTime;
	}
	if (mDownPressed)
	{
		mPosition.y += mSpeed * elapsedTime;
	}
	if (mRightPressed)
	{
		mPosition.x += mSpeed * elapsedTime;
	}
	if (mLeftPressed)
	{
		mPosition.x -= mSpeed * elapsedTime;
	}

	mSprite.setPosition(mPosition);

	if (mPosition.x > mArena.width - mTileSize)
	{
		mPosition.x = mArena.width - mTileSize;
	}

	if (mPosition.x < mArena.left + mTileSize)
	{
		mPosition.x = mArena.left + mTileSize;
	}

	if (mPosition.y > mArena.height - mTileSize)
	{
		mPosition.y = mArena.height - mTileSize;
	}

	if (mPosition.y < mArena.top + mTileSize)
	{
		mPosition.y = mArena.top + mTileSize;
	}

	float angle = (atan2(mousePosition.y - mResolution.y / 2, mousePosition.x - mResolution.x / 2) * 180) / 3.141;
	mSprite.setRotation(angle);
}

void Player::UpgradeSpeed()
{
	mSpeed += (START_SPEED * .2);
}

void Player::UpgradeHealth()
{
	mMaxHealth += (START_HEALTH * .2);
}

void Player::IncreaseHealthLevel(int amount)
{
	mHealth += amount;

	if (mHealth > mMaxHealth)
	{
		mHealth = mMaxHealth;
	}
}

int Player::GetHealth()
{
	return mHealth;
}
