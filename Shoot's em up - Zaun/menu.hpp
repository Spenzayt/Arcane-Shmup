#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class Menu {
private:
    RenderWindow window;
    Font font;
    Texture image;
    Sprite bg;

    vector<string> options;
    vector<Vector2f> coords;
    vector<Text> texts;

    int pos = 1;
    bool play = false;

    void set_values();
    void loop_events();
    void draw_all();

public:
    Menu();
    ~Menu() = default;

    void run_menu();

    bool isPlaySelected() const { return play; }
};
