#include "Class_Marcus.hpp"

Enemies Enemies_Class;

Marcus::Marcus() : Enemies("Marcus", 1600, 800, 100) {}

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			marcus_walk_sprite.setTextureRect(sf::IntRect(marcus_anim.x * 512, 0, 640, 512));
			window.draw(marcus_walk_sprite);
		}
		else {
			marcus_walk_sprite.setTextureRect(sf::IntRect(marcus_anim.x * 512, 0, 640, 512));
			window.draw(marcus_walk_sprite);
		}
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