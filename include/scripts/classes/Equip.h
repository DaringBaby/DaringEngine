#pragma once
#include <string>
#include "scripts/classes/Item.h"
class Equip: public Item
{
	private:
		int strength_bonus;
		int intelligence_bonus;
		int speed_bonus;
		int defense_bonus;
		int magic_defense_bonus;
		int luck_bonus;
	public:
		Equip(std::string name, std::string description, int price, int strength_bonus, int intelligence_bonus, int speed_bonus, int defense_bonus, int magic_defense_bonus, int luck_bonus);
		int get_strength_bonus();
		int get_intelligence_bonus();
		int get_speed_bonus();
		int get_defense_bonus();
		int get_magic_defense_bonus();
		int get_luck_bonus();
		void set_strength_bonus(int strength_bonus);
		void set_intelligence_bonus(int intelligence_bonus);
		void set_speed_bonus(int speed_bonus);
		void set_defense_bonus(int defense_bonus);
		void set_magic_defense_bonus(int magic_defense_bonus);
		void set_luck_bonus(int luck_bonus);
};
