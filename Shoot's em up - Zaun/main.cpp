#include <SFML/Graphics.hpp>
#include <iostream>
#include "parallax.hpp"
#include "Classes.hpp"


using namespace std;
using namespace sf;

int main() {

    ParallaxBackground background1("assets/backgrounds/ground-zaun.png", 150.0f, 530, 1, 0.6);
    ParallaxBackground background2("assets/backgrounds/background-zaun.jpeg", 20.0f, -1700, 2, 2);

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
            if (event.type == sf::Event::Closed)
                game.window.close(); // Fermer la fenêtre
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
            if (game.ekko_S.ekko_anim_isAttacking) game.ekko_S.countAnimAtk++;
            if (game.ekko_S.countAnimAtk == 12) {
                game.ekko_S.ekko_anim_isAttacking = false;
                game.ekko_S.countAnimAtk = 0;
            }
            startAttTime = nowAttTime;
        }
#pragma region Background
        background1.update(deltaTime.asSeconds());
        background2.update(deltaTime.asSeconds());

        background2.draw(game.window);
        background1.draw(game.window);

#pragma endregion Background

        game.dontExitFromScreen();
        game.printWindow();
        game.window.display();
    }

    return 0;
}