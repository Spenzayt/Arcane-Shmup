#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
            if (event.type == Event::Closed)
                game.window.close();
        }
        game.Command();
        game.window.clear();
        game.printWindow();
        game.window.display();
        game.window.clear();


    }
}