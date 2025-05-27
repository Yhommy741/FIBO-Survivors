#pragma once
#include "game.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include "entity.h"
#include "player.h"
#include "map.h"

Game::Game(int argc, char* argv[])
    : userInput{ false, false, false, false, false, false } // Initialize userInput
{
    // Initialize exeDir using the executable path  
    exePath = std::filesystem::path(argv[0]);
    exeDir = exePath.parent_path();

    // Initialize player 
    player = std::make_unique<Player>("FIBOGoose.png", exeDir,4);
    map = std::make_unique<Map>("GrassTile.png", exeDir);
}

void Game::init()
{
    window.create(sf::VideoMode({ 1920, 1080 }), "FIBO Survivors", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    view.setSize({ 1920.f, 1080.f });
    view.setCenter({ 960.f, 540.f });
    window.setView(view);

}

void Game::userInputSystem() 
{
    // Reset movement input every frame
    userInput.up = false;
    userInput.down = false;
    userInput.left = false;
    userInput.right = false;
    userInput.esc = false;
    userInput.pause = false;

    // Real-time movement polling (smooth movement)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        userInput.up = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        userInput.down = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        userInput.left = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        userInput.right = true;
    
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void Game::renderSystem() 
{
	window.clear(sf::Color::Black);
	
}

void Game::update() 
{
    userInputSystem();
    renderSystem();
    switch (gameState) {
    case PLAYING:
        updatePlaying();
        break;
    case PAUSED:
        break;
    case GAME_OVER:
        updateGameOver();
        break;
    }
    window.display();
}

void Game::updatePlaying() 
{
    float deltaTime = clock.restart().asSeconds();

    view.setCenter(player->getPosition());
    window.setView(view);

	map->draw(window,player->getPosition());
    player->animate(deltaTime);
	player->move(userInput.up, userInput.down, userInput.left, userInput.right);
    player->draw(window);
}

void Game::updateGameOver() 
{

}

void Game::run() 
{
    while (window.isOpen()) 
    {
        update();
    }
}