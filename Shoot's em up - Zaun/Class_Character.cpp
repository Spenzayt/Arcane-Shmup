#include "Class_Character.hpp"

Character::Character() {}

Character::Character(std::string n, int CX, int CY) : c_name(n), c_coordX(CX), c_coordY(CY) {}

Character::~Character() {}

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

///////////////////////////////////////

Character Char_Class;

Ekko::Ekko() : Character("Ekko", 225, 800) {}

Ekko::~Ekko() {}

void Ekko::ekkoInitAnimations() {
	if (!ekko_walk_texture.loadFromFile("assets\\characters\\ekko\\Ekko_walk_128_V2.png")) {
		std::cout << "ekko est pas chargé bro" << std::endl << std::endl; // Erreur si le fichier est introuvable
	}
	ekko_walk_texture.setSmooth(true);
	ekko_walk_sprite.setTexture(ekko_walk_texture);
	ekko_walk_sprite.setTextureRect(sf::IntRect(128, 0, 128, 128));
	ekko_walk_sprite.setPosition(Char_Class.getCoordX(), Char_Class.getCoordY());

	/////////////////
	if (!ekko_Auto_Attack_texture.loadFromFile("assets\\characters\\ekko\\Ekko_Auto_Attack_128V3.png")) {
		std::cout << "ekkoAutoAttack est pas chargé bro" << std::endl << std::endl;
	}
	ekko_Auto_Attack_texture.setSmooth(true);
	ekko_Auto_Attack_sprite.setTexture(ekko_Auto_Attack_texture);
	ekko_Auto_Attack_sprite.setTextureRect(sf::IntRect(128, 0, 128, 128));
	ekko_Auto_Attack_sprite.setPosition(Char_Class.getCoordX(), Char_Class.getCoordY());

	///////////////
	if (!ekko_SlowZone_texture.loadFromFile("assets\\characters\\ekko\\SlowZone-Spell.png")) {
		std::cout << "SlowZone est pas chargé bro" << std::endl << std::endl;
	}
	ekko_SlowZone_texture.setSmooth(true);
	ekko_SlowZone_sprite.setTexture(ekko_SlowZone_texture);

	/////////////////
	if (!ekko_Boomerang_texture.loadFromFile("assets\\characters\\ekko\\Auto attack Ekko petit.png")) {
		std::cout << "Boomerang est pas chargé bro" << std::endl << std::endl;
	}
	ekko_Boomerang_texture.setSmooth(true);
	ekko_Boomerang_sprite.setTexture(ekko_Boomerang_texture);
	ekko_Boomerang_sprite.setScale(2, 2);
	ekko_Boomerang_sprite.setTextureRect(sf::IntRect(91, 0, 91, 53));
}

void Ekko::ekkoDontExitFromScreen() {
	if (ekko_walk_sprite.getPosition().x <= 0) ekko_walk_sprite.setPosition(sf::Vector2f(0, ekko_walk_sprite.getPosition().y));
	if (ekko_walk_sprite.getPosition().y <= 525) ekko_walk_sprite.setPosition(sf::Vector2f(ekko_walk_sprite.getPosition().x, 525));
	if (ekko_walk_sprite.getPosition().x >= 1920 - ekko_walk_sprite.getGlobalBounds().width) ekko_walk_sprite.setPosition(sf::Vector2f(1920 - ekko_walk_sprite.getGlobalBounds().width, ekko_walk_sprite.getPosition().y));
	if (ekko_walk_sprite.getPosition().y >= 1070 - ekko_walk_sprite.getGlobalBounds().height) ekko_walk_sprite.setPosition(sf::Vector2f(ekko_walk_sprite.getPosition().x, 1070 - ekko_walk_sprite.getGlobalBounds().height));

	if (ekko_Auto_Attack_sprite.getPosition().x <= 0) ekko_Auto_Attack_sprite.setPosition(sf::Vector2f(0, ekko_Auto_Attack_sprite.getPosition().y));
	if (ekko_Auto_Attack_sprite.getPosition().y <= 525) ekko_Auto_Attack_sprite.setPosition(sf::Vector2f(ekko_Auto_Attack_sprite.getPosition().x, 525));
	if (ekko_Auto_Attack_sprite.getPosition().x >= 1920 - ekko_Auto_Attack_sprite.getGlobalBounds().width) ekko_Auto_Attack_sprite.setPosition(sf::Vector2f(1920 - ekko_Auto_Attack_sprite.getGlobalBounds().width, ekko_Auto_Attack_sprite.getPosition().y));
	if (ekko_Auto_Attack_sprite.getPosition().y >= 1070 - ekko_Auto_Attack_sprite.getGlobalBounds().height) ekko_Auto_Attack_sprite.setPosition(sf::Vector2f(ekko_Auto_Attack_sprite.getPosition().x, 1070 - ekko_Auto_Attack_sprite.getGlobalBounds().height));
}

