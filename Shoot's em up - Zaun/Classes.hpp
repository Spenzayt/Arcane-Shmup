#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <windows.h>

class Entities {
protected:
	int E_coordX = 0;
	int E_coordY = 0;
	int E_health = 0;
	bool E_isAlive = true;
	bool E_isAttacking = false;
	bool E_isHit = false;
	bool E_isDying = false;
	bool E_isDead = false;
	std::string E_name;

public:

	Entities(bool A) : E_health(), E_coordX(), E_coordY(), E_isAlive(A) {}

	~Entities() {
		std::cout << E_name << " est détruit";
	}

	virtual int losePV(int damage) {
		E_health -= damage;
		if (E_health <= 0) {
			E_health = 0;
			E_isAlive = false;
		}
		return E_health;
	}
	virtual int getHealth() {
		return E_health;
	}
	virtual int getCoordX() {
		return E_coordX;
	}
	virtual int setCoordX(int X) {
		E_coordX += X;
		return E_coordX;
	}
	virtual int getCoordY() {
		return E_coordY;
	}
	virtual int setCoordY(int Y) {
		E_coordY += Y;
		return E_coordY;
	}
	virtual std::string getName() {
		return E_name;
	}
	virtual bool getAlive() {
		return E_isAlive;
	}
	virtual int heal() {
		E_health += 30;
		return E_health;
	}
	virtual int setHealth(int pv) {
		E_health = pv;
		return E_health;
	}
	virtual int HealthReset(int pv) {
		E_health = pv;
		return E_health;
	}
	virtual bool LifeReset() {
		E_isAlive = true;
		return E_isAlive;
	}
};

class Character : public Entities {
protected:
	std::string c_name;
	int c_coordX = 225;
	int	c_coordY = 800;
	int c_health;
	bool c_isAlive = true;

public:
	Character() : Entities(true) {}
	Character(std::string n, int CX, int CY, int h) : c_name(n), c_coordX(CX), c_coordY(CY), c_health(h), Entities(true) {}

	int losePV(int damage) override {
		c_health -= damage;
		if (c_health <= 0) {
			c_health = 0;
			c_isAlive = false;
		}
		return c_health;
	}
	int getHealth() override {
		return c_health;
	}
	int getCoordX() override {
		return c_coordX;
	}
	int setCoordX(int X) override {
		c_coordX += X;
		return c_coordX;
	}
	int getCoordY() override {
		return c_coordY;
	}
	int setCoordY(int Y) override {
		c_coordY += Y;
		return c_coordY;
	}
	std::string getName() override {
		return c_name;
	}
	bool getAlive() override {
		return c_isAlive;
	}
	int heal() override {
		c_health++;
		return c_health;
	}
	int setHealth(int pv) override {
		c_health = pv;
		return c_health;
	}
	int HealthReset(int pv) override {
		c_health = pv;
		return c_health;
	}
	bool LifeReset() {
		c_isAlive = true;
		return c_isAlive;
	}
}; Character Char_Class;



class Enemies : public Entities {
protected:
	std::string e_name;
	int e_coordX, e_coordY;
	int e_health;
	bool e_isAlive = true;


public:
	Enemies(std::string n, int CX, int CY, int h) : e_name(n), e_coordX(CX), e_coordY(CY), e_health(h), Entities(true) {}

	int losePV(int damage) override {
		e_health -= damage;
		if (e_health <= 0) {
			e_health = 0;
			e_isAlive = false;
		}
		return e_health;
	}
	int getHealth() override {
		return e_health;
	}
	int getCoordX() override {
		return e_coordX;
	}
	int setCoordX(int X) override {
		e_coordX += X;
		return e_coordX;
	}
	int getCoordY() override {
		return e_coordY;
	}
	int setCoordY(int Y) override {
		e_coordY += Y;
		return e_coordY;
	}
	std::string getName() override {
		return e_name;
	}
	bool getAlive() override {
		return e_isAlive;
	}
	int heal() override {
		e_health++;
		return e_health;
	}
	int setHealth(int pv) override {
		e_health = pv;
		return e_health;
	}
	int HealthReset(int pv) override {
		e_health = pv;
		return e_health;
	}
	bool LifeReset() {
		e_isAlive = true;
		return e_isAlive;
	}
};

class Ekko : public Character {
public:
	Ekko() : Character("Ekko", 225, 800, 100) {}


};

class Game {
public:

	sf::RenderWindow window;
	sf::Texture ekko_walk_texture;
	sf::Sprite ekko_walk_sprite;
	sf::Vector2i ekko_anim;


	sf::Texture ekko_Attack_texture;
	sf::Sprite ekko_Attack_sprite;
	sf::Vector2i ekko_anim_Attack;

	struct Ekko {
		bool isAttacking = false;
		bool ekko_anim_isAttacking = false;
		bool isHealing = false;
		bool isHit = false;
		bool ekko_anim_isHit = false;
		bool isDying = false;
		bool ekko_anim_isDying = false;
		bool printBody = false;
		int countAnimAtk = 0;
		int countAnimHeal = 0;
		int countAnimHit = 0;
		int countAnimDeath = 0;
		int DeathCount = 0;
	}; Ekko ekko_S;



