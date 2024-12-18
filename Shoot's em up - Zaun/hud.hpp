#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class HUD {
private:
    sf::Sprite spriteHealth;
    sf::Texture textureHealth;
    int maxLife;
    int currentLife;
    int numberOfStates;

    sf::Sprite marcusSpriteHealth;
    sf::Texture marcusTextureHealth;
    int marcusMaxLife;
    int marcusCurrentLife;
    int marcusNumberOfStates;

public:
    HUD(int x, int y, int maxLife);
    ~HUD();

    void updateLife(int newLife);

    void draw(sf::RenderWindow& window);

    void updatePosition(int x, int y);
};

class SCORE {
private:
    sf::Font font;
    sf::Text scoreText;

public:
    SCORE();
    ~SCORE();

    void updateScore(int score);

    void drawScore(sf::RenderWindow& window);
};