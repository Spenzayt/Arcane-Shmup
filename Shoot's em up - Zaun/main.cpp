#include <iostream>
#include "parallax.hpp"
#include <SFML/Graphics.hpp>
#include "Classes.hpp"
#include "hud.hpp"
#include "buff.hpp"
#include <SFML/Window.hpp>
#include <string>

Game game;
Menu menu;

void Wave(int NbOfEasySoldiers, int NbOfMediumSoldiers, int NbOfHardSoldiers) {
    Soldier_Class.createSoldiers(NbOfEasySoldiers);
    MediumSoldier_Class.createSoldiers(NbOfMediumSoldiers);
    HardSoldier_Class.createSoldiers(NbOfHardSoldiers);
}

int mainGame() {
    cout << "Easy : " << game.NbEasySoldier << std::endl;
    cout << "Medium : " << game.NbMediumSoldier << std::endl;
    cout << "Hard : " << game.NbHardSoldier << std::endl;
    cout << "Waves : " << game.MaxWaves << std::endl;

    ParallaxBackground background1("assets/backgrounds/ground-zaunV2.png", 150.0f, 630, 1.1, 1.1);
    ParallaxBackground background2("assets/backgrounds/background-zaun.jpeg", 20.0f, -1890, 2, 2);

    Clock clock;

    Ekko_Class.ekkoInitAnimations();
    Ekko_Class.bulletInit();
    Ekko_Class.initializeSpells();

    //Marcus_Class.marcusInitAnimations();
    //Marcus_Class.marcusBulletInit();

    Soldier_Class.soldierInitAnimations();
    Soldier_Class.soldierBulletInit();

    MediumSoldier_Class.mediumSoldierInitAnimations();
    MediumSoldier_Class.mediumSoldierBulletInit();

    HardSoldier_Class.hardSoldierInitAnimations();
    HardSoldier_Class.hardSoldierBulletInit();

    Wave(game.NbEasySoldier, game.NbMediumSoldier, game.NbHardSoldier);

    HUD healthBar(100, 100, 3);

    int animationDelay = 20;
    int animationDelayAttack = 50;

    bool invincibilityTimer = false;

    BlueBuff blueBuff(sf::Vector2f(1000, 800));
    RedBuff redBuff(sf::Vector2f(1000, 1000));

    bool BlueBuffTimer = false;
    bool RedBuffTimer = false;

#pragma region Clocks

    animationDelay = static_cast<int>(20.0f / Ekko_Class.Ekko_speed);
    animationDelayAttack = static_cast<int>(50.0f / Ekko_Class.Ekko_attackSpeed);

    auto startTime = chrono::steady_clock::now();
    auto waitTime = chrono::milliseconds(70);
    auto startAttTime = chrono::steady_clock::now();
    auto waitAttTime = chrono::milliseconds(animationDelayAttack);
    auto startReadyToAttackTime = chrono::steady_clock::now();
    auto waitReadyToAttackTime = chrono::seconds(1);
    auto startDashTime = chrono::steady_clock::now();
    auto waitDashTime = chrono::milliseconds(5);
    
    auto startHitTime = chrono::steady_clock::now();
    auto waitHitTime = chrono::milliseconds(160);

    chrono::steady_clock::time_point invincibilityStartTime;
    chrono::steady_clock::time_point SlowZoneStartTime;

    auto M_startTime = chrono::steady_clock::now();
    auto M_waitTime = chrono::milliseconds(70);
    auto M_startAttTime = chrono::steady_clock::now();
    auto M_waitAttTime = chrono::milliseconds(50);
    auto M_startReadyToAttackTime = chrono::steady_clock::now();
    auto M_waitReadyToAttackTime = chrono::seconds(1);

    auto S_startTime = chrono::steady_clock::now();
    auto S_waitTime = chrono::milliseconds(Soldier_Class.attackSpeed);
    auto S_startAttTime = chrono::steady_clock::now();
    auto S_waitAttTime = chrono::milliseconds(800);
    auto S_startDying = chrono::steady_clock::now();
    auto S_waitDying = chrono::seconds(3);
    auto S_startReadyToAttackTime = chrono::steady_clock::now();
    auto S_waitReadyToAttackTime = chrono::seconds(1);

    auto startNewWave = chrono::steady_clock::now();
    auto waitNewWave = chrono::seconds(4);
    auto startNewWave2 = chrono::steady_clock::now();
    auto waitNewWave2 = chrono::seconds(2);


    auto MS_startTime = chrono::steady_clock::now();
    auto MS_waitTime = chrono::milliseconds(MediumSoldier_Class.attackSpeed);
    auto MS_startAttTime = chrono::steady_clock::now();
    auto MS_waitAttTime = chrono::milliseconds(800);
    auto MS_startDying = chrono::steady_clock::now();
    auto MS_waitDying = chrono::seconds(3);
    auto MS_startReadyToAttackTime = chrono::steady_clock::now();
    auto MS_waitReadyToAttackTime = chrono::seconds(1);

    auto HS_startTime = chrono::steady_clock::now();
    auto HS_waitTime = chrono::milliseconds(HardSoldier_Class.attackSpeed);
    auto HS_startAttTime = chrono::steady_clock::now();
    auto HS_waitAttTime = chrono::milliseconds(800);
    auto HS_startDying = chrono::steady_clock::now();
    auto HS_waitDying = chrono::seconds(3);
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

#pragma region KonamiCode
           if (event.type == sf::Event::KeyPressed) {
               game.inputSequence.push_back(event.key.code);

                // Limiter la taille de la séquence à celle du Konami Code
              if (game.inputSequence.size() > game.konamiCode.size()) {
                  game.inputSequence.erase(game.inputSequence.begin());
                }

                // Vérifier si la séquence correspond au Konami Code
                game.checkKonamiCode();
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
        if (Ekko_Class.getAlive()) {
            Ekko_Class.ekkoCommand();
            Ekko_Class.ekkoDontExitFromScreen();
            Ekko_Class.updatePositionHistory();
            Ekko_Class.updateSpells();

            int xHealth = Ekko_Class.ekko_walk_sprite.getPosition().x - 10;
            int yHeatlh = Ekko_Class.ekko_walk_sprite.getPosition().y - 15;
            healthBar.updatePosition(xHealth, yHeatlh);

            auto nowTime = chrono::steady_clock::now();
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
            if (Ekko_Class.Ekko_invincibility) {
                auto nowHitTime = chrono::steady_clock::now();
                if (nowHitTime >= startHitTime + waitHitTime) {
                    Ekko_Class.ekko_walk_sprite.setColor(sf::Color::Transparent);
                }
                if (nowHitTime >= startHitTime + waitHitTime + chrono::milliseconds(160)) {
                    Ekko_Class.ekko_walk_sprite.setColor(sf::Color::White);
                    startHitTime = nowHitTime;
                }
            }
            if (!Ekko_Class.Ekko_invincibility && !blueBuff.BlueBuffActivated && !redBuff.RedBuffActivated) {
                Ekko_Class.ekko_walk_sprite.setColor(sf::Color::White);
                Ekko_Class.ekko_Auto_Attack_sprite.setColor(sf::Color::White);
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
            healthBar.draw(game.window);

            /*Ekko_Class.ekko_anim_Bullet_Auto_Attack.x++;
            if (Ekko_Class.ekko_anim_Bullet_Auto_Attack.x * 32 >= Ekko_Class.ekko_Auto_Attack_texture.getSize().x) // boucle qui permet de revenir a la premiere slide de l'anim
                Ekko_Class.ekko_anim_Bullet_Auto_Attack.x = 0;*/

            for (int i = 0; i < Ekko_Class.bullets.size(); i++) {
                bool destroy = false;
                game.window.draw(Ekko_Class.bullets[i]);
                Ekko_Class.bullets[i].move(20 * Ekko_Class.Ekko_attackSpeed, 0);
                Ekko_Class.ekko_Bullet_Auto_Attack_sprite.setPosition(Ekko_Class.bullets[i].getPosition().x - 30, Ekko_Class.bullets[i].getPosition().y - 6);

                //Soldier
                for (auto& soldier : Soldier_Class.soldiers_vector) {
                    if (Ekko_Class.bullets[i].getGlobalBounds().intersects(soldier.soldier_walk_sprite.getGlobalBounds()) && soldier.getAlive()) {
                        soldier.losePV(1);
                        destroy = true;
                    }
                }
                //MediumSoldier
                for (auto& mediumSoldier : MediumSoldier_Class.mediumSoldiers_vector) {
                    if (Ekko_Class.bullets[i].getGlobalBounds().intersects(mediumSoldier.medium_soldier_walk_sprite.getGlobalBounds()) && mediumSoldier.getAlive()) {
                        mediumSoldier.losePV(1);
                        destroy = true;
                    }
                }
                //HardSoldier
                for (auto& hardSoldier : HardSoldier_Class.hardSoldiers_vector) {
                    if (Ekko_Class.bullets[i].getGlobalBounds().intersects(hardSoldier.hard_soldier_walk_sprite.getGlobalBounds()) && hardSoldier.getAlive()) {
                        hardSoldier.losePV(1);
                        destroy = true;
                    }
                }
                if (destroy) 
                    Ekko_Class.bullets.erase(Ekko_Class.bullets.begin() + i);

                /*if (Ekko_Class.ekko_Bullet_Auto_Attack_sprite.getPosition().x >= 1850) {
                    Ekko_Class.bullets.erase(Ekko_Class.bullets.begin() + i);
                }*/

                Ekko_Class.ekko_Bullet_Auto_Attack_sprite.move(20 * Ekko_Class.Ekko_attackSpeed, 0);
                game.window.draw(Ekko_Class.ekko_Bullet_Auto_Attack_sprite);
            }

            if (invincibilityTimer) {
                auto now = chrono::steady_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(now - invincibilityStartTime).count();
                if (duration > 1) {
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
                }
            }
            if (soldier.getAlive()) {
                auto S_nowTime = chrono::steady_clock::now();
                if (S_nowTime >= S_startTime + S_waitTime) {
                    Soldier_Class.soldier_anim.x++;
                    Soldier_Class.attackCountSoldier++;
                    Soldier_Class.reload = false;
                    if (Soldier_Class.attackCountSoldier == 2) {
                        Soldier_Class.bulletCreation();
                        Soldier_Class.countBulletsSoldier++;
                    }
                    if (Soldier_Class.soldier_anim.x == 10) {
                        Soldier_Class.attackCountSoldier = 0;
                    }
                    if (Soldier_Class.countBulletsSoldier == 10) {
                        Soldier_Class.reload = true;
                    }
                    if (Soldier_Class.reload == true) {
                        S_waitTime = chrono::seconds(1);
                        Soldier_Class.countBulletsSoldier = 0;
                    }
                    if (Soldier_Class.reload == false) {
                        S_waitTime = chrono::milliseconds(Soldier_Class.attackSpeed);
                    }
                    S_startTime = S_nowTime;
                }

                soldier.soldier_walk_sprite.setTextureRect(sf::IntRect(Soldier_Class.soldier_anim.x * 200, 0, -200, 157));

                if (Soldier_Class.soldier_anim.x * 200 >= Soldier_Class.soldier_walk_texture.getSize().x + 200) {
                    Soldier_Class.soldier_anim.x = 2;
                }

                for (int i = 0; i < soldier.SoldierBullets.size(); i++) {
                    if (soldier.SoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_SlowZone_sprite.getGlobalBounds()) && Ekko_Class.getAlive() && Ekko_Class.ekko_S.SlowZone) {
                        soldier.bulletSpeed = 0.2f;
                    }

                    if (!soldier.SoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_SlowZone_sprite.getGlobalBounds()) && Ekko_Class.getAlive()) {
                        soldier.bulletSpeed = 1.0f;
                    }

                    soldier.SoldierBullets[i].move(-10 * soldier.bulletSpeed, 0);
                    game.window.draw(soldier.SoldierBullets[i]);
                    Soldier_Class.soldier_Bullet_Auto_Attack_sprite.setPosition(soldier.SoldierBullets[i].getPosition().x - 5, soldier.SoldierBullets[i].getPosition().y + 2);

                    if (soldier.SoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_walk_sprite.getGlobalBounds()) && !Ekko_Class.Ekko_invincibility && Ekko_Class.getAlive()) {
                        healthBar.updateLife(Ekko_Class.losePV(1));
                        Ekko_Class.Ekko_invincibility = true;
                        invincibilityTimer = true;
                        invincibilityStartTime = chrono::steady_clock::now();
                        soldier.SoldierBullets.erase(soldier.SoldierBullets.begin() + i);
                    }

                    /*if (soldier.SoldierBullets[i].getGlobalBounds().intersects(game.window.getSize().x) {
                        soldier.SoldierBullets.erase(soldier.SoldierBullets.begin() + i);
                    }*/ // Ca marche pas mais tu capte

                    // pourquoi il détruit tout ce tdc je comprends pas je crois que le sprite se détruit pas jsp

                    soldier.soldier_Bullet_Auto_Attack_sprite.move(-10, 0);
                    game.window.draw(Soldier_Class.soldier_Bullet_Auto_Attack_sprite);
                }
            }
            Soldier_Class.soldierPrintWindow(game.window);
        }
