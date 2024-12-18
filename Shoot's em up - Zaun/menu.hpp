#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

class Menu {
public:
    int mainMenu(sf::RenderWindow& window);

    int NbEasySoldierCustom = 1;
    int NbMediumSoldierCustom = 1;
    int NbHardSoldierCustom = 1;
    int MaxWavesCustom = 1;
    float CoefDifficultyCustom = 1.5f;
    float volumeMusic = 10.f;

    sf::Sprite background_sprite;
    sf::Text title, subtitle;


private:
    sf::Texture background_texture;

    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    std::vector<std::string> buttonLabels = { "Jouer", "Custom", "Options", "Quitter" };
    std::vector<bool> buttonFled;

    std::vector<int> optionValues = { 0, 0, 0, 0, 0 };

    sf::RectangleShape leftButton1, leftButton2, leftButton3, leftButton4, leftButton5;
    sf::RectangleShape rightButton1, rightButton2, rightButton3, rightButton4, rightButton5;
    sf::Text optionText1, optionText2, optionText3, optionText4, optionText5;
    sf::Text leftButtonText1, leftButtonText2, leftButtonText3, leftButtonText4, leftButtonText5;
    sf::Text rightButtonText1, rightButtonText2, rightButtonText3, rightButtonText4, rightButtonText5;

    sf::RectangleShape playButton;
    sf::Text playButtonText;

    sf::Texture settingsExitButtonTexture;
    sf::Sprite settingsExitButtonSprite;
    sf::RectangleShape settingsMenu;
    sf::Text settingsTextGameMusic;
    sf::Text valueSettingsTextGameMusic;
    sf::Text plus;
    sf::Text minus;



    sf::Vector2f buttonSize = { 400.f, 100.f };
    sf::Vector2f hoverSize = buttonSize * 1.05f;
    float buttonSpacing = 40.f;
    float initialYPos = 250.f;

    bool isMousePressed = false;
    int mode = 1;
};