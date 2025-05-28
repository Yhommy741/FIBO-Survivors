#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>
#include <optional>

// Map Class to handle map loading and rendering
class Map {
protected:
    std::filesystem::path exeDir;
    std::string fileName;

    sf::Texture texture;
    std::optional<sf::Sprite> sprite;

    int frameWidth = 32;
    int frameHeight = 32;

public:

	// Constructor to initialize the map with a file name and executable directory
    Map(std::string fileName_, const std::filesystem::path& exeDir_);

	// Initialize the map by loading the texture and creating a sprite
    void initialize();
    void load();

	//Generate Tile around player Make it like Infinity Map
    void draw(sf::RenderWindow& window,sf::Vector2f playerPosition);

};