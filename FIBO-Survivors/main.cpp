#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Angle.hpp>
#include <filesystem>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>

// --- Rects Intersect helper for SFML 3.x ---
bool rectsIntersect(const sf::FloatRect& a, const sf::FloatRect& b) {
    return (a.position.x < b.position.x + b.size.x) && (a.position.x + a.size.x > b.position.x) &&
        (a.position.y < b.position.y + b.size.y) && (a.position.y + a.size.y > b.position.y);
}

// --- Bullet class ---
class Bullet {
public:
    Bullet(
        const sf::Texture& texture,
        const sf::Vector2f& startPos,
        const sf::Vector2f& targetPos,
        float speed,
        float baseDamage,
        float damageModifier = 0.0f
    ) : sprite(texture),
        position(startPos),
        speed(speed),
        damage(baseDamage + damageModifier),
        distanceTraveled(0.0f),
        animationFrame(0),
        animationTimer(0.0f)
    {
        sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 16 }));
        sprite.setOrigin({ 8.f, 8.f });
        sprite.setPosition(position);
        sprite.setScale({ 7.f, 7.f });

        // Calculate normalized direction vector
        sf::Vector2f dir = targetPos - startPos;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len != 0)
            direction = dir / len;
        else
            direction = { 1.f, 0.f };

        float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f + 180.f;
        sprite.setRotation(sf::degrees(angle));
    }

    void update(float dt) {
        sf::Vector2f move = direction * speed * dt;
        position += move;
        distanceTraveled += std::sqrt(move.x * move.x + move.y * move.y);
        sprite.setPosition(position);

        animationTimer += dt;
        if (animationTimer > 0.08f) {
            animationFrame = (animationFrame + 1) % 4;
            sprite.setTextureRect(sf::IntRect({ 0, animationFrame * 16 }, { 16, 16 }));
            animationTimer = 0.0f;
        }

        float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f + 180.f;
        sprite.setRotation(sf::degrees(angle));
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(sprite);
    }

    bool isAlive() const {
        return distanceTraveled < 1000.f;
    }

    // Hitbox เล็กลง (กลางกระสุน)
    sf::FloatRect getHitbox() const {
        sf::FloatRect box = sprite.getGlobalBounds();
        float shrink = 0.4f; // shrink 40%
        box.position.x += box.size.x * shrink / 2.f;
        box.position.y += box.size.y * shrink / 2.f;
        box.size.x *= (1.f - shrink);
        box.size.y *= (1.f - shrink);
        return box;
    }

private:
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;
    float damage;
    float distanceTraveled;
    int animationFrame;
    float animationTimer;
};

// --- Monster (Capa) class ---
class Monster {
public:
    Monster(const sf::Texture& texture, const sf::Vector2f& startPos)
        : sprite(texture), position(startPos), hitCount(0), highlightTimer(0.f), dead(false), deathTimer(0.f),
        animFrame(0), animTimer(0.f)
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 32, 32 }));
        sprite.setOrigin({ 16.f, 16.f });
        sprite.setPosition(position);
        sprite.setScale({ 4.f, 4.f });
    }

    void update(float dt, const sf::Vector2f& playerPos) {
        if (dead) {
            if (deathTimer > 0.f)
                deathTimer -= dt;
            return;
        }
        // Animation
        animTimer += dt;
        if (animTimer > 0.09f) {
            animFrame = (animFrame + 1) % 8;
            sprite.setTextureRect(sf::IntRect({ animFrame * 32, 0 }, { 32, 32 }));
            animTimer = 0.f;
        }
        // Move toward player
        sf::Vector2f dir = playerPos - position;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len > 1e-2f) {
            dir /= len;
            position += dir * 200.0f * dt;
            sprite.setPosition(position);
        }
        if (highlightTimer > 0.f)
            highlightTimer -= dt;
    }

    void draw(sf::RenderWindow& window) const {
        if (dead && deathTimer <= 0.f) return;
        sf::Sprite s = sprite;
        if (highlightTimer > 0.f || (dead && deathTimer > 0.f)) {
            s.setColor(sf::Color(255, 80, 80));
        }
        window.draw(s);
    }

    // Hitbox เล็กลง (กลางตัว)
    sf::FloatRect getHitbox() const {
        sf::FloatRect box = sprite.getGlobalBounds();
        float shrink = 0.5f; // shrink 50%
        box.position.x += box.size.x * shrink / 2.f;
        box.position.y += box.size.y * shrink / 2.f;
        box.size.x *= (1.f - shrink);
        box.size.y *= (1.f - shrink);
        return box;
    }

    bool checkPlayerCollision(const sf::FloatRect& playerBounds) {
        return !dead && rectsIntersect(getHitbox(), playerBounds);
    }

    bool checkBulletCollision(const sf::FloatRect& bulletBounds) {
        return !dead && rectsIntersect(getHitbox(), bulletBounds);
    }

    void onHitPlayer() {
        hitCount++;
        highlightTimer = 0.2f;
        if (hitCount >= 2) {
            dead = true;
            deathTimer = 0.5f;
        }
    }

    void onHitByBullet() {
        if (!dead) {
            dead = true;
            highlightTimer = 0.5f;
            deathTimer = 0.5f;
        }
    }

    bool isDead() const { return dead && deathTimer <= 0.f; }

