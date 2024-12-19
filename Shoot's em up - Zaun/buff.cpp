#include "buff.hpp"

/*Buff::Buff(const sf::Vector2f& spawnPosition) : position(spawnPosition) {
    sprite.setPosition(position);
}

void Buff::setPosition(sf::Vector2f& newPosition) {
    sprite.setPosition(newPosition);
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
    BlueBuffActivated = false;
    if (!texture.loadFromFile("assets/UI/BlueBuff.png")) {
        std::cerr << "Error loading blue buff texture!" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setPosition(1000, 1000);
}

////////////////////////

RedBuff::RedBuff(const sf::Vector2f& spawnPosition) : Buff(spawnPosition) {
    initRedBuff();
}

void RedBuff::initRedBuff() {
    RedBuffActivated = false;
    if (!texture.loadFromFile("assets/UI/RedBuff.png")) {
        std::cerr << "Error loading red buff texture!" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setPosition(1000, 500);
}*/