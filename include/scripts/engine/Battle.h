#pragma once
#include <vector>
#include <iostream>
#include "scripts/classes/Character.h"
#include "scripts/classes/Enemy.h"
#include "scripts/classes/PlayerVars.h"
#include <utility>
#include <algorithm>

class Battle
{
private:
	int turn;
public:
	bool start_battle(std::vector<Character>& characters, std::vector<Enemy> enemies, PlayerVars& playervars);
	std::vector<std::string> check_speed(std::vector<Character> characters, std::vector<Enemy> enemies);
	void bubble_sort(std::vector<int>& speed_values, std::vector<std::string>& speed_names);
	int attack_calc(Character* chara, Enemy enemy);
	void attack_magic(Character* chara, std::vector<Enemy>& enemies, Attack magic);
	void magic_damage_calc(Character* chara, Enemy& enemy, Attack magic);
	void heal_magic(Character* chara, std::vector<Character>& characters, Attack magic);
	void buff_magic(Character* chara, std::vector<Character>& characters, std::vector<Enemy>& enemies, Attack attack);
	void apply_buff_ally(Character& chara, std::string stat, float amount);
	void apply_buff_enemy(Enemy& enemy, std::string stat, float amount);
	void healing_item(std::vector<Character>& characters, PlayerVars& playervars, int item_index);
	void mana_item(std::vector<Character>& characters, PlayerVars& playervars, int item_index);
	void revive_item(std::vector<Character>& characters, PlayerVars& playervars, int item_index);
	void damaging_item(std::vector<Enemy>& enemies, PlayerVars& playervars, int item_index);

	int stat_scaling(Character* chara, std::string scaling);
	int enemy_scaling(Enemy* enemy, std::string scaling);
};
