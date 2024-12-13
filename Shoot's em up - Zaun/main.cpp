#include <iostream>
#include "parallax.hpp"
#include "menu.hpp"
#include "Classes.hpp"
#include "hud.hpp"
#include <SFML/Window.hpp>


using namespace std;
using namespace sf;

Ekko ekko;
Marcus marcus;
Soldier soldier;
MediumSoldier mediumSoldier;
HardSoldier hardSoldier;
Game game;

std::vector<sf::Keyboard::Key> konamiCode = {
    sf::Keyboard::Up, sf::Keyboard::Up,
    sf::Keyboard::Down, sf::Keyboard::Down,
    sf::Keyboard::Left, sf::Keyboard::Right,
    sf::Keyboard::Left, sf::Keyboard::Right,
    sf::Keyboard::B, sf::Keyboard::A
}; 
std::vector<sf::Keyboard::Key> inputSequence;

void checkKonamiCode() {
    if (inputSequence == konamiCode) {
        std::cout << "Konami Code active !" << std::endl;
        ekko.Ekko_invincibility = true;
    }
}

int mainGame() {

    ParallaxBackground background1("assets/backgrounds/ground-zaunV2.png", 150.0f, 630, 1.1, 1.1);
    ParallaxBackground background2("assets/backgrounds/background-zaun.jpeg", 20.0f, -1890, 2, 2);

    Clock clock;

    game.init();
    ekko.ekkoInitAnimations();
    marcus.marcusInitAnimations();
    soldier.soldierInitAnimations();
    mediumSoldier.mediumSoldierInitAnimations();
    hardSoldier.soldierInitAnimations();
    ekko.bulletInit();
    ekko.initializeSpells();
    marcus.marcusBulletInit();
    soldier.soldierBulletInit();
    mediumSoldier.mediumSoldierBulletInit();
    hardSoldier.soldierBulletInit();
    game.addEnemies(1);
    HUD healthBar(100,100, 3);
    game.addEkko();
    int animationDelay = 20;
    bool invincibilityTimer = false;


#pragma region Clocks
    auto startTime = chrono::steady_clock::now();
    auto waitTime = chrono::milliseconds(70);
    auto startAttTime = chrono::steady_clock::now();
    auto waitAttTime = chrono::milliseconds(50);
    auto startReadyToAttackTime = chrono::steady_clock::now();
    auto waitReadyToAttackTime = chrono::seconds(1);
    auto startDashTime = chrono::steady_clock::now();
    auto waitDashTime = chrono::milliseconds(5);

    chrono::steady_clock::time_point invincibilityStartTime;

    auto M_startTime = chrono::steady_clock::now();
    auto M_waitTime = chrono::milliseconds(70);
    /*auto M_startAttTime = chrono::steady_clock::now();
    auto M_waitAttTime = chrono::milliseconds(50);
    auto M_startReadyToAttackTime = chrono::steady_clock::now();
    auto M_waitReadyToAttackTime = chrono::seconds(1);*/

    auto S_startTime = chrono::steady_clock::now();
    auto S_waitTime = chrono::milliseconds(soldier.soldier_S.attackSpeed);
    auto S_startAttTime = chrono::steady_clock::now();
    auto S_waitAttTime = chrono::milliseconds(800);
    auto S_startReadyToAttackTime = chrono::steady_clock::now();
    auto S_waitReadyToAttackTime = chrono::seconds(1);

    auto MS_startTime = chrono::steady_clock::now();
    auto MS_waitTime = chrono::milliseconds(mediumSoldier.soldier_S.attackSpeed);
    auto MS_startAttTime = chrono::steady_clock::now();
    auto MS_waitAttTime = chrono::milliseconds(800);
    auto MS_startReadyToAttackTime = chrono::steady_clock::now();
    auto MS_waitReadyToAttackTime = chrono::seconds(1);

    auto HS_startTime = chrono::steady_clock::now();
    auto HS_waitTime = chrono::milliseconds(hardSoldier.soldier_S.attackSpeed);
    auto HS_startAttTime = chrono::steady_clock::now();
    auto HS_waitAttTime = chrono::milliseconds(800);
    auto HS_startReadyToAttackTime = chrono::steady_clock::now();
    auto HS_waitReadyToAttackTime = chrono::seconds(1);

#pragma endregion Clocks

    while (game.window.isOpen()) {
        Time deltaTime = clock.restart();
        Event event;
        while (game.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                game.window.close();

#pragma region KonamiCode
            if (event.type == sf::Event::KeyPressed) {
                inputSequence.push_back(event.key.code);

                // Limiter la taille de la séquence à celle du Konami Code
                if (inputSequence.size() > konamiCode.size()) {
                    inputSequence.erase(inputSequence.begin());
                }

                // Vérifier si la séquence correspond au Konami Code
                checkKonamiCode();
            }
        }

#pragma endregion KonamiCode

#pragma region Background
        background1.update(deltaTime.asSeconds());
        background2.update(deltaTime.asSeconds());

        background2.draw(game.window);
        background1.draw(game.window);

#pragma endregion Background

#pragma region Ekko
        if (ekko.getAlive()) {
            ekko.ekkoCommand();
            ekko.ekkoDontExitFromScreen();
            ekko.updatePositionHistory();
            ekko.updateTeleport();

            int xHealth = ekko.ekko_walk_sprite.getPosition().x - 10;
            int yHeatlh = ekko.ekko_walk_sprite.getPosition().y - 15;
            healthBar.updatePosition(xHealth, yHeatlh);

            auto nowTime = chrono::steady_clock::now();

            animationDelay  = static_cast<int>(20.0f / ekko.Ekko_speed);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) waitTime = chrono::milliseconds(animationDelay);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) waitTime = chrono::milliseconds(animationDelay);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) waitTime = chrono::milliseconds(animationDelay);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) waitTime = chrono::milliseconds(animationDelay);
            else {
                waitTime = chrono::milliseconds(70);
            }
            if (nowTime >= startTime + waitTime) {
                ekko.ekko_anim.x++;
                startTime = nowTime;
            }
            if (ekko.ekko_S.ekko_anim_isAttacking) {
                auto nowAttTime = chrono::steady_clock::now();
                if (nowAttTime >= startAttTime + waitAttTime) {
                    ekko.ekko_S.countAnimAtk++;
                    ekko.ekko_anim_Auto_Attack.x++;
                    if (ekko.ekko_S.countAnimAtk == 1) {
                        ekko.bullets.push_back(sf::CircleShape());
                        ekko.bullets.back().setFillColor(sf::Color::Transparent);
                        ekko.bullets.back().setRadius(10);
                        ekko.bullets.back().setPosition(ekko.ekko_Auto_Attack_sprite.getPosition().x + 128, ekko.ekko_Auto_Attack_sprite.getPosition().y + 32);
                    }
                    if (ekko.ekko_S.countAnimAtk == 9) {
                        ekko.ekko_S.countAnimAtk = 0;
                        ekko.ekko_S.ekko_anim_isAttacking = false;
                    }
                    startAttTime = nowAttTime;
                }
            }

            ekko.ekkoPrintWindow(game.window);

            /*Ekko_Class.ekko_anim_Bullet_Auto_Attack.x++;
            if (Ekko_Class.ekko_anim_Bullet_Auto_Attack.x * 32 >= Ekko_Class.ekko_Auto_Attack_texture.getSize().x) // boucle qui permet de revenir a la premiere slide de l'anim
                Ekko_Class.ekko_anim_Bullet_Auto_Attack.x = 0;*/

            for (int i = 0; i < ekko.bullets.size(); i++) {
                game.window.draw(ekko.bullets[i]);
                ekko.bullets[i].move(20, 0);
                ekko.ekko_Bullet_Auto_Attack_sprite.setPosition(ekko.bullets[i].getPosition().x - 30, ekko.bullets[i].getPosition().y - 6);

                // Soldier
                if (ekko.bullets[i].getGlobalBounds().intersects(soldier.soldier_walk_sprite.getGlobalBounds()) && soldier.getAlive()) {
                    soldier.losePV(1);
                    ekko.bullets.erase(ekko.bullets.begin() + i);
                }

                // Medium Soldier
                else if (ekko.bullets[i].getGlobalBounds().intersects(mediumSoldier.medium_soldier_walk_sprite.getGlobalBounds()) && mediumSoldier.getAlive()) {
                    mediumSoldier.losePV(1);
                    ekko.bullets.erase(ekko.bullets.begin() + i);
                }

                // Hard Soldier
                else if (ekko.bullets[i].getGlobalBounds().intersects(hardSoldier.soldier_walk_sprite.getGlobalBounds()) && hardSoldier.getAlive()) {
                    hardSoldier.losePV(1);
                    ekko.bullets.erase(ekko.bullets.begin() + i);
                }

                if (ekko.ekko_Bullet_Auto_Attack_sprite.getPosition().x >= 1850) {
                    ekko.bullets.erase(ekko.bullets.begin() + i);
                }

                ekko.ekko_Bullet_Auto_Attack_sprite.move(20, 0);
                game.window.draw(ekko.ekko_Bullet_Auto_Attack_sprite);
            }
        }

