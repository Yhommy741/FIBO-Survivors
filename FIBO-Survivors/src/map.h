#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>
#include <optional>

class Map {
protected:
    std::filesystem::path exeDir;
    std::string fileName;

    sf::Texture texture;
    std::optional<sf::Sprite> sprite;

    int frameWidth = 32;
    int frameHeight = 32;

public:
    Map(std::string fileName_, const std::filesystem::path& exeDir_);

    void initialize();
    void load();
    void draw(sf::RenderWindow& window,sf::Vector2f playerPosition);

};