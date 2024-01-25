//////////////////////////////////////////////////////////////////////////
///
///		WELCOME TO THE THIRD PROJECT IN
///		JOHN HORTON'S BEGINNER GAME PROGRAMMING BOOK
/// 
///		
/// 
///////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include "GameConstants.h"
#include "Player.h"

#if _DEBUG // If Debug Config, use console subsystem
int main()
#else // If Release Config, use windows subsystem
int WinMain()
#endif
{
	enum class State {
		PAUSED, LEVELING_UP,
		GAME_OVER, PLAYING
	};
	// Start with the GAME_OVER state
	State state = State::GAME_OVER;

	// create the main window, prevent it from being resized
	sf::RenderWindow mainWindow(sf::VideoMode(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT), "Template Project", sf::Style::Titlebar | sf::Style::Close);
	// set framerate
	mainWindow.setFramerateLimit(144);

	sf::View mainView(sf::FloatRect(0, 0, GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT));


	// clock for timing
	sf::Clock clock;

	sf::Time gameTimeTotal;

	sf::Vector2f mouseWorldPosition;
	sf::Vector2i mouseScreenPosition;

	Player player;

	sf::IntRect arena;



	// start the game loop
	while (mainWindow.isOpen())
	{
		// Handle Timing
		sf::Time dt = clock.restart();

		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				// Pause a game while playing
				if (event.key.code == sf::Keyboard::Return && state == State::PLAYING)
				{
					state = State::PAUSED;
				}
				// Restart while paused
				else if (event.key.code == sf::Keyboard::Return && state == State::PAUSED)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}
				// Start a new game while in GAME_OVER state
				else if (event.key.code == sf::Keyboard::Return && state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;
				}

				if (state == State::PLAYING)
				{
				}
			}
		}

		// Clear window
		mainWindow.clear();

		// Draw stuff here


		// Finish drawing.
		mainWindow.display();
	}

	return 0;
}