#ifndef PARALLAXBACKGROUND_HPP
#define PARALLAXBACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class ParallaxBackground {
public:
    ParallaxBackground(const string& textureFile, float speed, int y, float scaleX, float scaleY);

    void update(float deltaTime);
    void draw(RenderWindow& window);

private:
    Texture m_texture;
    Sprite m_sprite1;
    Sprite m_sprite2;
    float m_speed;
};

#endif
