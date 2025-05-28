#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>
#include <optional>

class UI {
protected:
    std::filesystem::path exeDir;
    std::string fileName;

    sf::Texture texture;
    std::optional<sf::Sprite> sprite;

    // Animation-related members
    sf::IntRect animationFrame;
    int frameWidth = 32;
    int frameHeight = 32;
    int totalFrames;
    float frameDuration = 0.1f;
    float elapsedTime = 0.0f;

public:
    UI(std::string fileName_, const std::filesystem::path& exeDir_, int numFrames);

    virtual void initialize();
    virtual void load();
    virtual void draw(sf::RenderWindow& window);
    virtual sf::Vector2f getPosition();

};
