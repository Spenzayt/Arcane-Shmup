#include <iostream>
#include <map>
#include "parallax.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Classes.hpp"
#include "menu.hpp"
#include "hud.hpp"
#include <SFML/Window.hpp>
#include <string>

Game game;
Menu menu;

int startMainMenu();

void Wave(int NbOfEasySoldiers, int NbOfMediumSoldiers, int NbOfHardSoldiers) {
    Soldier_Class.createSoldiers(NbOfEasySoldiers);
    MediumSoldier_Class.createSoldiers(NbOfMediumSoldiers);
    HardSoldier_Class.createSoldiers(NbOfHardSoldiers);
}

std::vector<Buff*> buffs;

void spawnBuff(sf::Vector2f position) {
    if (rand() % 2 == 0) {
        buffs.push_back(new BlueBuff(position));
    }
    else {
        buffs.push_back(new RedBuff(position));
    }
}

int mainGame() {

    sf::Music PaintBlue;
    if (!PaintBlue.openFromFile("assets\\Music\\Paint The Town BlueWAV.wav"))
        cout << "music pas chargé bro" << endl << endl;
    PaintBlue.setLoop(true);
    PaintBlue.setVolume(menu.volumeMusic);
    PaintBlue.play();

    if (game.isCustom) {
        game.NbEasySoldier = menu.NbEasySoldierCustom;
        game.NbMediumSoldier = menu.NbMediumSoldierCustom;
        game.NbHardSoldier = menu.NbHardSoldierCustom;
        game.MaxWaves = menu.MaxWavesCustom;
    }

    cout << "Easy : " << game.NbEasySoldier << std::endl;
    cout << "Medium : " << game.NbMediumSoldier << std::endl;
    cout << "Hard : " << game.NbHardSoldier << std::endl;
    cout << "Waves : " << game.MaxWaves << std::endl;

#pragma region Game Initialisation
    ParallaxBackground background1("assets/backgrounds/ground-zaunV2.png", 150.0f, 630, 1.1, 1.1);
    ParallaxBackground background2("assets/backgrounds/background-zaun.jpeg", 20.0f, -1890, 2, 2);

    Clock clock;

    Ekko_Class.ekkoInitAnimations();
    Ekko_Class.bulletInit();
    Ekko_Class.initializeSpells();
    cooldown.initCooldown(game.window);

    Marcus_Class.marcusInitAnimations();
    Marcus_Class.marcusBulletInit();

    Soldier_Class.soldierInitAnimations();
    Soldier_Class.soldierBulletInit();

    MediumSoldier_Class.mediumSoldierInitAnimations();
    MediumSoldier_Class.mediumSoldierBulletInit();

    HardSoldier_Class.hardSoldierInitAnimations();
    HardSoldier_Class.hardSoldierBulletInit();

    HUD healthBar(100, 100, 3);
    SCORE score;

    int animationDelay = 20;
    int animationDelayAttack = 50;

    bool invincibilityTimer = false;

    bool BlueBuffTimer = false;
    bool RedBuffTimer = false;

    if (game.isCustom) {
        game.MaxEasySoldier = menu.MaxEasySoldierCustom;
        game.MaxMediumSoldier = menu.MaxMediumSoldierCustom;
        game.MaxHardSoldier = menu.MaxHardSoldierCustom;
        game.TimeBeforeBoss = menu.TimeBeforeBossCustom;
    }

#pragma endregion Game Initialisation

#pragma region Clocks

    animationDelay = static_cast<int>(20.0f / Ekko_Class.Ekko_speed);

    auto startTime = chrono::steady_clock::now();
    auto waitTime = chrono::milliseconds(70);
    auto startAttTime = chrono::steady_clock::now();
    auto startReadyToAttackTime = chrono::steady_clock::now();
    auto waitReadyToAttackTime = chrono::seconds(1);
    auto startDashTime = chrono::steady_clock::now();
    auto waitDashTime = chrono::milliseconds(5);

    auto startPositionTime = chrono::steady_clock::now();
    auto waitPositionTime = chrono::milliseconds(100);

    auto startHitTime = chrono::steady_clock::now();
    auto waitHitTime = chrono::milliseconds(160);

    chrono::steady_clock::time_point invincibilityStartTime;
    chrono::steady_clock::time_point SlowZoneStartTime;

    auto M_startAttTime = chrono::steady_clock::now();
    auto M_waitAttTime = chrono::milliseconds(Marcus_Class.attackSpeed);
    auto M_startDying = chrono::steady_clock::now();
    auto M_waitDying = chrono::seconds(3);
    auto M_startReadyToAttackTime = chrono::steady_clock::now();
    auto M_waitReadyToAttackTime = chrono::seconds(1);

    auto M_startTrans = chrono::steady_clock::now();
    auto M_waitTrans = chrono::milliseconds(250);

    auto S_startTime = chrono::steady_clock::now();
    auto S_waitTime = chrono::milliseconds(Soldier_Class.attackSpeed);
    auto S_startAttTime = chrono::steady_clock::now();
    auto S_waitAttTime = chrono::milliseconds(800);
    auto S_startDying = chrono::steady_clock::now();
    auto S_waitDying = chrono::seconds(3);
    auto S_startReadyToAttackTime = chrono::steady_clock::now();
    auto S_waitReadyToAttackTime = chrono::seconds(1);

    auto startNewWaveSoldier = chrono::steady_clock::now();
    auto waitNewWaveSoldier = chrono::seconds(6);

    auto startNewWaveMediumSoldier = chrono::steady_clock::now();
    auto waitNewWaveMediumSoldier = chrono::seconds(10);

    auto startNewWaveHardSoldier = chrono::steady_clock::now();
    auto waitNewWaveHardSoldier = chrono::seconds(15);

    auto startNewWaveMarcus = chrono::steady_clock::now();
    auto waitNewWaveMarcus = chrono::seconds(game.TimeBeforeBoss);

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

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                game.isPaused = !game.isPaused;
            }

