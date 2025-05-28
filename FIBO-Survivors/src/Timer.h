#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <array>
#include <optional>

class Timer {
protected:
    std::filesystem::path exeDir;
    std::string fileName;

    sf::Texture texture;
    std::array<std::optional<sf::Sprite>, 5> sprites; // 5 sprites for MM:SS

    int frameWidth = 20;
    int frameHeight = 20;

    float elapsedSeconds = 0.f;

    int maxMinutes = 15;
    int totalFrames = 11;  

public:
    Timer(const std::string& fileName, const std::filesystem::path& exeDir, int totalFrames = 11);

    void initialize();
    void load();
    void update(float deltaTime, sf::Vector2f playerPosition);
    void draw(sf::RenderWindow& window);

protected:
    int digitToFrame(int digit);
};
