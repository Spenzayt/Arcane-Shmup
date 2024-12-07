#include "Class_Character.hpp"
struct Ekko_S {
	bool isAttacking = false;
	bool ekko_anim_isAttacking = false;
	bool isHealing = false;
	bool isHit = false;
	bool ekko_anim_isHit = false;
	bool isDying = false;
	bool ekko_anim_isDying = false;
	bool printBody = false;
	int countAnimAtk = 0;
	int countAnimHeal = 0;
	int countAnimHit = 0;
	int countAnimDeath = 0;
	int DeathCount = 0;
}; Ekko_S ekko_S;


class Ekko : public Character {
public:
	sf::Texture ekko_walk_texture;
	sf::Sprite ekko_walk_sprite;
	sf::Vector2i ekko_anim;


	sf::Texture ekko_Attack_texture;
	sf::Sprite ekko_Attack_sprite;
	sf::Vector2i ekko_anim_Attack;

	Ekko() : Character("Ekko", 225, 800, 100) {}

	void ekkoDontExitFromScreen();
	void ekkoInitAnimations();
	void ekkoPrintWindow();
	void ekkoCommand();

}; Ekko Ekko_Class;