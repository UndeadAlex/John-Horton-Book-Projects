//////////////////////////////////////////////////////////////////////////
///
///				WELCOME TO THE FIRST PROJECT IN
///				JOHN HORTON'S BEGINNER GAME PROGRAMMING BOOK
/// 
///				These are not designed to be the exact same as
///				what is shown in the book, i have re factored 
///				specific areas i thought might need as such.
/// 
///				e.g. the original book keeps code in a single .cpp file.
///				i chose to use classes where i thought they made sense.
/// 
///////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <array>

#include "GameConstants.h"
#include "GameRandom.h"

#include "TextureManager.h"
#include "AudioManager.h"

#include "Bee.h"
#include "Cloud.h"



enum GameState {
	START = 0,
	PLAYING = 1,
	END = 2,
};

enum class BranchSide{ LEFT, RIGHT, NONE };

constexpr int NUM_BRANCHES = 6;
void UpdateBranches(int seed, std::array<BranchSide, NUM_BRANCHES>& branchPositions)
{
	for (int i = NUM_BRANCHES - 1; i > 0; i--)
	{
		branchPositions[i] = branchPositions[i - 1];
	}

	int r = GameRandom::RandInt(0,5,seed);
	switch (r)
	{
	case 0:
		branchPositions[0] = BranchSide::LEFT;
		break;
	case 1:
		branchPositions[0] = BranchSide::RIGHT;
		break;
	default:
		branchPositions[0] = BranchSide::NONE;
		break;

	}
}

std::string enum_to_string(BranchSide t) {
	switch (t) {
	case BranchSide::LEFT:
		return "Left";
	case BranchSide::RIGHT:
		return "Right";
	case BranchSide::NONE:
		return "None";
	default:
		return "Invalid";

	}
}

#if _DEBUG // If Debug Config, use console subsystem
int main()
#else // If Release Config, use windows subsystem
int WinMain()
#endif
{
	using namespace sf;

	// create the main window, prevent it from being resized
	RenderWindow mainWindow(VideoMode(GameConstants::gWindowWidth, GameConstants::gWindowHeight), "Timmmmmberrrrr!", sf::Style::Titlebar | sf::Style::Close);
	mainWindow.setFramerateLimit(144);

	// clock for timing
	Clock clock;

	// Game State
	GameState gameState = GameState::START;


	// Load textures.
	{
		TextureManager::LoadTexture("assets/graphics/background.png", "background");
		TextureManager::LoadTexture("assets/graphics/tree.png", "tree");
		TextureManager::LoadTexture("assets/graphics/bee.png", "bee");
		TextureManager::LoadTexture("assets/graphics/cloud.png", "cloud");
		TextureManager::LoadTexture("assets/graphics/branch.png", "branch");
		TextureManager::LoadTexture("assets/graphics/player.png", "player");
		TextureManager::LoadTexture("assets/graphics/rip.png", "gravestone");
		TextureManager::LoadTexture("assets/graphics/axe.png", "axe");
		TextureManager::LoadTexture("assets/graphics/log.png", "log");
	}

	// Load Sounds
	{
		AudioManager::LoadAudio("assets/sounds/chop.wav", "chop");
		AudioManager::LoadAudio("assets/sounds/death.wav", "death");
		AudioManager::LoadAudio("assets/sounds/out_of_time.wav", "out_of_time");
	}
	
	// Initialize Player's score.
	int score = 0;
	
	// Branch Init
	std::array<Sprite, NUM_BRANCHES> branches;
	std::array<BranchSide, NUM_BRANCHES> branchPositions = { BranchSide::NONE,BranchSide::NONE, BranchSide::NONE, BranchSide::NONE, BranchSide::NONE, BranchSide::NONE };
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(*TextureManager::GetTexture("branch"));
		branches[i].setPosition(-2000, -2000);
		// Set the sprite's origin to dead centre
		branches[i].setOrigin(220, 20);
	}

	// HUD Text
	Text messageText;
	Text scoreText;

	Font KomiFont;
	if (!KomiFont.loadFromFile("assets/fonts/KOMIKAP_.ttf")) { printf("Failed to load font."); }
	
	// Set Message Text Settings
	messageText.setFont(KomiFont);
	messageText.setString("Press Enter to start!");
	messageText.setCharacterSize(75);
	messageText.setFillColor(Color::White);
	
	// Set Score Text Settings
	scoreText.setFont(KomiFont);
	scoreText.setString("Score: 0");
	scoreText.setCharacterSize(100);
	scoreText.setFillColor(Color::White);

	// Setup Debug text
