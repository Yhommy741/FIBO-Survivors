#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <filesystem>
#include <fstream>

int main(int argc, char* argv[])
{
    // File Path Settings
    std::filesystem::path exePath = std::filesystem::absolute(argv[0]);
    std::filesystem::path exeDir = exePath.parent_path();
    std::string fileName = "FIBOGoose.png";
    std::filesystem::path assetPath = exeDir / ".." / ".." / "assets" / "entity" / "player" / fileName;
    assetPath = std::filesystem::weakly_canonical(assetPath);

    // Window and player setup
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "FIBO Survivors");
    sf::Texture playerTexture;
    sf::Sprite playerSprite(playerTexture);

    if (playerTexture.loadFromFile(assetPath.string())) {
        playerSprite.setTexture(playerTexture);
        playerSprite.setTextureRect(sf::IntRect({ 0,0 }, { 32,32 }));
        playerSprite.setOrigin({ 16.f, 16.f });
        playerSprite.setScale({ 5.f, 5.f });
    }
    else {
        std::cerr << "Failed to load player texture: " << assetPath << std::endl;
        return -1;
    }

    // Map tile settings
    std::string mapFile = "GrassTile.png";
    std::filesystem::path mapPath = exeDir / ".." / ".." / "assets" / "map" / mapFile;
    mapPath = std::filesystem::weakly_canonical(mapPath);

    sf::Texture tileTexture;
    if (!tileTexture.loadFromFile(mapPath.string())) {
        std::cerr << "Failed to load map tile: " << mapPath << std::endl;
        return -1;
    }
    sf::Sprite tile(tileTexture);

    // Animation Settings
    sf::Clock animationClock;
    float frameDuration = 0.1f;
    int currentFrame = 0;
    const int numFrames = 4;
    bool facingRight = true;

    // Player position
    sf::Vector2f playerPosition = window.getView().getCenter();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::Black);

        // Movement input
        const float speed = 1.f;
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            movement.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            movement.y += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            movement.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            movement.x += 1.f;

        // Normalize movement
        if (movement.x != 0.f || movement.y != 0.f)
        {
            float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
            movement.x = (movement.x / length) * speed;
            movement.y = (movement.y / length) * speed;
        }

        playerPosition += movement;
        playerSprite.setPosition(playerPosition);

        // Animation update
        if (animationClock.getElapsedTime().asSeconds() > frameDuration)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            playerSprite.setTextureRect(sf::IntRect({ currentFrame * 32, 0 }, { 32, 32 }));
            animationClock.restart();
        }

        // Flip sprite based on direction
        if (movement.x < 0) {
            if (facingRight) {
                facingRight = false;
                playerSprite.setScale({ -5.f, 5.f });
                playerSprite.setOrigin({ 16.f, 16.f });
            }
        }
        else if (movement.x > 0) {
            if (!facingRight) {
                facingRight = true;
                playerSprite.setScale({ 5.f, 5.f });
                playerSprite.setOrigin({ 16.f, 16.f });
            }
        }

		// Map Generation
        const int tileSize = tileTexture.getSize().x;
        const int N = 20;

        int px = static_cast<int>(std::floor(playerPosition.x / tileSize));
        int py = static_cast<int>(std::floor(playerPosition.y / tileSize));
        for (int y = -N; y <= N; ++y) {
            for (int x = -N; x <= N; ++x) {
                tile.setPosition(
                    {static_cast<float>((px + x) * tileSize),
                     static_cast<float>((py + y) * tileSize) }
                );
                window.draw(tile);
            }
        }

        // Center the view on the player
        sf::View view = window.getView();
        view.setCenter(playerPosition);
        window.setView(view);
        window.draw(playerSprite);
        window.display();
    }
}