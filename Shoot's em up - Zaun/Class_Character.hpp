#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <windows.h>
#include <unordered_map>
#include <deque>

using namespace std;

class Character {
protected:
	int c_coordX = 225;
	int	c_coordY = 800;
	int c_health;
	bool c_isAlive;
	bool c_invincibility;
	int c_speed;
	int c_attackSpeed;

public:
	Character();
	Character(int CX, int CY);

	~Character();

	struct Ekko_S {
		bool isAttacking = false;
		bool ekko_anim_isAttacking = false;
		int countAnimAtk = 0;
		bool SlowZone = false;
		bool Boomerang = false;
		bool Ult = false;
	}; Ekko_S ekko_S;

	int losePV(int damage);
	int setHealth(int newHealth);
	int getHealth();
	int getCoordX();
	int setCoordX(int X);
	int getCoordY();
	int setCoordY(int Y);
	bool getAlive();
	bool LifeReset();
};

//////////////

class Cooldown {
public:
	struct SpellIcon {
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Text cooldownText;
		bool isReady;
		bool isUnlocked;
		float cooldownTime;
		float elapsedTime;

		SpellIcon() : isReady(true), cooldownTime(0), elapsedTime(0) {}
	};

	SpellIcon Qspell;
	SpellIcon Wspell;
	SpellIcon Espell;
	SpellIcon Ult;
	sf::Font font;

	sf::Text A;
	sf::Text E;
	sf::Text C;
	sf::Text X;

	void updateSpell(SpellIcon& spell, float deltaTime);

	Cooldown();
	~Cooldown();

	void initCooldown(sf::RenderWindow& window);
	void update(float deltaTime, bool Q, bool W, bool E, bool R);
	void draw(sf::RenderWindow& window);
	void startCooldown(const std::string& spellName, float cooldown);
};

//////////////

class Ekko : public Character {
public:
	sf::Texture ekko_walk_texture;
	sf::Sprite ekko_walk_sprite;
	sf::Vector2i ekko_anim;


	/*sf::Texture ekko_Attack_texture;
	sf::Sprite ekko_Attack_sprite;
	sf::Vector2i ekko_anim_Attack;*/

	sf::Texture ekko_Auto_Attack_texture;
	sf::Sprite ekko_Auto_Attack_sprite;
	sf::Vector2i ekko_anim_Auto_Attack;

	sf::Texture ekko_Bullet_Auto_Attack_texture;
	sf::Sprite ekko_Bullet_Auto_Attack_sprite;
	sf::Vector2i ekko_anim_Bullet_Auto_Attack;

	sf::Texture ekko_SlowZone_texture;
	sf::Sprite ekko_SlowZone_sprite;

	sf::Texture ekko_Boomerang_texture;
	sf::Sprite ekko_Boomerang_sprite;

	sf::Text textEnd;
	sf::Font font;
	sf::Text textWin;
	sf::RectangleShape boutonRestart;
	sf::Text textRestart;

	int Ekko_coordX;
	int	Ekko_coordY;
	int Ekko_health;
	bool Ekko_isAlive;
	bool Ekko_invincibility;
	float Ekko_speed;
	float Ekko_attackSpeed;
	int boomerangDamage;
	bool blueBuffActivated;
	bool redBuffActivated;

	std::vector<sf::CircleShape> bullets;

	Ekko(Cooldown& cooldown);
	void initializeSpells();
	bool canCastSpell(const std::string& spellName);
	void castSpell(const std::string& spellName);


	void initEndMenu();
	void printEndMenu(sf::RenderWindow& window);

	void initWinMenu();
	void printWinMenu(sf::RenderWindow& window);


	~Ekko();

	void ekkoDontExitFromScreen();
	void ekkoInitAnimations();
	void ekkoPrintWindow(sf::RenderWindow& window);
	void ekkoCommand();
	void bulletInit();
	void dash();
	void updatePositionHistory();
	void updateSpells(int gameLevel);
	void SlowZone();
	void Boomerang();
	void ult();

	sf::Vector2f dashTargetPosition;
	sf::Vector2f dashDirection;
	bool isDashing;
	sf::Clock dashingTimer;

	bool isSlowZoneActive;
	sf::Vector2f SlowZoneTargetPosition;
	sf::Clock SlowZoneTimer;

	bool isTouchByBoom;
	bool isBoomerangActive;
	bool isBoomerangStart;
	bool isBoomerangComingBack;
	sf::Clock BoomerangTimer;

	bool isUlting;
	sf::Clock UltTimer;

	sf::Vector2f BoomerangStartPosition;
	sf::Vector2f BoomerangTargetPosition;

	bool QspellUnlocked;
	bool WspellUnlocked;
	bool EspellUnlocked;
	bool UltUnlocked;

	int points;
	int usedPoints;
	int level;

private:
	sf::Vector2f direction;
	sf::Vector2f playerPosition;

	struct SpellInfo {
		float cooldownTime = 0.0f;
		std::chrono::time_point<std::chrono::high_resolution_clock> lastCastTime;
	};

	Cooldown& cooldown;
	std::unordered_map<std::string, SpellInfo> spells;
};

