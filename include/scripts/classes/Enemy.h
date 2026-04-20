#pragma once
#include <string>
#include <vector>
#include "scripts/classes/Item.h"
#include "scripts/classes/Attack.h"

class Enemy
{
	private:
		std::string name;
		std::string type_enemy;
		std::string element;
		int level;
		int exp_given;
		int gold_given;
		int max_hp;
		int current_hp;
		int max_mp;
		int current_mp;
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
		std::vector<Item> drop_items;
		std::vector<int> drop_chances; // percentuali di drop corrispondenti agli item
		std::vector<Attack> attacks;

public:
	Enemy(std::string name, std::string type_enemy, std::string element, int level, int exp_given, int gold_given, int max_hp, int max_mp, int strength, int intelligence, int speed, int defense, int magic_defense, std::vector<Item> drop_items, std::vector<int> drop_chances, std::vector<Attack> attacks);
	std::string get_name();
	std::string get_type_enemy();
	std::string get_element();
	int get_level();
	int get_exp_given();
	int get_gold_given();
	int get_current_hp();
	int get_max_hp();
	int get_current_mp();
	int get_max_mp();
	int get_strength();
	int get_intelligence();
	int get_speed();
	int get_defense();
	int get_magic_defense();
	std::vector<Item> get_drop_items();
	std::vector<int> get_drop_chances();
	std::vector<Attack> get_attacks();
	void set_name(std::string name);
	void set_level(int level);
	void set_exp_given(int exp_given);
	void set_gold_given(int gold_given);
	void set_current_hp(int hp);
	void set_max_hp(int hp);
	void set_current_mp(int mp);
	void set_max_mp(int mp);
	void set_strength(int strength);
	void set_intelligence(int intelligence);
	void set_speed(int speed);
	void set_defense(int defense);
	void set_magic_defense(int magic_defense);
	void set_type_enemy(std::string type_enemy);
	void set_element(std::string element);
	void set_drop_items(std::vector<Item> drop_items);
	void set_drop_chances(std::vector<int> drop_chances);
	void set_attacks(std::vector<Attack> attacks);
	void set_current_strength(int strength);
	void set_current_intelligence(int intelligence);
	void set_current_speed(int speed);
	void set_current_defense(int defense);
	void set_current_magic_defense(int magic_defense);
	void add_attack(Attack attack);
	int get_current_strength();
	int get_current_intelligence();
	int get_current_speed();
	int get_current_defense();
	int get_current_magic_defense();

};
