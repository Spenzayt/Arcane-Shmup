#include "menu.hpp"

int Menu::mainMenu(sf::RenderWindow& window) {
    mode = 1;

#pragma region InitMenu
    if (!background_texture.loadFromFile("assets/backgrounds/arcane_background.jpg")) {
        std::cerr << "Error loading Texture!" << std::endl;
        return -1;
    }
    background_sprite.setTexture(background_texture);

    sf::Text title;
    sf::Font font;
    if (!font.loadFromFile("assets/Arcane Nine.otf")) {
        std::cerr << "Error loading Font!" << std::endl;
        return -1;
    }

    title.setFont(font);
    title.setString("Zaun : La bataille des nations");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);

    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
    title.setPosition(window.getSize().x / 2.0f, 100.f);

    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;

    std::vector<std::string> buttonLabels = { "Jouer", "Custom", "Options", "Quitter" };
    std::vector<bool> buttonFled(buttonLabels.size(), false);
    sf::Vector2f buttonSize(400.f, 100.f);
    float buttonSpacing = 40.f;
    float initialYPos = 300.f;

    for (size_t i = 0; i < buttonLabels.size(); ++i) {
        sf::RectangleShape button(buttonSize);
        button.setFillColor(sf::Color::Color(70, 70, 200)); // Dark Blue
        button.setOutlineThickness(5.f);
        button.setOutlineColor(sf::Color::Color(200, 200, 255)); // Light Blue
        button.setPosition((window.getSize().x - buttonSize.x) / 2.f, initialYPos + i * (buttonSize.y + buttonSpacing));

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

    isMousePressed = false;

    // Settings
    if (!settingsExitButtonTexture.loadFromFile("assets\\UI\\exitButtonV2.png")) {
        std::cout << "settings exit text pas charge bro" << std::endl << std::endl;
    }

#pragma endregion InitMenu

#pragma region initCustomLevelsMenu

    sf::Text subtitle;
    subtitle.setFont(font);
    subtitle.setString("Custom Mode");
    subtitle.setCharacterSize(60);
    subtitle.setFillColor(sf::Color::White);
    subtitle.setStyle(sf::Text::Bold);

    sf::FloatRect subtitleBounds = subtitle.getLocalBounds();
    subtitle.setOrigin(subtitleBounds.left + subtitleBounds.width / 2.0f, subtitleBounds.top + subtitleBounds.height / 2.0f);
    subtitle.setPosition(window.getSize().x / 2.0f, 200.f);

    std::vector<int> optionValues = { MaxEasySoldierCustom, MaxMediumSoldierCustom, MaxHardSoldierCustom, TimeBeforeBossCustom };

    sf::RectangleShape leftButton1(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape leftButton2(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape leftButton3(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape leftButton4(sf::Vector2f(60.f, 80.f));

    sf::RectangleShape rightButton1(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape rightButton2(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape rightButton3(sf::Vector2f(60.f, 80.f));
    sf::RectangleShape rightButton4(sf::Vector2f(60.f, 80.f));

    sf::Text optionText1, optionText2, optionText3, optionText4;
    sf::Text titleOptionText1, titleOptionText2, titleOptionText3, titleOptionText4;
    sf::Text leftButtonText1, leftButtonText2, leftButtonText3, leftButtonText4;
    sf::Text rightButtonText1, rightButtonText2, rightButtonText3, rightButtonText4;

    float optionSpacing = 160.f;

    leftButton1.setFillColor(sf::Color(100, 100, 255));
    leftButton1.setPosition((window.getSize().x - 60.f * 4) / 2.f, initialYPos);
    leftButton2.setFillColor(sf::Color(100, 100, 255));
    leftButton2.setPosition((window.getSize().x - 60.f * 4) / 2.f, initialYPos + optionSpacing);
    leftButton3.setFillColor(sf::Color(100, 100, 255));
    leftButton3.setPosition((window.getSize().x - 60.f * 4) / 2.f, initialYPos + 2 * optionSpacing);
    leftButton4.setFillColor(sf::Color(100, 100, 255));
    leftButton4.setPosition((window.getSize().x - 60.f * 4) / 2.f, initialYPos + 3 * optionSpacing);

    rightButton1.setFillColor(sf::Color(100, 100, 255));
    rightButton1.setPosition((window.getSize().x + 60.f * 2) / 2.f, initialYPos);
    rightButton2.setFillColor(sf::Color(100, 100, 255));
    rightButton2.setPosition((window.getSize().x + 60.f * 2) / 2.f, initialYPos + optionSpacing);
    rightButton3.setFillColor(sf::Color(100, 100, 255));
    rightButton3.setPosition((window.getSize().x + 60.f * 2) / 2.f, initialYPos + 2 * optionSpacing);
    rightButton4.setFillColor(sf::Color(100, 100, 255));
    rightButton4.setPosition((window.getSize().x + 60.f * 2) / 2.f, initialYPos + 3 * optionSpacing);

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

    titleOptionText1.setFont(font);
    titleOptionText1.setString("Maximum de Soldier Easy par Wave :");
    titleOptionText1.setCharacterSize(36);
    titleOptionText1.setFillColor(sf::Color::White);

    titleOptionText2.setFont(font);
    titleOptionText2.setString("Maximum de Soldier Medium par Wave :");
    titleOptionText2.setCharacterSize(36);
    titleOptionText2.setFillColor(sf::Color::White);

    titleOptionText3.setFont(font);
    titleOptionText3.setString("Maximum de Soldier Hard par Wave :");
    titleOptionText3.setCharacterSize(36);
    titleOptionText3.setFillColor(sf::Color::White);

    titleOptionText4.setFont(font);
    titleOptionText4.setString("Temps avant l'arriver du Boss");
    titleOptionText4.setCharacterSize(36);
    titleOptionText4.setFillColor(sf::Color::White);

    optionText1.setPosition((window.getSize().x / 2.f) - 15, initialYPos + 10.f);
    optionText2.setPosition((window.getSize().x / 2.f) - 15, initialYPos + optionSpacing + 10.f);
    optionText3.setPosition((window.getSize().x / 2.f) - 15, initialYPos + 2 * optionSpacing + 10.f);
    optionText4.setPosition((window.getSize().x / 2.f) - 15, initialYPos + 3 * optionSpacing + 10.f);

    titleOptionText1.setPosition((window.getSize().x / 2.f) - 250, initialYPos - 50.f);
    titleOptionText2.setPosition((window.getSize().x / 2.f) - 250, initialYPos + optionSpacing - 50.f);
    titleOptionText3.setPosition((window.getSize().x / 2.f) - 250, initialYPos + 2 * optionSpacing - 50.f);
    titleOptionText4.setPosition((window.getSize().x / 2.f) - 250, initialYPos + 3 * optionSpacing - 50.f);

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

    leftButtonText1.setPosition(leftButton1.getPosition().x + 15.f, leftButton1.getPosition().y + 2.f);
    leftButtonText2.setPosition(leftButton2.getPosition().x + 15.f, leftButton2.getPosition().y + 2.f);
    leftButtonText3.setPosition(leftButton3.getPosition().x + 15.f, leftButton3.getPosition().y + 2.f);
    leftButtonText4.setPosition(leftButton4.getPosition().x + 15.f, leftButton4.getPosition().y + 2.f);

    rightButtonText1.setPosition(rightButton1.getPosition().x + 15.f, rightButton1.getPosition().y + 2.f);
    rightButtonText2.setPosition(rightButton2.getPosition().x + 15.f, rightButton2.getPosition().y + 2.f);
    rightButtonText3.setPosition(rightButton3.getPosition().x + 15.f, rightButton3.getPosition().y + 2.f);
    rightButtonText4.setPosition(rightButton4.getPosition().x + 15.f, rightButton4.getPosition().y + 2.f);

    sf::RectangleShape playButton(sf::Vector2f(250.f, 80.f));
    sf::Text playButtonText;

    playButton.setFillColor(sf::Color(70, 70, 200));  // Dark Blue
    playButton.setPosition(window.getSize().x / 2.f - 125.f, initialYPos + 3 * optionSpacing + 150.f);

    playButtonText.setFont(font);
    playButtonText.setString("Jouer");
    playButtonText.setCharacterSize(60);
    playButtonText.setFillColor(sf::Color::White);
    sf::FloatRect playButtonTextBounds = playButtonText.getLocalBounds();
    playButtonText.setOrigin(playButtonTextBounds.left + playButtonTextBounds.width / 2.0f, playButtonTextBounds.top + playButtonTextBounds.height / 2.0f);
    playButtonText.setPosition(playButton.getPosition().x + playButton.getSize().x / 2.f, playButton.getPosition().y + playButton.getSize().y / 2.f);


    sf::RectangleShape returnButton(sf::Vector2f(90.f, 90.f));
    sf::Text returnButtonText;

    returnButton.setFillColor(sf::Color(100, 100, 255));
    returnButton.setPosition(50, 50);

    returnButtonText.setFont(font);
    returnButtonText.setString("X");
    returnButtonText.setCharacterSize(80);
    returnButtonText.setFillColor(sf::Color::White);
    returnButtonText.setPosition(75, 43);

#pragma endregion initCustomLevelsMenu

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

#pragma region ClicksMenu
        if (mode == 1) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            bool isHovering = false;

            for (size_t i = 0; i < buttons.size(); ++i) {
                isHovering = buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

                if (isHovering) {
                    buttons[i].setFillColor(sf::Color::Color(100, 100, 255)); // Blue
                    buttons[i].setSize(hoverSize);

                    if (!buttonFled[i]) {
                        buttons[i].setPosition((window.getSize().x - hoverSize.x) / 2.f, initialYPos + i * (originalSize.y + buttonSpacing) - (hoverSize.y - originalSize.y) / 2.f);
                        buttonFled[i] = true;
                    }
                }
                else {
                    buttons[i].setFillColor(sf::Color::Color(70, 70, 200)); // Dark Blue
                    buttons[i].setSize(originalSize);

                    if (buttonFled[i]) {
                        buttons[i].setPosition((window.getSize().x - originalSize.x) / 2.f, initialYPos + i * (originalSize.y + buttonSpacing));
                        buttonFled[i] = false;
                    }
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMousePressed) {
                for (size_t i = 0; i < buttons.size(); ++i) {
                    if (buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        if (buttonLabels[i] == "Jouer") {
                            return 1; // Play
                        }

                        if (buttonLabels[i] == "Custom") {
                            mode = 2; // Custom Game
                        }

                        if (buttonLabels[i] == "Options") {
                            mode = 3;
                        }

                        if (buttonLabels[i] == "Quitter") {
                            window.close();
                        }

                        isMousePressed = true;
                        break;
                    }
                }
            }

            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                isMousePressed = false;
            }
        }
#pragma endregion ClicksMenu

#pragma region ClicksCustomLevelsMenu

        if (mode == 2) {
            bool mouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

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
                    optionValues[3] = std::max(2, optionValues[3] - 1);
                    optionText4.setString(std::to_string(optionValues[3]));
                    isMousePressed = true;
                }
            }
            else {
                leftButton4.setFillColor(sf::Color(70, 70, 200));
            }

            if (rightButton1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                rightButton1.setFillColor(sf::Color(100, 100, 255));  // Blue on hover
                if (mouseButtonPressed && !isMousePressed) {
                    optionValues[0] = std::min(20, optionValues[0] + 1);
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
                    optionValues[1] = std::min(20, optionValues[1] + 1);
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
                    optionValues[2] = std::min(20, optionValues[2] + 1);
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
                    optionValues[3] = std::min(300, optionValues[3] + 1); // 5min max
                    optionText4.setString(std::to_string(optionValues[3]));
                    isMousePressed = true;
                }
            }
            else {
                rightButton4.setFillColor(sf::Color(70, 70, 200));
            }

            if (!mouseButtonPressed) {
                isMousePressed = false;
            }

            if (playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                playButton.setFillColor(sf::Color(100, 100, 255));  // Light Blue
                if (mouseButtonPressed && !isMousePressed) {

                    MaxEasySoldierCustom = optionValues[0];
                    MaxMediumSoldierCustom = optionValues[1];
                    MaxHardSoldierCustom = optionValues[2];
                    TimeBeforeBossCustom = optionValues[3];
                    return 2;
                    isMousePressed = true;
                }
            }
            else {
                playButton.setFillColor(sf::Color(70, 70, 200));  // Dark Blue
            }

            if (returnButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                returnButton.setFillColor(sf::Color(100, 100, 255));  // Light Blue
                if (mouseButtonPressed && !isMousePressed) {
                    mode = 1;
                }
            }
            else {
                returnButton.setFillColor(sf::Color(70, 70, 200));  // Dark Blue
            }
        }

#pragma endregion ClicksCustomLevelsMenu

        if (mode == 3) {
            settingsMenu.setSize(sf::Vector2f(1500, 700));
            settingsMenu.setPosition(200, 200);
            settingsMenu.setFillColor(sf::Color::Black);

            settingsExitButtonSprite.setTexture(settingsExitButtonTexture);
            settingsExitButtonSprite.setPosition(1400, 210);
            if ((sf::Mouse::getPosition().x <= 1700 && sf::Mouse::getPosition().x >= 1400) && (sf::Mouse::getPosition().y <= 337 && sf::Mouse::getPosition().y >= 210)) {
                settingsExitButtonSprite.setColor(sf::Color::Red);
            }
            else {
                settingsExitButtonSprite.setColor(sf::Color::White);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::Mouse::getPosition().x <= 1700 && sf::Mouse::getPosition().x >= 1400) && (sf::Mouse::getPosition().y <= 337 && sf::Mouse::getPosition().y >= 210)) {
                mode = 1;
            }

            settingsTextGameMusic.setFont(font);
            settingsTextGameMusic.setString("Volume Game Music : ");
            settingsTextGameMusic.setPosition(400, 530);
            settingsTextGameMusic.setScale(1.5f, 1.5f);
            settingsTextGameMusic.setStyle(sf::Text::Bold);

            valueSettingsTextGameMusic.setFont(font);
            std::string Volume_MenuMusic(std::to_string(volumeMusic));
            valueSettingsTextGameMusic.setString(Volume_MenuMusic);
            valueSettingsTextGameMusic.setPosition(800, 530);
            valueSettingsTextGameMusic.setScale(1.5f, 1.5f);
            valueSettingsTextGameMusic.setStyle(sf::Text::Bold);

            plus.setFont(font);
            plus.setString(" + ");
            plus.setPosition(1100, 450);
            plus.setScale(3, 3);

            minus.setFont(font);
            minus.setString(" - ");
            minus.setPosition(1100, 550);
            minus.setScale(3, 3);

            //plus
            if ((sf::Mouse::getPosition().x <= 1150 && sf::Mouse::getPosition().x >= 1120) && (sf::Mouse::getPosition().y <= 520 && sf::Mouse::getPosition().y >= 490)) {
                plus.setFillColor(sf::Color::Red);
            }
            else {
                plus.setFillColor(sf::Color::White);
            }
            if ((sf::Mouse::getPosition().x <= 1150 && sf::Mouse::getPosition().x >= 1120) && (sf::Mouse::getPosition().y <= 520 && sf::Mouse::getPosition().y >= 490) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && volumeMusic < 100) {
                volumeMusic += 5.f;
            }

            //minus
            if ((sf::Mouse::getPosition().x <= 1150 && sf::Mouse::getPosition().x >= 1120) && (sf::Mouse::getPosition().y <= 620 && sf::Mouse::getPosition().y >= 590)) {
                minus.setFillColor(sf::Color::Red);
            }
            else {
                minus.setFillColor(sf::Color::White);
            }
            if ((sf::Mouse::getPosition().x <= 1150 && sf::Mouse::getPosition().x >= 1120) && (sf::Mouse::getPosition().y <= 620 && sf::Mouse::getPosition().y >= 590) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && volumeMusic > 0) {
                volumeMusic -= 5.f;
            }
        }

        window.clear();
        window.draw(background_sprite);
        window.draw(title);

        if (mode == 1) {
            for (size_t i = 0; i < buttons.size(); ++i) {
                window.draw(buttons[i]);
                window.draw(buttonTexts[i]);
            }
        }

        else if (mode == 2) {

#pragma region DrawCustomLevelsMenu
            window.draw(subtitle);

            window.draw(leftButton1);
            window.draw(rightButton1);
            window.draw(titleOptionText1);
            window.draw(optionText1);
            window.draw(leftButtonText1);
            window.draw(rightButtonText1);

            window.draw(leftButton2);
            window.draw(rightButton2);
            window.draw(titleOptionText2);
            window.draw(optionText2);
            window.draw(leftButtonText2);
            window.draw(rightButtonText2);

            window.draw(leftButton3);
            window.draw(rightButton3);
            window.draw(titleOptionText3);
            window.draw(optionText3);
            window.draw(leftButtonText3);
            window.draw(rightButtonText3);

            window.draw(leftButton4);
            window.draw(rightButton4);
            window.draw(titleOptionText4);
            window.draw(optionText4);
            window.draw(leftButtonText4);
            window.draw(rightButtonText4);

            window.draw(playButton);
            window.draw(playButtonText);

            window.draw(returnButton);
            window.draw(returnButtonText);

#pragma endregion DrawCustomLevelsMenu

        }

        else if (mode == 3) {
            window.draw(settingsMenu);
            window.draw(settingsExitButtonSprite);
            window.draw(settingsTextGameMusic);
            window.draw(valueSettingsTextGameMusic);
            window.draw(plus);
            window.draw(minus);
        }


        window.display();
    }
    return 0; 
}