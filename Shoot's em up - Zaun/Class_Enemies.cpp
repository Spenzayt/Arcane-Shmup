#include "Class_Enemies.hpp"

Enemies::Enemies() {}

Enemies::Enemies(std::string n, int CX, int CY, int h, bool A) : e_name(n), e_coordX(CX), e_coordY(CY), e_health(h), e_isAlive(A) {}

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


Enemies Enemies_Class;

Marcus::Marcus() : Enemies("Marcus", 1600, 800, 100, true) {}

Marcus::~Marcus() {}

void Marcus::marcusInitAnimations() {
	if (!marcus_walk_texture.loadFromFile("assets\\characters\\marcus\\marcus no move.png")) {
		std::cout << "marcus est pas chargé bro" << std::endl << std::endl; // Erreur si le fichier est introuvable
	}
	marcus_walk_texture.setSmooth(true);
	marcus_walk_sprite.setTexture(marcus_walk_texture);
	marcus_walk_sprite.setTextureRect(sf::IntRect(512, 0, 640, 512));
	marcus_walk_sprite.setPosition(Enemies_Class.getCoordX(), Enemies_Class.getCoordY());

	/////////////////
	/*if (!ekko_Auto_Attack_texture.loadFromFile("assets\\characters\\ekko\\Ekko_Auto_Attack_128V3.png")) {
		std::cout << "ekkoAutoAttack est pas chargé bro" << std::endl << std::endl;
	}
	ekko_Auto_Attack_texture.setSmooth(true);

	ekko_Auto_Attack_sprite.setTexture(ekko_Auto_Attack_texture);
	ekko_Auto_Attack_sprite.setTextureRect(sf::IntRect(128, 0, 128, 128));
	ekko_Auto_Attack_sprite.setPosition(Char_Class.getCoordX(), Char_Class.getCoordY());*/
}

void Marcus::marcusDontExitFromScreen() {
	if (marcus_walk_sprite.getPosition().x <= 0) marcus_walk_sprite.setPosition(sf::Vector2f(0, marcus_walk_sprite.getPosition().y));
	if (marcus_walk_sprite.getPosition().y <= 525) marcus_walk_sprite.setPosition(sf::Vector2f(marcus_walk_sprite.getPosition().x, 525));
	if (marcus_walk_sprite.getPosition().x >= 1920 - marcus_walk_sprite.getGlobalBounds().width) marcus_walk_sprite.setPosition(sf::Vector2f(1920 - marcus_walk_sprite.getGlobalBounds().width, marcus_walk_sprite.getPosition().y));
	if (marcus_walk_sprite.getPosition().y >= 1070 - marcus_walk_sprite.getGlobalBounds().height) marcus_walk_sprite.setPosition(sf::Vector2f(marcus_walk_sprite.getPosition().x, 1070 - marcus_walk_sprite.getGlobalBounds().height));

	if (marcus_walk_sprite.getPosition().x <= 0) marcus_walk_sprite.setPosition(sf::Vector2f(0, marcus_walk_sprite.getPosition().y));
	if (marcus_walk_sprite.getPosition().y <= 525) marcus_walk_sprite.setPosition(sf::Vector2f(marcus_walk_sprite.getPosition().x, 525));
	if (marcus_walk_sprite.getPosition().x >= 1920 - marcus_walk_sprite.getGlobalBounds().width) marcus_walk_sprite.setPosition(sf::Vector2f(1920 - marcus_walk_sprite.getGlobalBounds().width, marcus_walk_sprite.getPosition().y));
	if (marcus_walk_sprite.getPosition().y >= 1070 - marcus_walk_sprite.getGlobalBounds().height) marcus_walk_sprite.setPosition(sf::Vector2f(marcus_walk_sprite.getPosition().x, 1070 - marcus_walk_sprite.getGlobalBounds().height));
}

