#include <iostream>
#include "parallax.hpp"
#include "menu.hpp"
#include "Classes.hpp"

using namespace std;
using namespace sf;

Ekko Ekko_Class;
Marcus Marcus_Class;
Soldier Soldier_Class;

int mainGame() {

    ParallaxBackground background1("assets/backgrounds/ground-zaunV2.png", 150.0f, 630, 1.1, 1.1);
    ParallaxBackground background2("assets/backgrounds/background-zaun.jpeg", 20.0f, -1890, 2, 2);

    Clock clock;

    game.init();
    Ekko_Class.ekkoInitAnimations();
    Marcus_Class.marcusInitAnimations();
    Soldier_Class.soldierInitAnimations();
    Ekko_Class.bulletInit();
    Marcus_Class.marcusBulletInit();
    //Soldier_Class.soldierBulletInit();

    auto startTime = chrono::steady_clock::now();
    auto waitTime = chrono::milliseconds(70);
    auto startAttTime = chrono::steady_clock::now();
    auto waitAttTime = chrono::milliseconds(50);
    auto startReadyToAttackTime = chrono::steady_clock::now();
    auto waitReadyToAttackTime = chrono::seconds(1);

    auto M_startTime = chrono::steady_clock::now();
    auto M_waitTime = chrono::milliseconds(70);
    /*auto M_startAttTime = chrono::steady_clock::now();
    auto M_waitAttTime = chrono::milliseconds(50);
    auto M_startReadyToAttackTime = chrono::steady_clock::now();
    auto M_waitReadyToAttackTime = chrono::seconds(1);*/

    auto S_startTime = chrono::steady_clock::now();
    auto S_waitTime = chrono::milliseconds(90);
    auto S_startAttTime = chrono::steady_clock::now();
    auto S_waitAttTime = chrono::milliseconds(800);
    auto S_startReadyToAttackTime = chrono::steady_clock::now();
    auto S_waitReadyToAttackTime = chrono::seconds(1);


    while (game.window.isOpen()) {
        Time deltaTime = clock.restart();
        Event event;
        while (game.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                game.window.close(); // Fermer la fen�tre
        }


#pragma region Background
        background1.update(deltaTime.asSeconds());
        background2.update(deltaTime.asSeconds());

        background2.draw(game.window);
        background1.draw(game.window);

#pragma endregion Background

#pragma region Ekko

        Ekko_Class.ekkoCommand();
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
        if (Ekko_Class.ekko_S.ekko_anim_isAttacking) {
            auto nowAttTime = chrono::steady_clock::now();
            if (nowAttTime >= startAttTime + waitAttTime) {
                Ekko_Class.ekko_S.countAnimAtk++;
                Ekko_Class.ekko_anim_Auto_Attack.x++;
                if (Ekko_Class.ekko_S.countAnimAtk == 1) {
                    Ekko_Class.bullets.push_back(sf::CircleShape());
                    Ekko_Class.bullets.back().setFillColor(sf::Color::Transparent);
                    Ekko_Class.bullets.back().setRadius(10);
                    Ekko_Class.bullets.back().setPosition(Ekko_Class.ekko_Auto_Attack_sprite.getPosition().x + 128, Ekko_Class.ekko_Auto_Attack_sprite.getPosition().y + 32);
                }
                if (Ekko_Class.ekko_S.countAnimAtk == 9) {
                    Ekko_Class.ekko_S.countAnimAtk = 0;
                    Ekko_Class.ekko_S.ekko_anim_isAttacking = false;
                }
                startAttTime = nowAttTime;
            }
        }

        Ekko_Class.ekkoPrintWindow(game.window);

        for (int i = 0; i < Ekko_Class.bullets.size(); i++) {
            game.window.draw(Ekko_Class.bullets[i]);
            Ekko_Class.bullets[i].move(20, 0);
            Ekko_Class.ekko_Bullet_Auto_Attack_sprite.setPosition(Ekko_Class.bullets[i].getPosition().x - 30, Ekko_Class.bullets[i].getPosition().y - 6);
            game.window.draw(Ekko_Class.ekko_Bullet_Auto_Attack_sprite);
            Ekko_Class.ekko_Bullet_Auto_Attack_sprite.move(20, 0);
        }

#pragma endregion Ekko

#pragma region Marcus
        Marcus_Class.marcusDontExitFromScreen();

        /*auto M_nowTime = chrono::steady_clock::now();
        M_waitTime = chrono::milliseconds(70);
        if (M_nowTime >= M_startTime + M_waitTime) {
            Marcus_Class.marcus_anim.x++;
            M_startTime = M_nowTime;
        }*/
        /*if (Ekko_Class.ekko_S.ekko_anim_isAttacking) {
            auto nowAttTime = chrono::steady_clock::now();
            if (nowAttTime >= startAttTime + waitAttTime) {
                Ekko_Class.ekko_S.countAnimAtk++;
                Ekko_Class.ekko_anim_Auto_Attack.x++;
                if (Ekko_Class.ekko_S.countAnimAtk == 1) {
                    Ekko_Class.bullets.push_back(sf::CircleShape());
                    Ekko_Class.bullets.back().setFillColor(sf::Color::Transparent);
                    Ekko_Class.bullets.back().setRadius(10);
                    Ekko_Class.bullets.back().setPosition(Ekko_Class.ekko_Auto_Attack_sprite.getPosition().x + 128, Ekko_Class.ekko_Auto_Attack_sprite.getPosition().y + 32);
                }
                if (Ekko_Class.ekko_S.countAnimAtk == 9) {
                    Ekko_Class.ekko_S.countAnimAtk = 0;
                    Ekko_Class.ekko_S.ekko_anim_isAttacking = false;
                }
                startAttTime = nowAttTime;
            }
        }*/

        //Marcus_Class.marcusPrintWindow(game.window);

        /*for (int i = 0; i < Ekko_Class.bullets.size(); i++) {
            game.window.draw(Ekko_Class.bullets[i]);
            Ekko_Class.bullets[i].move(20, 0);
            Ekko_Class.ekko_Bullet_Auto_Attack_sprite.setPosition(Ekko_Class.bullets[i].getPosition().x - 30, Ekko_Class.bullets[i].getPosition().y - 6);
            game.window.draw(Ekko_Class.ekko_Bullet_Auto_Attack_sprite);
            Ekko_Class.ekko_Bullet_Auto_Attack_sprite.move(20, 0);
        }*/
#pragma endregion Marcus

        //Soldier_Class.soldierDontExitFromScreen();

        auto S_nowTime = chrono::steady_clock::now();

        if (S_nowTime >= S_startTime + S_waitTime) {
            Soldier_Class.soldier_anim.x++;
            Soldier_Class.soldier_S.countAnimAtk++;
            if (Soldier_Class.soldier_S.countAnimAtk == 2) {
                Soldier_Class.SoldierBullets.push_back(sf::CircleShape());
                Soldier_Class.SoldierBullets.back().setFillColor(sf::Color::Red);
                Soldier_Class.SoldierBullets.back().setRadius(10);
                Soldier_Class.SoldierBullets.back().setPosition(Soldier_Class.soldier_walk_sprite.getPosition().x, Soldier_Class.soldier_walk_sprite.getPosition().y + 80);
            }

            if (Soldier_Class.soldier_S.countAnimAtk == 10) {
                Soldier_Class.soldier_S.countAnimAtk = 0;
            }

            if (Soldier_Class.soldier_anim.x * 200 >= Soldier_Class.soldier_walk_texture.getSize().x + 200) // boucle qui permet de revenir a la premiere slide de l'anim
                Soldier_Class.soldier_anim.x = 2;
            S_startTime = S_nowTime;
        }

        Soldier_Class.soldierPrintWindow(game.window);

        for (int i = 0; i < Soldier_Class.SoldierBullets.size(); i++) {
            Soldier_Class.SoldierBullets[i].move(-30, 0);
            game.window.draw(Soldier_Class.SoldierBullets[i]);
             /*Soldier_Class.soldier_Bullet_Auto_Attack_sprite.setPosition(Soldier_Class.SoldierBullets[i].getPosition().x - 30, Soldier_Class.SoldierBullets[i].getPosition().y - 6);
             game.window.draw(Soldier_Class.soldier_Bullet_Auto_Attack_sprite);
             Soldier_Class.soldier_Bullet_Auto_Attack_sprite.move(-30, 0);*/
        }

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