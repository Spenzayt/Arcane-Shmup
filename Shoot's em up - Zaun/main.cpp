#include <iostream>
#include "parallax.hpp"
#include "menu.hpp"
#include "Classes.hpp"
#include "hud.hpp"
#include "buff.hpp"
#include <SFML/Window.hpp>


using namespace std;
using namespace sf;

Ekko Ekko_Class;
Marcus Marcus_Class;
Soldier Soldier_Class;
MediumSoldier MediumSoldier_Class;
HardSoldier HardSoldier_Class;
Game game;

int attackCountS = 0;
std::vector<sf::Keyboard::Key> konamiCode = {
    sf::Keyboard::Up, sf::Keyboard::Up,
    sf::Keyboard::Down, sf::Keyboard::Down,
    sf::Keyboard::Left, sf::Keyboard::Right,
    sf::Keyboard::Left, sf::Keyboard::Right,
    sf::Keyboard::B, sf::Keyboard::A
}; 

std::vector<sf::Keyboard::Key> inputSequence;

bool konamiCodeActivated = false;

void checkKonamiCode() {
    if (inputSequence == konamiCode) {
        if (!konamiCodeActivated) {
            std::cout << "Konami Code active !" << std::endl;
            Ekko_Class.Ekko_invincibility = true;
            konamiCodeActivated = true;
        }
        else {
            std::cout << "Konami Code desactivated !" << std::endl;
            Ekko_Class.Ekko_invincibility = false;
            konamiCodeActivated = false;
        }
    }
}

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


    MediumSoldier_Class.mediumSoldierInitAnimations();
    MediumSoldier_Class.mediumSoldierBulletInit();

    HardSoldier_Class.soldierInitAnimations();
    HardSoldier_Class.soldierBulletInit();

    vector<Soldier> vec;
    /*for (int i = 0; i < 3; i++)
    {
        vec.emplace_back();
    }*/
    Soldier_Class.createSoldiers(4);
    HUD healthBar(100, 100, 3);

    int animationDelay = 20;
    int animationDelayAttack = 50;
    bool invincibilityTimer = false;

    BlueBuff blueBuff(sf::Vector2f(1000, 800));
    RedBuff redBuff(sf::Vector2f(1000, 1000));

    bool BlueBuffTimer = false;
    bool RedBuffTimer = false;

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
    auto M_startAttTime = chrono::steady_clock::now();
    auto M_waitAttTime = chrono::milliseconds(50);
    auto M_startReadyToAttackTime = chrono::steady_clock::now();
    auto M_waitReadyToAttackTime = chrono::seconds(1);

    auto S_startTime = chrono::steady_clock::now();
    auto S_waitTime = chrono::milliseconds(Soldier_Class.soldier_S.attackSpeed);
    auto S_startAttTime = chrono::steady_clock::now();
    auto S_waitAttTime = chrono::milliseconds(800);
    auto S_startDying = chrono::steady_clock::now();
    auto S_waitDying = chrono::seconds(3);

    auto startNewWave = chrono::steady_clock::now();
    auto waitNewWave = chrono::seconds(10);
    auto startNewWave2 = chrono::steady_clock::now();
    auto waitNewWave2 = chrono::seconds(2);
    auto S_startReadyToAttackTime = chrono::steady_clock::now();
    auto S_waitReadyToAttackTime = chrono::seconds(1);

    auto MS_startTime = chrono::steady_clock::now();
    auto MS_waitTime = chrono::milliseconds(MediumSoldier_Class.soldier_S.attackSpeed);
    auto MS_startAttTime = chrono::steady_clock::now();
    auto MS_waitAttTime = chrono::milliseconds(800);
    auto MS_startReadyToAttackTime = chrono::steady_clock::now();
    auto MS_waitReadyToAttackTime = chrono::seconds(1);

    auto HS_startTime = chrono::steady_clock::now();
    auto HS_waitTime = chrono::milliseconds(HardSoldier_Class.soldier_S.attackSpeed);
    auto HS_startAttTime = chrono::steady_clock::now();
    auto HS_waitAttTime = chrono::milliseconds(800);
    auto HS_startReadyToAttackTime = chrono::steady_clock::now();
    auto HS_waitReadyToAttackTime = chrono::seconds(1);

    auto BlueBuffStartTime = chrono::steady_clock::now();
    auto RedBuffStartTime = chrono::steady_clock::now();
