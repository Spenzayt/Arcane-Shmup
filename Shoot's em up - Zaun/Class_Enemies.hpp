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