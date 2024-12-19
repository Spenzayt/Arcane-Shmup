#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

class Buff {
protected:
    sf::Texture texture;

public:
    sf::Sprite sprite;
    sf::Vector2f position;
    bool activated;
    std::chrono::steady_clock::time_point startTime;
    float speed = 10.f;

public:
    Buff(const sf::Vector2f& spawnPosition, const std::string& textureFile);
    virtual ~Buff() {}

    void setPosition(const sf::Vector2f& newPosition);
    void draw(sf::RenderWindow& window);
    bool touchByThePlayer(const sf::Sprite& playerSprite);
    bool isActivated() const;
    void activate();
    void deactivate();
    std::chrono::steady_clock::time_point getStartTime() const { return startTime; }
    void update();
};

class BlueBuff : public Buff {
public:
    BlueBuff(const sf::Vector2f& spawnPosition);
};

class RedBuff : public Buff {
public:
    RedBuff(const sf::Vector2f& spawnPosition);
};