#pragma endregion Clocks

    while (game.window.isOpen()) {
        Time deltaTime = clock.restart();
        Event event;
        while (game.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                game.window.close();
        }

         auto newWaveNowTime = chrono::steady_clock::now();
            if (newWaveNowTime >= startNewWave + waitNewWave) {
                for (int i = 0; i < 10; i++) {
                    Soldier_Class.createSoldiers(1);
                    startNewWave = newWaveNowTime;
                }
            }
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

#pragma endregion KonamiCode

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

                animationDelay = static_cast<int>(20.0f / Ekko_Class.Ekko_speed);

                animationDelayAttack = static_cast<int>(50.0f / Ekko_Class.Ekko_attackSpeed);
                auto waitAttTime = chrono::milliseconds(animationDelayAttack);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) waitTime = chrono::milliseconds(animationDelay);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) waitTime = chrono::milliseconds(animationDelay);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) waitTime = chrono::milliseconds(animationDelay);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) waitTime = chrono::milliseconds(animationDelay);
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
                    bool destroy = false;
                    Ekko_Class.bullets[i].move(20, 0);
                    game.window.draw(Ekko_Class.bullets[i]);
                    Ekko_Class.ekko_Bullet_Auto_Attack_sprite.setPosition(Ekko_Class.bullets[i].getPosition().x - 30, Ekko_Class.bullets[i].getPosition().y - 6);

                    for (auto& soldier : Soldier_Class.soldiers_vector) {
                        if (Ekko_Class.bullets[i].getGlobalBounds().intersects(soldier.soldier_walk_sprite.getGlobalBounds()) && soldier.getAlive()) {
                            soldier.losePV(1);
                            destroy = true;
                        }
                    }
                    if (destroy) /////////////////////////////////////////////////  REPRENDRE CETTE FONCTION POUR EVITER LES CRASH
                        Ekko_Class.bullets.erase(Ekko_Class.bullets.begin() + i);

                    for (int i = 0; i < Ekko_Class.bullets.size(); i++) {
                        game.window.draw(Ekko_Class.bullets[i]);
                        Ekko_Class.bullets[i].move(20 * Ekko_Class.Ekko_attackSpeed, 0);
                        Ekko_Class.ekko_Bullet_Auto_Attack_sprite.setPosition(Ekko_Class.bullets[i].getPosition().x - 30, Ekko_Class.bullets[i].getPosition().y - 6);

                        // Soldier
                        if (Ekko_Class.bullets[i].getGlobalBounds().intersects(Soldier_Class.soldier_walk_sprite.getGlobalBounds()) && Soldier_Class.getAlive()) {
                            Soldier_Class.losePV(1);
                            Ekko_Class.bullets.erase(Ekko_Class.bullets.begin() + i);
                        }

                        // Medium Soldier
                        else if (Ekko_Class.bullets[i].getGlobalBounds().intersects(MediumSoldier_Class.medium_soldier_walk_sprite.getGlobalBounds()) && MediumSoldier_Class.getAlive()) {
                            MediumSoldier_Class.losePV(1);
                            Ekko_Class.bullets.erase(Ekko_Class.bullets.begin() + i);
                        }

                        // Hard Soldier
                        else if (Ekko_Class.bullets[i].getGlobalBounds().intersects(HardSoldier_Class.soldier_walk_sprite.getGlobalBounds()) && HardSoldier_Class.getAlive()) {
                            HardSoldier_Class.losePV(1);
                            Ekko_Class.bullets.erase(Ekko_Class.bullets.begin() + i);
                        }

                        if (Ekko_Class.ekko_Bullet_Auto_Attack_sprite.getPosition().x >= 1850) {
                            Ekko_Class.bullets.erase(Ekko_Class.bullets.begin() + i);
                        }

                        Ekko_Class.ekko_Bullet_Auto_Attack_sprite.move(20 * Ekko_Class.Ekko_attackSpeed, 0);
                        game.window.draw(Ekko_Class.ekko_Bullet_Auto_Attack_sprite);
                    }
                }

                if (invincibilityTimer) {
                    auto now = chrono::steady_clock::now();
                    auto duration = chrono::duration_cast<chrono::seconds>(now - invincibilityStartTime).count();
                    if (duration > 2) {
                        Ekko_Class.Ekko_invincibility = false;
                        invincibilityTimer = false;
                    }
                }
            }

