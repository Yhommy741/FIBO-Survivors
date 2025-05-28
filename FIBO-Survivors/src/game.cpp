#pragma once
#include "game.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include "entity.h"
#include "player.h"
#include "map.h"
#include "monster.h"
#include "bullet.h"
#include "hpbar.h"
#include "ui.h"

Game::Game(int argc, char* argv[])
    : userInput{ false, false, false, false, false, false } // Initialize userInput
{
    // Initialize exeDir using the executable path  
    exePath = std::filesystem::path(argv[0]);
    exeDir = exePath.parent_path();

    // Initialize player 
    player = std::make_unique<Player>("FIBOGoose.png", exeDir,4);
    map = std::make_unique<Map>("GrassTile.png", exeDir);
	hpBar = std::make_unique<HpBar>("HP.png", exeDir, 11); 
    gameOver = std::make_unique<UI>("GameOver.png", exeDir, 0);
    monster = std::make_unique<Monster>("Sprite-Capa-stand.png", exeDir, 4);
    monster->randomSpawn(player->getPosition());

    // สร้าง monster หลายตัว
    int monsterCount = 5; // จำนวนที่ต้องการ
    for (int i = 0; i < monsterCount; ++i) {
        MonsterInfo info = getRandomMonsterInfo();
        auto m = std::make_unique<Monster>(info.fileName, exeDir, info.numFrames);
        m->randomSpawn(player->getPosition());
        monsters.push_back(std::move(m));
    }

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

    map->draw(window, player->getPosition());
    player->animate(deltaTime);
    player->move(userInput.up, userInput.down, userInput.left, userInput.right);
    player->draw(window);
    hpBar->update(player->getPosition());
    hpBar->draw(window);

    if (monsterSpawnClock.getElapsedTime().asSeconds() >= monsterSpawnInterval) {
        MonsterInfo info = getRandomMonsterInfo();
        auto m = std::make_unique<Monster>(info.fileName, exeDir, info.numFrames);
        m->randomSpawn(player->getPosition());
        monsters.push_back(std::move(m));
        monsterSpawnClock.restart();
    }

    for (auto& m : monsters) {
        m->animate(deltaTime);
        m->moveToward(player->getPosition(), 2.f);
        m->draw(window);
    }

    if (bulletClock.getElapsedTime().asSeconds() >= bulletSpawnInterval) {
        sf::Vector2i mousePosScreen = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosWorld = window.mapPixelToCoords(mousePosScreen);
        sf::Vector2f playerPos = player->getPosition();
        sf::Vector2f direction = mousePosWorld - playerPos;

        bullets.push_back(std::make_unique<Bullet>(exeDir, playerPos, direction));
        bulletClock.restart();
    }

    for (auto it = bullets.begin(); it != bullets.end();) {
        (*it)->update(deltaTime);
        (*it)->draw(window);

        // Remove if dead
        if ((*it)->isDead()) {
            it = bullets.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool bulletRemoved = false;

        for (auto monsterIt = monsters.begin(); monsterIt != monsters.end();) {
            if ((*bulletIt)->getBounds().findIntersection((*monsterIt)->getBounds())) {
                bulletIt = bullets.erase(bulletIt);
                monsterIt = monsters.erase(monsterIt);
                bulletRemoved = true;
                break; // break out of monster loop
            }
            else {
                ++monsterIt;
            }
        }

        if (!bulletRemoved) ++bulletIt;
    }

    auto it = monsters.begin();
    bool damagedThisFrame = false;
    while (it != monsters.end()) {
        (*it)->animate(deltaTime);
        (*it)->moveToward(player->getPosition(), 2.f);
        (*it)->draw(window);

        if (!damagedThisFrame && player->getSprite() && (*it)->getSprite()) {
            auto playerPos = player->getPosition();
            auto monsterPos = (*it)->getPosition();

            float dx = playerPos.x - monsterPos.x;
            float dy = playerPos.y - monsterPos.y;
            float distance = std::sqrt(dx * dx + dy * dy);

            float collisionRadius = 32.0f;
            if (distance < collisionRadius) {
                player->decreaseHp(1);
                hpBar->animate(player->getHp());
                it = monsters.erase(it);
                damagedThisFrame = true;

                if (player->getHp() <= 0) {
                    gameState = GAME_OVER;
                    return;
                }
                continue;
            }
        }
        ++it;
    }
}

void Game::updateGameOver()
{
    view.setCenter(gameOver->getPosition());
    window.setView(view);
    gameOver->draw(window);
}

void Game::run() 
{
    while (window.isOpen()) 
    {
        update();
    }
}




