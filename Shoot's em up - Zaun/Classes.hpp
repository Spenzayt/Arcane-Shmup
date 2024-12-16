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
	sf::RenderWindow window;

	enum Level { CUSTOM, LEVEL_1, LEVEL_2 };

	void init() {
		window.create(sf::VideoMode(1920, 1080), "Zaun : La bataille des nations", sf::Style::Fullscreen);
		window.setFramerateLimit(60);
	}
};