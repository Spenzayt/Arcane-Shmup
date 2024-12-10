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

///////////////////////////////////////

Character Char_Class;

Ekko::Ekko() : Character("Ekko", 225, 800, 100) {}

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
		ekko_walk_sprite.move(-10.f, 0.f);
		ekko_Auto_Attack_sprite.move(-10.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		ekko_walk_sprite.move(10.f, 0.f);
		ekko_Auto_Attack_sprite.move(10.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		ekko_walk_sprite.move(0.f, -10.f);
		ekko_Auto_Attack_sprite.move(0.f, -10.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		ekko_walk_sprite.move(0.f, 10.f);
		ekko_Auto_Attack_sprite.move(0.f, 10.f);
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
			// A Spell Action
			cout << "A Spell" << endl;
		}
		else if (spellName == "E Spell") {
			// E Spell Action
			cout << "E Spell" << endl;

		}
		else if (spellName == "C Spell") {
			cout << "C Spell" << endl;
			dash();
		}
		else if (spellName == "X Ult") {
			// X Ult Action
			if (!positionHistory.empty()) {
				auto targetPosition = positionHistory.front().first; // Position d'il y a 4 secondes
				isTeleporting = true;
				teleportTimer.restart();
				std::cout << "X Ult activated. Teleporting to: " << targetPosition.x << ", " << targetPosition.y << std::endl;
			}
			else {
				std::cout << "No position history. Cannot activate X Ult." << std::endl;
				isTeleporting = false; // Assurez-vous que la téléportation est désactivée si l'historique est vide.
			}
		}
		spells[spellName].lastCastTime = std::chrono::high_resolution_clock::now();
	}
}

void Ekko::dash() {
	// Initialisation pour le dash
	sf::Vector2i mousePosition = sf::Mouse::getPosition();
	sf::Vector2f playerPosition = ekko_walk_sprite.getPosition();

	// Calculer la direction vers le pointeur de la souris
	sf::Vector2f direction((mousePosition.x - 64) - playerPosition.x, (mousePosition.y - 64) - playerPosition.y);
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0) {
		direction.x /= length;
		direction.y /= length;
	}

	// Calculer la position finale après le dash
	dashTargetPosition = playerPosition + direction * 200.0f;

	// Activer le dash
	isDashing = true;
	dashingTimer.restart();
}


void Ekko::updatePositionHistory() {
	// Vérifiez si l'historique doit être mis à jour
	if (positionClock.getElapsedTime().asSeconds() >= 0.1f) {
		// Ajoutez la position actuelle au deque
		positionHistory.emplace_back(ekko_walk_sprite.getPosition(), positionClock.getElapsedTime());
		// Gardez uniquement les 4 dernières secondes
		if (positionHistory.size() > 40) {
			positionHistory.pop_front();
		}
		positionClock.restart();
	}
}

void Ekko::updateTeleport() {
	if (isDashing) {
		float elapsed = dashingTimer.getElapsedTime().asSeconds();
		float dashDuration = 0.2f; // Durée totale du dash en secondes
		if (elapsed >= dashDuration) {
			// Fin du dash
			ekko_walk_sprite.setPosition(dashTargetPosition);
			ekko_Auto_Attack_sprite.setPosition(dashTargetPosition);
			isDashing = false;
		}
		else {
			// Interpolation linéaire vers la position cible
			sf::Vector2f startPosition = ekko_walk_sprite.getPosition();
			sf::Vector2f interpolatedPosition = startPosition + (dashTargetPosition - startPosition) * (elapsed / dashDuration);

			ekko_walk_sprite.setPosition(interpolatedPosition);
			ekko_Auto_Attack_sprite.setPosition(interpolatedPosition);
		}
	}

	if (isTeleporting) {
		float t = teleportTimer.getElapsedTime().asSeconds() / 0.5f;
		if (t >= 1.0f) {
			// Téléportation terminée
			sf::Vector2f targetPosition = positionHistory.front().first;
			ekko_walk_sprite.setPosition(targetPosition);
			ekko_Auto_Attack_sprite.setPosition(targetPosition);
			isTeleporting = false;
		}
		else {
			// Interpolation vers la position cible
			sf::Vector2f targetPosition = positionHistory.front().first;
			sf::Vector2f currentPosition = ekko_walk_sprite.getPosition();
			sf::Vector2f interpolatedPosition = currentPosition + t * (targetPosition - currentPosition);

			ekko_walk_sprite.setPosition(interpolatedPosition);
			ekko_Auto_Attack_sprite.setPosition(interpolatedPosition);
		}
	}
}