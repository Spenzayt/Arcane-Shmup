#include <iostream>
#include <SFML/Graphics.hpp>

class Game {

public : 

	sf::RenderWindow window;
	sf::Texture ekko_walk_texture;
	sf::Sprite ekko_walk_sprite;
	sf::Vector2i ekko_anim;


	void init() {
		window.create(sf::VideoMode(1920, 1080), "Chapitre 1, Zaun : La bataille des nations");
		window.setFramerateLimit(60);
	}

	void initAnimations() {
		if (!ekko_walk_texture.loadFromFile("assets\\characters\\ekko\\Ekko_walk_128_V42.png")) {
			std::cout << "ekko est pas chargé bro" << std::endl << std::endl; // Erreur si le fichier est introuvable
		}
		ekko_walk_texture.setSmooth(true);
		ekko_walk_sprite.setTexture(ekko_walk_texture);
		ekko_walk_sprite.setTextureRect(sf::IntRect(128, 0, 128, 128));
		ekko_walk_sprite.setPosition(225, 100);
	}

	void printWindow() {
		ekko_anim.x++;
		if (ekko_anim.x * 128 >= ekko_walk_texture.getSize().x) // boucle qui permet de revenir a la premiere slide de l'anim
			ekko_anim.x = 0;
		// ici, ce code permet de creer l'animation Idle du personnage
		ekko_walk_sprite.setTextureRect(sf::IntRect(ekko_anim.x * 128, 0, 128, 128));
		window.draw(ekko_walk_sprite);
	}

	void Command() {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			// left key is pressed: move our character
			ekko_walk_sprite.move(-10.f, 0.f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			// left key is pressed: move our character
			ekko_walk_sprite.move(10.f, 0.f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			// left key is pressed: move our character
			ekko_walk_sprite.move(0.f, -10.f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			// left key is pressed: move our character
			ekko_walk_sprite.move(0.f, 10.f);
		}
	}
}; Game game;

class Entities {
protected : 
	int E_coordX = 0;
	int E_coordY = 0;
	int E_health = 0;
	bool E_isAlive = true;
	bool E_isAttacking = false;
	bool E_isHit = false;
	bool E_isDying = false;
	bool E_isDead = false;
	std::string name;

public : 

	Entities(int h, std::string n) : E_health(h), name(n) {}

	~Entities() {
		std::cout << name << " est détruit";
	}
};

class Character {
public : 

};

class Enemies {

};

