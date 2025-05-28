#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>
#include <optional>

// Class HpBar to represent the health bar in the game
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
    // Constructor to initialize the HpBar with a file name and executable directory
    HpBar(std::string fileName, const std::filesystem::path& exeDir, int numFrames);

	// Initializes the health bar texture and sprite
    void initialize();

	// loads the health bar texture from the file
    void load();

	// Draws the health bar on the given window
    void draw(sf::RenderWindow& window);

	// Updates the health bar position based on the player's position
    void update(sf::Vector2f playerPosition);

	// Updates the health bar texture based on the current health points
    void animate(int currrntHp);
};
