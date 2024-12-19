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
	std::string c_name;
	int c_coordX = 225;
	int	c_coordY = 800;
	int c_health = 3;
	bool c_isAlive = true;
	bool c_invincibility = false;
	int c_speed = 1;
	int c_attackSpeed = 1;

public:
	Character();
	Character(std::string n, int CX, int CY);

	~Character();

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
		bool SlowZone = false;
		bool Boomerang = false;
	}; Ekko_S ekko_S;

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

//////////////

class Cooldown {
private:
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

	void updateSpell(SpellIcon& spell, float deltaTime);

public:
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

	std::string Ekko_name;
	int Ekko_coordX = 225;
	int	Ekko_coordY = 800;
	int Ekko_health = 3;
	bool Ekko_isAlive = true;
	bool Ekko_invincibility = false;
	float Ekko_speed = 1.0f;
	float Ekko_attackSpeed = 1.0f;
	int boomerangDamage = 5;
	bool blueBuffActivated = false;
	bool redBuffActivated = false;


	std::vector<sf::CircleShape> bullets;

	Ekko(Cooldown& cooldown);
	void initializeSpells();
	bool canCastSpell(const std::string& spellName);
	void castSpell(const std::string& spellName);

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

	std::deque<std::pair<sf::Vector2f, sf::Time>> positionHistory;
	sf::Clock positionClock;
	bool isTeleporting = false;
	sf::Clock teleportTimer;

	sf::Vector2f dashTargetPosition;
	sf::Vector2f dashDirection;
	bool isDashing = false;
	sf::Clock dashingTimer;

	bool isSlowZoneActive = false;
	sf::Vector2f SlowZoneTargetPosition;
	sf::Clock SlowZoneTimer;

	bool isBoomerangActive = false;
	bool isBoomerangStart = false;
	bool isBoomerangComingBack = false;
	sf::Clock BoomerangTimer;

	sf::Vector2f BoomerangStartPosition;
	sf::Vector2f BoomerangTargetPosition;

	bool QspellUnlocked;
	bool WspellUnlocked;
	bool EspellUnlocked;
	bool UltUnlocked;

private:
	sf::Vector2f direction;
	sf::Vector2f playerPosition;

	struct SpellInfo {
		float cooldownTime = 0.0f;
		std::chrono::time_point<std::chrono::high_resolution_clock> lastCastTime;
	};

	Cooldown& cooldown;
	std::unordered_map<std::string, SpellInfo> spells;

	int points;
	int usedPoints;
	int level;
};

