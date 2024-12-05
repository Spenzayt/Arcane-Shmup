#include <SFML/Graphics.hpp>
#include <iostream>
#include "parallax.hpp"
#include "Classes.hpp"
#include "parallax.hpp"

using namespace std;
using namespace sf;

int main() {
    RenderWindow window;

    ParallaxBackground background1("../assets/backgrounds/ground-zaun.png", 150.0f, 530, 1, 0.6);
    ParallaxBackground background2("../assets/backgrounds/background-zaun.jpeg", 20.0f, -1700, 2, 2);

    Clock clock;

    game.init();
    game.initAnimations();
    auto startTime = chrono::steady_clock::now();
    auto waitTime = chrono::milliseconds(70);
    auto startAttTime = chrono::steady_clock::now();
    auto waitAttTime = chrono::milliseconds(30);

    while (game.window.isOpen()) {
        Time deltaTime = clock.restart();
        Event event;
        while (game.window.pollEvent(event)) {
            if (event.type == Event::Closed)
                cout << "Fermeture de la fenêtre." << endl;
                game.window.close();
        }
        game.Command();
        game.window.clear();
        auto nowTime = chrono::steady_clock::now();
        if (nowTime >= startTime + waitTime) {
            game.ekko_anim.x++;
            startTime = nowTime;
        }
        auto nowAttTime = chrono::steady_clock::now();
        if (nowAttTime >= startAttTime + waitAttTime) {
            game.ekko_anim_Attack.x++;
            if (game.ekkoStruct.ekko_anim_isAttacking) game.ekkoStruct.countAnimAttack++;
            if (game.ekkoStruct.countAnimAttack == 12) {
                game.ekkoStruct.ekko_anim_isAttacking = false;
                game.ekkoStruct.countAnimAttack = 0;
            }
            startAttTime = nowAttTime;
        }

        game.printWindow();

        background1.update(deltaTime.asSeconds());
        background2.update(deltaTime.asSeconds());

        background2.draw(window);
        background1.draw(window);

        game.window.display();
    }

    return 0;
}