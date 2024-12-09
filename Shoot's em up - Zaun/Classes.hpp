#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <windows.h>
#include "Class_Character.hpp"
#include "Class_Enemies.hpp"


class Game {
private :
	vector<Soldier*> soldiers;
public:

	~Game() {
		for (auto soldier : soldiers)
			delete soldier;
	}

	sf::RenderWindow window;

	void init() {
		window.create(sf::VideoMode(1920, 1080), "Zaun : La bataille des nations", sf::Style::Fullscreen);
		window.setFramerateLimit(60);
	}

	void addEnemies(int soldierNumber) {
		for (int i = 0; i < soldierNumber; i++) {
			int classes = rand() % 8;
			switch (classes) {
			case 0:
				soldiers.push_back(new Soldier());
				break;
			}
		}
	}

}; Game game;