#pragma endregion Soldier

#pragma region MediumSoldier
        for (auto& mediumSoldier : MediumSoldier_Class.mediumSoldiers_vector) {
            if (!mediumSoldier.getAlive()) {
                auto MS_nowDying = chrono::steady_clock::now();
                if (MS_nowDying >= MS_startDying + MS_waitDying) {
                    mediumSoldier.medium_soldier_walk_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
                }
            }
            if (mediumSoldier.getAlive()) {

                auto MS_nowTime = chrono::steady_clock::now();

                if (MS_nowTime >= MS_startTime + MS_waitTime) {
                    MediumSoldier_Class.medium_soldier_anim.x++;
                    MediumSoldier_Class.attackCountMediumSoldier++;
                    MediumSoldier_Class.reload = false;
                    if (MediumSoldier_Class.attackCountMediumSoldier == 2) {
                        MediumSoldier_Class.bulletCreation();
                        MediumSoldier_Class.countBulletsMediumSoldier++;
                    }
                    if (MediumSoldier_Class.medium_soldier_anim.x == 10) {
                        MediumSoldier_Class.attackCountMediumSoldier = 0;
                    }
                    if (MediumSoldier_Class.countBulletsMediumSoldier == 10) {
                        MediumSoldier_Class.reload = true;
                    }
                    if (MediumSoldier_Class.reload == true) {
                        MS_waitTime = chrono::seconds(1);
                        MediumSoldier_Class.countBulletsMediumSoldier = 0;
                    }
                    if (MediumSoldier_Class.reload == false) {
                        MS_waitTime = chrono::milliseconds(MediumSoldier_Class.attackSpeed);
                    }
                    MS_startTime = MS_nowTime;
                }

                mediumSoldier.medium_soldier_walk_sprite.setTextureRect(sf::IntRect(MediumSoldier_Class.medium_soldier_anim.x * 200, 0, -200, 157));

                if (MediumSoldier_Class.medium_soldier_anim.x * 200 >= MediumSoldier_Class.medium_soldier_walk_texture.getSize().x + 200) {
                    MediumSoldier_Class.medium_soldier_anim.x = 2;
                }

                for (int i = 0; i < mediumSoldier.MediumSoldierBullets.size(); i++) {
                    mediumSoldier.MediumSoldierBullets[i].move(-10 * mediumSoldier.bulletSpeed, 0);
                    game.window.draw(mediumSoldier.MediumSoldierBullets[i]);
                    MediumSoldier_Class.medium_soldier_Bullet_Auto_Attack_sprite.setPosition(mediumSoldier.MediumSoldierBullets[i].getPosition().x +10, mediumSoldier.MediumSoldierBullets[i].getPosition().y + 2);

                    if (mediumSoldier.MediumSoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_walk_sprite.getGlobalBounds()) && !Ekko_Class.Ekko_invincibility && Ekko_Class.getAlive()) {
                        healthBar.updateLife(Ekko_Class.losePV(1));
                        Ekko_Class.Ekko_invincibility = true;
                        invincibilityTimer = true;
                        invincibilityStartTime = chrono::steady_clock::now();
                        mediumSoldier.MediumSoldierBullets.erase(mediumSoldier.MediumSoldierBullets.begin() + i);
                    }

                    /*if (mediumSoldier.medium_soldier_Bullet_Auto_Attack_sprite.getPosition().x >= 1850) {
                        mediumSoldier.MediumSoldierBullets.erase(mediumSoldier.MediumSoldierBullets.begin() + i);
                    }*/

                    mediumSoldier.medium_soldier_Bullet_Auto_Attack_sprite.move(-10, 0);
                    game.window.draw(MediumSoldier_Class.medium_soldier_Bullet_Auto_Attack_sprite);
                }
            }
            MediumSoldier_Class.mediumSoldierPrintWindow(game.window);
        }

