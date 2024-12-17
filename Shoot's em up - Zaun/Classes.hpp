#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <windows.h>
#include "Class_Character.hpp"
#include "Class_Enemies.hpp"

Ekko Ekko_Class;
Marcus Marcus_Class;
Soldier Soldier_Class;
MediumSoldier MediumSoldier_Class;
HardSoldier HardSoldier_Class;

class Menu {
public:
	sf::Texture background_texture;
	sf::Sprite background_sprite;
};


class Game {
public:
	sf::RenderWindow window;

	enum Mode { MENU, CUSTOM, LEVEL_1, LEVEL_2 };
	Mode currentMode = MENU;

	enum GamePhase { WavesPhase, BossPhase};
	GamePhase currentPhase = WavesPhase;

	bool konamiCodeActivated = false;

	int currentWave = 1;

	//////////////////
	//Custom
	int NbEasySoldier = 1;
	int NbMediumSoldier = 1;
	int NbHardSoldier = 1;
	int MaxWaves = 3;
	float CoefDifficulty = 3.0f;
	//////////////////

	void init() {
		window.create(sf::VideoMode(1920, 1080), "Zaun : La bataille des nations", sf::Style::Fullscreen);
		window.setFramerateLimit(60);
	}

	std::vector<sf::Keyboard::Key> konamiCode = {
	sf::Keyboard::Up, sf::Keyboard::Up,
	sf::Keyboard::Down, sf::Keyboard::Down,
	sf::Keyboard::Left, sf::Keyboard::Right,
	sf::Keyboard::Left, sf::Keyboard::Right,
	sf::Keyboard::B, sf::Keyboard::A
	};
	std::vector<sf::Keyboard::Key> inputSequence;

	void checkKonamiCode() {
		if (inputSequence == konamiCode) {
			if (!konamiCodeActivated) {
				std::cout << "Konami Code active !" << std::endl;
				Ekko_Class.Ekko_invincibility = true;
				konamiCodeActivated = true;
			}
			else {
				std::cout << "Konami Code desactivated !" << std::endl;
				Ekko_Class.Ekko_invincibility = false;
				konamiCodeActivated = false;
			}
		}
	}
};