void Marcus::marcusBulletInit() {
	/*if (!ekko_Bullet_Auto_Attack_texture.loadFromFile("assets\\characters\\ekko\\AutotAttackEkko.png")) {
		std::cout << "ekkoBulletAutoAttack est pas chargé bro" << std::endl << std::endl;
	}
	ekko_Bullet_Auto_Attack_texture.setSmooth(true);

	ekko_Bullet_Auto_Attack_sprite.setTexture(ekko_Bullet_Auto_Attack_texture);
	ekko_Bullet_Auto_Attack_sprite.setTextureRect(sf::IntRect(32, 0, -32, 32));
	ekko_Bullet_Auto_Attack_sprite.setPosition(marcus_walk_sprite.getPosition().x + 128, marcus_walk_sprite.getPosition().y - 32);*/
}

void Marcus::marcusPrintWindow(sf::RenderWindow& window) {
	if (!marcus_S.marcus_anim_isAttacking) {
		if (marcus_anim.x * 512 >= marcus_walk_texture.getSize().x) // boucle qui permet de revenir a la premiere slide de l'anim
			marcus_anim.x = 0;

		marcus_walk_sprite.setTextureRect(sf::IntRect(marcus_anim_Auto_Attack.x * 512, 0, 640, 512));
		window.draw(marcus_walk_sprite);
		//////////////////////////////
	}

	/*if (ekko_S.ekko_anim_isAttacking) {
		if (ekko_anim_Auto_Attack.x * 128 >= ekko_Auto_Attack_texture.getSize().x)
			ekko_anim_Auto_Attack.x = 0;

		marcus_walk_sprite.setTextureRect(sf::IntRect(ekko_anim_Auto_Attack.x * 128, 0, 128, 128));
		window.draw(marcus_walk_sprite);
	}*/
	//////////////////////////////
}

int Marcus::losePV(int damage) {
	m_health -= damage;
	if (m_health <= 0) {
		m_health = 0;
		m_isAlive = false;
	}
	return m_health;
}
int Marcus::getHealth() {
	return m_health;
}
int Marcus::getCoordX() {
	return m_coordX;
}
int Marcus::setCoordX(int X) {
	m_coordX += X;
	return m_coordX;
}
int Marcus::getCoordY() {
	return m_coordY;
}
int Marcus::setCoordY(int Y) {
	m_coordY += Y;
	return m_coordY;
}
std::string Marcus::getName() {
	return m_name;
}
bool Marcus::getAlive() {
	return m_isAlive;
}
int Marcus::heal() {
	m_health++;
	return m_health;
}



Soldier::Soldier() : Enemies("Soldier", 1600, 600, 1, true) {}

Soldier::~Soldier() {}

void Soldier::soldierInitAnimations() {
	if (!soldier_walk_texture.loadFromFile("assets\\characters\\Soldier\\attack_200.png")) {
		std::cout << "soldier est pas chargé bro" << std::endl << std::endl; // Erreur si le fichier est introuvable
	}
	soldier_walk_texture.setSmooth(true);
	soldier_walk_sprite.setTexture(soldier_walk_texture);
	soldier_walk_sprite.setTextureRect(sf::IntRect(200, 0, 200, 200));
	soldier_walk_sprite.setPosition(1600, 600);

	/////////////////
	/*if (!ekko_Auto_Attack_texture.loadFromFile("assets\\characters\\ekko\\Ekko_Auto_Attack_128V3.png")) {
		std::cout << "ekkoAutoAttack est pas chargé bro" << std::endl << std::endl;
	}
	ekko_Auto_Attack_texture.setSmooth(true);

	ekko_Auto_Attack_sprite.setTexture(ekko_Auto_Attack_texture);
	ekko_Auto_Attack_sprite.setTextureRect(sf::IntRect(128, 0, 128, 128));
	ekko_Auto_Attack_sprite.setPosition(Char_Class.getCoordX(), Char_Class.getCoordY());*/
}