void Ekko::bulletInit() {
	if (!ekko_Bullet_Auto_Attack_texture.loadFromFile("assets\\characters\\ekko\\AutotAttackEkko.png")) {
		std::cout << "ekkoBulletAutoAttack est pas chargé bro" << std::endl << std::endl;
	}
	ekko_Bullet_Auto_Attack_texture.setSmooth(true);

	ekko_Bullet_Auto_Attack_sprite.setTexture(ekko_Bullet_Auto_Attack_texture);
	ekko_Bullet_Auto_Attack_sprite.setTextureRect(sf::IntRect(32, 0, -32, 32));
	ekko_Bullet_Auto_Attack_sprite.setPosition(ekko_Auto_Attack_sprite.getPosition().x + 128, ekko_Auto_Attack_sprite.getPosition().y - 32);
}

void Ekko::ekkoCommand() {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		ekko_S.ekko_anim_isAttacking = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		ekko_walk_sprite.move(-10.f * Ekko_speed, 0.f);
		ekko_Auto_Attack_sprite.move(-10.f * Ekko_speed, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		ekko_walk_sprite.move(10.f * Ekko_speed, 0.f);
		ekko_Auto_Attack_sprite.move(10.f * Ekko_speed, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		ekko_walk_sprite.move(0.f, -10.f * Ekko_speed);
		ekko_Auto_Attack_sprite.move(0.f, -10.f * Ekko_speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		ekko_walk_sprite.move(0.f, 10.f * Ekko_speed);
		ekko_Auto_Attack_sprite.move(0.f, 10.f * Ekko_speed);
	}
	/////////////
	// Spells & Ult

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		castSpell("A Spell");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		castSpell("E Spell");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		castSpell("C Spell");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		castSpell("X Ult");
	}
}

void Ekko::ekkoPrintWindow(sf::RenderWindow& window) {
	if (!ekko_S.ekko_anim_isAttacking) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if (ekko_anim.x * 128 >= ekko_walk_texture.getSize().x + 118) // boucle qui permet de revenir a la premiere slide de l'anim
				ekko_anim.x = 2;
			ekko_walk_sprite.setTextureRect(sf::IntRect(ekko_anim.x * 128, 0, -128, 128));
			window.draw(ekko_walk_sprite);
		}
		else {
			if (ekko_anim.x * 128 >= ekko_walk_texture.getSize().x) // boucle qui permet de revenir a la premiere slide de l'anim
				ekko_anim.x = 0;
			ekko_walk_sprite.setTextureRect(sf::IntRect(ekko_anim.x * 128, 0, 128, 128));
			window.draw(ekko_walk_sprite);
		}
		//////////////////////////////
	}

	if (ekko_S.ekko_anim_isAttacking) {
		if (ekko_anim_Auto_Attack.x * 128 >= ekko_Auto_Attack_texture.getSize().x)
			ekko_anim_Auto_Attack.x = 0;

		ekko_Auto_Attack_sprite.setTextureRect(sf::IntRect(ekko_anim_Auto_Attack.x * 128, 0, 128, 128));
		window.draw(ekko_Auto_Attack_sprite);
	}
	//////////////////////////////

	if (ekko_S.SlowZone) {
		window.draw(ekko_SlowZone_sprite);
	}

	//////////////

	if (ekko_S.Boomerang) {
		window.draw(ekko_Boomerang_sprite);
	}
}

