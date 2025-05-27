#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>
#include <optional>

class Entity {
private:
    std::filesystem::path exeDir;
    std::string fileName;

    sf::Texture texture;
    std::optional<sf::Sprite> sprite;



public:
    Entity(std::string fileName_, const std::filesystem::path& exeDir_);

    void initialize();
    void load();
    void draw(sf::RenderWindow& window);
};