#if _DEBUG
	Text debugText;
	debugText.setFont(KomiFont);
	debugText.setString("Debug");
	debugText.setCharacterSize(50);
	debugText.setFillColor(Color::White);
	debugText.setOrigin(debugText.getLocalBounds().width, 0);
	debugText.setPosition(GameConstants::gWindowWidth, 0);
#endif

	// Position the text
	GameConstants::centreTextOrigin(messageText);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// Background Graphics
	Sprite backgroundSprite;
	backgroundSprite.setTexture(*TextureManager::GetTexture("background"));
	backgroundSprite.setPosition(0, 0);

	// Tree Graphics
	Sprite treeSprite;
	treeSprite.setTexture(*TextureManager::GetTexture("tree"));
	treeSprite.setPosition(810,0);

	// The cutest lil bee
	Bee CuteBee(mainWindow, {0,0});
	CuteBee.Init();

	// McCool Cloud's 
	Cloud Cloud1(mainWindow, { 0,0 });
	Cloud1.Init();
	Cloud Cloud2(mainWindow, { 0,250 });
	Cloud2.Init();
	Cloud Cloud3(mainWindow, { 0,500 });
	Cloud3.Init();

	// Player
	Sprite playerSprite;
	playerSprite.setTexture(*TextureManager::GetTexture("player"));
	playerSprite.setPosition(580, 720);

	BranchSide playerSide = BranchSide::LEFT;

	// Gravestone
	Sprite graveSprite;
	graveSprite.setTexture(*TextureManager::GetTexture("gravestone"));
	graveSprite.setPosition(600, 860);

	// Axe
	Sprite axeSprite;
	axeSprite.setTexture(*TextureManager::GetTexture("axe"));
	axeSprite.setPosition(700, 830);

	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	// Tree log
	Sprite logSprite;
	logSprite.setTexture(*TextureManager::GetTexture("log"));
	logSprite.setPosition(810, 720);

	bool logActive = false;
	sf::Vector2f logSpeed = { 1000, -1500 };

	bool acceptInput = false;

	UpdateBranches(0, branchPositions);

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
			else if (event.type == Event::KeyReleased && gameState == PLAYING)
			{
				acceptInput = true;
				axeSprite.setPosition(2000, axeSprite.getPosition().y);
			}
			else if (gameState != GameState::PLAYING && event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
			{
				// Start Game
				gameState = GameState::PLAYING;

				score = 0;
				timeRemaining = 6;

				for (int i = 1; i < NUM_BRANCHES; i++)
				{
					branchPositions[i] = BranchSide::NONE;
				}
				// Make sure the gravestone is hidden
				graveSprite.setPosition(675, 2000);
				// Move the player into position
				playerSprite.setPosition(580, 720);
				acceptInput = true;
			}
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { mainWindow.close(); }
		
		// Update Loop
		{
			switch (gameState)
			{
			case START:
			{
				break;
			}
			case PLAYING:
			{
				timeRemaining -= dt.asSeconds();
				timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

				if (timeRemaining <= 0.0f) 
				{
					// Pause the game
					gameState = GameState::END;
					// Change the message shown to the player
					messageText.setString("Out of time!!\nPress ENTER to continue!");
					//Reposition the text based on its new size
					GameConstants::centreTextOrigin(messageText);
					messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

					AudioManager::GetAudio("out_of_time")->play();
				}


				CuteBee.Update(dt);
				Cloud1.Update(dt);
				Cloud2.Update(dt);
				Cloud3.Update(dt);

				// Set score text to value of score.
				std::stringstream scoreStream;
				scoreStream << "Score: " << score;
				scoreText.setString(scoreStream.str());

				// Update branch sprites
				for (int i = 0; i < NUM_BRANCHES; i++)
				{
					float height = i * 150;

					if (branchPositions[i] == BranchSide::LEFT)
					{
						branches[i].setPosition(610, height);
						branches[i].setRotation(180);
					}
					else if (branchPositions[i] == BranchSide::RIGHT)
					{
						branches[i].setPosition(1330, height);
						branches[i].setRotation(0);
					}
					else
					{
						branches[i].setPosition(-3000, height);
						branches[i].setRotation(0);
					}
				}

				// Handle the log of truth!
				if (logActive)
				{
					logSprite.setPosition(logSprite.getPosition() + (logSpeed * dt.asSeconds()));
					if (logSprite.getPosition().x < -100 || logSprite.getPosition().x > 2000)
					{
						logActive = false;
						logSprite.setPosition(810, 720);
					}
				}

				// Wrap the player controls to
				// Make sure we are accepting input
				if (acceptInput)
				{
					if (Keyboard::isKeyPressed(Keyboard::Right))
					{
						playerSide = BranchSide::RIGHT;
						score++;

						timeRemaining += (2 / score) + .15;

						axeSprite.setPosition(AXE_POSITION_RIGHT, axeSprite.getPosition().y);

						playerSprite.setPosition(1200, 720);

						UpdateBranches(score, branchPositions);

						logSprite.setPosition(810, 720);
						logSpeed.x = -5000;
						logActive = true;

						AudioManager::GetAudio("chop")->play();

						acceptInput = false;
					}
					else if (Keyboard::isKeyPressed(Keyboard::Left))
					{
						playerSide = BranchSide::LEFT;
						score++;

						timeRemaining += (2 / score) + .15;

						axeSprite.setPosition(AXE_POSITION_LEFT, axeSprite.getPosition().y);

						playerSprite.setPosition(580, 720);

						UpdateBranches(score, branchPositions);

						logSprite.setPosition(810, 720);
						logSpeed.x = 5000;
						logActive = true;

						AudioManager::GetAudio("chop")->play();

						acceptInput = false;
					}
				}
				if (branchPositions[5] == playerSide)
				{
					gameState = GameState::END;
					acceptInput = false;

					graveSprite.setPosition(525, 760);

					playerSprite.setPosition(2000, 660);

					messageText.setString("SQUISHED!!");
					GameConstants::centreTextOrigin(messageText);
					messageText.setPosition(GameConstants::gWindowWidth / 2, GameConstants::gWindowHeight / 2);

					AudioManager::GetAudio("death")->play();
				}
#if _DEBUG
				std::stringstream debugStream;
				debugStream << "PS: " << enum_to_string(playerSide) << std::endl; 
				for (int i = 0; i < NUM_BRANCHES; i++)
				{
					debugStream << "BS "<< i << ": " << enum_to_string(branchPositions[i]) << std::endl;
				}
				debugText.setString(debugStream.str());
				debugText.setOrigin(debugText.getLocalBounds().width, 0);
				debugText.setPosition(GameConstants::gWindowWidth,0);
#endif
				break;
			}
			case END:
			{

				break;
			}
			default:
				break;
			}

			
		}

		// Render Loop
		{
			// Clear window
			mainWindow.clear();

			// Use Gamestate to render only specific elements
			switch (gameState)
			{
			case START:
			{
				mainWindow.draw(messageText);
				break;
			}
			case PLAYING:
			{
				// Draw background
				mainWindow.draw(backgroundSprite);

				// Draw Clouds
				Cloud1.Render();
				Cloud2.Render();
				Cloud3.Render();

				// Draw the branches
				for (int i = 0; i < NUM_BRANCHES; i++) 
				{
					mainWindow.draw(branches[i]);
				}

				// Draw tree
				mainWindow.draw(treeSprite);
				
				// Draw player
				mainWindow.draw(playerSprite);

				// Draw axe
				mainWindow.draw(axeSprite);

				// Draw log
				if(logActive)
					mainWindow.draw(logSprite);

				// Draw the BEEEEE :P
				CuteBee.Render();

				mainWindow.draw(scoreText);
				mainWindow.draw(timeBar);
				mainWindow.draw(debugText);
				break;
			}
			case END:
			{
				mainWindow.draw(backgroundSprite);

				// Draw the branches
				for (int i = 0; i < NUM_BRANCHES; i++)
				{
					mainWindow.draw(branches[i]);
				}

				// Draw tree
				mainWindow.draw(treeSprite);

				// Draw grave
				mainWindow.draw(graveSprite);

				mainWindow.draw(scoreText);
				mainWindow.draw(messageText);
				break;
			}
			default:
				break;
			}

			// Finish drawing.
			mainWindow.display();
		}
	}

	return 0;
}