struct SpellInfo {
	float cooldownTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastCastTime;
};

std::unordered_map<std::string, SpellInfo> spells;

void Ekko::initializeSpells() {
	spells["A Spell"] = { 2.0f, std::chrono::high_resolution_clock::now() };
	spells["E Spell"] = { 3.0f, std::chrono::high_resolution_clock::now() };
	spells["C Spell"] = { 0.5f, std::chrono::high_resolution_clock::now() };
	spells["X Ult"] = { 5.0f, std::chrono::high_resolution_clock::now() };
	positionClock.restart();
}

bool Ekko::canCastSpell(const std::string& spellName) {
	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> elapsed = currentTime - spells[spellName].lastCastTime;
	return elapsed.count() >= spells[spellName].cooldownTime;
}

void Ekko::castSpell(const std::string& spellName) {
	if (canCastSpell(spellName)) {
		if (spellName == "A Spell") {
			cout << "A Spell" << endl;
			Boomerang();
		}
		else if (spellName == "E Spell") {
			cout << "E Spell" << endl;
			SlowZone();
		}
		else if (spellName == "C Spell") {
			cout << "C Spell" << endl;
			dash();
		}
		else if (spellName == "X Ult") {
			if (!positionHistory.empty()) {
				auto targetPosition = positionHistory.front().first;
				isTeleporting = true;
				teleportTimer.restart();
				std::cout << "X Ult activated. Teleporting to: " << targetPosition.x << ", " << targetPosition.y << std::endl;
			}
			else {
				std::cout << "No position history. Cannot activate X Ult." << std::endl;
				isTeleporting = false;
			}
		}
		spells[spellName].lastCastTime = std::chrono::high_resolution_clock::now();
	}
}

void Ekko::dash() {
	sf::Vector2i mousePosition = sf::Mouse::getPosition();
	sf::Vector2f playerPosition = ekko_walk_sprite.getPosition();

	sf::Vector2f direction((mousePosition.x - 64) - playerPosition.x, (mousePosition.y - 64) - playerPosition.y);
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0) {
		direction.x /= length;
		direction.y /= length;
	}

	dashTargetPosition = playerPosition + direction * 200.0f;

	isDashing = true;
	dashingTimer.restart();
}


void Ekko::updatePositionHistory() {
	if (positionClock.getElapsedTime().asSeconds() >= 0.1f) {
		positionHistory.emplace_back(ekko_walk_sprite.getPosition(), positionClock.getElapsedTime());
		if (positionHistory.size() > 40) {
			positionHistory.pop_front();
		}
		positionClock.restart();
	}
}

