#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <vector>
#include "scripts/classes/Attack.h"

// STRENGTH, INTELLIGENCE, SPEED, DEFENSE, MAGIC_DEFENSE

class Character
{
private:
	std::string name;
	std::string classe;
	int level;
	int max_hp;
	int current_hp;
	int max_mp;
	int current_mp;
	int exp;
	int next_level_exp;
	int strength;
	int current_strength;
	int intelligence;
	int current_intelligence;
	int speed;
	int current_speed;
	int defense;
	int current_defense;
	int magic_defense;
	int current_magic_defense;
	int luck;
	int current_luck;
	std::vector<Attack> attacks;
	// get attacks when leveling up in the future

public:
	Character(std::string name, std::string classe, int level, int max_hp, int max_mp, int strength, int intelligence, int speed, int defense, int magic_defense, int luck, std::vector<Attack> attacks);

	void set_name(std::string name);

	std::string get_name();

	void set_classe(std::string classe);

	std::string get_classe();

	int get_level();

	void set_level(int level);

	int get_current_hp();

	void set_current_hp(int hp);

	int get_max_hp();

	void set_max_hp(int hp);

	int get_current_mp();

	void set_current_mp(int mp);

	int get_max_mp();

	void set_max_mp(int mp);

	int get_exp();

	void set_exp(int exp);

	int get_next_level_exp();

	void set_next_level_exp(int exp);

	int get_strength();

	int get_current_strength();

	void set_strength(int strength);

	void set_current_strength(int strength);

	int get_intelligence();

	int get_current_intelligence();

	void set_intelligence(int intelligence);

	void set_current_intelligence(int intelligence);

	int get_speed();

	int get_current_speed();

	void set_speed(int speed);

	void set_current_speed(int speed);

	int get_defense();

	int get_current_defense();

	void set_defense(int defense);

	void set_current_defense(int defense);

	int get_magic_defense();

	int get_current_magic_defense();

	void set_magic_defense(int magic_defense);

	void set_current_magic_defense(int magic_defense);

	int get_luck();

	int get_current_luck();

	void set_luck(int luck);

	void set_current_luck(int luck);

	void gain_exp(int exp_gained);

	void level_up();

	std::vector<Attack> get_attacks();

	void set_attacks(std::vector<Attack> attacks);

	void add_attack(Attack attack);
};

#endif
