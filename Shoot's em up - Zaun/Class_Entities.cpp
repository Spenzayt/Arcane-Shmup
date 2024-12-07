#include "Class_Entities.hpp"

Entities::Entities(bool A) : E_health(), E_coordX(), E_coordY(), E_isAlive(A) {


}

int Entities::losePV(int damage) {
	E_health -= damage;
	if (E_health <= 0) {
		E_health = 0;
		E_isAlive = false;
	}
	return E_health;
}
int Entities::getHealth() {
	return E_health;
}
int Entities::getCoordX() {
	return E_coordX;
}
int Entities::setCoordX(int X) {
	E_coordX += X;
	return E_coordX;
}
int Entities::getCoordY() {
	return E_coordY;
}
int Entities::setCoordY(int Y) {
	E_coordY += Y;
	return E_coordY;
}
std::string Entities::getName() {
	return E_name;
}
bool Entities::getAlive() {
	return E_isAlive;
}
int Entities::heal() {
	E_health += 30;
	return E_health;
}
int Entities::setHealth(int pv) {
	E_health = pv;
	return E_health;
}
int Entities::HealthReset(int pv) {
	E_health = pv;
	return E_health;
}
bool Entities::LifeReset() {
	E_isAlive = true;
	return E_isAlive;
}