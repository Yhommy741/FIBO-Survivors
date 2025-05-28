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
   sf::Clock monsterSpawnClock;
   sf::Clock bulletClock;
   float monsterSpawnInterval = 0.4f;
   float bulletSpawnInterval = 0.5f;

   Input userInput;  

   std::unique_ptr<Player> player;
   std::unique_ptr<Map> map;
   std::unique_ptr<Monster> monster;
   std::unique_ptr<HpBar> hpBar;
   std::unique_ptr<UI> gameOver;
   std::vector<std::unique_ptr<Monster>> monsters;
   std::vector<std::unique_ptr<Bullet>> bullets;

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
