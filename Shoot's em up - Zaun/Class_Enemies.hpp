#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

class Enemies {
protected:
	std::string e_name;
	int e_coordX = 1600;
	int e_coordY = 800;
	int e_health;
	bool e_isAlive = true;


public:
	Enemies();
	Enemies(std::string n, int CX, int CY, int h);

	struct Marcus_S {
		bool isAttacking = false;
		bool marcus_anim_isAttacking = false;
		bool isHealing = false;
		bool isHit = false;
		bool marcus_anim_isHit = false;
		bool isDying = false;
		bool marcus_anim_isDying = false;
		bool printBody = false;
		int countAnimAtk = 0;
		int countAnimHeal = 0;
		int countAnimHit = 0;
		int countAnimDeath = 0;
		int DeathCount = 0;
	}; Marcus_S marcus_S;

	struct Soldier_S {
		bool isAttacking = false;
		bool anim_isAttacking = true;
		bool isHealing = false;
		bool isHit = false;
		bool anim_isHit = false;
		bool isDying = false;
		bool anim_isDying = false;
		bool printBody = false;
		int countAnimAtk = 0;
		int countAnimHeal = 0;
		int countAnimHit = 0;
		int countAnimDeath = 0;
		int DeathCount = 0;
	}; Soldier_S soldier_S;

	int losePV(int damage);
	int getHealth();
	int getCoordX();
	int setCoordX(int X);
	int getCoordY();
	int setCoordY(int Y);
	std::string getName();
	bool getAlive();
	int heal();
	int setHealth(int pv);
	int HealthReset(int pv);
	bool LifeReset();
};

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


class Soldier : public Enemies {
public:
	sf::Texture soldier_walk_texture;
	sf::Sprite soldier_walk_sprite;
	sf::Vector2i soldier_anim;


	/*sf::Texture ekko_Attack_texture;
	sf::Sprite ekko_Attack_sprite;
	sf::Vector2i ekko_anim_Attack;*/

	/*sf::Texture soldier_Auto_Attack_texture;
	sf::Sprite soldier_Auto_Attack_sprite;
	sf::Vector2i soldier_anim_Auto_Attack;

	sf::Texture soldier_Bullet_Auto_Attack_texture;
	sf::Sprite soldier_Bullet_Auto_Attack_sprite;
	sf::Vector2i soldier_anim_Bullet_Auto_Attack;*/

	vector<sf::CircleShape> SoldierBullets;

	Soldier();

	void soldierDontExitFromScreen();
	void soldierInitAnimations();
	void soldierPrintWindow(sf::RenderWindow& window);
	void soldierBulletInit();
};