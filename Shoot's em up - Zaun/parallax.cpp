#include "Parallax.hpp"
#include <iostream>

using namespace std;
using namespace sf;

ParallaxBackground::ParallaxBackground(const string& textureFile, float speed, int y, float scaleX, float scaleY) : m_speed(speed) {
    if (!m_texture.loadFromFile(textureFile)) {
        cerr << "Erreur de chargement de la texture! Utilisation d'une texture par défaut." << endl;
    }

    m_sprite1.setTexture(m_texture);
    m_sprite2.setTexture(m_texture);

    m_sprite1.setPosition(0, y);
    m_sprite2.setPosition(m_texture.getSize().x * scaleX, y);

    m_sprite1.setScale(scaleX, scaleY);
    m_sprite2.setScale(scaleX, scaleY);
}

void ParallaxBackground::update(float deltaTime) {
    float scaledWidth = m_texture.getSize().x * m_sprite1.getScale().x;

    m_sprite1.move(-m_speed * deltaTime, 0);
    m_sprite2.move(-m_speed * deltaTime, 0);

    if (m_sprite1.getPosition().x + scaledWidth < 0) {
        m_sprite1.setPosition(m_sprite2.getPosition().x + scaledWidth, m_sprite1.getPosition().y);
    }

    if (m_sprite2.getPosition().x + scaledWidth < 0) {
        m_sprite2.setPosition(m_sprite1.getPosition().x + scaledWidth, m_sprite2.getPosition().y);
    }
}

void ParallaxBackground::draw(RenderWindow& window) {
    window.draw(m_sprite1);
    window.draw(m_sprite2);
}