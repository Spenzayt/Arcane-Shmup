#include "buff.hpp"

Buff::Buff(const sf::Vector2f& spawnPosition) : position(spawnPosition) {
    sprite.setPosition(position);
}

void Buff::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
    sprite.setPosition(position);
}

void Buff::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Buff::touchByThePlayer(const sf::Sprite& playerSprite) {
    return sprite.getGlobalBounds().intersects(playerSprite.getGlobalBounds());
}

////////////////////////

BlueBuff::BlueBuff(const sf::Vector2f& spawnPosition) : Buff(spawnPosition) {
    initBlueBuff();
}

void BlueBuff::initBlueBuff() {
    if (!texture.loadFromFile("assets/UI/BlueBuff.png")) {
        std::cerr << "Error loading blue buff texture!" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
}

////////////////////////

RedBuff::RedBuff(const sf::Vector2f& spawnPosition) : Buff(spawnPosition) {
    initRedBuff();
}

void RedBuff::initRedBuff() {
    if (!texture.loadFromFile("assets/UI/RedBuff.png")) {
        std::cerr << "Error loading red buff texture!" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
}