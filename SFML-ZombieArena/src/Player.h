#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class Player
{
public:
	Player();
	virtual ~Player();

	void Spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);

	void ResetPlayerStats();

	bool Hit(sf::Time timeHit);

	sf::Time GetLastHitTime();

	sf::FloatRect GetPosition();

	sf::Vector2f GetCenter();

	float GetRotation();

	sf::Sprite GetSprite();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void StopLeft();
	void StopRight();
	void StopUp();
	void StopDown();

	void Update(float elapsedTime, sf::Vector2i mousePosition);

	void UpgradeSpeed();
	void UpgradeHealth();
	void IncreaseHealthLevel(int amount);
	int GetHealth();

private:
	const float START_SPEED = 200.0f;
	const float START_HEALTH = 100.0f;

	sf::Vector2f mPosition;

	sf::Sprite mSprite;

	sf::Texture mTexture;

	sf::Vector2f mResolution;

	sf::IntRect mArena;

	int mTileSize;

	bool mUpPressed;
	bool mDownPressed;
	bool mLeftPressed;
	bool mRightPressed;

	int mHealth;
	int mMaxHealth;

	sf::Time mLastHit;

	float mSpeed;
};

#endif