#pragma endregion Ekko

#pragma region Marcus
            //Marcus_Class.marcusDontExitFromScreen();

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

            /*Soldier_Class.soldier_anim_Bullet_Auto_Attack.x++;
            if (Soldier_Class.soldier_anim_Bullet_Auto_Attack.x * 32 >= Soldier_Class.soldier_Auto_Attack_texture.getSize().x) // boucle qui permet de revenir a la premiere slide de l'anim
                Soldier_Class.soldier_anim_Bullet_Auto_Attack.x = 0;*/
            for (auto& soldier : Soldier_Class.soldiers_vector) {
                if (!soldier.getAlive()) {
                    auto S_nowDying = chrono::steady_clock::now();
                    if (S_nowDying >= S_startDying + S_waitDying) {
                        soldier.soldier_walk_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));

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
                            }

                            if (soldier.getAlive()) {

                                auto S_nowTime = chrono::steady_clock::now();
                                if (S_nowTime >= S_startTime + S_waitTime) {
                                    Soldier_Class.soldier_anim.x++;
                                    attackCountS++;
                                    if (attackCountS == 2) {
                                        Soldier_Class.bulletCreation();
                                    }
                                    if (Soldier_Class.soldier_anim.x == 10) {
                                        attackCountS = 0;
                                    }
                                    S_startTime = S_nowTime;
                                }



                                auto S_nowAttTime = chrono::steady_clock::now();
                                if (S_nowAttTime >= S_startAttTime + S_waitAttTime) {

                                    S_startAttTime = S_nowAttTime;
                                }

                                soldier.soldier_walk_sprite.setTextureRect(sf::IntRect(Soldier_Class.soldier_anim.x * 200, 0, -200, 157));

                                if (Soldier_Class.soldier_anim.x * 200 >= Soldier_Class.soldier_walk_texture.getSize().x + 200) {
                                    Soldier_Class.soldier_anim.x = 2;
                                }

                                for (int i = 0; i < soldier.SoldierBullets.size(); i++) {
                                    soldier.SoldierBullets[i].move(-10 * soldier.soldier_S.bulletSpeed, 0);
                                    game.window.draw(soldier.SoldierBullets[i]);
                                    Soldier_Class.soldier_Bullet_Auto_Attack_sprite.setPosition(soldier.SoldierBullets[i].getPosition().x - 5, soldier.SoldierBullets[i].getPosition().y + 2);

                                    if (soldier.SoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_walk_sprite.getGlobalBounds())) {
                                        healthBar.updateLife(Ekko_Class.losePV(1));
                                        soldier.SoldierBullets.erase(soldier.SoldierBullets.begin() + i);

                                        if (!Ekko_Class.Ekko_invincibility) {
                                            healthBar.updateLife(Ekko_Class.losePV(1));
                                            Ekko_Class.Ekko_invincibility = true;
                                            invincibilityTimer = true;
                                            invincibilityStartTime = chrono::steady_clock::now();
                                        }
                                    }

                                    if (soldier.soldier_Bullet_Auto_Attack_sprite.getPosition().x >= 1850) {
                                        soldier.SoldierBullets.erase(soldier.SoldierBullets.begin() + i);
                                    }

                                    soldier.soldier_Bullet_Auto_Attack_sprite.move(-10, 0);
                                    game.window.draw(Soldier_Class.soldier_Bullet_Auto_Attack_sprite);
                                }
                            }
                            Soldier_Class.otherSoldiersSpawn(game.window);
                        }
                    }
                }
            }
