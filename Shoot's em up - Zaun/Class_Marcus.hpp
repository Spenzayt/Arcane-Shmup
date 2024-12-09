#include "Class_Enemies.hpp"

class Marcus : public Enemies {
public:
	sf::Texture marcus_walk_texture;
	sf::Sprite marcus_walk_sprite;
	sf::Vector2i marcus_anim;


	/*sf::Texture ekko_Attack_texture;
	sf::Sprite ekko_Attack_sprite;
	sf::Vector2i ekko_anim_Attack;*/

	sf::Texture marcus_Auto_Attack_texture;
	sf::Sprite marcus_Auto_Attack_sprite;
	sf::Vector2i marcus_anim_Auto_Attack;

	sf::Texture marcus_Bullet_Auto_Attack_texture;
	sf::Sprite marcus_Bullet_Auto_Attack_sprite;
	sf::Vector2i marcus_anim_Bullet_Auto_Attack;

	vector<sf::CircleShape> MarcusBullets;

	Marcus();

	void marcusDontExitFromScreen();
	void marcusInitAnimations();
	void marcusPrintWindow(sf::RenderWindow& window);
	void marcusBulletInit();
};