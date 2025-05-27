#include "map.h"

Map::Map(std::string fileName_, const std::filesystem::path& exeDir_)
	: exeDir(exeDir_), fileName(fileName_) {
	initialize();
}

void Map::initialize() {
	load();
}

void Map::load() {
    std::filesystem::path assetPath = exeDir / ".." / ".." / "assets" / "map" / fileName;
    assetPath = std::filesystem::weakly_canonical(assetPath);

    if (!texture.loadFromFile(assetPath.string())) {
        std::cerr << "Failed to load texture\n";
        return;
    }

    // Create the sprite and set its properties
    sprite = sf::Sprite(texture);
    sprite->setScale({ 0.8, 0.8 });
    sprite->setPosition({ 960.f, 540.f });
}

void Map::draw(sf::RenderWindow& window, sf::Vector2f playerPosition) {
    if (!sprite) return;

    int gridSize = 20;
    int halfGrid = gridSize / 2;

    // Get the size of the tile (after scaling)
    float tileWidth = texture.getSize().x * sprite->getScale().x;
    float tileHeight = texture.getSize().y * sprite->getScale().y;

    // Find the top-left tile index to start drawing
    int startX = static_cast<int>(std::floor(playerPosition.x / tileWidth)) - halfGrid;
    int startY = static_cast<int>(std::floor(playerPosition.y / tileHeight)) - halfGrid;

    for (int y = 0; y < gridSize; ++y) {
        for (int x = 0; x < gridSize; ++x) {
            float drawX = (startX + x) * tileWidth + tileWidth / 2.f;
            float drawY = (startY + y) * tileHeight + tileHeight / 2.f;
            sprite->setPosition(sf::Vector2f(drawX, drawY));
            window.draw(*sprite);
        }
    }
}