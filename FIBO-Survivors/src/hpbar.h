#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>
#include <optional>

class HpBar {
protected:
    std::filesystem::path exeDir;
    std::string fileName;

    sf::Texture texture;
    std::optional<sf::Sprite> sprite;

    // Animation-related members
    sf::IntRect animationFrame;
    int frameWidth = 64;
    int frameHeight = 32;
    int totalFrames;
    float frameDuration = 0.1f;
    float elapsedTime = 0.0f;

public:
    HpBar(std::string fileName, const std::filesystem::path& exeDir, int numFrames);

    void initialize();
    void load();
    void draw(sf::RenderWindow& window);
    void update(sf::Vector2f playerPosition);
    void animate(int currrntHp);
};
