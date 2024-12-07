#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <windows.h>


using namespace std;

class Entities {
protected:
	int E_coordX = 0;
	int E_coordY = 0;
	int E_health = 0;
	bool E_isAlive = true;
	bool E_isAttacking = false;
	bool E_isHit = false;
	bool E_isDying = false;
	bool E_isDead = false;
	std::string E_name;

public:

	Entities(bool A);

	virtual int losePV(int damage);
	virtual int getHealth();
	virtual int getCoordX();
	virtual int setCoordX(int X);
	virtual int getCoordY();
	virtual int setCoordY(int Y);
	virtual std::string getName();
	virtual bool getAlive();
	virtual int heal();
	virtual int setHealth(int pv);
	virtual int HealthReset(int pv);
	virtual bool LifeReset();
};