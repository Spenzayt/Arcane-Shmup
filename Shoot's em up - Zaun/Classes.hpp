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
public:

	vector<Soldier*> soldiers;

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
			soldiers.push_back(new Soldier());
		}
	}

	void Death() {
		for (auto everySoldiers = soldiers.begin(); everySoldiers != soldiers.end(); ) { 
			auto soldiers = *everySoldiers;
			if (soldiers->getAlive() == false) {
				cout << " (" << soldiers->getCoordX() << ", " << soldiers->getCoordY() << ")" << " est mort." << endl << endl;
				soldiers->~Soldier();
				delete soldiers;
				//everySoldiers = soldiers.erase(everySoldiers);
			}
			else {
				++everySoldiers;
			}
		}
	}

};