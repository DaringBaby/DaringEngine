#include "scripts/classes/PlayerVars.h"

void PlayerVars::create_player(std::string player_name) {
	std::string name = player_name;
	int gold = 0;

}

std::string PlayerVars::get_name() {
	return this->name;
}

void PlayerVars::set_name(std::string player_name) {
	this->name = player_name;
}

int PlayerVars::get_gold() {
	return this->gold;
}

void PlayerVars::set_gold(int amount) {
	this->gold = amount;
}

void PlayerVars::add_gold(int amount) {
	this->gold += amount;
}

void PlayerVars::subtract_gold(int amount) {
	this->gold -= amount;
}

std::vector<Item> PlayerVars::get_inventory() {
	return this->inventory;
}

std::vector<int> PlayerVars::get_items_quantity() {
	return this->items_quantity;
}

void PlayerVars::add_item(Item item, int quantity) {
	for (int i=0; i< this->inventory.size(); i++) {
		if (this->inventory[i].get_name() == item.get_name()) {
			this->items_quantity[i] += quantity;
			return;
		}
	}
	this->inventory.push_back(item);
	this->items_quantity.push_back(quantity);
	return;
}

void PlayerVars::remove_item(Item item, int quantity) {
	for (int i = 0; i < this->inventory.size(); i++) {
		if (this->inventory[i].get_name() == item.get_name()) {
			if (this->items_quantity[i] > quantity) {
				this->items_quantity[i] -= quantity;
				return;
			}
			else {
				this->inventory.erase(this->inventory.begin() + i);
				this->items_quantity.erase(this->items_quantity.begin() + i);
				return;
			}
		}
	}
}

std::vector<Equip> PlayerVars::get_equipment() {
	return this->equipment;
}

std::vector<int> PlayerVars::get_equip_quantity() {
	return this->equip_quantity;
}

void PlayerVars::add_equip(Equip equip, int quantity) {
	for (int i=0; i< this->equipment.size(); i++) {
		if (this->equipment[i].get_name() == equip.get_name()) {
			this->equip_quantity[i] += quantity;
			return;
		}
	}
	this->equipment.push_back(equip);
	this->equip_quantity.push_back(quantity);
	return;
}

void PlayerVars::remove_equip(Equip equip, int quantity) {
	for (int i = 0; i < this->equipment.size(); i++) {
		if (this->equipment[i].get_name() == equip.get_name()) {
			if (this->equip_quantity[i] > quantity) {
				this->equip_quantity[i] -= quantity;
				return;
			}
			else {
				this->equipment.erase(this->equipment.begin() + i);
				this->equip_quantity.erase(this->equip_quantity.begin() + i);
				return;
			}
		}
	}
}

bool PlayerVars::get_flag(int index) {
	return this->flags[index];
}

void PlayerVars::set_flag(int index, bool value) {
	this->flags[index] = value;
}

void PlayerVars::add_flag(bool value) {
	this->flags.push_back(value);
}