#pragma endregion Soldier

#pragma region MediumSoldier


            if (MediumSoldier_Class.getAlive() == true) {
                MediumSoldier_Class.mediumSoldierDontExitFromScreen();

                auto MS_nowTime = chrono::steady_clock::now();

                if (MS_nowTime >= MS_startTime + MS_waitTime) {
                    MediumSoldier_Class.medium_soldier_anim.x++;
                    MediumSoldier_Class.soldier_S.countAnimAtk++;
                    if (MediumSoldier_Class.soldier_S.countAnimAtk == 2) {
                        for (int i = 0; i < 3; i++) {
                            MediumSoldier_Class.MediumSoldierBullets.push_back(sf::CircleShape());
                            MediumSoldier_Class.MediumSoldierBullets.back().setFillColor(sf::Color::Transparent);
                            MediumSoldier_Class.MediumSoldierBullets.back().setRadius(10);
                            MediumSoldier_Class.MediumSoldierBullets.back().setPosition(MediumSoldier_Class.medium_soldier_walk_sprite.getPosition().x, MediumSoldier_Class.medium_soldier_walk_sprite.getPosition().y + (60 + i * 20));
                        }
                    }

                    if (MediumSoldier_Class.medium_soldier_anim.x * 200 >= MediumSoldier_Class.medium_soldier_walk_texture.getSize().x + 200) {
                        MediumSoldier_Class.medium_soldier_anim.x = 2;
                        MediumSoldier_Class.soldier_S.countAnimAtk = 0;
                    }
                    MS_startTime = MS_nowTime;
                }

                MediumSoldier_Class.mediumSoldierPrintWindow(game.window);

            }

            for (int i = 0; i < MediumSoldier_Class.MediumSoldierBullets.size(); i++) {
                MediumSoldier_Class.MediumSoldierBullets[i].move(-10 * MediumSoldier_Class.soldier_S.bulletSpeed, 0);
                game.window.draw(MediumSoldier_Class.MediumSoldierBullets[i]);
                MediumSoldier_Class.medium_soldier_Bullet_Auto_Attack_sprite.setPosition(MediumSoldier_Class.MediumSoldierBullets[i].getPosition().x + 10, MediumSoldier_Class.MediumSoldierBullets[i].getPosition().y + 2);

                if (MediumSoldier_Class.MediumSoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_walk_sprite.getGlobalBounds())) {
                    MediumSoldier_Class.MediumSoldierBullets.erase(MediumSoldier_Class.MediumSoldierBullets.begin() + i);

                    if (!Ekko_Class.Ekko_invincibility) {
                        healthBar.updateLife(Ekko_Class.losePV(1));
                        Ekko_Class.Ekko_invincibility = true;
                        invincibilityTimer = true;
                        invincibilityStartTime = chrono::steady_clock::now();
                    }
                }

                if (MediumSoldier_Class.medium_soldier_Bullet_Auto_Attack_sprite.getPosition().x >= 1850) {
                    MediumSoldier_Class.MediumSoldierBullets.erase(MediumSoldier_Class.MediumSoldierBullets.begin() + i);
                }

                MediumSoldier_Class.medium_soldier_Bullet_Auto_Attack_sprite.move(-10, 0);
                game.window.draw(MediumSoldier_Class.medium_soldier_Bullet_Auto_Attack_sprite);

            }


#pragma endregion MediumSoldier