#pragma region KonamiCode

            if (event.type == sf::Event::KeyPressed) {
                game.inputSequence.push_back(event.key.code);

                if (game.inputSequence.size() > game.konamiCode.size()) {
                    game.inputSequence.erase(game.inputSequence.begin());
                }

                game.checkKonamiCode();
            }

#pragma endregion KonamiCode

        }

        game.window.clear();

#pragma region Pause

        if (game.isPaused) {
            sf::Font font;
            if (!font.loadFromFile("assets/Arcane Nine.otf")) {
                std::cerr << "Error loading Font!" << std::endl;
                return -1;
            }

            menu.title.setFont(font);
            menu.title.setString("Zaun : La bataille des nations");
            menu.title.setCharacterSize(100);
            menu.title.setFillColor(sf::Color::White);
            menu.title.setStyle(sf::Text::Bold);

            sf::FloatRect titleBounds = menu.title.getLocalBounds();
            menu.title.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
            menu.title.setPosition(game.window.getSize().x / 2.0f, 100.f);

            menu.subtitle.setFont(font);
            menu.subtitle.setString("PAUSE");
            menu.subtitle.setCharacterSize(60);
            menu.subtitle.setFillColor(sf::Color::White);
            menu.subtitle.setStyle(sf::Text::Bold);

            sf::FloatRect subtitleBounds = menu.subtitle.getLocalBounds();
            menu.subtitle.setOrigin(subtitleBounds.left + subtitleBounds.width / 2.0f, subtitleBounds.top + subtitleBounds.height / 2.0f);
            menu.subtitle.setPosition(game.window.getSize().x / 2.0f, 200.f);

            std::vector<sf::RectangleShape> buttons;
            std::vector<sf::Text> buttonTexts;

            std::vector<std::string> buttonLabels = { "Reprendre", "Options", "Menu Principal", "Quitter" };
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

#pragma region ClicksPauseMenu

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
                        if (buttonLabels[i] == "Reprendre") {
                            game.isPaused = false;
                        }

                        if (buttonLabels[i] == "Options") {
                            // Options
                        }

                        if (buttonLabels[i] == "Menu Principal") {
                            startMainMenu();
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

            game.window.draw(menu.background_sprite);
            game.window.draw(menu.title);
            game.window.draw(menu.subtitle);

            for (size_t i = 0; i < buttons.size(); ++i) {
                game.window.draw(buttons[i]);
                game.window.draw(buttonTexts[i]);
            }

            game.window.display();
        }

#pragma endregion ClicksPauseMenu

#pragma endregion Pause

        else {
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
                Ekko_Class.updateSpells(game.level);

                cooldown.update(deltaTime.asSeconds(), Ekko_Class.QspellUnlocked, Ekko_Class.WspellUnlocked, Ekko_Class.EspellUnlocked, Ekko_Class.UltUnlocked);

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
                if (!Ekko_Class.Ekko_invincibility /* && !blueBuff.BlueBuffActivated && !redBuff.RedBuffActivated*/) {
                    Ekko_Class.ekko_walk_sprite.setColor(sf::Color::White);
                    Ekko_Class.ekko_Auto_Attack_sprite.setColor(sf::Color::White);
                }

                animationDelayAttack = static_cast<int>(50.0f / Ekko_Class.Ekko_attackSpeed);
                auto waitAttTime = chrono::milliseconds(animationDelayAttack);

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
                cooldown.draw(game.window);
                healthBar.draw(game.window);

                /*Ekko_Class.ekko_anim_Bullet_Auto_Attack.x++;
                if (Ekko_Class.ekko_anim_Bullet_Auto_Attack.x * 32 >= Ekko_Class.ekko_Auto_Attack_texture.getSize().x) // boucle qui permet de revenir a la premiere slide de l'anim
                    Ekko_Class.ekko_anim_Bullet_Auto_Attack.x = 0;*/

                for (int i = 0; i < Ekko_Class.bullets.size(); i++) {
                    bool destroy = false;
                    game.window.draw(Ekko_Class.bullets[i]);
                    Ekko_Class.bullets[i].move(20 * Ekko_Class.Ekko_attackSpeed, 0);
                    Ekko_Class.ekko_Bullet_Auto_Attack_sprite.setPosition(Ekko_Class.bullets[i].getPosition().x - 30, Ekko_Class.bullets[i].getPosition().y - 6);

                    //Marcus
                    if (Ekko_Class.bullets[i].getGlobalBounds().intersects(Marcus_Class.marcus_Auto_Attack_sprite.getGlobalBounds()) && Marcus_Class.getAlive()) {
                        Marcus_Class.losePV(1);
                        destroy = true;
                    }

                    //Soldier
                    for (auto& soldier : Soldier_Class.soldiers_vector) {
                        if (Ekko_Class.bullets[i].getGlobalBounds().intersects(soldier.soldier_walk_sprite.getGlobalBounds()) && soldier.getAlive()) {
                            soldier.losePV(1);
                            destroy = true;
                            if (!soldier.s_isAlive) {
                                game.score++;
                                if (rand() % 10 == 0) {
                                    spawnBuff(sf::Vector2f(soldier.soldier_walk_sprite.getPosition()));
                                }
                            }
                        }
                    }

                    //MediumSoldier
                    for (auto& mediumSoldier : MediumSoldier_Class.mediumSoldiers_vector) {
                        if (Ekko_Class.bullets[i].getGlobalBounds().intersects(mediumSoldier.medium_soldier_walk_sprite.getGlobalBounds()) && mediumSoldier.getAlive()) {
                            mediumSoldier.losePV(1);
                            destroy = true;
                            if (!mediumSoldier.ms_isAlive) {
                                if (rand() % 5 == 0) {
                                    spawnBuff(sf::Vector2f(mediumSoldier.medium_soldier_walk_sprite.getPosition()));
                                }
                                game.score++;
                            }
                        }
                    }

                    //HardSoldier
                    for (auto& hardSoldier : HardSoldier_Class.hardSoldiers_vector) {
                        if (Ekko_Class.bullets[i].getGlobalBounds().intersects(hardSoldier.hard_soldier_walk_sprite.getGlobalBounds()) && hardSoldier.getAlive()) {
                            hardSoldier.losePV(1);
                            destroy = true;
                            if (!hardSoldier.hs_isAlive) {
                                game.score++;
                                if (rand() % 2 == 0) {
                                    spawnBuff(sf::Vector2f(hardSoldier.hard_soldier_walk_sprite.getPosition()));
                                }
                            }
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
            if (Marcus_Class.marcusApparition) {
                if (!Marcus_Class.getAlive()) {
                    auto M_nowDying = chrono::steady_clock::now();
                    if (M_nowDying >= M_startDying + M_waitDying) {
                        Marcus_Class.marcus_Auto_Attack_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
                        Marcus_Class.marcus_SecondPhase_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
                        Marcus_Class.marcus_SecondPhase_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
                    }
                }
                if (Marcus_Class.getAlive()) {
                    if (Marcus_Class.moveToFight == true) {
                        Marcus_Class.marcus_Auto_Attack_sprite.move(-2, 0);
                    }
                    if (Marcus_Class.marcus_Auto_Attack_sprite.getPosition().x <= 1300) {
                        Marcus_Class.moveToFight = false;
                    }
                    if (Ekko_Class.isBoomerangActive && Ekko_Class.ekko_Boomerang_sprite.getGlobalBounds().intersects(Marcus_Class.marcus_Auto_Attack_sprite.getGlobalBounds())) {
                        Marcus_Class.losePV(Ekko_Class.boomerangDamage);
                    }

                    //ici fait en sorte que le Marcus puisse bouger tout le temps pendant qu'il attaque quand il est en deuxieme phase
                    //fait bouger les trois sprite comme ça pas d'emmerde

                    ///////////////////////////////////////////////////////////////////////


                    if (Marcus_Class.m_health <= 30 && !Marcus_Class.isAttackingV2) {
                        Marcus_Class.isAttacking = false;
                        Marcus_Class.transIsIn = true;

                        auto M_nowTrans = chrono::steady_clock::now();
                        if (M_nowTrans >= M_startTrans + M_waitTrans) {
                            Marcus_Class.marcus_anim_TransSecondPhase.x++;
                            Marcus_Class.countAnimTrans++;
                            M_startTrans = M_nowTrans;
                        }

                        if (Marcus_Class.countAnimTrans == 13) {
                            Marcus_Class.isAttackingV2 = true;
                            Marcus_Class.transIsIn = false;
                        }
                    }

                    auto M_nowAttTime = chrono::steady_clock::now();
                    if (M_nowAttTime >= M_startAttTime + M_waitAttTime) {

                        if (Marcus_Class.isAttackingV2) {
                            Marcus_Class.marcus_anim_SecondPhase.x++;
                            Marcus_Class.countLaserTime++;
                            if (Marcus_Class.countLaserTime == 330) {
                                Marcus_Class.laserActive = true;
                            }
                            if (Marcus_Class.laserActive && !Marcus_Class.moveToFight && !Marcus_Class.transIsIn) {
                                Marcus_Class.MarcusLaser.push_back(sf::CircleShape());
                                Marcus_Class.MarcusLaser.back().setFillColor(sf::Color::Red);
                                Marcus_Class.MarcusLaser.back().setRadius(15);
                                Marcus_Class.MarcusLaser.back().setPosition(Marcus_Class.marcus_Auto_Attack_sprite.getPosition().x + 250, Marcus_Class.marcus_Auto_Attack_sprite.getPosition().y - 300);
                                if (Marcus_Class.countLaserTime == 500) {
                                    Marcus_Class.laserActive = false;
                                }
                            }
                        }
                        else if (Marcus_Class.isAttacking) {
                            Marcus_Class.marcus_anim_Auto_Attack.x++;
                        }
                        ///////////////////////////////////////////////////////////////////////////////////////////////////////
                        Marcus_Class.countAnimAtk++;
                        Marcus_Class.reload = false;
                        if (Marcus_Class.countAnimAtk == 1 && !Marcus_Class.moveToFight && !Marcus_Class.transIsIn) {
                            Marcus_Class.countBulletsMarcus++;
                            Marcus_Class.MarcusBullets.push_back(sf::CircleShape());
                            Marcus_Class.MarcusBullets.back().setTexture(&Marcus_Class.marcus_Bullet_Auto_Attack_texture);
                            Marcus_Class.MarcusBullets.back().setTextureRect(sf::IntRect(32, 0, 32, 32));
                            Marcus_Class.MarcusBullets.back().setRadius(15);
                            Marcus_Class.MarcusBullets.back().setPosition(Marcus_Class.marcus_Auto_Attack_sprite.getPosition().x, Marcus_Class.marcus_Auto_Attack_sprite.getPosition().y + 260);
                        }
                        if (Marcus_Class.countAnimAtk == 5) {
                            Marcus_Class.countAnimAtk = 0;
                        }

                        if (Marcus_Class.isAttackingV2) {
                            if (Marcus_Class.countBulletsMarcus >= 25) {
                                Marcus_Class.reload = true;
                            }
                        }
                        else if (!Marcus_Class.isAttackingV2) {
                            if (Marcus_Class.countBulletsMarcus >= 17) {
                                Marcus_Class.reload = true;
                            }
                        }
                        if (Marcus_Class.isAttackingV2) {
                            if (Marcus_Class.reload) {
                                M_waitAttTime = chrono::seconds(2);
                                Marcus_Class.countBulletsMarcus = 0;
                            }
                            if (!Marcus_Class.reload) {
                                M_waitAttTime = chrono::milliseconds(Marcus_Class.attackSpeed2);
                            }
                        }
                        if (!Marcus_Class.isAttackingV2) {
                            if (Marcus_Class.reload) {
                                M_waitAttTime = chrono::seconds(2);
                                Marcus_Class.countBulletsMarcus = 0;
                            }
                            if (!Marcus_Class.reload) {
                                M_waitAttTime = chrono::milliseconds(Marcus_Class.attackSpeed);
                            }
                        }
                        M_startAttTime = M_nowAttTime;
                    }

                    Marcus_Class.marcusPrintWindow(game.window);

                    for (int i = 0; i < Marcus_Class.MarcusBullets.size(); i++) {
                        bool destroyBulletsMarcus = false;
                        if (Ekko_Class.ekko_walk_sprite.getPosition().y <= 700) Marcus_Class.MarcusBullets[i].move(-15 * Marcus_Class.bulletSpeed, (Ekko_Class.ekko_walk_sprite.getPosition().x) / (Marcus_Class.marcus_Auto_Attack_sprite.getPosition().y - Ekko_Class.ekko_walk_sprite.getPosition().y));/* / (Marcus_Class.marcus_Auto_Attack_sprite.getPosition().y / Ekko_Class.ekko_walk_sprite.getPosition().y - 260)*/
                        else Marcus_Class.MarcusBullets[i].move(-15 * Marcus_Class.bulletSpeed, ((Ekko_Class.ekko_walk_sprite.getPosition().x + Ekko_Class.ekko_walk_sprite.getPosition().y) / (Marcus_Class.marcus_Auto_Attack_sprite.getPosition().y + 128)));
                        
                        game.window.draw(Marcus_Class.MarcusBullets[i]);

                        if (Marcus_Class.MarcusBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_walk_sprite.getGlobalBounds()) && !Ekko_Class.Ekko_invincibility && Ekko_Class.getAlive()) {
                            healthBar.updateLife(Ekko_Class.losePV(1));
                            Ekko_Class.Ekko_invincibility = true;
                            invincibilityTimer = true;
                            invincibilityStartTime = chrono::steady_clock::now();
                            destroyBulletsMarcus = true;
                            //Marcus_Class.MarcusBullets.erase(Marcus_Class.MarcusBullets.begin() + i);
                        }
                        else if (Marcus_Class.MarcusBullets[i].getPosition().x < 0 || Marcus_Class.MarcusBullets[i].getPosition().y < 0 || Marcus_Class.MarcusBullets[i].getPosition().y > 1080) {
                            destroyBulletsMarcus = true;
                            //Marcus_Class.MarcusBullets.erase(Marcus_Class.MarcusBullets.begin() + i);
                        }


                        if (destroyBulletsMarcus == true) {
                            Marcus_Class.MarcusBullets.erase(Marcus_Class.MarcusBullets.begin() + i);
                        }
                    }

                    for (int i = 0; i < Marcus_Class.MarcusLaser.size(); i++) {
                        if (Ekko_Class.ekko_walk_sprite.getPosition().y < 700) Marcus_Class.MarcusLaser[i].move(-10 * Marcus_Class.laserSpeed, (Ekko_Class.ekko_walk_sprite.getPosition().x) / (Marcus_Class.marcus_Auto_Attack_sprite.getPosition().y - Ekko_Class.ekko_walk_sprite.getPosition().y)/* / (Marcus_Class.marcus_Auto_Attack_sprite.getPosition().y / Ekko_Class.ekko_walk_sprite.getPosition().y - 260)*/);
                        else Marcus_Class.MarcusLaser[i].move(-10 * Marcus_Class.laserSpeed, ((Ekko_Class.ekko_walk_sprite.getPosition().x + Ekko_Class.ekko_walk_sprite.getPosition().y) / (Marcus_Class.marcus_Auto_Attack_sprite.getPosition().y + 128)));
                        
                        game.window.draw(Marcus_Class.MarcusLaser[i]);

                        if (Marcus_Class.MarcusLaser[i].getGlobalBounds().intersects(Ekko_Class.ekko_walk_sprite.getGlobalBounds()) && !Ekko_Class.Ekko_invincibility && Ekko_Class.getAlive()) {
                            healthBar.updateLife(Ekko_Class.losePV(1));
                            Ekko_Class.Ekko_invincibility = true;
                            invincibilityTimer = true;
                            invincibilityStartTime = chrono::steady_clock::now();
                            Marcus_Class.MarcusLaser.erase(Marcus_Class.MarcusLaser.begin() + i);
                        }
                        else if (Marcus_Class.MarcusLaser[i].getPosition().x < 0 || Marcus_Class.MarcusLaser[i].getPosition().y < 0 || Marcus_Class.MarcusLaser[i].getPosition().y > 1080) {
                            Marcus_Class.MarcusLaser.erase(Marcus_Class.MarcusLaser.begin() + i);
                        }
                    }
                }
            }
#pragma endregion Marcus

#pragma region AllSoldiers

#pragma region Soldier

            for (auto& soldier : Soldier_Class.soldiers_vector) {
                if (!soldier.getAlive()) {
                    auto S_nowDying = chrono::steady_clock::now();
                    if (S_nowDying >= S_startDying + S_waitDying) {
                        soldier.soldier_walk_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
                    }
                }
                if (soldier.getAlive()) {
                    if (soldier.moveToFight == true) {
                        soldier.soldier_walk_sprite.move(-10, 0);
                    }
                    if (soldier.soldier_walk_sprite.getPosition().x <= 1300) {
                        soldier.moveToFight = false;
                    }
                    if (Ekko_Class.isBoomerangActive && Ekko_Class.ekko_Boomerang_sprite.getGlobalBounds().intersects(soldier.soldier_walk_sprite.getGlobalBounds())) {
                        soldier.losePV(Ekko_Class.boomerangDamage);
                        if (!soldier.s_isAlive) {
                            if (rand() % 10 == 0) {
                                spawnBuff(sf::Vector2f(soldier.soldier_walk_sprite.getPosition()));
                            }
                        }
                            game.score++;
                        }

                    }
                    auto S_nowTime = chrono::steady_clock::now();
                    if (S_nowTime >= S_startTime + S_waitTime) {
                        Soldier_Class.soldier_anim.x++;
                        Soldier_Class.attackCountSoldier++;
                        Soldier_Class.reload = false;
                        if (Soldier_Class.attackCountSoldier == 2 && !soldier.moveToFight) {
                            Soldier_Class.bulletCreation();
                            Soldier_Class.countBulletsSoldier++;
                        }
                        if (Soldier_Class.soldier_anim.x == 10) {
                            Soldier_Class.attackCountSoldier = 0;
                        }
                        if (Soldier_Class.countBulletsSoldier == 10 && !soldier.moveToFight) {
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

                        if (soldier.SoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_walk_sprite.getGlobalBounds()) && !Ekko_Class.Ekko_invincibility && Ekko_Class.getAlive()) {
                            healthBar.updateLife(Ekko_Class.losePV(1));
                            Ekko_Class.Ekko_invincibility = true;
                            invincibilityTimer = true;
                            invincibilityStartTime = chrono::steady_clock::now();
                            soldier.SoldierBullets.erase(soldier.SoldierBullets.begin() + i);
                        }

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
                    if (mediumSoldier.moveToFight == true) {
                        mediumSoldier.medium_soldier_walk_sprite.move(-8, 0);
                    }
                    if (mediumSoldier.medium_soldier_walk_sprite.getPosition().x <= 1200) {
                        mediumSoldier.moveToFight = false;
                    }
                    if (Ekko_Class.isBoomerangActive && Ekko_Class.ekko_Boomerang_sprite.getGlobalBounds().intersects(mediumSoldier.medium_soldier_walk_sprite.getGlobalBounds())) {
                        mediumSoldier.losePV(Ekko_Class.boomerangDamage);
                        if (!mediumSoldier.ms_isAlive) {
                            if (rand() % 5 == 0) {
                                spawnBuff(sf::Vector2f(mediumSoldier.medium_soldier_walk_sprite.getPosition()));
                            }
                            game.score++;
                        }
                    }
                    auto MS_nowTime = chrono::steady_clock::now();
                    if (MS_nowTime >= MS_startTime + MS_waitTime) {
                        MediumSoldier_Class.medium_soldier_anim.x++;
                        MediumSoldier_Class.attackCountMediumSoldier++;
                        MediumSoldier_Class.reload = false;
                        if (MediumSoldier_Class.attackCountMediumSoldier == 2 && !mediumSoldier.moveToFight) {
                            MediumSoldier_Class.bulletCreation();
                            MediumSoldier_Class.countBulletsMediumSoldier++;
                        }
                        if (MediumSoldier_Class.medium_soldier_anim.x == 10) {
                            MediumSoldier_Class.attackCountMediumSoldier = 0;
                        }
                        if (MediumSoldier_Class.countBulletsMediumSoldier == 10 && !mediumSoldier.moveToFight) {
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
                        if (mediumSoldier.MediumSoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_SlowZone_sprite.getGlobalBounds()) && Ekko_Class.getAlive() && Ekko_Class.ekko_S.SlowZone) {
                            mediumSoldier.bulletSpeed = 0.2f;
                        }

                        if (!mediumSoldier.MediumSoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_SlowZone_sprite.getGlobalBounds()) && Ekko_Class.getAlive()) {
                            mediumSoldier.bulletSpeed = 1.0f;
                        }

                        mediumSoldier.MediumSoldierBullets[i].move(-10 * mediumSoldier.bulletSpeed, 0);
                        game.window.draw(mediumSoldier.MediumSoldierBullets[i]);

                        if (mediumSoldier.MediumSoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_walk_sprite.getGlobalBounds()) && !Ekko_Class.Ekko_invincibility && Ekko_Class.getAlive()) {
                            healthBar.updateLife(Ekko_Class.losePV(1));
                            Ekko_Class.Ekko_invincibility = true;
                            invincibilityTimer = true;
                            invincibilityStartTime = chrono::steady_clock::now();
                            mediumSoldier.MediumSoldierBullets.erase(mediumSoldier.MediumSoldierBullets.begin() + i);
                        }

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
                    if (hardSoldier.moveToFight == true) {
                        hardSoldier.hard_soldier_walk_sprite.move(-7, 0);
                    }
                    if (hardSoldier.hard_soldier_walk_sprite.getPosition().x <= 1600) {
                        hardSoldier.moveToFight = false;
                    }
                    if (Ekko_Class.isBoomerangActive && Ekko_Class.ekko_Boomerang_sprite.getGlobalBounds().intersects(hardSoldier.hard_soldier_walk_sprite.getGlobalBounds())) {
                        hardSoldier.losePV(Ekko_Class.boomerangDamage);
                        if (!hardSoldier.hs_isAlive) {
                            if (rand() % 2 == 0) {
                                spawnBuff(sf::Vector2f(hardSoldier.hard_soldier_walk_sprite.getPosition()));
                            }
                            game.score++;
                        }
                    }
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
                        if (hardSoldier.HardSoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_SlowZone_sprite.getGlobalBounds()) && Ekko_Class.getAlive() && Ekko_Class.ekko_S.SlowZone) {
                            hardSoldier.bulletSpeed = 0.2f;
                        }

                        if (!hardSoldier.HardSoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_SlowZone_sprite.getGlobalBounds()) && Ekko_Class.getAlive()) {
                            hardSoldier.bulletSpeed = 1.0f;
                        }

                        hardSoldier.HardSoldierBullets[i].move(-10 * hardSoldier.bulletSpeed, 0);
                        game.window.draw(hardSoldier.HardSoldierBullets[i]);

                        if (hardSoldier.HardSoldierBullets[i].getGlobalBounds().intersects(Ekko_Class.ekko_walk_sprite.getGlobalBounds()) && !Ekko_Class.Ekko_invincibility && Ekko_Class.getAlive()) {
                            healthBar.updateLife(Ekko_Class.losePV(1));
                            Ekko_Class.Ekko_invincibility = true;
                            invincibilityTimer = true;
                            invincibilityStartTime = chrono::steady_clock::now();
                            hardSoldier.HardSoldierBullets.erase(hardSoldier.HardSoldierBullets.begin() + i);
                        }
                        game.window.draw(HardSoldier_Class.hard_soldier_Bullet_Auto_Attack_sprite);
                    }
                }
                HardSoldier_Class.hardSoldierPrintWindow(game.window);
            }