#pragma endregion MediumSoldier

#pragma region HardSoldier
        for (auto& hardSoldier : HardSoldier_Class.hardSoldiers_vector) {
            if (!hardSoldier.getAlive()) {
                auto HS_nowDying = chrono::steady_clock::now();
                if (HS_nowDying >= HS_startDying + HS_waitDying) {
                     hardSoldier.hard_soldier_walk_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
                }
            }
            if (hardSoldier.getAlive()) {

                auto HS_nowTime = chrono::steady_clock::now();

                if (HS_nowTime >= HS_startTime + HS_waitTime) {
                    HardSoldier_Class.hard_soldier_anim.x++;
                    HardSoldier_Class.attackCountHardSoldier++;
                    HardSoldier_Class.reload = false;
                    if (HardSoldier_Class.attackCountHardSoldier == 2) {
                        HardSoldier_Class.bulletCreation();
                        HardSoldier_Class.countBulletsHardSoldier++;
                    }
                    if (HardSoldier_Class.hard_soldier_anim.x == 10) {
                        HardSoldier_Class.attackCountHardSoldier = 0;
                    }
                    if (HardSoldier_Class.countBulletsHardSoldier == 10) {
                        HardSoldier_Class.reload = true;
                    }
                    if (HardSoldier_Class.reload == true) {
                        HS_waitTime = chrono::seconds(1);
                        HardSoldier_Class.countBulletsHardSoldier = 0;
                    }
                    if (HardSoldier_Class.reload == false) {
                        HS_waitTime = chrono::milliseconds(HardSoldier_Class.attackSpeed);
                    }
                    HS_startTime = HS_nowTime;
                }

                hardSoldier.hard_soldier_walk_sprite.setTextureRect(sf::IntRect(HardSoldier_Class.hard_soldier_anim.x * 200, 0, -200, 157));

                if (HardSoldier_Class.hard_soldier_anim.x * 200 >= HardSoldier_Class.hard_soldier_walk_texture.getSize().x + 200) {
                    HardSoldier_Class.hard_soldier_anim.x = 2;
                }

                for (int i = 0; i < hardSoldier.HardSoldierBullets.size(); i++) {
                    hardSoldier.HardSoldierBullets[i].move(-10 * hardSoldier.bulletSpeed, 0);
                    game.window.draw(hardSoldier.HardSoldierBullets[i]);
                    HardSoldier_Class.hard_soldier_Bullet_Auto_Attack_sprite.setPosition(hardSoldier.HardSoldierBullets[i].getPosition().x - 1, hardSoldier.HardSoldierBullets[i].getPosition().y);

                    if (hardSoldier.HardSoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_walk_sprite.getGlobalBounds()) && !Ekko_Class.Ekko_invincibility && Ekko_Class.getAlive()) {
                        healthBar.updateLife(Ekko_Class.losePV(1));
                        Ekko_Class.Ekko_invincibility = true;
                        invincibilityTimer = true;
                        invincibilityStartTime = chrono::steady_clock::now();
                        hardSoldier.HardSoldierBullets.erase(hardSoldier.HardSoldierBullets.begin() + i);
                    }

                    /*if (mediumSoldier.medium_soldier_Bullet_Auto_Attack_sprite.getPosition().x >= 1850) {
                        mediumSoldier.HardSoldierBullets.erase(mediumSoldier.HardSoldierBullets.begin() + i);
                    }*/

                    hardSoldier.hard_soldier_Bullet_Auto_Attack_sprite.move(-10, 0);
                    game.window.draw(HardSoldier_Class.hard_soldier_Bullet_Auto_Attack_sprite);
                }
            }
            HardSoldier_Class.hardSoldierPrintWindow(game.window);
        }