private:
    sf::Sprite sprite;
    sf::Vector2f position;
    int hitCount;
    float highlightTimer;
    bool dead;
    float deathTimer;
    int animFrame;
    float animTimer;
};

// สุ่มตำแหน่ง spawn รอบขอบจอ
sf::Vector2f randomMonsterSpawn(const sf::View& view, float margin = 100.f) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist01(0.f, 1.f);

    float left = view.getCenter().x - view.getSize().x / 2.f;
    float right = view.getCenter().x + view.getSize().x / 2.f;
    float top = view.getCenter().y - view.getSize().y / 2.f;
    float bottom = view.getCenter().y + view.getSize().y / 2.f;
    int edge = static_cast<int>(dist01(gen) * 4);
    float x, y;
    switch (edge) {
    case 0: // top
        x = left + dist01(gen) * view.getSize().x;
        y = top - margin;
        break;
    case 1: // bottom
        x = left + dist01(gen) * view.getSize().x;
        y = bottom + margin;
        break;
    case 2: // left
        x = left - margin;
        y = top + dist01(gen) * view.getSize().y;
        break;
    default: // right
        x = right + margin;
        y = top + dist01(gen) * view.getSize().y;
        break;
    }
    return { x, y };
}

int main(int argc, char* argv[])
{
    // File Path Settings
    std::filesystem::path exePath = std::filesystem::absolute(argv[0]);
    std::filesystem::path exeDir = exePath.parent_path();
    std::string fileName = "FIBOGoose.png";
    std::filesystem::path assetPath = exeDir / ".." / ".." / "assets" / "entity" / "player" / fileName;
    assetPath = std::filesystem::weakly_canonical(assetPath);

    // Load bullet texture
    // (Blue)
    std::string B_bulletFile = "Bullet_Bluefire_blue.png";
    std::filesystem::path B_bulletPath = exeDir / ".." / ".." / "assets" / "entity" / "bullet" / B_bulletFile;
    B_bulletPath = std::filesystem::weakly_canonical(B_bulletPath);

    // (Amethyst)
    std::string Ar_bulletFile = "Bullet_Bluefire_amethyst.png";
    std::filesystem::path Ar_bulletPath = exeDir / ".." / ".." / "assets" / "entity" / "bullet" / Ar_bulletFile;
    Ar_bulletPath = std::filesystem::weakly_canonical(Ar_bulletPath);

    // (Red)
    std::string R_bulletFile = "Bullet_Bluefire_red.png";
    std::filesystem::path R_bulletbulletPath = exeDir / ".." / ".." / "assets" / "entity" / "bullet" / R_bulletFile;
    R_bulletbulletPath = std::filesystem::weakly_canonical(R_bulletbulletPath);

    // Load monster texture
    std::string capaFile = "Sprite-Capa-stand.png";
    std::filesystem::path capaPath = exeDir / ".." / ".." / "assets" / "entity" / "monster" / capaFile;
    capaPath = std::filesystem::weakly_canonical(capaPath);

    // Window and player setup
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "FIBO Survivors");

    // --- Custom Cursor Setup ---
    std::string cursorFiles[3] = { "cursor_blue.png", "cursor_amethyst.png", "cursor_red.png" };
    sf::Texture cursorTextures[3];
    for (int i = 0; i < 3; ++i) {
        std::filesystem::path cursorPath = exeDir / ".." / ".." / "assets" / "entity" / "cursor" / cursorFiles[i];
        cursorPath = std::filesystem::weakly_canonical(cursorPath);
        if (!cursorTextures[i].loadFromFile(cursorPath.string())) {
            std::cerr << "Failed to load cursor texture: " << cursorPath << std::endl;
            return -1;
        }
    }
    sf::Sprite cursorSprite{ cursorTextures[0] };
    cursorSprite.setOrigin({ static_cast<float>(cursorTextures[0].getSize().x) / 2.f, static_cast<float>(cursorTextures[0].getSize().y) / 2.f });
    cursorSprite.setScale({ 2.f, 2.f });

    window.setMouseCursorVisible(false);

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

    // --- Bullet system setup ---
    sf::Texture bulletTextureBlue, bulletTextureAmethyst, bulletTextureRed;
    if (!bulletTextureBlue.loadFromFile(B_bulletPath.string())) {
        std::cerr << "Failed to load bullet texture: " << B_bulletPath << std::endl;
        return -1;
    }
    if (!bulletTextureAmethyst.loadFromFile(Ar_bulletPath.string())) {
        std::cerr << "Failed to load bullet texture: " << Ar_bulletPath << std::endl;
        return -1;
    }
    if (!bulletTextureRed.loadFromFile(R_bulletbulletPath.string())) {
        std::cerr << "Failed to load bullet texture: " << R_bulletbulletPath << std::endl;
        return -1;
    }
    std::vector<Bullet> bullets;

    // Bullet type: 1=Blue, 2=Amethyst, 3=Red
    int bulletType = 1;
    bool spacePressedLastFrame = false;

    float baseFireRate = 1.5f;
    float fireRateModifier = 0.0f;
    float baseDamage = 10.0f;
    float damageModifier = 0.0f;
    float bulletSpeed = 200.0f;

    sf::Clock fireClock;
    sf::Clock playerAnimClock;

    float frameDuration = 0.1f;
    int currentFrame = 0;
    const int numFrames = 4;
    bool facingRight = true;

    // --- Monster system setup ---
    sf::Texture capaTexture;
    if (!capaTexture.loadFromFile(capaPath.string())) {
        std::cerr << "Failed to load monster texture: " << capaPath << std::endl;
        return -1;
    }
    std::vector<Monster> monsters;
    sf::Clock monsterSpawnClock;
    const float monsterSpawnInterval = 1.5f;
    const int maxMonsters = 10;

    // Player position
    sf::Vector2f playerPosition = window.getView().getCenter();

    // Highlight timer for player
    float playerHighlightTimer = 0.f;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::Black);

        // Handle bullet type switching with Spacebar
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if (!spacePressedLastFrame) {
                bulletType = bulletType % 3 + 1; // 1->2->3->1
                spacePressedLastFrame = true;
            }
        }
        else {
            spacePressedLastFrame = false;
        }

        // Movement input
        const float speed = 1.f;
        sf::Vector2f movement{ 0.f, 0.f };
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

        // Animation update (player)
        if (playerAnimClock.getElapsedTime().asSeconds() > frameDuration)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            playerSprite.setTextureRect(sf::IntRect({ currentFrame * 32, 0 }, { 32, 32 }));
            playerAnimClock.restart();
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
                    { static_cast<float>((px + x) * tileSize),
                     static_cast<float>((py + y) * tileSize) }
                );
                window.draw(tile);
            }
        }

        // --- Monster spawn ---
        if (monsterSpawnClock.getElapsedTime().asSeconds() > monsterSpawnInterval && monsters.size() < maxMonsters) {
            sf::Vector2f spawnPos = randomMonsterSpawn(window.getView());
            if (std::hypot(spawnPos.x - playerPosition.x, spawnPos.y - playerPosition.y) > 300.f) {
                monsters.emplace_back(capaTexture, spawnPos);
                monsterSpawnClock.restart();
            }
        }

        // --- Update & draw monsters ---
        static sf::Clock monsterAnimClock;
        float dt = monsterAnimClock.restart().asSeconds();
        bool playerHit = false;
        for (auto it = monsters.begin(); it != monsters.end(); ) {
            it->update(dt, playerPosition);
            // Player collision
            sf::FloatRect playerHitbox = playerSprite.getGlobalBounds();
            float shrink = 0.5f;
            playerHitbox.position.x += playerHitbox.size.x * shrink / 2.f;
            playerHitbox.position.y += playerHitbox.size.y * shrink / 2.f;
            playerHitbox.size.x *= (1.f - shrink);
            playerHitbox.size.y *= (1.f - shrink);

            if (it->checkPlayerCollision(playerHitbox)) {
                if (!it->isDead()) {
                    it->onHitPlayer();
                    playerHit = true;
                }
            }
            ++it;
        }

        // --- Bullet vs Monster collision ---
        for (auto mIt = monsters.begin(); mIt != monsters.end(); ++mIt) {
            if (mIt->isDead()) continue;
            for (auto bIt = bullets.begin(); bIt != bullets.end(); ) {
                if (mIt->checkBulletCollision(bIt->getHitbox())) {
                    mIt->onHitByBullet();
                    bIt = bullets.erase(bIt);
                }
                else {
                    ++bIt;
                }
            }
        }

        // --- Remove dead monsters ---
        monsters.erase(
            std::remove_if(monsters.begin(), monsters.end(), [](const Monster& m) { return m.isDead(); }),
            monsters.end()
        );

        // --- Fire bullets toward mouse cursor ---
        float fireInterval = 1.0f / (baseFireRate + fireRateModifier);
        if (fireClock.getElapsedTime().asSeconds() >= fireInterval) {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mouseWorld = window.mapPixelToCoords(mousePixel);

            // ขยับจุดกำเนิดกระสุนออกจาก player
            sf::Vector2f dir = mouseWorld - playerPosition;
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (len != 0) dir /= len;
            sf::Vector2f bulletStart = playerPosition + dir * 40.f;

            // เลือก texture ตาม bulletType
            const sf::Texture* currentBulletTexture = nullptr;
            if (bulletType == 1) currentBulletTexture = &bulletTextureBlue;
            else if (bulletType == 2) currentBulletTexture = &bulletTextureAmethyst;
            else if (bulletType == 3) currentBulletTexture = &bulletTextureRed;

            bullets.emplace_back(
                *currentBulletTexture,
                bulletStart,
                mouseWorld,
                bulletSpeed,
                baseDamage,
                damageModifier
            );
            fireClock.restart();
        }

        // --- Update and draw bullets ---
        static sf::Clock bulletAnimClock;
        float dtBullet = bulletAnimClock.restart().asSeconds();
        for (auto it = bullets.begin(); it != bullets.end(); ) {
            it->update(dtBullet);
            if (!it->isAlive())
                it = bullets.erase(it);
            else
                ++it;
        }
        for (const auto& b : bullets)
            b.draw(window);

        // --- Draw monsters ---
        for (const auto& m : monsters)
            m.draw(window);

        // --- Player highlight on hit ---
        if (playerHit) {
            playerHighlightTimer = 0.2f;
        }
        if (playerHighlightTimer > 0.f) {
            playerSprite.setColor(sf::Color(255, 80, 80));
            playerHighlightTimer -= dt;
        }
        else {
            playerSprite.setColor(sf::Color::White);
        }

        // Center the view on the player
        sf::View view = window.getView();
        view.setCenter(playerPosition);
        window.setView(view);
        window.draw(playerSprite);

        // --- Draw custom cursor ---
        int cursorIndex = bulletType - 1;
        cursorSprite.setTexture(cursorTextures[cursorIndex], true);
        cursorSprite.setOrigin({ static_cast<float>(cursorTextures[cursorIndex].getSize().x) / 2.f, static_cast<float>(cursorTextures[cursorIndex].getSize().y) / 2.f });

        sf::Vector2i mousePixel{ sf::Mouse::getPosition(window) };
        sf::Vector2f mouseWorld{ window.mapPixelToCoords(mousePixel) };
        cursorSprite.setPosition(mouseWorld);
        window.draw(cursorSprite);

        window.display();
    }
}
