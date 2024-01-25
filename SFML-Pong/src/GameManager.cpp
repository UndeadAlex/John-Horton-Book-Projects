#include "GameManager.h"
#include "GameConstants.h"

#include <stdio.h>

GameManager::GameManager(sf::RenderWindow& window) : mRenderWindow(window)
{
	// Initialize the paddle locations, and the ball location.
	mPaddleOne.setPosition(16, GameConstants::WINDOW_HEIGHT / 2);
	mPaddleOne.SetupControls(sf::Keyboard::W, sf::Keyboard::S);

	mPaddleTwo.setPosition(GameConstants::WINDOW_WIDTH - 16, GameConstants::WINDOW_HEIGHT / 2);
	mPaddleTwo.SetupControls(sf::Keyboard::Up, sf::Keyboard::Down);

	mBall.setPosition(GameConstants::WINDOW_WIDTH / 2, GameConstants::WINDOW_HEIGHT / 2);

	// Load Digi font, no proper error handling such as closing the game, because this shouldnt really happen.
	if (!DigiFont.loadFromFile("assets/fonts/DS-DIGI.TTF")) { printf("Failed to load font."); }

	// Paddle one text
	mPaddleOneScoreText.setFont(DigiFont);
	mPaddleOneScoreText.setCharacterSize(128);
	mPaddleOneScoreText.setPosition(GameConstants::PLAYERONESCORE_TEXTOFFSET, 64);
	// Paddle two text
	mPaddleTwoScoreText.setFont(DigiFont);
	mPaddleTwoScoreText.setCharacterSize(128);
	mPaddleTwoScoreText.setPosition(GameConstants::PLAYERTWOSCORE_TEXTOFFSET, 64);

	// Initial refresh of the UI
	UpdateUIText();
}

GameManager::~GameManager()
{

}

void GameManager::Init()
{
	mBall.Serve(true);
}

void GameManager::HandleEvents(const sf::Event& e)
{
	mPaddleOne.HandleEvents(e);
	mPaddleTwo.HandleEvents(e);
}

void GameManager::Update(sf::Time& deltaTime)
{
	mBall.Update(deltaTime);

	mPaddleOne.Update(deltaTime);
	mPaddleTwo.Update(deltaTime);

	// TODO: Check if ball is overlapping paddle, if not then check its x position to see if win condition is true.
	if (mPaddleOne.getGlobalBounds().intersects(mBall.getGlobalBounds()))
		mBall.Bounce(true);
	else if (mPaddleTwo.getGlobalBounds().intersects(mBall.getGlobalBounds()))
		mBall.Bounce(true);

	sf::Vector2f ballPos = mBall.getPosition();
	if (ballPos.x > GameConstants::WINDOW_WIDTH)
		AwardScoreToPlayer(true);
	else if (ballPos.x < 0)
		AwardScoreToPlayer(false);
	else if (ballPos.y > GameConstants::WINDOW_HEIGHT)
		mBall.Bounce(false);
	else if (ballPos.y < 0)
		mBall.Bounce(false);
}

void GameManager::Render()
{
	mRenderWindow.draw(mPaddleOneScoreText);
	mRenderWindow.draw(mPaddleTwoScoreText);

	mRenderWindow.draw(mBall);

	mRenderWindow.draw(mPaddleOne);
	mRenderWindow.draw(mPaddleTwo);
}

void GameManager::AwardScoreToPlayer(bool isPlayerOne)
{
	if (isPlayerOne)
	{
		mPaddleOneScore += 1;
		mBall.Serve(false);
	}
	else
	{
		mPaddleTwoScore += 1;
		mBall.Serve(true);
	}

	UpdateUIText();
}

void GameManager::UpdateUIText()
{
	mPaddleOneScoreText.setString(std::to_string(mPaddleOneScore));
	GameConstants::CentreTextOrigin(mPaddleOneScoreText);

	mPaddleTwoScoreText.setString(std::to_string(mPaddleTwoScore));
	GameConstants::CentreTextOrigin(mPaddleTwoScoreText);
}

