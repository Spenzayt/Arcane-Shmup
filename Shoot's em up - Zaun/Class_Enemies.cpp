#include "Class_Enemies.hpp"

//Enemies::Enemies(std::string n, int CX, int CY, bool A) : e_name(n), e_coordX(CX), e_coordY(CY), e_isAlive(A) {}

Enemies::Enemies() {}
Enemies::Enemies(std::string n, int CX, int CY, bool A) {}
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

Marcus::Marcus() : Enemies("Marcus", 1600, 800, true) {}

Marcus::~Marcus() {}

void Marcus::marcusInitAnimations() {
	if (!marcus_walk_texture.loadFromFile("assets\\characters\\marcus\\marcus no move.png")) {
		std::cout << "marcus est pas charg� bro" << std::endl << std::endl; // Erreur si le fichier est introuvable
	}
	marcus_walk_texture.setSmooth(true);
	marcus_walk_sprite.setTexture(marcus_walk_texture);
	marcus_walk_sprite.setTextureRect(sf::IntRect(512, 0, 640, 512));
	marcus_walk_sprite.setPosition(Enemies_Class.getCoordX(), Enemies_Class.getCoordY());

	/////////////////
	/*if (!ekko_Auto_Attack_texture.loadFromFile("assets\\characters\\ekko\\Ekko_Auto_Attack_128V3.png")) {
		std::cout << "ekkoAutoAttack est pas charg� bro" << std::endl << std::endl;
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
		std::cout << "ekkoBulletAutoAttack est pas charg� bro" << std::endl << std::endl;
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


Soldier::Soldier() : Enemies("Soldier", 1600, 600, true) {}
Soldier::Soldier(const sf::Vector2f& positionSoldier, sf::Texture& soldierTexture){
		soldier_S.attackSpeed = 135;
		soldier_S.bulletSpeed = 0.8f;
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
		std::cout << "soldier est pas charg� bro" << std::endl << std::endl; // Erreur si le fichier est introuvable
	}
}

void Soldier::createSoldiers(int little) {
	for (int i = 0; i < little; i++) {
		soldiers_vector.emplace_back(sf::Vector2f(rand() % 960 + 800, rand() % 400 + 500), soldier_walk_texture);
		//cout << "crea de soldat x1" << endl << endl;
	}
}

void Soldier::bulletCreation() {
	for (auto& soldier : soldiers_vector) {
		soldier.SoldierBullets.push_back(sf::CircleShape());
		soldier.SoldierBullets.back().setFillColor(sf::Color::Transparent);
		soldier.SoldierBullets.back().setRadius(10);
		soldier.SoldierBullets.back().setPosition(soldier.soldier_walk_sprite.getPosition().x, soldier.soldier_walk_sprite.getPosition().y + 80);
	}
}

void Soldier::otherSoldiersSpawn(sf::RenderWindow& window) {
	for (auto& soldier : soldiers_vector) {
		window.draw(soldier.soldier_walk_sprite);
	}
}

void Soldier::soldierBulletInit() {
	if (!soldier_Bullet_Auto_Attack_texture.loadFromFile("assets\\characters\\Soldier\\soldierBullets.png")) {
		std::cout << "soldierBullets est pas charg� bro" << std::endl << std::endl;
	}
	soldier_Bullet_Auto_Attack_texture.setSmooth(true);
	soldier_Bullet_Auto_Attack_sprite.setTextureRect(sf::IntRect(32, 0, -32, 16));
	soldier_Bullet_Auto_Attack_sprite.setTexture(soldier_Bullet_Auto_Attack_texture);
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

///////////////////////////////

MediumSoldier::MediumSoldier() : Enemies("MediumSoldier", 1600, 700, true) {}

MediumSoldier::~MediumSoldier() {}

void MediumSoldier::mediumSoldierInitAnimations() {
	attackSpeed = 300;
	bulletSpeed = 0.5f;
	if (!medium_soldier_walk_texture.loadFromFile("assets\\characters\\Soldier\\attack_200_medium.png")) {
		std::cout << "soldier est pas charg� bro" << std::endl << std::endl; // Erreur si le fichier est introuvable
	}
	medium_soldier_walk_texture.setSmooth(true);
	medium_soldier_walk_sprite.setTexture(medium_soldier_walk_texture);
	medium_soldier_walk_sprite.setTextureRect(sf::IntRect(200, 0, 200, 200));
	medium_soldier_walk_sprite.setPosition(ms_coordX, ms_coordY);

	/////////////////
	/*if (!ekko_Auto_Attack_texture.loadFromFile("assets\\characters\\ekko\\Ekko_Auto_Attack_128V3.png")) {
		std::cout << "ekkoAutoAttack est pas charg� bro" << std::endl << std::endl;
	}
	ekko_Auto_Attack_texture.setSmooth(true);

	ekko_Auto_Attack_sprite.setTexture(ekko_Auto_Attack_texture);
	ekko_Auto_Attack_sprite.setTextureRect(sf::IntRect(128, 0, 128, 128));
	ekko_Auto_Attack_sprite.setPosition(Char_Class.getCoordX(), Char_Class.getCoordY());*/
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
		std::cout << "soldierBullets est pas charg� bro" << std::endl << std::endl;
	}
	medium_soldier_Bullet_Auto_Attack_texture.setSmooth(true);

	medium_soldier_Bullet_Auto_Attack_sprite.setTexture(medium_soldier_Bullet_Auto_Attack_texture);
	medium_soldier_Bullet_Auto_Attack_sprite.setTextureRect(sf::IntRect(32, 0, -32, 16));
	medium_soldier_Bullet_Auto_Attack_sprite.setPosition(medium_soldier_walk_sprite.getPosition().x + 5, medium_soldier_walk_sprite.getPosition().y + 80);
}

