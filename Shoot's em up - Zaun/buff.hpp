#include <SFML/Graphics.hpp>
#include <iostream>

class Buff {
private:
    sf::Texture buff_texture;
    sf::Sprite buff_sprite;
    sf::Vector2f buff_position;

public:
    Buff();
    
    ~Buff();
};

class BlueBuff : public Buff {
private:
    sf::Texture blue_buff_texture;
    sf::Sprite blue_buff_sprite;
    sf::Vector2f blue_buff_position;

public:
	BlueBuff();

	~BlueBuff();

    void initBlueBuff();

    void setPosition(const sf::Vector2f& newPosition);

    void draw(sf::RenderWindow& window);
};

BlueBuff::BlueBuff()
{
}

BlueBuff::~BlueBuff()
{
}