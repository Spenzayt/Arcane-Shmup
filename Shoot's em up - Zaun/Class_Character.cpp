#include "Class_Character.hpp"

Character::Character() {}

Character::Character(std::string n, int CX, int CY, int h) : c_name(n), c_coordX(CX), c_coordY(CY), c_health(h) {}

int Character::losePV(int damage) {
	c_health -= damage;
	if (c_health <= 0) {
		c_health = 0;
		c_isAlive = false;
	}
	return c_health;
}
int Character::getHealth() {
	return c_health;
}
int Character::getCoordX() {
	return c_coordX;
}
int Character::setCoordX(int X) {
	c_coordX += X;
	return c_coordX;
}
int Character::getCoordY() {
	return c_coordY;
}
int Character::setCoordY(int Y) {
	c_coordY += Y;
	return c_coordY;
}
std::string Character::getName() {
	return c_name;
}
bool Character::getAlive() {
	return c_isAlive;
}
int Character::heal() {
	c_health++;
	return c_health;
}
int Character::setHealth(int pv) {
	c_health = pv;
	return c_health;
}
int Character::HealthReset(int pv) {
	c_health = pv;
	return c_health;
}
bool Character::LifeReset() {
	c_isAlive = true;
	return c_isAlive;
}