#pragma region HardSoldier

            if (HardSoldier_Class.getAlive() == true) {
                HardSoldier_Class.soldierDontExitFromScreen();

                auto HS_nowTime = chrono::steady_clock::now();

                if (HS_nowTime >= HS_startTime + HS_waitTime) {
                    HardSoldier_Class.soldier_anim.x++;
                    HardSoldier_Class.soldier_S.countAnimAtk++;
                    if (HardSoldier_Class.soldier_S.countAnimAtk == 2) {
                        HardSoldier_Class.SoldierBullets.push_back(sf::CircleShape());
                        HardSoldier_Class.SoldierBullets.back().setFillColor(sf::Color::Transparent);
                        HardSoldier_Class.SoldierBullets.back().setRadius(10);
                        HardSoldier_Class.SoldierBullets.back().setPosition(HardSoldier_Class.soldier_walk_sprite.getPosition().x, HardSoldier_Class.soldier_walk_sprite.getPosition().y + 80);
                    }

                    if (HardSoldier_Class.soldier_anim.x * 200 >= HardSoldier_Class.soldier_walk_texture.getSize().x + 200) {
                        HardSoldier_Class.soldier_anim.x = 2;
                        HardSoldier_Class.soldier_S.countAnimAtk = 0;
                    }
                    HS_startTime = HS_nowTime;
                }
                HardSoldier_Class.soldierPrintWindow(game.window);
            }

            for (int i = 0; i < HardSoldier_Class.SoldierBullets.size(); i++) {
                HardSoldier_Class.SoldierBullets[i].move(-10 * HardSoldier_Class.soldier_S.bulletSpeed, 0);
                game.window.draw(HardSoldier_Class.SoldierBullets[i]);
                HardSoldier_Class.soldier_Bullet_Auto_Attack_sprite.setPosition(HardSoldier_Class.SoldierBullets[i].getPosition().x + 10, HardSoldier_Class.SoldierBullets[i].getPosition().y + 2);

                if (HardSoldier_Class.SoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_walk_sprite.getGlobalBounds())) {
                    HardSoldier_Class.SoldierBullets.erase(HardSoldier_Class.SoldierBullets.begin() + i);

                    if (!Ekko_Class.Ekko_invincibility) {
                        healthBar.updateLife(Ekko_Class.losePV(1));
                        Ekko_Class.Ekko_invincibility = true;
                        invincibilityTimer = true;
                        invincibilityStartTime = chrono::steady_clock::now();
                    }
                }

                if (HardSoldier_Class.soldier_Bullet_Auto_Attack_sprite.getPosition().x >= 1850) {
                    HardSoldier_Class.SoldierBullets.erase(HardSoldier_Class.SoldierBullets.begin() + i);
                }

                HardSoldier_Class.soldier_Bullet_Auto_Attack_sprite.move(-10, 0);
                game.window.draw(HardSoldier_Class.soldier_Bullet_Auto_Attack_sprite);

            }
#pragma endregion HardSoldier

#pragma region Buff

            if (blueBuff.touchByThePlayer(Ekko_Class.ekko_walk_sprite)) {
                if (!blueBuff.BlueBuffActivated) {
                    std::cout << "Starting Blue Buff!" << std::endl;
                    blueBuff.BlueBuffActivated = true;
                    BlueBuffTimer = true;
                    BlueBuffStartTime = chrono::steady_clock::now();
                    Ekko_Class.Ekko_speed = 1.5;
                }
            }

            if (BlueBuffTimer) {
                auto now = chrono::steady_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(now - BlueBuffStartTime).count();
                if (duration > 10) {
                    blueBuff.BlueBuffActivated = false;
                    BlueBuffTimer = false;
                    std::cout << "Ending Blue Buff!" << std::endl;
                    Ekko_Class.Ekko_speed = 1.0f;
                }
            }

            if (redBuff.touchByThePlayer(Ekko_Class.ekko_walk_sprite)) {
                if (!redBuff.RedBuffActivated) {
                    std::cout << "Starting Red Buff!" << std::endl;
                    redBuff.RedBuffActivated = true;
                    RedBuffTimer = true;
                    RedBuffStartTime = chrono::steady_clock::now();
                    Ekko_Class.Ekko_attackSpeed = 2.0f;
                }
            }

            if (RedBuffTimer) {
                auto now = chrono::steady_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(now - RedBuffStartTime).count();
                if (duration > 10) {
                    redBuff.RedBuffActivated = false;
                    RedBuffTimer = false;
                    std::cout << "Ending Red Buff!" << std::endl;
                    Ekko_Class.Ekko_attackSpeed = 1.0f;
                }
            } 

        blueBuff.draw(game.window);
        redBuff.draw(game.window);

#pragma endregion Buff

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