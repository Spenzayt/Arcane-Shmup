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
	vector<Ekko*> ekkos;
	
	~Game() {
		for (auto soldier : soldiers)
			delete soldier;
		for (auto ekkoG : ekkos)
			delete ekkoG;
	}

	sf::RenderWindow window;

	void init() {
		window.create(sf::VideoMode(1920, 1080), "Zaun : La bataille des nations", sf::Style::Fullscreen);
		window.setFramerateLimit(60);
	}

	void addEnemies(int soldierNumber) {
		for (int i = 0; i < soldierNumber; i++) {
			soldiers.push_back(new Soldier());
			cout << "création du soldat" << endl << endl;
		}
	}

	void addEkko() {
		ekkos.push_back(new Ekko());
		cout << "création de Ekko" << endl << endl;
	}
};