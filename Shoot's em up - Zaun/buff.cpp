#include "buff.hpp"

Buff::Buff(const sf::Vector2f& spawnPosition, const std::string& textureFile) : position(spawnPosition), activated(false) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture from " << textureFile << "!" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Buff::setPosition(const sf::Vector2f& newPosition) {
    sprite.setPosition(newPosition);
}

void Buff::update() {
    position.x -= speed;
    sprite.setPosition(position);
}

void Buff::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Buff::touchByThePlayer(const sf::Sprite& playerSprite) {
    return sprite.getGlobalBounds().intersects(playerSprite.getGlobalBounds());
}

bool Buff::isActivated() const {
    return activated;
}

void Buff::activate() {
    activated = true;
    startTime = std::chrono::steady_clock::now();
}

void Buff::deactivate() {
    activated = false;
}

////////////////////////

BlueBuff::BlueBuff(const sf::Vector2f& spawnPosition) : Buff(spawnPosition, "assets/UI/BlueBuff.png") {}

////////////////////////

RedBuff::RedBuff(const sf::Vector2f& spawnPosition) : Buff(spawnPosition, "assets/UI/RedBuff.png") {}
