#include <SFML/Graphics.hpp>
<<<<<<< Updated upstream
#include <SFML/Audio.hpp>
=======
>>>>>>> Stashed changes
#include "Classes.hpp"
#include "Animation & Images.hpp"
#include <windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

using namespace sf;

int main() {
    game.init();
    game.initAnimations();
    while (game.window.isOpen()) {
        Event event;
        while (game.window.pollEvent(event)) {
<<<<<<< Updated upstream
            if (event.type == Event::Closed)
=======
            if (event.type == sf::Event::Closed)
>>>>>>> Stashed changes
                game.window.close();
        }
        game.Command();
        game.window.clear();
        game.printWindow();
        game.window.display();
<<<<<<< Updated upstream
        game.window.clear();


=======
>>>>>>> Stashed changes
    }
}