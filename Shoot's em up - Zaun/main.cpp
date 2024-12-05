#include <SFML/Graphics.hpp>
#include <iostream>
#include "parallax.hpp"

using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(1920, 1080), "Effet de Parallaxe", Style::Fullscreen);

    ParallaxBackground background1("../assets/backgrounds/ground-zaun.png", 150.0f, 530, 1, 0.6);
    ParallaxBackground background2("../assets/backgrounds/background-zaun.jpeg", 20.0f, -1700, 2, 2);

    Clock clock;
    while (window.isOpen()) {
        Time deltaTime = clock.restart();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        background1.update(deltaTime.asSeconds());
        background2.update(deltaTime.asSeconds());

        window.clear();
        background2.draw(window);
        background1.draw(window);
        window.display();
    }

    return 0;
}