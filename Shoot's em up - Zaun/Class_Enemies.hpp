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
	int e_coordX;
	int e_coordY;
	int e_health;
	bool e_isAlive;


public:
	Enemies();
	Enemies(int CX, int CY, bool A);
	~Enemies();

	virtual int losePV(int damage);
	virtual int getHealth();
	virtual int setHealth(int newHealth);
	virtual int getCoordX();
	virtual int setCoordX(int X);
	virtual int getCoordY();
	virtual int setCoordY(int Y);
	virtual bool getAlive();
};

class Marcus : public Enemies {
public:

	int m_coordX;
	int m_coordY;
	int m_health;
	bool m_isAlive;
	bool marcusApparition;

	bool isAttacking;
	int countAnimAtk;
	bool moveToFight;
	bool reload;
	int countBulletsMarcus;
	int attackSpeed;
	int attackSpeed2;
	float bulletSpeed;
	float laserSpeed;
	float speed;
	int countAnimTrans;
	bool transIsIn;
	bool isAttackingV2;
	bool laserActive;
	int countLaserTime;

	sf::Texture marcus_Auto_Attack_texture;
	sf::Sprite marcus_Auto_Attack_sprite;
	sf::Vector2i marcus_anim_Auto_Attack;

	sf::Texture marcus_Bullet_Auto_Attack_texture;
	sf::Sprite marcus_Bullet_Auto_Attack_sprite;
	sf::Vector2i marcus_anim_Bullet_Auto_Attack;

	sf::Texture marcus_TransSecondPhase_texture;
	sf::Sprite marcus_TransSecondPhase_sprite;
	sf::Vector2i marcus_anim_TransSecondPhase;

	sf::Texture marcus_SecondPhase_texture;
	sf::Sprite marcus_SecondPhase_sprite;
	sf::Vector2i marcus_anim_SecondPhase;

	vector<sf::CircleShape> MarcusBullets;
	vector<sf::CircleShape> MarcusLaser;


	Marcus();
	~Marcus();

	void marcusInitAnimations();
	void marcusPrintWindow(sf::RenderWindow& window);
	void marcusBulletInit();

	int losePV(int damage) override;
	int getHealth() override;
	int setHealth(int newHealth) override;
	int getCoordX()override;
	int setCoordX(int X)override;
	int getCoordY()override;
	int setCoordY(int Y)override;
	bool getAlive()override;
};


class Soldier : public Enemies {
public:

	int s_coordX = 1600;
	int s_coordY = 500;
	int s_health = 1;
	bool s_isAlive = true;
	bool reload = false;
	int attackCountSoldier = 0;
	int countBulletsSoldier = 0;
	bool moveToFight = true;

	int attackSpeed = 100;
	float bulletSpeed = 1.0f;
	float speed = 1.0f;

	sf::Texture soldier_walk_texture;
	sf::Sprite soldier_walk_sprite;
	sf::Vector2i soldier_anim;

	/*sf::Texture soldier_Auto_Attack_texture;
	sf::Sprite soldier_Auto_Attack_sprite;
	sf::Vector2i soldier_anim_Auto_Attack;*/

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
	void deleteSoldiers();
	void soldierPrintWindow(sf::RenderWindow& window);
	void bulletCreation();

	int losePV(int damage) override;
	int getHealth() override;
	int getCoordX()override;
	int setCoordX(int X)override;
	int getCoordY()override;
	int setCoordY(int Y)override;
	bool getAlive()override;
};

class MediumSoldier : public Enemies {
public:

	int ms_coordX = 1600;
	int ms_coordY = 700;
	int ms_health = 2;
	bool ms_isAlive = true;
	bool reload = false;
	int attackCountMediumSoldier = 0;
	int countBulletsMediumSoldier = 0;
	bool moveToFight = true;

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
	void deleteMediumSoldiers();
	void bulletCreation();

	int losePV(int damage) override;
	int getHealth() override;
	int getCoordX()override;
	int setCoordX(int X)override;
	int getCoordY()override;
	int setCoordY(int Y)override;
	bool getAlive()override;
};

class HardSoldier : public Enemies {
public:

	int hs_coordX = 1600;
	int hs_coordY = 900;
	int hs_health = 3;
	bool hs_isAlive = true;
	bool reload = false;
	int attackCountHardSoldier = 0;
	int countBulletsHardSoldier = 0;
	bool moveToFight = true;

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
	void deleteHardSoldiers();
	void bulletCreation();

	int losePV(int damage) override;
	int getHealth() override;
	int getCoordX()override;
	int setCoordX(int X)override;
	int getCoordY()override;
	int setCoordY(int Y)override;
	bool getAlive()override;
};