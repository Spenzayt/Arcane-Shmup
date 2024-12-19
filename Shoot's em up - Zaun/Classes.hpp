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

Cooldown cooldown;
Ekko Ekko_Class(cooldown);
Marcus Marcus_Class;
Soldier Soldier_Class;
MediumSoldier MediumSoldier_Class;
HardSoldier HardSoldier_Class;

class Game {
public:
	sf::RenderWindow window;

	enum GamePhase { WavesPhase, BossPhase};
	GamePhase currentPhase = WavesPhase;

	bool isPaused;
	bool konamiCodeActivated;
	bool isCustom;

	int currentWave;
	int MaxEasySoldier;
	int MaxMediumSoldier;
	int MaxHardSoldier;
	int TimeBeforeBoss;
	int score;

	int level = 1;
	int maxLevel = 4;

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