#include "menu.hpp"

using namespace sf;
using namespace std;

Menu::Menu() {
    window.create(VideoMode(1920, 1080), "Zaun : La bataille des nations", Style::Fullscreen);

    if (!font.loadFromFile("assets/ethn.otf")) {
        cerr << "Error when loading font" << endl;
    }

    if (!image.loadFromFile("assets/backgrounds/background-menu.png")) {
        cerr << "Error when loading background menu" << endl;
    }

    bg.setTexture(image);
    bg.setScale(1.5f, 1.5f);

    set_values();
}

void Menu::set_values() {
    options = { "Arcane Shoot's em up", "Play", "Options", "Credits", "Quit" };
    coords = { {835, 65}, {940, 290}, {920, 425}, {920, 560}, {950, 690} };

    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setCharacterSize(i == 0 ? 19 : 24);
        text.setOutlineColor(Color::Black);
        text.setPosition(coords[i]);
        text.setOutlineThickness(i == 1 ? 4 : 0);
        texts.push_back(text);
    }
}

void Menu::loop_events() {
    Event event;
    static Clock keyTimer;

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
    }

    if (keyTimer.getElapsedTime().asMilliseconds() > 200) {
        if (Keyboard::isKeyPressed(Keyboard::Down) && pos < static_cast<int>(options.size()) - 1) {
            texts[pos].setOutlineThickness(0);
            ++pos;
            texts[pos].setOutlineThickness(4);
            keyTimer.restart();
        }

        if (Keyboard::isKeyPressed(Keyboard::Up) && pos > 1) {
            texts[pos].setOutlineThickness(0);
            --pos;
            texts[pos].setOutlineThickness(4);
            keyTimer.restart();
        }

        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            if (pos == 4) {
                window.close();
            }
            if (pos == 1) {
                play = true;
                window.close();
            }
            keyTimer.restart();
        }
    }
}

void Menu::draw_all() {
    window.clear();
    window.draw(bg);
    for (const auto& text : texts) {
        window.draw(text);
    }
    window.display();
}

void Menu::run_menu() {
    while (window.isOpen()) {
        loop_events();
        draw_all();
    }
}
