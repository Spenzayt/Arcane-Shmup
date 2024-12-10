#include "Class_Character.hpp"

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

	std::vector<sf::CircleShape> bullets;

	Ekko();

	void ekkoDontExitFromScreen();
	void ekkoInitAnimations();
	void ekkoPrintWindow(sf::RenderWindow& window);
	void ekkoCommand();
	void bulletInit();
    void initializeSpells();
    void castSpell(const std::string& spellName);;
	void dash();
	void updatePositionHistory();
	void updateTeleport();

	std::deque<std::pair<sf::Vector2f, sf::Time>> positionHistory;
	sf::Clock positionClock;
	bool isTeleporting = false;
	sf::Clock teleportTimer;

	sf::Vector2f dashTargetPosition;
	sf::Vector2f dashDirection;
	bool isDashing = false;
	sf::Clock dashingTimer;

private:
    sf::Vector2f direction;
    sf::Vector2f playerPosition;

    struct SpellInfo {
        float cooldownTime = 0.0f;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastCastTime;
    };
    std::unordered_map<std::string, SpellInfo> spells;
    bool canCastSpell(const std::string& spellName);
};
