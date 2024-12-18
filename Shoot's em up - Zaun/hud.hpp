#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class HUD {
private:
    sf::Sprite spriteHealth;
    sf::Texture textureHealth;
    int maxLife;
    int currentLife;
    int numberOfStates;

public:
    HUD(int x, int y, int maxLife);
    ~HUD();

    void updateLife(int newLife);

    void draw(sf::RenderWindow& window);

    void updatePosition(int x, int y);
};

#endif