#pragma endregion HardSoldier

#pragma endregion AllSoldiers

#pragma region Buff

            for (auto it = buffs.begin(); it != buffs.end(); ) {
                (*it)->update();
                ++it;
            }

            for (auto& buff : buffs) {
                if (buff->touchByThePlayer(Ekko_Class.ekko_walk_sprite)) {
                    if (!buff->isActivated()) {
                        buff->activate();
                        if (BlueBuff* blueBuff = dynamic_cast<BlueBuff*>(buff)) {
                            Ekko_Class.Ekko_speed = 1.5;
                            Ekko_Class.ekko_walk_sprite.setColor(sf::Color::Cyan);
                            Ekko_Class.ekko_Auto_Attack_sprite.setColor(sf::Color::Cyan);
                        }
                        else if (RedBuff* redBuff = dynamic_cast<RedBuff*>(buff)) {
                            Ekko_Class.Ekko_attackSpeed = 2.0f;
                            Ekko_Class.ekko_walk_sprite.setColor(sf::Color::Red);
                            Ekko_Class.ekko_Auto_Attack_sprite.setColor(sf::Color::Red);
                        }
                    }
                }
            }

            for (auto it = buffs.begin(); it != buffs.end(); ) {
                if ((*it)->isActivated()) {
                    auto now = std::chrono::steady_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - (*it)->getStartTime()).count();

                    if (duration > 10) {
                        (*it)->deactivate();

                        if (BlueBuff* blueBuff = dynamic_cast<BlueBuff*>(*it)) {
                            Ekko_Class.Ekko_speed = 1.0f;
                            Ekko_Class.ekko_walk_sprite.setColor(sf::Color::White);
                            Ekko_Class.ekko_Auto_Attack_sprite.setColor(sf::Color::White);
                        }
                        else if (RedBuff* redBuff = dynamic_cast<RedBuff*>(*it)) {
                            Ekko_Class.Ekko_attackSpeed = 1.0f;
                            Ekko_Class.ekko_walk_sprite.setColor(sf::Color::White);
                            Ekko_Class.ekko_Auto_Attack_sprite.setColor(sf::Color::White);
                        }

                        delete* it;
                        it = buffs.erase(it);
                    }
                    else {
                        ++it;
                    }
                }
                else {
                    ++it;
                }
            }


            for (auto& buff : buffs) {
                buff->draw(game.window);
            }