void Ekko::updateSpells() {
	if (isDashing) {
		float elapsed = dashingTimer.getElapsedTime().asSeconds();
		float dashDuration = 0.2f;
		if (elapsed >= dashDuration) {
			ekko_walk_sprite.setPosition(dashTargetPosition);
			ekko_Auto_Attack_sprite.setPosition(dashTargetPosition);
			isDashing = false;
		}
		else {
			sf::Vector2f startPosition = ekko_walk_sprite.getPosition();
			sf::Vector2f interpolatedPosition = startPosition + (dashTargetPosition - startPosition) * (elapsed / dashDuration);

			ekko_walk_sprite.setPosition(interpolatedPosition);
			ekko_Auto_Attack_sprite.setPosition(interpolatedPosition);
		}
	}

	if (isTeleporting) {
		float t = teleportTimer.getElapsedTime().asSeconds() / 0.5f;
		if (t >= 1.0f) {
			sf::Vector2f targetPosition = positionHistory.front().first;
			ekko_walk_sprite.setPosition(targetPosition);
			ekko_Auto_Attack_sprite.setPosition(targetPosition);
			isTeleporting = false;
		}
		else {
			sf::Vector2f targetPosition = positionHistory.front().first;
			sf::Vector2f currentPosition = ekko_walk_sprite.getPosition();
			sf::Vector2f interpolatedPosition = currentPosition + t * (targetPosition - currentPosition);

			ekko_walk_sprite.setPosition(interpolatedPosition);
			ekko_Auto_Attack_sprite.setPosition(interpolatedPosition);
		}
	}

	if (isSlowZoneActive) {
		if (!ekko_S.SlowZone) {
			ekko_S.SlowZone = true;
			ekko_SlowZone_sprite.setPosition(SlowZoneTargetPosition);
			SlowZoneTimer.restart();
		}

		float tSlow = SlowZoneTimer.getElapsedTime().asSeconds();

		if (tSlow >= 5.0f) {
			ekko_S.SlowZone = false;
			isSlowZoneActive = false;
		}
	}

	if (isBoomerangActive) {
		if (!isBoomerangStart) {
			isBoomerangStart = true;
			ekko_S.Boomerang = true;
			BoomerangTimer.restart();
			BoomerangStartPosition = ekko_Boomerang_sprite.getPosition();
			BoomerangTargetPosition = sf::Vector2f(BoomerangStartPosition.x + 800.0f, BoomerangStartPosition.y);
		}

		if (!isBoomerangComingBack) {
			float tBoomerangGo = BoomerangTimer.getElapsedTime().asSeconds();

			if (tBoomerangGo >= 2.0f) {
				isBoomerangComingBack = true;
				BoomerangTimer.restart();
			}
			else {
				sf::Vector2f direction = BoomerangTargetPosition - BoomerangStartPosition;
				float progress = tBoomerangGo / 2.0f;
				sf::Vector2f interpolatedPosition = BoomerangStartPosition + direction * progress;

				ekko_Boomerang_sprite.setPosition(interpolatedPosition);
			}
		}

		if (isBoomerangComingBack) {
			float tBoomerangReturn = BoomerangTimer.getElapsedTime().asSeconds();
			ekko_Boomerang_sprite.setTextureRect(sf::IntRect(91, 0, -91, 53));

			if (tBoomerangReturn >= 0.5f) {
				isBoomerangComingBack = false;
				isBoomerangActive = false;
				ekko_S.Boomerang = false;
				ekko_Boomerang_sprite.setTextureRect(sf::IntRect(91, 0, 91, 53));

				isBoomerangStart = false;
				BoomerangStartPosition = sf::Vector2f(0, 0);
				BoomerangTargetPosition = sf::Vector2f(0, 0);
			}
			else {
				sf::Vector2f currentEkkoPosition = sf::Vector2f(ekko_walk_sprite.getPosition().x + 100, ekko_walk_sprite.getPosition().y + 20);
				sf::Vector2f currentBoomerangPosition = ekko_Boomerang_sprite.getPosition();
				sf::Vector2f direction = currentEkkoPosition - currentBoomerangPosition;
				float progress = tBoomerangReturn / 0.5f;
				sf::Vector2f interpolatedPosition = currentBoomerangPosition + direction * progress;

				ekko_Boomerang_sprite.setPosition(interpolatedPosition);
			}
		}
	}
}

void Ekko::SlowZone() {
	sf::Vector2f playerPosition = ekko_walk_sprite.getPosition();

	SlowZoneTargetPosition = sf::Vector2f(playerPosition.x + 400.0f, playerPosition.y - 64);

	isSlowZoneActive = true;
}

void Ekko::Boomerang() {
	isBoomerangActive = true;
	ekko_Boomerang_sprite.setPosition(sf::Vector2f(ekko_walk_sprite.getPosition().x, ekko_walk_sprite.getPosition().y + 0));
}