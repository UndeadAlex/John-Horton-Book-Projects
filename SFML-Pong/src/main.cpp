//////////////////////////////////////////////////////////////////////////
///
///		WELCOME TO THE SECOND PROJECT IN
///		JOHN HORTON'S BEGINNER GAME PROGRAMMING BOOK
/// 
///		Its Pong, theres not much i can say here.
///		Writing this pre-development the plan is Pong
///		but with power-ups, not super original but it beats a standard Pong clone.
///		Its either going to be Insta power-ups or
///		stored power-ups similar to Mario Kart.or maybe a mix of both ?
///		I'm really not sure
/// 
///////////////////////////////////////////////////////////////////////////


#include <SFML/Graphics.hpp>
#include <sstream>

#include "GameConstants.h"
#include "GameRandom.h"
#include "Bat.h"
#include "Ball.h"

// enum is in charge of what states the game can be in.
// Start, Playing, End. as i don't need a complex state system for Pong.
enum GameState { START = 0, PLAYING = 1, END = 2 };

// Looks messy :( but its the method i found for using the windows subsystem in release builds.
#if _DEBUG // If Debug Config, use console subsystem
int main()
#else // If Release Config, use windows subsystem
int WinMain()
#endif
{
	using namespace sf;

	// create the main window, prevent it from being resized
	RenderWindow mainWindow(VideoMode(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT), "Pingy Pongy", sf::Style::Titlebar | sf::Style::Close);

	// set framerate
	mainWindow.setFramerateLimit(144);

	// clock for timing
	Clock clock;

	GameState gameState = GameState::START;

	Font DigiFont;
	if (!DigiFont.loadFromFile("assets/fonts/DS-DIGI.ttf")) { printf("Failed to load font."); }

	int playerOneScore = 0;
	Text playerOneScoreText("0", DigiFont, 75);
	int playerTwoScore = 0;
	Text playerTwoScoreText("0", DigiFont, 75);

	Bat playerOne(15, GameConstants::WINDOW_HEIGHT / 2, 10,100, sf::Keyboard::W, sf::Keyboard::S);
	Bat playerTwo(GameConstants::WINDOW_WIDTH - 15, GameConstants::WINDOW_HEIGHT/2, 10, 100, sf::Keyboard::Up, sf::Keyboard::Down);
	Ball ball(GameConstants::GetWindowCentre(), 15.f);
	ball.Serve(0);

	// start the game loop
	while (mainWindow.isOpen())
	{
		// Handle Timing
		Time dt = clock.restart();

		// Handle Events.
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				mainWindow.close();
			}

			if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				mainWindow.close();
			}

			if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				// reset game.
			}
		}

		// Update Loop.
		{
			ball.Update(dt);

			// Check ball win condition
			switch (ball.CheckWin())
			{
			case 0:
				playerOneScore++;
				playerOneScoreText.setString(std::to_string(playerOneScore));
				break;
			case 1:
				playerTwoScore++;
				playerTwoScoreText.setString(std::to_string(playerTwoScore));
				break;
			default:
				break;
			}

			playerOne.Update(dt);
			playerTwo.Update(dt);
		}

		// Render Loop.
		{
			// Clear window
			mainWindow.clear();

			// Draw the players
			mainWindow.draw(playerOne);
			mainWindow.draw(playerTwo);

			// Draw the ball
			mainWindow.draw(ball);

			mainWindow.draw(playerOneScoreText);
			mainWindow.draw(playerTwoScoreText);

			// Finish drawing.
			mainWindow.display();
		}
	}

	return 0;
}