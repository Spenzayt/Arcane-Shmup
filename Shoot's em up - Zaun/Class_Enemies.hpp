#include "Class_Entities.hpp"

class Enemies : public Entities {
protected:
	std::string e_name;
	int e_coordX, e_coordY;
	int e_health;
	bool e_isAlive = true;


public:
	Enemies();
	Enemies(std::string n, int CX, int CY, int h);

	int losePV(int damage) override;
	int getHealth() override;
	int getCoordX() override;
	int setCoordX(int X) override;
	int getCoordY() override;
	int setCoordY(int Y) override;
	std::string getName() override;
	bool getAlive() override;
	int heal() override;
	int setHealth(int pv) override;
	int HealthReset(int pv) override;
	bool LifeReset();
}; Enemies Enn_Class;