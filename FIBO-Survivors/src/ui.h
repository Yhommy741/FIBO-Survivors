#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>
#include <optional>

// UI class represents a UI in the game.
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
    // Constructor to initialize the UI with a file name and executable directory
    UI(std::string fileName_, const std::filesystem::path& exeDir_, int numFrames);

    // Initializes UI texture and sprite
    virtual void initialize();
    virtual void load();

    // Draws UI on the given window
    virtual void draw(sf::RenderWindow& window);

    // Getter of UI Position
    virtual sf::Vector2f getPosition();

};
