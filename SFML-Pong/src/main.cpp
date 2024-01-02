//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include "GameConstants.h"
#include "GameRandom.h"

#if _DEBUG // If Debug Config, use console subsystem
int main()
#else // If Release Config, use windows subsystem
int WinMain()
#endif
{
	using namespace sf;

	// create the main window, prevent it from being resized
	RenderWindow mainWindow(VideoMode(GameConstants::gWindowWidth, GameConstants::gWindowHeight), "Template Project", sf::Style::Titlebar | sf::Style::Close);

	// set framerate
	mainWindow.setFramerateLimit(144);

	// clock for timing
	Clock clock;

	// start the game loop
	while (mainWindow.isOpen())
	{
		// Handle Timing
		Time dt = clock.restart();

		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				mainWindow.close();
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