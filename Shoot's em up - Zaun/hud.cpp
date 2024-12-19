#include "HUD.hpp"

HUD::HUD(int x, int y, int maxLife) : maxLife(maxLife), currentLife(maxLife), numberOfStates(4)
{
    if (!textureHealth.loadFromFile("assets/UI/LifeBar.png")) {
        std::cerr << "Error loading Texture!" << std::endl;
    }

    spriteHealth.setTexture(textureHealth);
    spriteHealth.setPosition(x,y);
    spriteHealth.setScale(2, 2);

    sf::Vector2u textureSize = textureHealth.getSize();
    spriteHealth.setTextureRect(sf::IntRect(0, 0, textureSize.x / numberOfStates, textureSize.y));
}

HUD::~HUD() {}

void HUD::updateLife(int newLife) {
    sf::Vector2u textureSize = textureHealth.getSize();

    if (newLife == 3) {
        spriteHealth.setTextureRect(sf::IntRect(0, 0, textureSize.x / numberOfStates, textureSize.y));
    }
    else if (newLife == 2) {
        spriteHealth.setTextureRect(sf::IntRect(83, 0, textureSize.x / numberOfStates, textureSize.y));
    }
    if (newLife == 1) {
        spriteHealth.setTextureRect(sf::IntRect(166, 0, textureSize.x / numberOfStates, textureSize.y));
    }
    else if (newLife == 0) {
        spriteHealth.setTextureRect(sf::IntRect(166+83, 0, textureSize.x / numberOfStates, textureSize.y));
    }
}

void HUD::updatePosition(int x, int y) {
    spriteHealth.setPosition(x, y);
}

void HUD::draw(sf::RenderWindow& window) {
    window.draw(spriteHealth);
}

////////////////

SCORE::SCORE() {
    if (!font.loadFromFile("assets/Arcane Nine.otf")) {
        std::cerr << "Error loading Font!" << std::endl;
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(48);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20, 10);
    scoreText.setString("Score : 0");

}

SCORE::~SCORE() {}

void SCORE::updateScore(int score) {
    scoreText.setString("Score : " + std::to_string(score));
}

void SCORE::drawScore(sf::RenderWindow& window) {
    window.draw(scoreText);
}
