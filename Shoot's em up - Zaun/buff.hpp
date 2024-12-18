#include <SFML/Graphics.hpp>
#include <iostream>

class Buff {
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;

public:
    Buff( const sf::Vector2f& spawnPosition);

    void setPosition(const sf::Vector2f& newPosition);

    void draw(sf::RenderWindow& window);

    bool touchByThePlayer(const sf::Sprite& playerSprite);
};

class BlueBuff : public Buff {
public:
    BlueBuff(const sf::Vector2f& spawnPosition);
    void initBlueBuff();

    bool BlueBuffActivated = false;
};

class RedBuff : public Buff {
public:
    RedBuff(const sf::Vector2f& spawnPosition);
    void initRedBuff();

    bool RedBuffActivated = false;
};
