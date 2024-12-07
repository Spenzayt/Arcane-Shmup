#include "Class_Ekko.hpp"

sf::RenderWindow window;

Ekko::Ekko() : Character("Ekko", 225, 800, 100) {}

void Ekko::ekkoDontExitFromScreen() {
	if (ekko_walk_sprite.getPosition().x <= 0) ekko_walk_sprite.setPosition(sf::Vector2f(0, ekko_walk_sprite.getPosition().y));
	if (ekko_walk_sprite.getPosition().y <= 530) ekko_walk_sprite.setPosition(sf::Vector2f(ekko_walk_sprite.getPosition().x, 530));
	if (ekko_walk_sprite.getPosition().x >= 1920 - ekko_walk_sprite.getGlobalBounds().width) ekko_walk_sprite.setPosition(sf::Vector2f(1920 - ekko_walk_sprite.getGlobalBounds().width, ekko_walk_sprite.getPosition().y));
	if (ekko_walk_sprite.getPosition().y >= 1080 - ekko_walk_sprite.getGlobalBounds().height) ekko_walk_sprite.setPosition(sf::Vector2f(ekko_walk_sprite.getPosition().x, 1080 - ekko_walk_sprite.getGlobalBounds().height));

	if (ekko_Attack_sprite.getPosition().x <= 0) ekko_Attack_sprite.setPosition(sf::Vector2f(0, ekko_Attack_sprite.getPosition().y));
	if (ekko_Attack_sprite.getPosition().y <= 530) ekko_Attack_sprite.setPosition(sf::Vector2f(ekko_Attack_sprite.getPosition().x, 530));
	if (ekko_Attack_sprite.getPosition().x >= 1920 - ekko_Attack_sprite.getGlobalBounds().width) ekko_Attack_sprite.setPosition(sf::Vector2f(1920 - ekko_Attack_sprite.getGlobalBounds().width, ekko_Attack_sprite.getPosition().y));
	if (ekko_Attack_sprite.getPosition().y >= 1080 - ekko_Attack_sprite.getGlobalBounds().height) ekko_Attack_sprite.setPosition(sf::Vector2f(ekko_Attack_sprite.getPosition().x, 1080 - ekko_Attack_sprite.getGlobalBounds().height));
}

void Ekko::ekkoInitAnimations() {
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

void Ekko::ekkoPrintWindow() {
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

void Ekko::ekkoCommand() {

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
