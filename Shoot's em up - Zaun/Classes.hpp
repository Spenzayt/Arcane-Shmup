#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <windows.h>
#include "Class_Character.hpp"
#include "Class_Enemies.hpp"
#include "buff.hpp"

Ekko Ekko_Class;
Marcus Marcus_Class;
Soldier Soldier_Class;
MediumSoldier MediumSoldier_Class;
HardSoldier HardSoldier_Class;

class Game {
public:
	sf::RenderWindow window;

	enum GamePhase { WavesPhase, BossPhase};
	GamePhase currentPhase = WavesPhase;

	bool isPaused = false;

	bool konamiCodeActivated = false;

	int currentWave = 1;

	bool isCustom = false;

	//////////////////
	//Custom
	int NbEasySoldier = 3;
	int NbMediumSoldier = 2;
	int NbHardSoldier = 1;
	int MaxWaves = 5;
	float CoefDifficulty = 2.0f;
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