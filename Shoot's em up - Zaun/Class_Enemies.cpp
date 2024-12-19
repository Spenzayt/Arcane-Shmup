#include "Class_Enemies.hpp"

Enemies::Enemies() {}
Enemies::Enemies(int CX, int CY, bool A) {}
Enemies::~Enemies() {}

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
int Enemies::setHealth(int newHealth) {
	e_health = newHealth;
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
bool Enemies::getAlive() {
	return e_isAlive;
}

Enemies Enemies_Class;

Marcus::Marcus() : Enemies(1600, 800, true) {}

Marcus::~Marcus() {}

void Marcus::marcusInitAnimations() {
	/////////////////
	if (!marcus_Auto_Attack_texture.loadFromFile("assets\\characters\\marcus\\marcusOnBoard.png")) {
		std::cerr << "Error loading Texture!" << std::endl;
	}
	marcus_Auto_Attack_texture.setSmooth(true);

	marcus_Auto_Attack_sprite.setTexture(marcus_Auto_Attack_texture);
	marcus_Auto_Attack_sprite.setPosition(m_coordX, m_coordY);


	if (!marcus_TransSecondPhase_texture.loadFromFile("assets\\characters\\marcus\\marcusTransSecondPhase.png")) {
		std::cerr << "Error loading Texture!" << std::endl;
	}
	marcus_TransSecondPhase_texture.setSmooth(true);

	marcus_TransSecondPhase_sprite.setTexture(marcus_TransSecondPhase_texture);
	marcus_TransSecondPhase_sprite.setPosition(1300, m_coordY);


	if (!marcus_SecondPhase_texture.loadFromFile("assets\\characters\\marcus\\marcusSecodStateShootV3.png")) {
		std::cerr << "Error loading Texture!" << std::endl;
	}
	marcus_SecondPhase_texture.setSmooth(true);

	marcus_SecondPhase_sprite.setTexture(marcus_SecondPhase_texture);
	marcus_SecondPhase_sprite.setPosition(1300, m_coordY);
}

void Marcus::marcusBulletInit() {
	if (!marcus_Bullet_Auto_Attack_texture.loadFromFile("assets\\characters\\marcus\\marcusBullet.png")) {
		std::cerr << "Error loading Texture!" << std::endl;
	}
	marcus_Bullet_Auto_Attack_texture.setSmooth(true);

	marcus_Bullet_Auto_Attack_sprite.setTexture(marcus_Bullet_Auto_Attack_texture);
	marcus_Bullet_Auto_Attack_sprite.setTextureRect(sf::IntRect(32, 0, -32, 32));
	marcus_Bullet_Auto_Attack_sprite.setPosition(marcus_Auto_Attack_sprite.getPosition().x + 128, marcus_Auto_Attack_sprite.getPosition().y - 32);
}

void Marcus::marcusPrintWindow(sf::RenderWindow& window) {
	if (isAttacking && !isAttackingV2 && !transIsIn) {
		if (marcus_anim_Auto_Attack.x * 540 >= marcus_Auto_Attack_texture.getSize().x)
			marcus_anim_Auto_Attack.x = 0;

		marcus_Auto_Attack_sprite.setTextureRect(sf::IntRect(marcus_anim_Auto_Attack.x * 540, 0, 540, 512));
		window.draw(marcus_Auto_Attack_sprite);
	}

	if (transIsIn && !isAttacking && !isAttackingV2) {
		if (marcus_anim_TransSecondPhase.x * 640 >= marcus_TransSecondPhase_texture.getSize().x)
			marcus_anim_TransSecondPhase.x = 0;

		marcus_TransSecondPhase_sprite.setTextureRect(sf::IntRect(marcus_anim_TransSecondPhase.x * 640, 0, 640, 512));
		window.draw(marcus_TransSecondPhase_sprite);
	}

	if (isAttackingV2 && !transIsIn && !isAttacking) {
		if (marcus_anim_SecondPhase.x * 640 >= marcus_SecondPhase_texture.getSize().x)
			marcus_anim_SecondPhase.x = 0;

		marcus_SecondPhase_sprite.setTextureRect(sf::IntRect(marcus_anim_SecondPhase.x * 640, 0, 640, 512));
		window.draw(marcus_SecondPhase_sprite);
	}
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
int Marcus::setHealth(int newHealth) {
	m_health = newHealth;
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
bool Marcus::getAlive() {
	return m_isAlive;
}


Soldier::Soldier() : Enemies(1600, 600, true) {}
Soldier::Soldier(const sf::Vector2f& positionSoldier, sf::Texture& soldierTexture){
		attackSpeed = 135;
		bulletSpeed = 0.8f;
		soldier_walk_texture.setSmooth(true);
		soldier_walk_sprite.setTexture(soldierTexture);
		soldier_walk_sprite.setTextureRect(sf::IntRect(200, 0, -200, 157));
		soldier_walk_sprite.setPosition(positionSoldier);
}
Soldier::~Soldier() {}

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

void Soldier::soldierInitAnimations() {
	if (!soldier_walk_texture.loadFromFile("assets\\characters\\Soldier\\attack_200.png")) {
		std::cerr << "Error loading Texture!" << std::endl;
	}
}

void Soldier::createSoldiers(int little) {
	for (int i = 0; i < little; i++) {
		soldiers_vector.emplace_back(sf::Vector2f(rand() % 2000 + 2300, rand() % 400 + 500), soldier_walk_texture);
	}
}

void Soldier::deleteSoldiers() {
	soldiers_vector.clear();
}

void Soldier::bulletCreation() {
	for (auto& soldier : soldiers_vector) {
		soldier.SoldierBullets.push_back(sf::CircleShape());
		soldier.SoldierBullets.back().setTexture(&soldier_Bullet_Auto_Attack_texture);
		soldier.SoldierBullets.back().setTextureRect(sf::IntRect(32, 0, -32, 16));
		soldier.SoldierBullets.back().setRadius(10);
		soldier.SoldierBullets.back().setPosition(soldier.soldier_walk_sprite.getPosition().x, soldier.soldier_walk_sprite.getPosition().y + 80);
	}
}

void Soldier::soldierPrintWindow(sf::RenderWindow& window) {
	for (auto& soldier : soldiers_vector) {
		window.draw(soldier.soldier_walk_sprite);
	}
}

void Soldier::soldierBulletInit() {
	if (!soldier_Bullet_Auto_Attack_texture.loadFromFile("assets\\characters\\Soldier\\soldierBullets.png")) {
		std::cerr << "Error loading Texture!" << std::endl;
	}
	soldier_Bullet_Auto_Attack_texture.setSmooth(true);
	/*soldier_Bullet_Auto_Attack_sprite.setTextureRect(sf::IntRect(32, 0, -32, 16));
	soldier_Bullet_Auto_Attack_sprite.setTexture(soldier_Bullet_Auto_Attack_texture);*/
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
bool Soldier::getAlive() {
	return s_isAlive;
}

///////////////////////////////

MediumSoldier::MediumSoldier() : Enemies(1600, 700, true) {}

MediumSoldier::MediumSoldier(const sf::Vector2f& positionSoldier, sf::Texture& soldierTexture) {
	attackSpeed = 300;
	bulletSpeed = 0.8f;
	medium_soldier_walk_texture.setSmooth(true);
	medium_soldier_walk_sprite.setTexture(soldierTexture);
	medium_soldier_walk_sprite.setTextureRect(sf::IntRect(200, 0, -200, 157));
	medium_soldier_walk_sprite.setPosition(positionSoldier);
}

MediumSoldier::~MediumSoldier() {}

void MediumSoldier::mediumSoldierInitAnimations() {
	attackSpeed = 300;
	bulletSpeed = 0.5f;
	if (!medium_soldier_walk_texture.loadFromFile("assets\\characters\\Soldier\\attack_200_medium.png")) {
		std::cerr << "Error loading Texture!" << std::endl;
	}
	medium_soldier_walk_texture.setSmooth(true);
	medium_soldier_walk_sprite .setTexture(medium_soldier_walk_texture);
	medium_soldier_walk_sprite.setTextureRect(sf::IntRect(200, 0, 200, 200));
	medium_soldier_walk_sprite.setPosition(ms_coordX, ms_coordY);
}

void MediumSoldier::mediumSoldierDontExitFromScreen() {
	if (medium_soldier_walk_sprite.getPosition().x <= 0) medium_soldier_walk_sprite.setPosition(sf::Vector2f(0, medium_soldier_walk_sprite.getPosition().y));
	if (medium_soldier_walk_sprite.getPosition().y <= 525) medium_soldier_walk_sprite.setPosition(sf::Vector2f(medium_soldier_walk_sprite.getPosition().x, 525));
	if (medium_soldier_walk_sprite.getPosition().x >= 1920 - medium_soldier_walk_sprite.getGlobalBounds().width) medium_soldier_walk_sprite.setPosition(sf::Vector2f(1920 - medium_soldier_walk_sprite.getGlobalBounds().width, medium_soldier_walk_sprite.getPosition().y));
	if (medium_soldier_walk_sprite.getPosition().y >= 1070 - medium_soldier_walk_sprite.getGlobalBounds().height) medium_soldier_walk_sprite.setPosition(sf::Vector2f(medium_soldier_walk_sprite.getPosition().x, 1070 - medium_soldier_walk_sprite.getGlobalBounds().height));

	if (medium_soldier_walk_sprite.getPosition().x <= 0) medium_soldier_walk_sprite.setPosition(sf::Vector2f(0, medium_soldier_walk_sprite.getPosition().y));
	if (medium_soldier_walk_sprite.getPosition().y <= 525) medium_soldier_walk_sprite.setPosition(sf::Vector2f(medium_soldier_walk_sprite.getPosition().x, 525));
	if (medium_soldier_walk_sprite.getPosition().x >= 1920 - medium_soldier_walk_sprite.getGlobalBounds().width) medium_soldier_walk_sprite.setPosition(sf::Vector2f(1920 - medium_soldier_walk_sprite.getGlobalBounds().width, medium_soldier_walk_sprite.getPosition().y));
	if (medium_soldier_walk_sprite.getPosition().y >= 1070 - medium_soldier_walk_sprite.getGlobalBounds().height) medium_soldier_walk_sprite.setPosition(sf::Vector2f(medium_soldier_walk_sprite.getPosition().x, 1070 - medium_soldier_walk_sprite.getGlobalBounds().height));
}

void MediumSoldier::mediumSoldierBulletInit() {
	if (!medium_soldier_Bullet_Auto_Attack_texture.loadFromFile("assets\\characters\\Soldier\\mediumSoldierBullets.png")) {
		std::cerr << "Error loading Texture!" << std::endl;
	}
	medium_soldier_Bullet_Auto_Attack_texture.setSmooth(true);

	/*medium_soldier_Bullet_Auto_Attack_sprite.setTexture(medium_soldier_Bullet_Auto_Attack_texture);
	medium_soldier_Bullet_Auto_Attack_sprite.setTextureRect(sf::IntRect(32, 0, -32, 16));
	medium_soldier_Bullet_Auto_Attack_sprite.setPosition(medium_soldier_walk_sprite.getPosition().x + 5, medium_soldier_walk_sprite.getPosition().y + 80);*/
}

void MediumSoldier::bulletCreation() {
	for (auto& mediumSoldier : mediumSoldiers_vector) {
		for (int i = 0; i < 3; i++) {
			mediumSoldier.MediumSoldierBullets.push_back(sf::CircleShape());
			mediumSoldier.MediumSoldierBullets.back().setTexture(&medium_soldier_Bullet_Auto_Attack_texture);
			mediumSoldier.MediumSoldierBullets.back().setTextureRect(sf::IntRect(32, 0, -32, 16));
			mediumSoldier.MediumSoldierBullets.back().setRadius(10);
			mediumSoldier.MediumSoldierBullets.back().setPosition(mediumSoldier.medium_soldier_walk_sprite.getPosition().x, mediumSoldier.medium_soldier_walk_sprite.getPosition().y + (60 + i * 20));
		}
	}
}
void MediumSoldier::mediumSoldierPrintWindow(sf::RenderWindow& window) {
	for (auto& mediumSoldier : mediumSoldiers_vector) {
		window.draw(mediumSoldier.medium_soldier_walk_sprite);
	}
}

void MediumSoldier::createSoldiers(int little) {
	for (int i = 0; i < little; i++) {
		mediumSoldiers_vector.emplace_back(sf::Vector2f(rand() % 2000 + 2300, rand() % 350 + 550), medium_soldier_walk_texture);
	}
}

void MediumSoldier::deleteMediumSoldiers() {
	mediumSoldiers_vector.clear();
}

int MediumSoldier::losePV(int damage) {
	ms_health -= damage;
	if (ms_health <= 0) {
		ms_health = 0;
		ms_isAlive = false;
	}
	return ms_health;
}
int MediumSoldier::getHealth() {
	return ms_health;
}
int MediumSoldier::getCoordX() {
	return ms_coordX;
}
int MediumSoldier::setCoordX(int X) {
	ms_coordX += X;
	return ms_coordX;
}
int MediumSoldier::getCoordY() {
	return ms_coordY;
}
int MediumSoldier::setCoordY(int Y) {
	ms_coordY += Y;
	return ms_coordY;
}
bool MediumSoldier::getAlive() {
	return ms_isAlive;
}

////////////////////////

HardSoldier::HardSoldier() : Enemies(1600, 900, true) {}

HardSoldier::HardSoldier(const sf::Vector2f& positionSoldier, sf::Texture& soldierTexture) {
	attackSpeed = 90;
	bulletSpeed = 1.5f;
	hard_soldier_walk_texture.setSmooth(true);
	hard_soldier_walk_sprite.setTexture(soldierTexture);
	hard_soldier_walk_sprite.setTextureRect(sf::IntRect(200, 0, -200, 157));
	hard_soldier_walk_sprite.setPosition(positionSoldier);
}

HardSoldier::~HardSoldier() {}

void HardSoldier::hardSoldierInitAnimations() {
	if (!hard_soldier_walk_texture.loadFromFile("assets\\characters\\Soldier\\attack_200_hard.png")) {
		std::cerr << "Error loading Texture!" << std::endl;
	}
	hard_soldier_walk_texture.setSmooth(true);
	hard_soldier_walk_sprite.setTexture(hard_soldier_walk_texture);
	hard_soldier_walk_sprite.setTextureRect(sf::IntRect(200, 0, 200, 200));
	hard_soldier_walk_sprite.setPosition(hs_coordX, hs_coordY);
}

void HardSoldier::hardSoldierDontExitFromScreen() {
	if (hard_soldier_walk_sprite.getPosition().x <= 0) hard_soldier_walk_sprite.setPosition(sf::Vector2f(0, hard_soldier_walk_sprite.getPosition().y));
	if (hard_soldier_walk_sprite.getPosition().y <= 525) hard_soldier_walk_sprite.setPosition(sf::Vector2f(hard_soldier_walk_sprite.getPosition().x, 525));
	if (hard_soldier_walk_sprite.getPosition().x >= 1920 - hard_soldier_walk_sprite.getGlobalBounds().width) hard_soldier_walk_sprite.setPosition(sf::Vector2f(1920 - hard_soldier_walk_sprite.getGlobalBounds().width, hard_soldier_walk_sprite.getPosition().y));
	if (hard_soldier_walk_sprite.getPosition().y >= 1070 - hard_soldier_walk_sprite.getGlobalBounds().height) hard_soldier_walk_sprite.setPosition(sf::Vector2f(hard_soldier_walk_sprite.getPosition().x, 1070 - hard_soldier_walk_sprite.getGlobalBounds().height));

	if (hard_soldier_walk_sprite.getPosition().x <= 0) hard_soldier_walk_sprite.setPosition(sf::Vector2f(0, hard_soldier_walk_sprite.getPosition().y));
	if (hard_soldier_walk_sprite.getPosition().y <= 525) hard_soldier_walk_sprite.setPosition(sf::Vector2f(hard_soldier_walk_sprite.getPosition().x, 525));
	if (hard_soldier_walk_sprite.getPosition().x >= 1920 - hard_soldier_walk_sprite.getGlobalBounds().width) hard_soldier_walk_sprite.setPosition(sf::Vector2f(1920 - hard_soldier_walk_sprite.getGlobalBounds().width, hard_soldier_walk_sprite.getPosition().y));
	if (hard_soldier_walk_sprite.getPosition().y >= 1070 - hard_soldier_walk_sprite.getGlobalBounds().height) hard_soldier_walk_sprite.setPosition(sf::Vector2f(hard_soldier_walk_sprite.getPosition().x, 1070 - hard_soldier_walk_sprite.getGlobalBounds().height));
}

void HardSoldier::hardSoldierBulletInit() {
	if (!hard_soldier_Bullet_Auto_Attack_texture.loadFromFile("assets\\characters\\Soldier\\soldierBulletshard.png")) {
		std::cerr << "Error loading Texture!" << std::endl;
	}
	hard_soldier_Bullet_Auto_Attack_texture.setSmooth(true);

	/*hard_soldier_Bullet_Auto_Attack_sprite.setTexture(hard_soldier_Bullet_Auto_Attack_texture);
	hard_soldier_Bullet_Auto_Attack_sprite.setTextureRect(sf::IntRect(32, 0, -32, 16));
	hard_soldier_Bullet_Auto_Attack_sprite.setPosition(hard_soldier_walk_sprite.getPosition().x + 5, hard_soldier_walk_sprite.getPosition().y + 80);*/
}

void HardSoldier::hardSoldierPrintWindow(sf::RenderWindow& window) {
	for (auto& hardSoldier : hardSoldiers_vector) {
		window.draw(hardSoldier.hard_soldier_walk_sprite);
	}
}


void HardSoldier::createSoldiers(int little) {
	for (int i = 0; i < little; i++) {
		hardSoldiers_vector.emplace_back(sf::Vector2f(rand() % 2000 + 2300, rand() % 400 + 500), hard_soldier_walk_texture);
	}
}

void HardSoldier::deleteHardSoldiers() {
	hardSoldiers_vector.clear();
}

void HardSoldier::bulletCreation() {
	for (auto& hardSoldier : hardSoldiers_vector) {
		hardSoldier.HardSoldierBullets.push_back(sf::CircleShape());
		hardSoldier.HardSoldierBullets.back().setTexture(&hard_soldier_Bullet_Auto_Attack_texture);
		hardSoldier.HardSoldierBullets.back().setTextureRect(sf::IntRect(32, 0, -32, 16));		
		hardSoldier.HardSoldierBullets.back().setRadius(10);
		hardSoldier.HardSoldierBullets.back().setPosition(hardSoldier.hard_soldier_walk_sprite.getPosition().x, hardSoldier.hard_soldier_walk_sprite.getPosition().y + 80);
	}
}

int HardSoldier::losePV(int damage) {
	hs_health -= damage;
	if (hs_health <= 0) {
		hs_health = 0;
		hs_isAlive = false;
	}
	return hs_health;
}
int HardSoldier::getHealth() {
	return hs_health;
}
int HardSoldier::getCoordX() {
	return hs_coordX;
}
int HardSoldier::setCoordX(int X) {
	hs_coordX += X;
	return hs_coordX;
}
int HardSoldier::getCoordY() {
	return hs_coordY;
}
int HardSoldier::setCoordY(int Y) {
	hs_coordY += Y;
	return hs_coordY;
}
bool HardSoldier::getAlive() {
	return hs_isAlive;
}