#pragma endregion Buff

#pragma region Waves        

            if (game.currentPhase == game.WavesPhase && game.currentWave < game.TimeBeforeBoss) {
                if (!Marcus_Class.marcusApparition) {
                    auto newWaveNowTimeSoldier = chrono::steady_clock::now();
                    if (newWaveNowTimeSoldier >= startNewWaveSoldier + waitNewWaveSoldier) {
                        for (int i = 0; i < rand() % 1 + game.MaxEasySoldier; i++)
                        {
                            Soldier_Class.createSoldiers(1);
                        }
                        startNewWaveSoldier = newWaveNowTimeSoldier;
                    }

                    auto newWaveNowTimeMediumSoldier = chrono::steady_clock::now();
                    if (newWaveNowTimeMediumSoldier >= startNewWaveMediumSoldier + waitNewWaveMediumSoldier) {
                        for (int i = 0; i < rand() % 1 + game.MaxMediumSoldier; i++)
                        {
                            MediumSoldier_Class.createSoldiers(1);
                        }
                        startNewWaveMediumSoldier = newWaveNowTimeMediumSoldier;
                    }

                    auto newWaveNowTimeHardSoldier = chrono::steady_clock::now();
                    if (newWaveNowTimeHardSoldier >= startNewWaveHardSoldier + waitNewWaveHardSoldier) {
                        for (int i = 0; i < rand() % 1 + game.MaxHardSoldier; i++)
                        {
                            HardSoldier_Class.createSoldiers(1);
                        }
                        startNewWaveHardSoldier = newWaveNowTimeHardSoldier;
                    }
                }

                auto newWaveNowTimeMarcus = chrono::steady_clock::now();
                if (newWaveNowTimeMarcus >= startNewWaveMarcus + waitNewWaveMarcus) {
                    Marcus_Class.marcusApparition = true;
                }
            }

