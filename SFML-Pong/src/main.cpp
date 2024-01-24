//////////////////////////////////////////////////////////////////////////
///
///		WELCOME TO THE SECOND PROJECT IN
///		JOHN HORTON'S BEGINNER GAME PROGRAMMING BOOK
/// 
///		Its Pong, theres not much i can say here.
///		Writing this pre-development the plan is Pong
///		but with power-ups, not super original but it beats a standard Pong clone.
///		Its either going to be Insta power-ups or
///		stored power-ups similar to Mario Kart or maybe a mix of both ?
///		I'm really not sure
/// 
///////////////////////////////////////////////////////////////////////////


#include <SFML/Graphics.hpp>
#include <sstream>

#include "GameConstants.h"
#include "GameRandom.h"

#include "GameManager.h"

// enum is in charge of what states the game can be in.
// Start, Playing, End. as i don't need a complex state system for Pong.
//enum GameState { START = 0, PLAYING = 1, END = 2 };

// Looks messy :( but its the method i found for using the windows subsystem in release builds.
#if _DEBUG // If Debug Config, use console subsystem
int main()
#else // If Release Config, use windows subsystem
int WinMain()
#endif
{
	// create the main window, prevent it from being resized
	sf::RenderWindow mainWindow(sf::VideoMode(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT), "Pingy Pongy", sf::Style::Titlebar | sf::Style::Close);

	// set framerate
	mainWindow.setFramerateLimit(144);

	// clock for timing
	sf::Clock clock;

	//GameState gameState = GameState::START;

	GameManager gameManager(mainWindow);
	gameManager.Init();

	// the dividing line in the middle of the screen because it looks cool ?
	sf::RectangleShape dividingLine(sf::Vector2f(GameConstants::WINDOW_WIDTH * 0.01f, GameConstants::WINDOW_HEIGHT));
	dividingLine.setOrigin(dividingLine.getSize().x / 2, 0);
	dividingLine.setPosition(GameConstants::WINDOW_WIDTH / 2, 0);
	dividingLine.setFillColor(sf::Color(31, 31, 31));

	// start the game loop
	while (mainWindow.isOpen())
	{
		// Handle Timing
		sf::Time dt = clock.restart();

		// Handle Events.
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				mainWindow.close();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				// reset game.
			}

			// Pass event to Paddles
			gameManager.HandleEvents(event);
		}

		// Update Loop.
		{
			gameManager.Update(dt);
		}

		// Render Loop.
		{
			// Clear window
			mainWindow.clear();

			// Draw middle line
			mainWindow.draw(dividingLine);

			gameManager.Render();

			// Finish drawing.
			mainWindow.display();
		}
	}

	return 0;
}