void MediumSoldier::mediumSoldierPrintWindow(sf::RenderWindow& window) {
	medium_soldier_walk_sprite.setTextureRect(sf::IntRect(medium_soldier_anim.x * 200, 0, -200, 200));
	window.draw(medium_soldier_walk_sprite);

	//////////////////////////////

	/*if (ekko_S.ekko_anim_isAttacking) {
		if (ekko_anim_Auto_Attack.x * 128 >= ekko_Auto_Attack_texture.getSize().x)
			ekko_anim_Auto_Attack.x = 0;

		marcus_walk_sprite.setTextureRect(sf::IntRect(ekko_anim_Auto_Attack.x * 128, 0, 128, 128));
		window.draw(marcus_walk_sprite);
	}*/
	//////////////////////////////
}

void MediumSoldier::bulletCreation() {
	for (auto& mediumSoldier : mediumSoldiers_vector) {
		for (int i = 0; i < 3; i++) {
			mediumSoldier.MediumSoldierBullets.push_back(sf::CircleShape());
			mediumSoldier.MediumSoldierBullets.back().setFillColor(sf::Color::Transparent);
			mediumSoldier.MediumSoldierBullets.back().setRadius(10);
			mediumSoldier.MediumSoldierBullets.back().setPosition(mediumSoldier.medium_soldier_walk_sprite.getPosition().x, mediumSoldier.medium_soldier_walk_sprite.getPosition().y + (60 + i * 20));
		}
	}
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
std::string MediumSoldier::getName() {
	return ms_name;
}
bool MediumSoldier::getAlive() {
	return ms_isAlive;
}
int MediumSoldier::heal() {
	ms_health++;
	return ms_health;
}

////////////////////////

HardSoldier::HardSoldier() : Enemies("HardSoldier", 1600, 900, true) {}

HardSoldier::~HardSoldier() {}

void HardSoldier::hardSoldierInitAnimations() {
	attackSpeed = 45;
	bulletSpeed = 1.5f;
	if (!hardSoldier_walk_texture.loadFromFile("assets\\characters\\Soldier\\attack_200.png")) {
		std::cout << "soldier est pas charg� bro" << std::endl << std::endl; // Erreur si le fichier est introuvable
	}
	hardSoldier_walk_texture.setSmooth(true);
	hardSoldier_walk_sprite.setTexture(hardSoldier_walk_texture);
	hardSoldier_walk_sprite.setTextureRect(sf::IntRect(200, 0, 200, 200));
	hardSoldier_walk_sprite.setPosition(hs_coordX, hs_coordY);

	/////////////////
	/*if (!ekko_Auto_Attack_texture.loadFromFile("assets\\characters\\ekko\\Ekko_Auto_Attack_128V3.png")) {
		std::cout << "ekkoAutoAttack est pas charg� bro" << std::endl << std::endl;
	}
	ekko_Auto_Attack_texture.setSmooth(true);

	ekko_Auto_Attack_sprite.setTexture(ekko_Auto_Attack_texture);
	ekko_Auto_Attack_sprite.setTextureRect(sf::IntRect(128, 0, 128, 128));
	ekko_Auto_Attack_sprite.setPosition(Char_Class.getCoordX(), Char_Class.getCoordY());*/
}

void HardSoldier::hardSoldierDontExitFromScreen() {
	if (hardSoldier_walk_sprite.getPosition().x <= 0) hardSoldier_walk_sprite.setPosition(sf::Vector2f(0, hardSoldier_walk_sprite.getPosition().y));
	if (hardSoldier_walk_sprite.getPosition().y <= 525) hardSoldier_walk_sprite.setPosition(sf::Vector2f(hardSoldier_walk_sprite.getPosition().x, 525));
	if (hardSoldier_walk_sprite.getPosition().x >= 1920 - hardSoldier_walk_sprite.getGlobalBounds().width) hardSoldier_walk_sprite.setPosition(sf::Vector2f(1920 - hardSoldier_walk_sprite.getGlobalBounds().width, hardSoldier_walk_sprite.getPosition().y));
	if (hardSoldier_walk_sprite.getPosition().y >= 1070 - hardSoldier_walk_sprite.getGlobalBounds().height) hardSoldier_walk_sprite.setPosition(sf::Vector2f(hardSoldier_walk_sprite.getPosition().x, 1070 - hardSoldier_walk_sprite.getGlobalBounds().height));

	if (hardSoldier_walk_sprite.getPosition().x <= 0) hardSoldier_walk_sprite.setPosition(sf::Vector2f(0, hardSoldier_walk_sprite.getPosition().y));
	if (hardSoldier_walk_sprite.getPosition().y <= 525) hardSoldier_walk_sprite.setPosition(sf::Vector2f(hardSoldier_walk_sprite.getPosition().x, 525));
	if (hardSoldier_walk_sprite.getPosition().x >= 1920 - hardSoldier_walk_sprite.getGlobalBounds().width) hardSoldier_walk_sprite.setPosition(sf::Vector2f(1920 - hardSoldier_walk_sprite.getGlobalBounds().width, hardSoldier_walk_sprite.getPosition().y));
	if (hardSoldier_walk_sprite.getPosition().y >= 1070 - hardSoldier_walk_sprite.getGlobalBounds().height) hardSoldier_walk_sprite.setPosition(sf::Vector2f(hardSoldier_walk_sprite.getPosition().x, 1070 - hardSoldier_walk_sprite.getGlobalBounds().height));
}

void HardSoldier::hardSoldierBulletInit() {
	if (!hardSoldier_Bullet_Auto_Attack_texture.loadFromFile("assets\\characters\\Soldier\\soldierBullets.png")) {
		std::cout << "soldierBullets est pas charg� bro" << std::endl << std::endl;
	}
	hardSoldier_Bullet_Auto_Attack_texture.setSmooth(true);

	hardSoldier_Bullet_Auto_Attack_sprite.setTexture(hardSoldier_Bullet_Auto_Attack_texture);
	hardSoldier_Bullet_Auto_Attack_sprite.setTextureRect(sf::IntRect(32, 0, -32, 16));
	hardSoldier_Bullet_Auto_Attack_sprite.setPosition(hardSoldier_walk_sprite.getPosition().x + 5, hardSoldier_walk_sprite.getPosition().y + 80);
}

void HardSoldier::hardSoldierPrintWindow(sf::RenderWindow& window) {
	hardSoldier_walk_sprite.setTextureRect(sf::IntRect(hardSoldier_anim.x * 200, 0, -200, 200));
	window.draw(hardSoldier_walk_sprite);

	//////////////////////////////

	/*if (ekko_S.ekko_anim_isAttacking) {
		if (ekko_anim_Auto_Attack.x * 128 >= ekko_Auto_Attack_texture.getSize().x)
			ekko_anim_Auto_Attack.x = 0;

		marcus_walk_sprite.setTextureRect(sf::IntRect(ekko_anim_Auto_Attack.x * 128, 0, 128, 128));
		window.draw(marcus_walk_sprite);
	}*/
	//////////////////////////////
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
std::string HardSoldier::getName() {
	return hs_name;
}
bool HardSoldier::getAlive() {
	return hs_isAlive;
}
int HardSoldier::heal() {
	hs_health++;
	return hs_health;
}
