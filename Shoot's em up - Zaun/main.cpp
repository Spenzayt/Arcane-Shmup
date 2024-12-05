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
    auto startTime = std::chrono::steady_clock::now();
    auto waitTime = std::chrono::milliseconds(70);
    auto startAttTime = std::chrono::steady_clock::now();
    auto waitAttTime = std::chrono::milliseconds(30);
    // Boucle principale
    while (game.window.isOpen()) {
        sf::Event event;
        while (game.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                game.window.close();
        }
        game.Command();
        game.window.clear();

        auto nowTime = std::chrono::steady_clock::now();
        if (nowTime >= startTime + waitTime) {
            game.ekko_anim.x++;
            startTime = nowTime;
        }
        auto nowAttTime = std::chrono::steady_clock::now();
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
        game.window.display();

    }
}