#include "Class_Character.hpp"

class Ekko : public Character {
public:
	sf::Texture ekko_walk_texture;
	sf::Sprite ekko_walk_sprite;
	sf::Vector2i ekko_anim;


	/*sf::Texture ekko_Attack_texture;
	sf::Sprite ekko_Attack_sprite;
	sf::Vector2i ekko_anim_Attack;*/

	sf::Texture ekko_Auto_Attack_texture;
	sf::Sprite ekko_Auto_Attack_sprite;
	sf::Vector2i ekko_anim_Auto_Attack;

	sf::Texture ekko_Bullet_Auto_Attack_texture;
	sf::Sprite ekko_Bullet_Auto_Attack_sprite;
	sf::Vector2i ekko_anim_Bullet_Auto_Attack;

	vector<sf::CircleShape> bullets;

	Ekko();

	void ekkoDontExitFromScreen();
	void ekkoInitAnimations();
	void ekkoPrintWindow(sf::RenderWindow& window);
	void ekkoCommand();
	void bulletInit();
};