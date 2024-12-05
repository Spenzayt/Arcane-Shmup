#include "Classes.hpp"
#include "Animation & Images.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

int main() {
    game.init();
    game.initAnimations();
    // Boucle principale
    while (game.window.isOpen()) {
        sf::Event event;
        while (game.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                game.window.close(); // Fermer la fenêtre
        }
        game.Command();
        game.window.clear();
        game.printWindow();
        game.window.display();

    }
}