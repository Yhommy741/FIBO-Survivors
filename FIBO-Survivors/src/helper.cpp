#include "Helper.h"

sf::Vector2f randomMonsterSpawn(const sf::View& view, float margin) {
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