#pragma endregion Waves 

#pragma region Score

            score.updateScore(game.score);
            score.drawScore(game.window);

#pragma endregion Score

#pragma region Cooldown

            float deltaTime = clock.restart().asSeconds();
            cooldown.draw(game.window);

#pragma endregion Cooldown

#pragma region Levels

            if (game.score >= game.level * 10 && game.level < game.maxLevel) game.level++;

#pragma endregion Levels

            game.window.display();
        }
    }
    for (auto& buff : buffs) {
        delete buff;
    }
    buffs.clear();

    return 0;
}

int startMainMenu() {
    game.isPaused = false;
    game.konamiCodeActivated = false;
    game.currentWave = 1;
    game.currentPhase = game.WavesPhase;
    game.isCustom = false;
    game.score = 0;

    game.MaxEasySoldier = 4;
    game.MaxMediumSoldier = 3;
    game.MaxHardSoldier = 2;
    game.TimeBeforeBoss = 90;

    menu.MaxEasySoldierCustom = 4;
    menu.MaxMediumSoldierCustom = 3;
    menu.MaxHardSoldierCustom = 2;
    menu.TimeBeforeBossCustom = 90;

    Soldier_Class.deleteSoldiers();
    MediumSoldier_Class.deleteMediumSoldiers();
    HardSoldier_Class.deleteHardSoldiers();

    int mode = menu.mainMenu(game.window);
    if (mode == 1) {
        mainGame();
    }
    else if (mode == 2) {
        game.isCustom = true;
        mainGame();
    }
    return 0;
}


int main() {
    game.init();
    startMainMenu();
    return 0;
}