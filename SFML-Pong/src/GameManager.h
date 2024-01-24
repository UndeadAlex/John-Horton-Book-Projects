#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Paddle.h"
#include "Ball.h"

class GameManager
{
public:
	GameManager(sf::RenderWindow& window);
	virtual ~GameManager();

	void Init();
	void HandleEvents(const sf::Event& e);
	void Update(sf::Time& deltaTime);

	void Render();

private:
	void AwardScoreToPlayer(bool isPlayerOne);
	void UpdateUIText();

	int mPaddleOneScore = 0, mPaddleTwoScore = 0;

	Paddle mPaddleOne;
	Paddle mPaddleTwo;
	Ball mBall;

	// UI
	sf::Font DigiFont;
	sf::Text mPaddleOneScoreText;
	sf::Text mPaddleTwoScoreText;

	sf::RenderWindow& mRenderWindow;
};

#endif