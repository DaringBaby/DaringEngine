#pragma once

#include <string>
#include <vector>
#include "scripts/classes/Item.h"
#include "scripts/classes/Equip.h"
class PlayerVars {
	private:
		std::string name;
		int gold;
		std::vector<Item> inventory;
		std::vector<int> items_quantity;
		std::vector<Equip> equipment;
		std::vector<int> equip_quantity;
		std::vector<bool> flags;
public:
		void create_player(std::string player_name);
		std::string get_name();
		void set_name(std::string player_name);
		int get_gold();
		void set_gold(int amount);
		void add_gold(int amount);
		void subtract_gold(int amount);
		std::vector<Item> get_inventory();
		std::vector<int> get_items_quantity();
		void add_item(Item item, int quantity);
		void remove_item(Item item, int quantity);
		std::vector<Equip> get_equipment();
		std::vector<int> get_equip_quantity();
		void add_equip(Equip equip, int quantity);
		void remove_equip(Equip equip, int quantity);
		bool get_flag(int index);
		void set_flag(int index, bool value);
		void add_flag(bool value);
};
