#include <SFML/Graphics.hpp>
#include <iostream>
#include "parallax.hpp"
#include "menu.hpp"
#include "Classes.hpp"
#include "Class_Ekko.hpp"

using namespace std;
using namespace sf;

int mainGame() {

    ParallaxBackground background1("assets/backgrounds/ground-zaun.png", 150.0f, 410, 1, 1);
    ParallaxBackground background2("assets/backgrounds/background-zaun.jpeg", 20.0f, -1700, 2, 2);

    Clock clock;

    game.init();
    Ekko_Class.ekkoInitAnimations();
    auto startTime = chrono::steady_clock::now();
    auto waitTime = chrono::milliseconds(70);
    auto startAttTime = chrono::steady_clock::now();
    auto waitAttTime = chrono::milliseconds(30);

    while (game.window.isOpen()) {
        Time deltaTime = clock.restart();
        Event event;
        while (game.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                game.window.close(); // Fermer la fen�tre
        }
        Ekko_Class.ekkoCommand();
#pragma region Background
        background1.update(deltaTime.asSeconds());
        background2.update(deltaTime.asSeconds());

        background2.draw(game.window);
        background1.draw(game.window);

#pragma endregion Background
        Ekko_Class.ekkoDontExitFromScreen();
        auto nowTime = chrono::steady_clock::now();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) waitTime = chrono::milliseconds(20);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) waitTime = chrono::milliseconds(20);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) waitTime = chrono::milliseconds(20);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) waitTime = chrono::milliseconds(20);
        else {
            waitTime = chrono::milliseconds(70);
        }
        if (nowTime >= startTime + waitTime) {
            Ekko_Class.ekko_anim.x++;
            startTime = nowTime;
        }
        if (ekko_S.ekko_anim_isAttacking) {
            auto nowAttTime = chrono::steady_clock::now();
            if (nowAttTime >= startAttTime + waitAttTime) {
                ekko_S.countAnimAtk++;
                Ekko_Class.ekko_anim_Attack.x++;
                if (ekko_S.countAnimAtk == 12) {
                    ekko_S.countAnimAtk = 0;
                    ekko_S.ekko_anim_isAttacking = false;
                }
                startAttTime = nowAttTime;
            }
        }

        Ekko_Class.ekkoPrintWindow();
        game.window.display();
    }

    return 0;
}

int main() {
    Menu menu;
    menu.run_menu();
    if (menu.isPlaySelected()) {
        mainGame();
    }
    return EXIT_SUCCESS;
}