#pragma endregion HardSoldier

#pragma region Buff

        if (blueBuff.touchByThePlayer(Ekko_Class.ekko_walk_sprite)) {
            if (!blueBuff.BlueBuffActivated) {
                blueBuff.BlueBuffActivated = true;
                BlueBuffTimer = true;
                BlueBuffStartTime = chrono::steady_clock::now();
                Ekko_Class.Ekko_speed = 1.5;
                Ekko_Class.ekko_walk_sprite.setColor(sf::Color::Cyan);
                Ekko_Class.ekko_Auto_Attack_sprite.setColor(sf::Color::Cyan);
            }
        }

        if (BlueBuffTimer) {
            auto now = chrono::steady_clock::now();
            auto duration = chrono::duration_cast<chrono::seconds>(now - BlueBuffStartTime).count();
            if (duration > 10) {
                blueBuff.BlueBuffActivated = false;
                BlueBuffTimer = false;
                Ekko_Class.Ekko_speed = 1.0f;
                Ekko_Class.ekko_walk_sprite.setColor(sf::Color::White);
                Ekko_Class.ekko_Auto_Attack_sprite.setColor(sf::Color::White);
            }
        }

        if (redBuff.touchByThePlayer(Ekko_Class.ekko_walk_sprite)) {
            if (!redBuff.RedBuffActivated) {
                redBuff.RedBuffActivated = true;
                RedBuffTimer = true;
                RedBuffStartTime = chrono::steady_clock::now();
                Ekko_Class.Ekko_attackSpeed = 2.0f;
                Ekko_Class.ekko_walk_sprite.setColor(sf::Color::Red);
                Ekko_Class.ekko_Auto_Attack_sprite.setColor(sf::Color::Red);
            }
        }
       
        if (RedBuffTimer) {
            auto now = chrono::steady_clock::now();
            auto duration = chrono::duration_cast<chrono::seconds>(now - RedBuffStartTime).count();
            if (duration > 10) {
                redBuff.RedBuffActivated = false;
                RedBuffTimer = false;
                Ekko_Class.Ekko_attackSpeed = 1.0f;
                Ekko_Class.ekko_walk_sprite.setColor(sf::Color::White);
                Ekko_Class.ekko_Auto_Attack_sprite.setColor(sf::Color::White);
            }
        }

        blueBuff.draw(game.window);
        redBuff.draw(game.window);

