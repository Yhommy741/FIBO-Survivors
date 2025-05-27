#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <filesystem>
#include <vector>
#include <memory>
#include "entity.h"
#include "player.h"
#include "map.h"
#include "monster.h"

enum GameState {
    PLAYING,
    GAME_OVER,
    PAUSED
};

struct Input
{
    bool up;
	bool down;
	bool left;
	bool right;
	bool esc;
	bool pause;
};

class Game {  
private:  
   std::filesystem::path exePath;  
   std::filesystem::path exeDir;  
   sf::RenderWindow window;  
   sf::View view;  

   GameState gameState = PLAYING;  

   sf::Clock clock;

   Input userInput;  

   std::unique_ptr<Player> player;
   std::unique_ptr<Map> map;
   

   void update();  
   void userInputSystem();  
   void renderSystem();  
   void updatePlaying();  
   void updateGameOver();  

public:  
   Game(int argc, char* argv[]);  
   void init();  
   void run();  
};    
