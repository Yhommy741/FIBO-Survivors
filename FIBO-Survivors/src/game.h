#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>
#include <filesystem>
#include <vector>
#include <memory>
#include "entity.h"
#include "player.h"
#include "map.h"
#include "monster.h"
#include "bullet.h"
#include "hpbar.h"
#include "ui.h"
#include "Timer.h"

//Game status
enum GameState {
    PLAYING,
    GAME_OVER,
    PAUSED
};

// Input structure to handle user input
struct Input
{
    bool up;
	bool down;
	bool left;
	bool right;
	bool esc;
	bool pause;
};

// Game class to manage the game state, rendering objects, and user input
class Game {  
private:  
   std::filesystem::path exePath;  
   std::filesystem::path exeDir;  
   sf::RenderWindow window;  
   sf::View view;  

   // Game state setup
   GameState gameState = PLAYING;  

   // Game clock and timers
   sf::Clock clock;
   sf::Clock monsterSpawnClock;
   sf::Clock bulletClock;

   // monster and bullet spawn intervals
   float monsterSpawnInterval = 0.4f;
   float bulletSpawnInterval = 0.5f;

   // User input handling
   Input userInput;  

   // Game objects
   std::unique_ptr<Player> player;
   std::unique_ptr<Map> map;
   std::unique_ptr<Monster> monster;
   std::unique_ptr<HpBar> hpBar;
   std::unique_ptr<UI> gameOver;
   std::vector<std::unique_ptr<Monster>> monsters;
   std::vector<std::unique_ptr<Bullet>> bullets;
   std::unique_ptr<Timer> timer;

   // Handling All game objects rendering and updates
   void update();  

   // Handling user input, rendering, and game state updates
   void userInputSystem();  

   // Clear the window and render all game objects
   void renderSystem();  

   //Handling All game objects rendering and updates on Playing state
   void updatePlaying();  

   // Handling game over state rendering
   void updateGameOver();  

public:  
	// Constructor to initialize the game with command line arguments
    Game(int argc, char* argv[]);  

	// Initialize the game window, view, and other resources
    void init(); 

	// Game loop to run the game
    void run();  
};
