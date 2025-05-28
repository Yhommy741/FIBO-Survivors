#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <array>
#include <optional>

// Class Timer represents Survive timee in the game.
class Timer {
protected:
    std::filesystem::path exeDir;
    std::string fileName;

    sf::Texture texture;
    std::array<std::optional<sf::Sprite>, 5> sprites;

    int frameWidth = 20;
    int frameHeight = 20;

    float elapsedSeconds = 0.f;

    int maxMinutes = 15;
    int totalFrames = 11;  

public:
	// Constructor to initialize the Timer with a file name, executable directory, and total frames
    Timer(const std::string& fileName, const std::filesystem::path& exeDir, int totalFrames = 11);

	// Initializes the Timer by loading the texture and setting up sprites
    void initialize();
    void load();

	// Updates the Timer based on elapsed time and player position
    void update(float deltaTime, sf::Vector2f playerPosition);

	// Draws the Timer on the given window
    void draw(sf::RenderWindow& window);

protected:
	// Converts a digit to the corresponding frame index
    int digitToFrame(int digit);
};
