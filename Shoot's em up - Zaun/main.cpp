#include <iostream>
#include "parallax.hpp"
#include "menu.hpp"
#include "Classes.hpp"
#include "hud.hpp"

using namespace std;
using namespace sf;

Ekko Ekko_Class;
Marcus Marcus_Class;
Soldier Soldier_Class;
Game game;


int mainGame() {
    ParallaxBackground background1("assets/backgrounds/ground-zaunV2.png", 150.0f, 630, 1.1, 1.1);
    ParallaxBackground background2("assets/backgrounds/background-zaun.jpeg", 20.0f, -1890, 2, 2);

    Clock clock;

    game.init();

    Ekko_Class.ekkoInitAnimations();
    Ekko_Class.bulletInit();
    Ekko_Class.initializeSpells();

    Marcus_Class.marcusInitAnimations();
    Marcus_Class.marcusBulletInit();

    Soldier_Class.soldierInitAnimations();
    Soldier_Class.soldierBulletInit();
    Soldier_Class.createSoldiers(5);

    HUD healthBar(100,100, 3);

    auto startTime = chrono::steady_clock::now();
    auto waitTime = chrono::milliseconds(70);
    auto startAttTime = chrono::steady_clock::now();
    auto waitAttTime = chrono::milliseconds(50);
    auto startReadyToAttackTime = chrono::steady_clock::now();
    auto waitReadyToAttackTime = chrono::seconds(1);
    auto startDashTime = chrono::steady_clock::now();
    auto waitDashTime = chrono::milliseconds(10);

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
        if (Ekko_Class.getAlive()) {
            Ekko_Class.ekkoCommand();
            Ekko_Class.ekkoDontExitFromScreen();
            Ekko_Class.updatePositionHistory();
            Ekko_Class.updateTeleport();

            int xHealth = Ekko_Class.ekko_walk_sprite.getPosition().x - 10;
            int yHeatlh = Ekko_Class.ekko_walk_sprite.getPosition().y - 15;
            healthBar.updatePosition(xHealth, yHeatlh);

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

            /*Ekko_Class.ekko_anim_Bullet_Auto_Attack.x++;
            if (Ekko_Class.ekko_anim_Bullet_Auto_Attack.x * 32 >= Ekko_Class.ekko_Auto_Attack_texture.getSize().x) // boucle qui permet de revenir a la premiere slide de l'anim
                Ekko_Class.ekko_anim_Bullet_Auto_Attack.x = 0;*/

            for (int i = 0; i < Ekko_Class.bullets.size(); i++) {
                game.window.draw(Ekko_Class.bullets[i]);
                Ekko_Class.bullets[i].move(20, 0);
                Ekko_Class.ekko_Bullet_Auto_Attack_sprite.setPosition(Ekko_Class.bullets[i].getPosition().x - 30, Ekko_Class.bullets[i].getPosition().y - 6);


                if (Ekko_Class.bullets[i].getGlobalBounds().intersects(Soldier_Class.soldier_walk_sprite.getGlobalBounds()) && Soldier_Class.getAlive()) {
                    Soldier_Class.losePV(1);
                    Ekko_Class.bullets.erase(Ekko_Class.bullets.begin() + i);
                }

                if (Ekko_Class.ekko_Bullet_Auto_Attack_sprite.getPosition().x >= 1850) {
                    Ekko_Class.bullets.erase(Ekko_Class.bullets.begin() + i);
                }


                Ekko_Class.ekko_Bullet_Auto_Attack_sprite.move(20, 0);
                game.window.draw(Ekko_Class.ekko_Bullet_Auto_Attack_sprite);
            }
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

#pragma region Soldier

        if (Soldier_Class.getAlive() == true) {
            //Soldier_Class.soldierDontExitFromScreen();

            auto S_nowTime = chrono::steady_clock::now();

            if (S_nowTime >= S_startTime + S_waitTime) {
                Soldier_Class.animationSoldier();
                S_startTime = S_nowTime;
            }

            Soldier_Class.otherSoldiersSpawn(game.window);

        }

        for (int i = 0; i < Soldier_Class.SoldierBullets.size(); i++) {
            Soldier_Class.SoldierBullets[i].move(-10, 0);
            game.window.draw(Soldier_Class.SoldierBullets[i]);
            Soldier_Class.soldier_Bullet_Auto_Attack_sprite.setPosition(Soldier_Class.SoldierBullets[i].getPosition().x + 10, Soldier_Class.SoldierBullets[i].getPosition().y + 2);

            if (Soldier_Class.SoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_walk_sprite.getGlobalBounds())) {
                healthBar.updateLife(Ekko_Class.losePV(1));
                Soldier_Class.SoldierBullets.erase(Soldier_Class.SoldierBullets.begin() + i);
            }

            if (Soldier_Class.soldier_Bullet_Auto_Attack_sprite.getPosition().x >= 1850) {
                Soldier_Class.SoldierBullets.erase(Soldier_Class.SoldierBullets.begin() + i);
            }

            Soldier_Class.soldier_Bullet_Auto_Attack_sprite.move(-10, 0);
            game.window.draw(Soldier_Class.soldier_Bullet_Auto_Attack_sprite);

        }


#pragma endregion Soldier
        healthBar.draw(game.window);
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