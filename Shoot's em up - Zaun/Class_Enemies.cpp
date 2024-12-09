#include "Class_Enemies.hpp"

Enemies::Enemies() {}

Enemies::Enemies(std::string n, int CX, int CY, int h) : e_name(n), e_coordX(CX), e_coordY(CY), e_health(h) {}

int Enemies::losePV(int damage) {
	e_health -= damage;
	if (e_health <= 0) {
		e_health = 0;
		e_isAlive = false;
	}
	return e_health;
}
int Enemies::getHealth() {
	return e_health;
}
int Enemies::getCoordX() {
	return e_coordX;
}
int Enemies::setCoordX(int X) {
	e_coordX += X;
	return e_coordX;
}
int Enemies::getCoordY() {
	return e_coordY;
}
int Enemies::setCoordY(int Y) {
	e_coordY += Y;
	return e_coordY;
}
std::string Enemies::getName() {
	return e_name;
}
bool Enemies::getAlive() {
	return e_isAlive;
}
int Enemies::heal() {
	e_health++;
	return e_health;
}
int Enemies::setHealth(int pv) {
	e_health = pv;
	return e_health;
}
int Enemies::HealthReset(int pv) {
	e_health = pv;
	return e_health;
}
bool Enemies::LifeReset() {
	e_isAlive = true;
	return e_isAlive;
}