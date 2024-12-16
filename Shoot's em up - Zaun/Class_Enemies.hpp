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
	int e_coordX;
	int e_coordY;
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
	int s_coordY = 500;
	int s_health = 1;
	bool s_isAlive = true;
	bool reload = false;
	int attackCountSoldier = 0;
	int countBulletsSoldier = 0;
	bool moveToFight = true;

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

	Soldier(const sf::Vector2f& positionSoldier, sf::Texture& soldierTexture);

	Soldier();

	~Soldier();

	void soldierDontExitFromScreen();
	void soldierInitAnimations();
	void soldierBulletInit();

	void createSoldiers(int little);
	void soldierPrintWindow(sf::RenderWindow& window);
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

class MediumSoldier : public Enemies {
public:

	std::string ms_name;
	int ms_coordX = 1600;
	int ms_coordY = 700;
	int ms_health = 2;
	bool ms_isAlive = true;
	bool reload = false;
	int attackCountMediumSoldier = 0;
	int countBulletsMediumSoldier = 0;
	bool moveToFight = true;

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

	sf::Texture medium_soldier_walk_texture;
	sf::Sprite medium_soldier_walk_sprite;
	sf::Vector2i medium_soldier_anim;

	/*sf::Texture medium_soldier_Auto_Attack_texture;
	sf::Sprite medium_soldier_Auto_Attack_sprite;
	sf::Vector2i medium_soldier_anim_Auto_Attack;*/

	sf::Texture medium_soldier_Bullet_Auto_Attack_texture;
	sf::Sprite medium_soldier_Bullet_Auto_Attack_sprite;
	sf::Vector2i medium_soldier_anim_Bullet_Auto_Attack;

	std::vector<MediumSoldier> mediumSoldiers_vector;
	vector<sf::CircleShape> MediumSoldierBullets;

	MediumSoldier(const sf::Vector2f& positionSoldier, sf::Texture& soldierTexture);

	MediumSoldier();

	~MediumSoldier();

	void mediumSoldierDontExitFromScreen();
	void mediumSoldierInitAnimations();
	void mediumSoldierPrintWindow(sf::RenderWindow& window);
	void mediumSoldierBulletInit();
	void createSoldiers(int little);
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

class HardSoldier : public Enemies {
public:

	std::string hs_name;
	int hs_coordX = 1600;
	int hs_coordY = 900;
	int hs_health = 3;
	bool hs_isAlive = true;
	bool reload = false;
	int attackCountHardSoldier = 0;
	int countBulletsHardSoldier = 0;
	bool moveToFight = true;

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
	int attackSpeed = 90;
	float bulletSpeed = 1.5f;
	float speed = 1.0f;

	sf::Texture hard_soldier_walk_texture;
	sf::Sprite hard_soldier_walk_sprite;
	sf::Vector2i hard_soldier_anim;

	/*sf::Texture hard_Soldier_Auto_Attack_texture;
	sf::Sprite hardSoldier_Auto_Attack_sprite;
	sf::Vector2i hardSoldier_anim_Auto_Attack;*/

	sf::Texture hard_soldier_Bullet_Auto_Attack_texture;
	sf::Sprite hard_soldier_Bullet_Auto_Attack_sprite;
	sf::Vector2i hard_soldier_anim_Bullet_Auto_Attack;

	std::vector<HardSoldier> hardSoldiers_vector;
	vector<sf::CircleShape> HardSoldierBullets;

	HardSoldier(const sf::Vector2f& positionSoldier, sf::Texture& soldierTexture);

	HardSoldier();

	~HardSoldier();

	void hardSoldierDontExitFromScreen();
	void hardSoldierInitAnimations();
	void hardSoldierPrintWindow(sf::RenderWindow& window);
	void hardSoldierBulletInit();
	void createSoldiers(int little);
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
