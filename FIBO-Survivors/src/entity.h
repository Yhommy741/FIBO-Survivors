#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>
#include <optional>

// Class Entity to represent a game entity with texture, sprite, and animation capabilities.
class Entity {
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
	//Constructor to initialize the entity with a file name, executable directory, and number of frames.
    Entity(std::string fileName_, const std::filesystem::path& exeDir_, int numFrames);

	// Initialize the entity by loading the texture and setting up the sprite.
    virtual void initialize();
    virtual void load();

	// Draw the entity to the specified render window.
    virtual void draw(sf::RenderWindow& window);

	// Animate the entity by updating the current frame based on elapsed time.
    virtual void animate(float deltaTime); 

	// Getters for position, bounds, and sprite.
    virtual sf::Vector2f getPosition();
    virtual sf::FloatRect getBounds();
    virtual const std::optional<sf::Sprite>& getSprite()const{return sprite;}
};