#pragma endregion Buff

#pragma region Waves
        if (game.currentPhase == game.WavesPhase && game.currentWave < game.MaxWaves) {
            auto newWaveNowTime = chrono::steady_clock::now();
            if (newWaveNowTime >= startNewWave + waitNewWave) {
                Wave(game.NbEasySoldier, game.NbMediumSoldier, game.NbHardSoldier);
                startNewWave = newWaveNowTime;
                game.currentWave++;
            }
        }

#pragma endregion Waves

        game.window.display();
    }
    return 0;
}

int customLevels() {

#pragma region initCustomLevelsMenu

    ////////////////////////
    // Background
    if (!menu.background_texture.loadFromFile("assets/backgrounds/background-menu.jpg")) {
        std::cerr << "Error: Failed to load background texture!" << std::endl;
        return -1;
    }
    menu.background_sprite.setTexture(menu.background_texture);
    menu.background_sprite.setScale(2, 2);

    ////////////////////////
    // Font + Title
    sf::Font font;
    if (!font.loadFromFile("assets/Arcane Nine.otf")) {
        std::cerr << "Error: Failed to load font!" << std::endl;
        return -1;
    }

    sf::Text title;
    title.setFont(font);
    title.setString("Zaun : La bataille des nations");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);

    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
    title.setPosition(game.window.getSize().x / 2.0f, 100.f);

    sf::Text subtitle;
    subtitle.setFont(font);
    subtitle.setString("Custom Mode");
    subtitle.setCharacterSize(60);
    subtitle.setFillColor(sf::Color::White);
    subtitle.setStyle(sf::Text::Bold);

    sf::FloatRect subtitleBounds = subtitle.getLocalBounds();
    subtitle.setOrigin(subtitleBounds.left + subtitleBounds.width / 2.0f, subtitleBounds.top + subtitleBounds.height / 2.0f);
    subtitle.setPosition(game.window.getSize().x / 2.0f, 200.f);

    ////////////////////////
    // Options setup
    std::vector<int> optionValues = { 0, 0, 0, 0, 0 };

    sf::RectangleShape leftButton1(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape leftButton2(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape leftButton3(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape leftButton4(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape leftButton5(sf::Vector2f(60.f, 80.f));

    sf::RectangleShape rightButton1(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape rightButton2(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape rightButton3(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape rightButton4(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape rightButton5(sf::Vector2f(60.f, 80.f));

    sf::Text optionText1, optionText2, optionText3, optionText4, optionText5;
    sf::Text leftButtonText1, leftButtonText2, leftButtonText3, leftButtonText4, leftButtonText5;
    sf::Text rightButtonText1, rightButtonText2, rightButtonText3, rightButtonText4, rightButtonText5;

    float optionSpacing = 100.f;
    float initialYPos = 350.f;

    leftButton1.setFillColor(sf::Color(100, 100, 255));
    leftButton1.setPosition((game.window.getSize().x - 60.f * 4) / 2.f, initialYPos);
    leftButton2.setFillColor(sf::Color(100, 100, 255));
    leftButton2.setPosition((game.window.getSize().x - 60.f * 4) / 2.f, initialYPos + optionSpacing);
    leftButton3.setFillColor(sf::Color(100, 100, 255));
    leftButton3.setPosition((game.window.getSize().x - 60.f * 4) / 2.f, initialYPos + 2 * optionSpacing);
    leftButton4.setFillColor(sf::Color(100, 100, 255));
    leftButton4.setPosition((game.window.getSize().x - 60.f * 4) / 2.f, initialYPos + 3 * optionSpacing);
    leftButton5.setFillColor(sf::Color(100, 100, 255));
    leftButton5.setPosition((game.window.getSize().x - 60.f * 4) / 2.f, initialYPos + 4 * optionSpacing);

    rightButton1.setFillColor(sf::Color(100, 100, 255));
    rightButton1.setPosition((game.window.getSize().x + 60.f * 2) / 2.f, initialYPos);
    rightButton2.setFillColor(sf::Color(100, 100, 255));
    rightButton2.setPosition((game.window.getSize().x + 60.f * 2) / 2.f, initialYPos + optionSpacing);
    rightButton3.setFillColor(sf::Color(100, 100, 255));
    rightButton3.setPosition((game.window.getSize().x + 60.f * 2) / 2.f, initialYPos + 2 * optionSpacing);
    rightButton4.setFillColor(sf::Color(100, 100, 255));
    rightButton4.setPosition((game.window.getSize().x + 60.f * 2) / 2.f, initialYPos + 3 * optionSpacing);
    rightButton5.setFillColor(sf::Color(100, 100, 255));
    rightButton5.setPosition((game.window.getSize().x + 60.f * 2) / 2.f, initialYPos + 4 * optionSpacing);

    optionText1.setFont(font);
    optionText1.setString(std::to_string(optionValues[0]));
    optionText1.setCharacterSize(50);
    optionText1.setFillColor(sf::Color::White);

    optionText2.setFont(font);
    optionText2.setString(std::to_string(optionValues[1]));
    optionText2.setCharacterSize(50);
    optionText2.setFillColor(sf::Color::White);

    optionText3.setFont(font);
    optionText3.setString(std::to_string(optionValues[2]));
    optionText3.setCharacterSize(50);
    optionText3.setFillColor(sf::Color::White);

    optionText4.setFont(font);
    optionText4.setString(std::to_string(optionValues[3]));
    optionText4.setCharacterSize(50);
    optionText4.setFillColor(sf::Color::White);

    optionText5.setFont(font);
    optionText5.setString(std::to_string(optionValues[4]));
    optionText5.setCharacterSize(50);
    optionText5.setFillColor(sf::Color::White);

    optionText1.setPosition((game.window.getSize().x / 2.f) - 15, initialYPos + 10.f);
    optionText2.setPosition((game.window.getSize().x / 2.f) - 15, initialYPos + optionSpacing + 10.f);
    optionText3.setPosition((game.window.getSize().x / 2.f) - 15, initialYPos + 2 * optionSpacing + 10.f);
    optionText4.setPosition((game.window.getSize().x / 2.f) - 15, initialYPos + 3 * optionSpacing + 10.f);
    optionText5.setPosition((game.window.getSize().x / 2.f) - 15, initialYPos + 4 * optionSpacing + 10.f);

    leftButtonText1.setFont(font);
    leftButtonText1.setString("<");
    leftButtonText1.setCharacterSize(60);
    leftButtonText1.setFillColor(sf::Color::White);

    leftButtonText2.setFont(font);
    leftButtonText2.setString("<");
    leftButtonText2.setCharacterSize(60);
    leftButtonText2.setFillColor(sf::Color::White);

    leftButtonText3.setFont(font);
    leftButtonText3.setString("<");
    leftButtonText3.setCharacterSize(60);
    leftButtonText3.setFillColor(sf::Color::White);

    leftButtonText4.setFont(font);
    leftButtonText4.setString("<");
    leftButtonText4.setCharacterSize(60);
    leftButtonText4.setFillColor(sf::Color::White);

    leftButtonText5.setFont(font);
    leftButtonText5.setString("<");
    leftButtonText5.setCharacterSize(60);
    leftButtonText5.setFillColor(sf::Color::White);

    rightButtonText1.setFont(font);
    rightButtonText1.setString(">");
    rightButtonText1.setCharacterSize(60);
    rightButtonText1.setFillColor(sf::Color::White);

    rightButtonText2.setFont(font);
    rightButtonText2.setString(">");
    rightButtonText2.setCharacterSize(60);
    rightButtonText2.setFillColor(sf::Color::White);

    rightButtonText3.setFont(font);
    rightButtonText3.setString(">");
    rightButtonText3.setCharacterSize(60);
    rightButtonText3.setFillColor(sf::Color::White);

    rightButtonText4.setFont(font);
    rightButtonText4.setString(">");
    rightButtonText4.setCharacterSize(60);
    rightButtonText4.setFillColor(sf::Color::White);

    rightButtonText5.setFont(font);
    rightButtonText5.setString(">");
    rightButtonText5.setCharacterSize(60);
    rightButtonText5.setFillColor(sf::Color::White);


    leftButtonText1.setPosition(leftButton1.getPosition().x + 15.f, leftButton1.getPosition().y + 2.f);
    leftButtonText2.setPosition(leftButton2.getPosition().x + 15.f, leftButton2.getPosition().y + 2.f);
    leftButtonText3.setPosition(leftButton3.getPosition().x + 15.f, leftButton3.getPosition().y + 2.f);
    leftButtonText4.setPosition(leftButton4.getPosition().x + 15.f, leftButton4.getPosition().y + 2.f);
    leftButtonText5.setPosition(leftButton5.getPosition().x + 15.f, leftButton5.getPosition().y + 2.f);

    rightButtonText1.setPosition(rightButton1.getPosition().x + 15.f, rightButton1.getPosition().y + 2.f);
    rightButtonText2.setPosition(rightButton2.getPosition().x + 15.f, rightButton2.getPosition().y + 2.f);
    rightButtonText3.setPosition(rightButton3.getPosition().x + 15.f, rightButton3.getPosition().y + 2.f);
    rightButtonText4.setPosition(rightButton4.getPosition().x + 15.f, rightButton4.getPosition().y + 2.f);
    rightButtonText5.setPosition(rightButton5.getPosition().x + 15.f, rightButton5.getPosition().y + 2.f);

    ////////////////////////
    // Play Button
    sf::RectangleShape playButton(sf::Vector2f(250.f, 80.f));
    sf::Text playButtonText;

    playButton.setFillColor(sf::Color(70, 70, 200));  // Dark Blue
    playButton.setPosition(game.window.getSize().x / 2.f - 125.f, initialYPos + 5 * optionSpacing + 50.f);

    playButtonText.setFont(font);
    playButtonText.setString("Jouer");
    playButtonText.setCharacterSize(60);
    playButtonText.setFillColor(sf::Color::White);
    sf::FloatRect playButtonTextBounds = playButtonText.getLocalBounds();
    playButtonText.setOrigin(playButtonTextBounds.left + playButtonTextBounds.width / 2.0f, playButtonTextBounds.top + playButtonTextBounds.height / 2.0f);
    playButtonText.setPosition(playButton.getPosition().x + playButton.getSize().x / 2.f, playButton.getPosition().y + playButton.getSize().y / 2.f);


    bool isMousePressed = false;

#pragma endregion initCustomLevelsMenu

    while (game.window.isOpen()) {
        sf::Event event;
        while (game.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                game.window.close();
            }
        }

#pragma region ClicksCustomLevelsMenu

        sf::Vector2i mousePos = sf::Mouse::getPosition(game.window);
        bool mouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        if (leftButton1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            leftButton1.setFillColor(sf::Color(100, 100, 255));  // Blue on hover
            if (mouseButtonPressed && !isMousePressed) {
                optionValues[0] = std::max(0, optionValues[0] - 1);
                optionText1.setString(std::to_string(optionValues[0])); 
                isMousePressed = true;
            }
        }
        else {
            leftButton1.setFillColor(sf::Color(70, 70, 200));  // Dark Blue when not hovering
        }

        if (leftButton2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            leftButton2.setFillColor(sf::Color(100, 100, 255));  // Blue on hover
            if (mouseButtonPressed && !isMousePressed) {
                optionValues[1] = std::max(0, optionValues[1] - 1);
                optionText2.setString(std::to_string(optionValues[1]));
                isMousePressed = true;
            }
        }
        else {
            leftButton2.setFillColor(sf::Color(70, 70, 200));
        }

        if (leftButton3.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            leftButton3.setFillColor(sf::Color(100, 100, 255));  // Blue on hover
            if (mouseButtonPressed && !isMousePressed) {
                optionValues[2] = std::max(0, optionValues[2] - 1);
                optionText3.setString(std::to_string(optionValues[2]));
                isMousePressed = true;
            }
        }
        else {
            leftButton3.setFillColor(sf::Color(70, 70, 200));
        }

        if (leftButton4.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            leftButton4.setFillColor(sf::Color(100, 100, 255));  // Blue on hover
            if (mouseButtonPressed && !isMousePressed) {
                optionValues[3] = std::max(0, optionValues[3] - 1);
                optionText4.setString(std::to_string(optionValues[3]));
                isMousePressed = true;
            }
        }
        else {
            leftButton4.setFillColor(sf::Color(70, 70, 200));
        }

        if (leftButton5.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            leftButton5.setFillColor(sf::Color(100, 100, 255));  // Blue on hover
            if (mouseButtonPressed && !isMousePressed) {
                optionValues[4] = std::max(0, optionValues[4] - 1);
                optionText5.setString(std::to_string(optionValues[4]));
                isMousePressed = true;
            }
        }
        else {
            leftButton5.setFillColor(sf::Color(70, 70, 200));
        }

        if (rightButton1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            rightButton1.setFillColor(sf::Color(100, 100, 255));  // Blue on hover
            if (mouseButtonPressed && !isMousePressed) {
                optionValues[0] = std::min(100, optionValues[0] + 1);
                optionText1.setString(std::to_string(optionValues[0]));
                isMousePressed = true;
            }
        }
        else {
            rightButton1.setFillColor(sf::Color(70, 70, 200));
        }

        if (rightButton2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            rightButton2.setFillColor(sf::Color(100, 100, 255));  // Blue on hover
            if (mouseButtonPressed && !isMousePressed) {
                optionValues[1] = std::min(100, optionValues[1] + 1);
                optionText2.setString(std::to_string(optionValues[1]));
                isMousePressed = true;
            }
        }
        else {
            rightButton2.setFillColor(sf::Color(70, 70, 200));
        }

        if (rightButton3.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            rightButton3.setFillColor(sf::Color(100, 100, 255));  // Blue on hover
            if (mouseButtonPressed && !isMousePressed) {
                optionValues[2] = std::min(100, optionValues[2] + 1);
                optionText3.setString(std::to_string(optionValues[2]));
                isMousePressed = true;
            }
        }
        else {
            rightButton3.setFillColor(sf::Color(70, 70, 200));
        }

        if (rightButton4.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            rightButton4.setFillColor(sf::Color(100, 100, 255));  // Blue on hover
            if (mouseButtonPressed && !isMousePressed) {
                optionValues[3] = std::min(100, optionValues[3] + 1);
                optionText4.setString(std::to_string(optionValues[3]));
                isMousePressed = true;
            }
        }
        else {
            rightButton4.setFillColor(sf::Color(70, 70, 200));
        }

        if (rightButton5.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            rightButton5.setFillColor(sf::Color(100, 100, 255));  // Blue on hover
            if (mouseButtonPressed && !isMousePressed) {
                optionValues[4] = std::min(100, optionValues[4] + 1);
                optionText5.setString(std::to_string(optionValues[4]));
                isMousePressed = true;
            }
        }
        else {
            rightButton5.setFillColor(sf::Color(70, 70, 200));
        }

        if (!mouseButtonPressed) {
            isMousePressed = false;
        }

        if (playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            playButton.setFillColor(sf::Color(100, 100, 255));  // Light Blue
            if (mouseButtonPressed && !isMousePressed) {

                game.NbEasySoldier = optionValues[0];
                game.NbMediumSoldier = optionValues[1];
                game.NbHardSoldier = optionValues[2];
                game.MaxWaves = optionValues[3];

                //game.CoefDifficulty = optionValues[5];

                mainGame();
                isMousePressed = true;
            }
        }
        else {
            playButton.setFillColor(sf::Color(70, 70, 200));  // Dark Blue
        }

#pragma endregion ClicksCustomLevelsMenu

#pragma region DrawCustomLevelsMenu
        game.window.clear();
        game.window.draw(menu.background_sprite);
        game.window.draw(title);
        game.window.draw(subtitle);

        game.window.draw(leftButton1);
        game.window.draw(rightButton1);
        game.window.draw(optionText1);
        game.window.draw(leftButtonText1);
        game.window.draw(rightButtonText1);

        game.window.draw(leftButton2);
        game.window.draw(rightButton2);
        game.window.draw(optionText2);
        game.window.draw(leftButtonText2);
        game.window.draw(rightButtonText2);

        game.window.draw(leftButton3);
        game.window.draw(rightButton3);
        game.window.draw(optionText3);
        game.window.draw(leftButtonText3);
        game.window.draw(rightButtonText3);

        game.window.draw(leftButton4);
        game.window.draw(rightButton4);
        game.window.draw(optionText4);
        game.window.draw(leftButtonText4);
        game.window.draw(rightButtonText4);

        game.window.draw(leftButton5);
        game.window.draw(rightButton5);
        game.window.draw(optionText5);
        game.window.draw(leftButtonText5);
        game.window.draw(rightButtonText5);

        game.window.draw(playButton);
        game.window.draw(playButtonText);

#pragma endregion DrawCustomLevelsMenu

        game.window.display();
    }
    return 0;
}

int mainMenu() {

    game.init();

#pragma region InitMenu
    ////////////////////////
    // Background
    if (!menu.background_texture.loadFromFile("assets/backgrounds/background-menu.jpg")) {
        cerr << "Error: Failed to load background texture!" << std::endl;
        return -1;
    }
    menu.background_sprite.setTexture(menu.background_texture);
    menu.background_sprite.setScale(2, 2);

    ////////////////////////
    // Font + Title
    sf::Text title;
    sf::Font font;
    if (!font.loadFromFile("assets/Arcane Nine.otf")) {
        std::cerr << "Error: Failed to load font!" << std::endl;
        return -1;
    }

    title.setFont(font);
    title.setString("Zaun : La bataille des nations");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);

    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
    title.setPosition(game.window.getSize().x / 2.0f, 100.f);

    ////////////////////////
    // Buttons
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;

    std::vector<std::string> buttonLabels = { "Jouer", "Custom", "Options", "Quitter" };
    std::vector<bool> buttonFled(buttonLabels.size(), false);
    sf::Vector2f buttonSize(400.f, 100.f);
    float buttonSpacing = 40.f;
    float initialYPos = 250.f;

    for (size_t i = 0; i < buttonLabels.size(); ++i) {
        sf::RectangleShape button(buttonSize);
        button.setFillColor(sf::Color::Color(70, 70, 200)); // Dark Blue
        button.setOutlineThickness(5.f);
        button.setOutlineColor(sf::Color::Color(200, 200, 255)); // Light Blue
        button.setPosition((game.window.getSize().x - buttonSize.x) / 2.f, initialYPos + i * (buttonSize.y + buttonSpacing));

        buttons.push_back(button);

        sf::Text buttonText;
        buttonText.setFont(font);
        buttonText.setString(buttonLabels[i]);
        buttonText.setCharacterSize(50);
        buttonText.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = buttonText.getLocalBounds();
        buttonText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
        buttonText.setPosition(button.getPosition().x + button.getSize().x / 2.f, button.getPosition().y + button.getSize().y / 2.f);

        buttonTexts.push_back(buttonText);
    }

    sf::Vector2f originalSize = buttons[0].getSize();
    sf::Vector2f hoverSize = originalSize * 1.05f;

    bool isMousePressed = false;

#pragma endregion InitMenu

    while (game.window.isOpen()) {
        Event event;
        while (game.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                game.window.close();
            }
        }

#pragma region ClickMenu
        sf::Vector2i mousePos = sf::Mouse::getPosition(game.window);
        bool isHovering = false;

        for (size_t i = 0; i < buttons.size(); ++i) {
            isHovering = buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

            if (isHovering) {
                buttons[i].setFillColor(sf::Color::Color(100, 100, 255)); // Blue
                buttons[i].setSize(hoverSize);

                if (!buttonFled[i]) {
                    buttons[i].setPosition((game.window.getSize().x - hoverSize.x) / 2.f, initialYPos + i * (originalSize.y + buttonSpacing) - (hoverSize.y - originalSize.y) / 2.f);
                    buttonFled[i] = true;
                }
            }
            else {
                buttons[i].setFillColor(sf::Color::Color(70, 70, 200)); // Dark Blue
                buttons[i].setSize(originalSize);

                if (buttonFled[i]) {
                    buttons[i].setPosition((game.window.getSize().x - originalSize.x) / 2.f, initialYPos + i * (originalSize.y + buttonSpacing));
                    buttonFled[i] = false;
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMousePressed) {
            for (size_t i = 0; i < buttons.size(); ++i) {
                if (buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    if (buttonLabels[i] == "Jouer") {
                        mainGame();
                    }

                    if (buttonLabels[i] == "Custom") {
                        customLevels();
                    }

                    if (buttonLabels[i] == "Options") {
                        // Options
                    }

                    if (buttonLabels[i] == "Quitter") {
                        game.window.close();
                    }

                    isMousePressed = true;
                    break;
                }
            }
        }

        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            isMousePressed = false;
        }

#pragma endregion ClickMenu

        if (game.currentMode == game.MENU) {
            game.window.clear();
            game.window.draw(menu.background_sprite);
            game.window.draw(title);

            for (size_t i = 0; i < buttons.size(); ++i) {
                game.window.draw(buttons[i]);
                game.window.draw(buttonTexts[i]);
            }

            game.window.display();
        }
    }
    return 0;
}

int main() {
    mainMenu();
    return 0;
}