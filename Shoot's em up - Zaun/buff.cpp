#include "buff.hpp"

Buff::Buff() {}

Buff::~Buff() {}

//////////////////////////

Buff buff;

void BlueBuff::initBlueBuff() {
	blue_buff_texture.setSmooth(true);
	blue_buff_sprite.setTexture(blue_buff_texture);
	blue_buff_sprite.setPosition(0,0);
}

void BlueBuff::setPosition(const sf::Vector2f& newPosition) {

}

void BlueBuff::draw(sf::RenderWindow& window) {
	window.draw(blue_buff_sprite);
}