void Soldier::soldierDontExitFromScreen() {
	if (soldier_walk_sprite.getPosition().x <= 0) soldier_walk_sprite.setPosition(sf::Vector2f(0, soldier_walk_sprite.getPosition().y));
	if (soldier_walk_sprite.getPosition().y <= 525) soldier_walk_sprite.setPosition(sf::Vector2f(soldier_walk_sprite.getPosition().x, 525));
	if (soldier_walk_sprite.getPosition().x >= 1920 - soldier_walk_sprite.getGlobalBounds().width) soldier_walk_sprite.setPosition(sf::Vector2f(1920 - soldier_walk_sprite.getGlobalBounds().width, soldier_walk_sprite.getPosition().y));
	if (soldier_walk_sprite.getPosition().y >= 1070 - soldier_walk_sprite.getGlobalBounds().height) soldier_walk_sprite.setPosition(sf::Vector2f(soldier_walk_sprite.getPosition().x, 1070 - soldier_walk_sprite.getGlobalBounds().height));

	if (soldier_walk_sprite.getPosition().x <= 0) soldier_walk_sprite.setPosition(sf::Vector2f(0, soldier_walk_sprite.getPosition().y));
	if (soldier_walk_sprite.getPosition().y <= 525) soldier_walk_sprite.setPosition(sf::Vector2f(soldier_walk_sprite.getPosition().x, 525));
	if (soldier_walk_sprite.getPosition().x >= 1920 - soldier_walk_sprite.getGlobalBounds().width) soldier_walk_sprite.setPosition(sf::Vector2f(1920 - soldier_walk_sprite.getGlobalBounds().width, soldier_walk_sprite.getPosition().y));
	if (soldier_walk_sprite.getPosition().y >= 1070 - soldier_walk_sprite.getGlobalBounds().height) soldier_walk_sprite.setPosition(sf::Vector2f(soldier_walk_sprite.getPosition().x, 1070 - soldier_walk_sprite.getGlobalBounds().height));
}

void Soldier::soldierBulletInit() {
	if (!soldier_Bullet_Auto_Attack_texture.loadFromFile("assets\\characters\\Soldier\\soldierBullets.png")) {
		std::cout << "soldierBullets est pas chargé bro" << std::endl << std::endl;
	}
	soldier_Bullet_Auto_Attack_texture.setSmooth(true);

	soldier_Bullet_Auto_Attack_sprite.setTexture(soldier_Bullet_Auto_Attack_texture);
	soldier_Bullet_Auto_Attack_sprite.setTextureRect(sf::IntRect(32, 0, -32, 16));
	soldier_Bullet_Auto_Attack_sprite.setPosition(soldier_walk_sprite.getPosition().x + 5, soldier_walk_sprite.getPosition().y + 80);
}

void Soldier::soldierPrintWindow(sf::RenderWindow& window) {
	soldier_walk_sprite.setTextureRect(sf::IntRect(soldier_anim.x * 200, 0, -200, 200));
	window.draw(soldier_walk_sprite);

	//////////////////////////////

	/*if (ekko_S.ekko_anim_isAttacking) {
		if (ekko_anim_Auto_Attack.x * 128 >= ekko_Auto_Attack_texture.getSize().x)
			ekko_anim_Auto_Attack.x = 0;

		marcus_walk_sprite.setTextureRect(sf::IntRect(ekko_anim_Auto_Attack.x * 128, 0, 128, 128));
		window.draw(marcus_walk_sprite);
	}*/
	//////////////////////////////
}

int Soldier::losePV(int damage) {
	s_health -= damage;
	if (s_health <= 0) {
		s_health = 0;
		s_isAlive = false;
	}
	return s_health;
}
int Soldier::getHealth() {
	return s_health;
}
int Soldier::getCoordX() {
	return s_coordX;
}
int Soldier::setCoordX(int X) {
	s_coordX += X;
	return s_coordX;
}
int Soldier::getCoordY() {
	return s_coordY;
}
int Soldier::setCoordY(int Y) {
	s_coordY += Y;
	return s_coordY;
}
std::string Soldier::getName() {
	return s_name;
}
bool Soldier::getAlive() {
	return s_isAlive;
}
int Soldier::heal() {
	s_health++;
	return s_health;
}