#pragma endregion Ekko

#pragma region Marcus
        marcus.marcusDontExitFromScreen();

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

        if (soldier.getAlive() == true) {
            soldier.soldierDontExitFromScreen();

            auto S_nowTime = chrono::steady_clock::now();

            if (S_nowTime >= S_startTime + S_waitTime) {
                soldier.soldier_anim.x++;
                soldier.soldier_S.countAnimAtk++;
                if (soldier.soldier_S.countAnimAtk == 2) {
                    soldier.SoldierBullets.push_back(sf::CircleShape());
                    soldier.SoldierBullets.back().setFillColor(sf::Color::Transparent);
                    soldier.SoldierBullets.back().setRadius(10);
                    soldier.SoldierBullets.back().setPosition(soldier.soldier_walk_sprite.getPosition().x, soldier.soldier_walk_sprite.getPosition().y + 80);
                }

                if (soldier.soldier_anim.x * 200 >= soldier.soldier_walk_texture.getSize().x + 200) {
                    soldier.soldier_anim.x = 2;
                    soldier.soldier_S.countAnimAtk = 0;
                }
                S_startTime = S_nowTime;
            }

            soldier.soldierPrintWindow(game.window);

        }

        /*Soldier_Class.soldier_anim_Bullet_Auto_Attack.x++;
        if (Soldier_Class.soldier_anim_Bullet_Auto_Attack.x * 32 >= Soldier_Class.soldier_Auto_Attack_texture.getSize().x) // boucle qui permet de revenir a la premiere slide de l'anim
            Soldier_Class.soldier_anim_Bullet_Auto_Attack.x = 0;*/

        for (int i = 0; i < soldier.SoldierBullets.size(); i++) {
            soldier.SoldierBullets[i].move(-10 * soldier.soldier_S.bulletSpeed, 0);
            game.window.draw(soldier.SoldierBullets[i]);
            soldier.soldier_Bullet_Auto_Attack_sprite.setPosition(soldier.SoldierBullets[i].getPosition().x + 10, soldier.SoldierBullets[i].getPosition().y + 2);

            if (soldier.SoldierBullets[i].getGlobalBounds().intersects(ekko.ekko_walk_sprite.getGlobalBounds())) {
                soldier.SoldierBullets.erase(soldier.SoldierBullets.begin() + i);

                if (!ekko.Ekko_invincibility) {
                    healthBar.updateLife(ekko.losePV(1));
                    ekko.Ekko_invincibility = true;
                    invincibilityTimer = true;
                    invincibilityStartTime = chrono::steady_clock::now();
                }
            }

            if (invincibilityTimer) {
                auto now = chrono::steady_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(now - invincibilityStartTime).count();
                if (duration > 2) {
                    ekko.Ekko_invincibility = false;
                    invincibilityTimer = false;
                }
            }

            if (soldier.soldier_Bullet_Auto_Attack_sprite.getPosition().x >= 1850) {
                soldier.SoldierBullets.erase(soldier.SoldierBullets.begin() + i);
            }

            soldier.soldier_Bullet_Auto_Attack_sprite.move(-10, 0);
            game.window.draw(soldier.soldier_Bullet_Auto_Attack_sprite);

        }
