#include "Class_Ekko.hpp"

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
}

void Ekko::ekkoPrintWindow(sf::RenderWindow& window) {
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
		if (ekko_anim_Auto_Attack.x * 128 >= ekko_Auto_Attack_texture.getSize().x)
			ekko_anim_Auto_Attack.x = 0;

		ekko_Auto_Attack_sprite.setTextureRect(sf::IntRect(ekko_anim_Auto_Attack.x * 128, 0, 128, 128));
		window.draw(ekko_Auto_Attack_sprite);
	}
	//////////////////////////////
}