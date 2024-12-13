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
	int e_health = 100;
	bool e_isAlive = true;


public:
	Enemies();
	Enemies(std::string n, int CX, int CY, bool A);
	~Enemies();

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
		bool anim_isAttacking = false;
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
		int attackSpeed = 100;
		float bulletSpeed = 1.0f;
		float speed = 1.0f;
	}; Soldier_S soldier_S;

	virtual int losePV(int damage);
	virtual int getHealth();
	virtual int getCoordX();
	virtual int setCoordX(int X);
	virtual int getCoordY();
	virtual int setCoordY(int Y);
	virtual std::string getName();
	virtual bool getAlive();
	virtual int heal();
};

class Marcus : public Enemies {
public:

	std::string m_name;
	int m_coordX = 1600;
	int m_coordY = 800;
	int m_health = 200;
	bool m_isAlive = true;

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
	~Marcus();


	void marcusDontExitFromScreen();
	void marcusInitAnimations();
	void marcusPrintWindow(sf::RenderWindow& window);
	void marcusBulletInit();

	int losePV(int damage) override;
	int getHealth() override;
	int getCoordX()override;
	int setCoordX(int X)override;
	int getCoordY()override;
	int setCoordY(int Y)override;
	std::string getName()override;
	bool getAlive()override;
	int heal()override;
};


class Soldier : public Enemies {
public:

	std::string s_name;
	int s_coordX = 1600;
	int s_coordY = 800;
	int s_health = 1;
	bool s_isAlive = true;

	sf::Texture soldier_walk_texture;
	sf::Sprite soldier_walk_sprite;
	sf::Vector2i soldier_anim;

	sf::Texture soldier_Auto_Attack_texture;
	sf::Sprite soldier_Auto_Attack_sprite;
	sf::Vector2i soldier_anim_Auto_Attack;

	sf::Texture soldier_Bullet_Auto_Attack_texture;
	sf::Sprite soldier_Bullet_Auto_Attack_sprite;
	sf::Vector2i soldier_anim_Bullet_Auto_Attack;

	std::vector<Soldier> soldiers_vector;
	std::vector<sf::CircleShape> SoldierBullets;

	Soldier(const sf::Color& color, const sf::Vector2f& positionSoldier, sf::Texture& soldierTexture) {
		soldier_S.attackSpeed = 135;
		soldier_S.bulletSpeed = 0.8f;
		soldier_walk_texture.setSmooth(true);
		soldier_walk_sprite.setTexture(soldierTexture);
		soldier_walk_sprite.setTextureRect(sf::IntRect(200, 0, -200, 157));
		soldier_walk_sprite.setColor(color);
		soldier_walk_sprite.setPosition(positionSoldier);
	}

	Soldier();

	~Soldier();

	void soldierDontExitFromScreen();
	void soldierInitAnimations();
	void soldierBulletInit();
	void death();

	void createSoldiers(int little);
	void otherSoldiersSpawn(sf::RenderWindow& window);
	void bulletCreation();

	int losePV(int damage) override;
	int getHealth() override;
	int getCoordX()override;
	int setCoordX(int X)override;
	int getCoordY()override;
	int setCoordY(int Y)override;
	std::string getName()override;
	bool getAlive()override;
	int heal()override;
};