#pragma endregion Soldier

#pragma region MediumSoldier

        if (mediumSoldier.getAlive() == true) {
            mediumSoldier.mediumSoldierDontExitFromScreen();

            auto MS_nowTime = chrono::steady_clock::now();

            if (MS_nowTime >= MS_startTime + MS_waitTime) {
                mediumSoldier.medium_soldier_anim.x++;
                mediumSoldier.soldier_S.countAnimAtk++;
                if (mediumSoldier.soldier_S.countAnimAtk == 2) {
                    for (int i = 0; i < 3; i++) {
                        mediumSoldier.MediumSoldierBullets.push_back(sf::CircleShape());
                        mediumSoldier.MediumSoldierBullets.back().setFillColor(sf::Color::Transparent);
                        mediumSoldier.MediumSoldierBullets.back().setRadius(10);
                        mediumSoldier.MediumSoldierBullets.back().setPosition(mediumSoldier.medium_soldier_walk_sprite.getPosition().x, mediumSoldier.medium_soldier_walk_sprite.getPosition().y + (60 + i * 20));
                    }
                }

                if (mediumSoldier.medium_soldier_anim.x * 200 >= mediumSoldier.medium_soldier_walk_texture.getSize().x + 200) {
                    mediumSoldier.medium_soldier_anim.x = 2;
                    mediumSoldier.soldier_S.countAnimAtk = 0;
                }
                MS_startTime = MS_nowTime;
            }

            mediumSoldier.mediumSoldierPrintWindow(game.window);

        }

        for (int i = 0; i < mediumSoldier.MediumSoldierBullets.size(); i++) {
            mediumSoldier.MediumSoldierBullets[i].move(-10 * mediumSoldier.soldier_S.bulletSpeed, 0);
            game.window.draw(mediumSoldier.MediumSoldierBullets[i]);
            mediumSoldier.medium_soldier_Bullet_Auto_Attack_sprite.setPosition(mediumSoldier.MediumSoldierBullets[i].getPosition().x + 10, mediumSoldier.MediumSoldierBullets[i].getPosition().y + 2);

            if (mediumSoldier.MediumSoldierBullets[i].getGlobalBounds().intersects(ekko.ekko_walk_sprite.getGlobalBounds())) {
                mediumSoldier.MediumSoldierBullets.erase(mediumSoldier.MediumSoldierBullets.begin() + i);

                if (!ekko.Ekko_invincibility) {
                    healthBar.updateLife(ekko.losePV(1));
                    ekko.Ekko_invincibility = true;
                    invincibilityTimer = true;
                    invincibilityStartTime = chrono::steady_clock::now();
                }
            }

            if (invincibilityTimer) {
                auto now = chrono::steady_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(now - invincibilityStartTime).count();
                if (duration > 2) {
                    ekko.Ekko_invincibility = false;
                    invincibilityTimer = false;
                }
            }

            if (mediumSoldier.medium_soldier_Bullet_Auto_Attack_sprite.getPosition().x >= 1850) {
                mediumSoldier.MediumSoldierBullets.erase(mediumSoldier.MediumSoldierBullets.begin() + i);
            }

            mediumSoldier.medium_soldier_Bullet_Auto_Attack_sprite.move(-10, 0);
            game.window.draw(mediumSoldier.medium_soldier_Bullet_Auto_Attack_sprite);

        }