	void init() {
		window.create(VideoMode(1920, 1080), "Zaun : La bataille des nations", sf::Style::Fullscreen);
		window.setFramerateLimit(60);
	}

	void dontExitFromScreen() {
		if (ekko_walk_sprite.getPosition().x <= 0) ekko_walk_sprite.setPosition(sf::Vector2f(0, ekko_walk_sprite.getPosition().y));
		if (ekko_walk_sprite.getPosition().y <= 530) ekko_walk_sprite.setPosition(sf::Vector2f(ekko_walk_sprite.getPosition().x, 530));
		if (ekko_walk_sprite.getPosition().x >= 1920 - ekko_walk_sprite.getGlobalBounds().width) ekko_walk_sprite.setPosition(sf::Vector2f(1920 - ekko_walk_sprite.getGlobalBounds().width, ekko_walk_sprite.getPosition().y));
		if (ekko_walk_sprite.getPosition().y >= 1080 - ekko_walk_sprite.getGlobalBounds().height) ekko_walk_sprite.setPosition(sf::Vector2f(ekko_walk_sprite.getPosition().x, 1080 - ekko_walk_sprite.getGlobalBounds().height));
		
		if (ekko_Attack_sprite.getPosition().x <= 0) ekko_Attack_sprite.setPosition(sf::Vector2f(0, ekko_Attack_sprite.getPosition().y));
		if (ekko_Attack_sprite.getPosition().y <= 530) ekko_Attack_sprite.setPosition(sf::Vector2f(ekko_Attack_sprite.getPosition().x, 530));
		if (ekko_Attack_sprite.getPosition().x >= 1920 - ekko_Attack_sprite.getGlobalBounds().width) ekko_Attack_sprite.setPosition(sf::Vector2f(1920 - ekko_Attack_sprite.getGlobalBounds().width, ekko_Attack_sprite.getPosition().y));
		if (ekko_Attack_sprite.getPosition().y >= 1080 - ekko_Attack_sprite.getGlobalBounds().height) ekko_Attack_sprite.setPosition(sf::Vector2f(ekko_Attack_sprite.getPosition().x, 1080 - ekko_Attack_sprite.getGlobalBounds().height));
	}

	void initAnimations() {
		if (!ekko_walk_texture.loadFromFile("assets\\characters\\ekko\\Ekko_walk_128_V42.png")) {
			std::cout << "ekko est pas chargé bro" << std::endl << std::endl; // Erreur si le fichier est introuvable
		}
		ekko_walk_texture.setSmooth(true);
		ekko_walk_sprite.setTexture(ekko_walk_texture);
		ekko_walk_sprite.setTextureRect(sf::IntRect(128, 0, 128, 128));
		ekko_walk_sprite.setPosition(Char_Class.getCoordX(), Char_Class.getCoordY());

		/////////////////
		if (!ekko_Attack_texture.loadFromFile("assets\\characters\\ekko\\Ekko_Attack_128.png")) {
			std::cout << "ekkoAttack est pas chargé bro" << std::endl << std::endl;
		}
		ekko_Attack_texture.setSmooth(true);

		ekko_Attack_sprite.setTexture(ekko_Attack_texture);
		ekko_Attack_sprite.setTextureRect(sf::IntRect(128, 0, 128, 128));
		ekko_Attack_sprite.setPosition(Char_Class.getCoordX(), Char_Class.getCoordY());
	}


	void printWindow() {
		if (!ekko_S.ekko_anim_isAttacking) {
			if (ekko_anim.x * 128 >= ekko_walk_texture.getSize().x) // boucle qui permet de revenir a la premiere slide de l'anim
				ekko_anim.x = 0;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				ekko_walk_sprite.setTextureRect(sf::IntRect(ekko_anim.x * 128, 0, -128, 128));
				window.draw(ekko_walk_sprite);
			}
			else {
				ekko_walk_sprite.setTextureRect(sf::IntRect(ekko_anim.x * 128, 0, 128, 128));
				window.draw(ekko_walk_sprite);
			}
			//////////////////////////////
		}

		if (ekko_S.ekko_anim_isAttacking) {
			if (ekko_anim_Attack.x * 128 >= ekko_Attack_texture.getSize().x)
				ekko_anim_Attack.x = 0;

			ekko_Attack_sprite.setTextureRect(sf::IntRect(ekko_anim_Attack.x * 128, 0, 128, 128));
			window.draw(ekko_Attack_sprite);
		}
		//////////////////////////////
	}

	void Command() {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			ekko_S.ekko_anim_isAttacking = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			//ekko_walk_sprite.setPosition(Char_Class += 10, 10);
			ekko_walk_sprite.move(-10.f, 0.f);
			ekko_Attack_sprite.move(-10.f, 0.f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			ekko_walk_sprite.move(10.f, 0.f);
			ekko_Attack_sprite.move(10.f, 0.f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			ekko_walk_sprite.move(0.f, -10.f);
			ekko_Attack_sprite.move(0.f, -10.f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			ekko_walk_sprite.move(0.f, 10.f);
			ekko_Attack_sprite.move(0.f, 10.f);
		}
	}
}; Game game;