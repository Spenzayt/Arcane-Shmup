#include "Class_Entities.hpp"

class Character : public Entities {
protected:
	std::string c_name;
	int c_coordX = 225;
	int	c_coordY = 800;
	int c_health;
	bool c_isAlive = true;

public:
	Character();
	Character(std::string n, int CX, int CY, int h);

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
}; 