#pragma endregion MediumSoldier

#pragma region HardSoldier

        if (hardSoldier.getAlive() == true) {
            hardSoldier.soldierDontExitFromScreen();

            auto HS_nowTime = chrono::steady_clock::now();

            if (HS_nowTime >= HS_startTime + HS_waitTime) {
                hardSoldier.soldier_anim.x++;
                hardSoldier.soldier_S.countAnimAtk++;
                if (hardSoldier.soldier_S.countAnimAtk == 2) {
                    hardSoldier.SoldierBullets.push_back(sf::CircleShape());
                    hardSoldier.SoldierBullets.back().setFillColor(sf::Color::Transparent);
                    hardSoldier.SoldierBullets.back().setRadius(10);
                    hardSoldier.SoldierBullets.back().setPosition(hardSoldier.soldier_walk_sprite.getPosition().x, hardSoldier.soldier_walk_sprite.getPosition().y + 80);
                }

                if (hardSoldier.soldier_anim.x * 200 >= hardSoldier.soldier_walk_texture.getSize().x + 200) {
                    hardSoldier.soldier_anim.x = 2;
                    hardSoldier.soldier_S.countAnimAtk = 0;
                }
                HS_startTime = HS_nowTime;
            }

            hardSoldier.soldierPrintWindow(game.window);

        }

        for (int i = 0; i < hardSoldier.SoldierBullets.size(); i++) {
            hardSoldier.SoldierBullets[i].move(-10 * hardSoldier.soldier_S.bulletSpeed, 0);
            game.window.draw(hardSoldier.SoldierBullets[i]);
            hardSoldier.soldier_Bullet_Auto_Attack_sprite.setPosition(hardSoldier.SoldierBullets[i].getPosition().x + 10, hardSoldier.SoldierBullets[i].getPosition().y + 2);

            if (hardSoldier.SoldierBullets[i].getGlobalBounds().intersects(ekko.ekko_walk_sprite.getGlobalBounds())) {
                hardSoldier.SoldierBullets.erase(hardSoldier.SoldierBullets.begin() + i);

                if (!ekko.Ekko_invincibility) {
                    healthBar.updateLife(ekko.losePV(1));
                    ekko.Ekko_invincibility = true;
                    invincibilityTimer = true;
                    invincibilityStartTime = chrono::steady_clock::now();
                }
            }

            if (invincibilityTimer) {
                auto now = chrono::steady_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(now - invincibilityStartTime).count();
                if (duration > 2) {
                    ekko.Ekko_invincibility = false;
                    invincibilityTimer = false;
                }
            }

            if (hardSoldier.soldier_Bullet_Auto_Attack_sprite.getPosition().x >= 1850) {
                hardSoldier.SoldierBullets.erase(hardSoldier.SoldierBullets.begin() + i);
            }

            hardSoldier.soldier_Bullet_Auto_Attack_sprite.move(-10, 0);
            game.window.draw(hardSoldier.soldier_Bullet_Auto_Attack_sprite);

        }
#pragma endregion HardSoldier


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