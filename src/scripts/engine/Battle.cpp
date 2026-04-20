#include "scripts/engine/Battle.h"
#include <iostream>

bool Battle::start_battle(std::vector<Character>& characters, std::vector<Enemy> enemies, PlayerVars& playervars) {
	this->turn = 0;
	bool battle = true;
	std::string type;
	Character* chara = nullptr;
	Enemy* enemy = nullptr;
	while (battle) { // battle loop // DID ENEMY ATTACK, CONTINUE WITH ENEMY HP <= 0 AND BATTLE END

		std::vector<std::string> turn_order = check_speed(characters, enemies); // turn order, desc

		for (int i = 0; i < turn_order.size(); i++) { // retrieve character/enemy that has to attack
			for (int j = 0; j < characters.size(); j++) {

				if (turn_order[i] == characters[j].get_name()) { // entity type is player
					type = "player";
					chara = &characters[j];
					break;
				}

				if (turn_order[i] == enemies[j].get_name()) { // entity type is enemy
					type = "enemy";
					enemy = &enemies[j];
					break;
				}


			}
			if (type == "player") {
				if (chara->get_current_hp() <= 0) {
					std::cout << chara->get_name() << " is unconscious and cannot act this turn.\n";
					continue; // skip turn if HP <= 0 // does it work?
				}

				int selection;
				std::cout << "It's " << chara->get_name() << "'s turn. Choose an action:\n";
				std::cout << "1. Attack\n2. Magic\n3. Use Item\n4. Flee\n";
				std::cin >> selection;
				switch (selection) {
				case 1:
				{
					int damage;
					int index_enemy;
					std::cout << chara->get_name() << " attacks!\n";
					if (enemies.size() == 1) {
						index_enemy = 0;
					}
					else {
						do {
							std::cout << "Choose an enemy to attack:\n";
							std::cin >> index_enemy;
						} while (index_enemy < 0 || index_enemy >= enemies.size());
					}
					damage = attack_calc(chara, enemies[index_enemy]);
					enemies[index_enemy].set_current_hp(enemies[index_enemy].get_current_hp() - damage);
					std::cout << "Dealt " << damage << " damage to " << enemies[index_enemy].get_name() << "!\n";
					break;
				}
				case 2:
				{
					int damage;
					int index_enemy;
					int index_magic;
					int index_go_back = chara->get_attacks().size() + 1;
					std::cout << "Magic: \n";
					for (int i = 0; i < chara->get_attacks().size(); i++) {
						std::cout << i << ". " << chara->get_attacks()[i].get_name() << " - " << chara->get_attacks()[i].get_desc() << " - Cost: " << chara->get_attacks()[i].get_cost() << " " << chara->get_attacks()[i].get_param_cost() << "\n";
					}
					std::cout << index_go_back << ". Go back\n";
					do {
						std::cin >> index_magic;
					} while (index_magic < 0 || index_magic > chara->get_attacks().size());
					if (index_magic == index_go_back) {
						break; // go back to action selection
					}

					if (chara->get_attacks()[i].get_stat_scaling() == "MP") {
						if (chara->get_current_mp() < chara->get_attacks()[index_magic].get_cost()) {
							std::cout << "Not enough MP!\n";
							break; // go back to action selection
						}
						else {
							chara->set_current_mp(chara->get_current_mp() - chara->get_attacks()[index_magic].get_cost());
						}
					}
					else if (chara->get_attacks()[i].get_stat_scaling() == "HP") {
						if (chara->get_current_hp() + 1 < chara->get_attacks()[index_magic].get_cost()) {
							std::cout << "Not enough HP!\n";
							break; // go back to action selection
						}
						else {
							chara->set_current_hp(chara->get_current_hp() - chara->get_attacks()[index_magic].get_cost());
						}
					}

					// select enemy to attack with magic
					std::string magic_type = chara->get_attacks()[index_magic].get_magic_type();
					if (magic_type == "Attack")
					{
						//
						attack_magic(chara, enemies, chara->get_attacks()[index_magic]);
					}

					else if (magic_type == "Heal")
					{
						heal_magic(chara, characters, chara->get_attacks()[index_magic]);
						//
					}

					else if (magic_type == "Buff")
					{
						buff_magic(chara, characters, enemies, chara->get_attacks()[index_magic]);
					};

					break;
				}

				case 3:
				{
					// std::cout << chara->get_name() << " uses an item!\n"; HOW TO EXIT FROM MENU?
					int item_index;
					std::string item_type;
					bool can_use = false;
					std::cout << "What item would you like to use?\n";

					for (int i = 0; i < playervars.get_inventory().size(); i++) {
						std::cout << i << ". " << playervars.get_inventory()[i].get_name() << " - " << playervars.get_inventory()[i].get_description() << " - Quantity: " << playervars.get_items_quantity()[i] << "\n";
					}

					do {
						std::cin >> item_index;
					} while (item_index < 0 || item_index >= playervars.get_inventory().size());

					std::cout << chara->get_name() << " uses " << playervars.get_inventory()[item_index].get_name() << "!\n";
					item_type = playervars.get_inventory()[item_index].get_type();



					if (item_type == "Key") {
						std::cout << chara->get_name() << " can't use that item in battle!\n";
					}

					if (item_type == "Healing") {
						healing_item(characters, playervars, item_index);
					}

					if (item_type == "Mana") {
						mana_item(characters, playervars, item_index);
					}

					if (item_type == "Revive") {
						revive_item(characters, playervars, item_index);
					}

					if (item_type == "Damaging") {
						damaging_item(enemies, playervars, item_index);
					}


					break;
				}

				case 4:
				{
					std::cout << "You fled.";
					// flee logic to be implemented
					return true;
				}
				}
			}

			else if (enemy->get_current_hp() > 0) {

				Attack enemy_attack = enemy->get_attacks()[rand() % enemy->get_attacks().size()];
				int index_ally = rand() % characters.size();
				std::string attack_type = enemy_attack.get_magic_type();
				int enemy_stat_value;
				int chara_def_value;

				// ENEMIES DO NOT USE MP YET


				if (attack_type == "Attack") { // ENEMY USES ATTACK
					int damage;
					if (enemy_attack.get_target_type() == "Single") {
						Character* target_ally = &characters[index_ally];
						enemy_stat_value = enemy_scaling(enemy, enemy_attack.get_stat_scaling());
						if (enemy_attack.get_def_type() == "DEFENSE") {
							chara_def_value = target_ally->get_current_defense();
						}
						else if (enemy_attack.get_def_type() == "MAGIC_DEFENSE") {
							chara_def_value = target_ally->get_current_magic_defense();
						}
						else {
							chara_def_value = 0;
						}
						damage = (enemy_attack.get_base_power() + (enemy_stat_value * enemy_attack.get_multiplier())) - chara_def_value;
						if (damage < 0) {
							damage = 0;
						}
						target_ally->set_current_hp(target_ally->get_current_hp() - damage);
						std::cout << enemy->get_name() << " uses " << enemy_attack.get_name() << " on " << target_ally->get_name() << "!\n";
						std::cout << "Dealt " << damage << " damage to " << target_ally->get_name() << "!\n";

					}
					else {
						for (int i = 0; i < characters.size(); i++) {
							if (characters[i].get_current_hp() <= 0) {
								continue; // skip unconscious allies
							}
							Character* target_ally = &characters[i];
							enemy_stat_value = enemy_scaling(enemy, enemy_attack.get_stat_scaling());
							if (enemy_attack.get_def_type() == "DEFENSE") {
								chara_def_value = target_ally->get_current_defense();
							}
							else if (enemy_attack.get_def_type() == "MAGIC_DEFENSE") {
								chara_def_value = target_ally->get_current_magic_defense();
							}
							else {
								chara_def_value = 0;
							}
							damage = (enemy_attack.get_base_power() + (enemy_stat_value * enemy_attack.get_multiplier())) - chara_def_value;
							if (damage < 0) {
								damage = 0;
							}
							target_ally->set_current_hp(target_ally->get_current_hp() - damage);
							std::cout << enemy->get_name() << " uses " << enemy_attack.get_name() << " on " << target_ally->get_name() << "!\n";
							std::cout << "Dealt " << damage << " damage to " << target_ally->get_name() << "!\n";
						}
					}
				}

				if (attack_type == "Heal") { // ENEMY USES HEAL
					if (enemy_attack.get_target_type() == "Single") {
						enemy->set_current_hp(enemy->get_current_hp() + enemy_attack.get_base_power());
						if (enemy->get_current_hp() > enemy->get_max_hp()) {
							enemy->set_current_hp(enemy->get_max_hp());
						}
						std::cout << enemy->get_name() << " uses " << enemy_attack.get_name() << "!\n";
						std::cout << "Healed " << enemy_attack.get_base_power() << " HP!\n";
					}
					else {
						for (int i = 0; i < enemies.size(); i++) {
							enemies[i].set_current_hp(enemies[i].get_current_hp() + enemy_attack.get_base_power());
							if (enemies[i].get_current_hp() > enemies[i].get_max_hp()) {
								enemies[i].set_current_hp(enemies[i].get_max_hp());
							}
							std::cout << enemy->get_name() << " uses " << enemy_attack.get_name() << "!\n";
							std::cout << "Healed " << enemy_attack.get_base_power() << " HP for " << enemies[i].get_name() << "!\n";
						}
					}


				}

				if (attack_type == "Buff") { // ENEMY USES BUFF
					float stat_boost_amount = enemy_attack.get_stat_boost_amount();
					if (stat_boost_amount >= 1) {

						std::string stat_to_boost = enemy_attack.get_stat_boost();
						if (enemy_attack.get_target_type() == "Single") {
							apply_buff_enemy(*enemy, stat_to_boost, stat_boost_amount);
							std::cout << enemy->get_name() << " uses " << enemy_attack.get_name() << "!\n";
							std::cout << "Increased " << stat_to_boost << " of " << enemy->get_name() << " by " << stat_boost_amount << "x!\n";
						}
						else {
							for (int i = 0; i < enemies.size(); i++) {
								apply_buff_enemy(enemies[i], stat_to_boost, stat_boost_amount);
								std::cout << enemy->get_name() << " uses " << enemy_attack.get_name() << "!\n";
								std::cout << "Increased " << stat_to_boost << " of " << enemies[i].get_name() << " by " << stat_boost_amount << "x!\n";
							}
						}

					}
					else { // DEBUFF
						std::string stat_to_debuff = enemy_attack.get_stat_boost();
						if (enemy_attack.get_target_type() == "Single") {
							apply_buff_ally(characters[index_ally], stat_to_debuff, stat_boost_amount);
							std::cout << enemy->get_name() << " uses " << enemy_attack.get_name() << "!\n";
							std::cout << "Decreased " << stat_to_debuff << " of " << characters[index_ally].get_name() << " by " << stat_boost_amount << "x!\n";
						}
						else {
							for (int i = 0; i < characters.size(); i++) {
								apply_buff_ally(characters[i], stat_to_debuff, stat_boost_amount);
								std::cout << enemy->get_name() << " uses " << enemy_attack.get_name() << "!\n";
								std::cout << "Decreased " << stat_to_debuff << " of " << characters[i].get_name() << " by " << stat_boost_amount << "x!\n";
							}
						}
					}




				}
			}
			for (int k = 0; k < enemies.size(); k++) {
				if (enemies[k].get_current_hp() <= 0) {
					std::cout << enemies[k].get_name() << " has been defeated!\n";
					playervars.add_gold(enemies[k].get_gold_given());
					std::cout << "Gained " << enemies[k].get_gold_given() << " gold!\n";
					for (int m = 0; m < characters.size(); m++) {
						if (characters[m].get_current_hp() <= 0) {
							continue; // skip unconscious allies
						}
						characters[m].gain_exp(enemies[k].get_exp_given());
						std::cout << characters[m].get_name() << " gained " << enemies[k].get_exp_given() << " EXP!\n";
					}
					for (int n = 0; n < enemies[k].get_drop_items().size(); n++) {
						int drop_chance = enemies[k].get_drop_chances()[n];
						int roll = rand() % 100 + 1; // random number between 1 and 100
						if (roll <= drop_chance) {
							playervars.add_item(enemies[k].get_drop_items()[n], 1);
							std::cout << "Obtained " << enemies[k].get_drop_items()[n].get_name() << " from " << enemies[k].get_name() << "!\n";
						}
					}
					enemies.erase(enemies.begin() + k);
				}
			}
			if (enemies.size() == 0) {
				std::cout << "All enemies defeated! You win the battle!\n";
				return true;
			}



		}
	}
}

void Battle::attack_magic(Character* chara, std::vector<Enemy>& enemies, Attack magic)
{
	int index_enemy;
	if (magic.get_target_type() == "Single") {
		if (enemies.size() == 1) {
			index_enemy = 0;
		}
		else {
			do {
				std::cout << "Choose an enemy to attack:\n";
				std::cin >> index_enemy;
			} while (index_enemy < 0 || index_enemy >= enemies.size());
		}
		magic_damage_calc(chara, enemies[index_enemy], magic);



	}
	else {
		magic_damage_calc(chara, enemies[index_enemy], magic);
		for (int i = 0; i < enemies.size(); i++) {
			magic_damage_calc(chara, enemies[i], magic);
		}
		// attack all enemies
	}
}

void Battle::magic_damage_calc(Character* chara, Enemy& enemy, Attack magic)
{
	// INSERT MAGIC TYPES AND WEAKNESSES LATER
	int stat_value;
	int damage;
	int enemy_def_value;
	stat_value = stat_scaling(chara, magic.get_stat_scaling());

	if (magic.get_def_type() == "DEFENSE") {
		enemy_def_value = enemy.get_current_defense();
	}

	else if (magic.get_def_type() == "MAGIC_DEFENSE") {
		enemy_def_value = enemy.get_current_magic_defense();
	}
	else {
		enemy_def_value = 0;
	}

	damage = (magic.get_base_power() + (stat_value * magic.get_multiplier())) - enemy_def_value;
	if (damage < 0) {
		damage = 0;
	}
	enemy.set_current_hp(enemy.get_current_hp() - damage);
	std::cout << chara->get_name() << " casts " << magic.get_name() << "!\n";
	std::cout << "Dealt " << damage << " damage to " << enemy.get_name() << "!\n";
	return;
}

void Battle::heal_magic(Character* chara, std::vector<Character>& characters, Attack magic)
{
	int index_ally;
	if (magic.get_target_type() == "Single") {
		std::cout << "Select the ally to heal:\n";
		for (int i=0; i < characters.size(); i++) {
			std::cout << i << ". " << characters[i].get_name() << " - HP: " << characters[i].get_current_hp() << "/" << characters[i].get_max_hp() << "\n";
		}
		do {
			std::cin >> index_ally;
		} while (index_ally < 0 || index_ally >= characters.size());
		int stat_value = stat_scaling(chara, magic.get_stat_scaling());
		int heal_amount = magic.get_base_power() + (stat_value * magic.get_multiplier());
		characters[index_ally].set_current_hp(characters[index_ally].get_current_hp() + heal_amount);
		if (characters[index_ally].get_current_hp() > characters[index_ally].get_max_hp()) {
			characters[index_ally].set_current_hp(characters[index_ally].get_max_hp());
		}
		std::cout << chara->get_name() << " casts " << magic.get_name() << "!\n";
		std::cout << "Healed " << heal_amount << " HP for " << characters[index_ally].get_name() << "!\n";

	}
	else {
		std::cout << chara->get_name() << " casts " << magic.get_name() << "!\n";
		for (int i = 0; i < characters.size(); i++) {
			int stat_value = stat_scaling(chara, magic.get_stat_scaling());
			int heal_amount = magic.get_base_power() + (stat_value * magic.get_multiplier());
			characters[i].set_current_hp(characters[i].get_current_hp() + heal_amount);
			if (characters[i].get_current_hp() > characters[i].get_max_hp()) {
				characters[i].set_current_hp(characters[i].get_max_hp());
			}
			std::cout << "Healed " << heal_amount << " HP for " << characters[i].get_name() << "!\n";
		}

	}

	return;
}

void Battle::buff_magic(Character* chara, std::vector<Character>& characters, std::vector<Enemy>& enemies, Attack magic) {
	int index_ally;
	int index_enemy;
	float stat_boost_amount = magic.get_stat_boost_amount(); // can we debuff allies and buff allies? idk not for now (QoL?)
	std::string stat_to_boost = magic.get_stat_boost();
	if (stat_boost_amount >= 1) {
		if (magic.get_target_type() == "Single") {
				std::cout << "Select the ally to buff:\n";
				do {
					std::cin >> index_ally;
				} while (index_ally < 0 || index_ally >= characters.size());
				apply_buff_ally(characters[index_ally], stat_to_boost, stat_boost_amount);
				std::cout << chara->get_name() << " casts " << magic.get_name() << "!\n";
				std::cout << "Increased " << stat_to_boost << " of " << characters[index_ally].get_name() << " by " << stat_boost_amount << "x!\n";
		}
		else {
			std::cout << chara->get_name() << " casts " << magic.get_name() << "!\n";
			for (int i = 0; i < characters.size(); i++) {
				apply_buff_ally(characters[i], stat_to_boost, stat_boost_amount);
				std::cout << "Increased " << stat_to_boost << " of " << characters[i].get_name() << " by " << stat_boost_amount << "x!\n";
			}
		}
	}
	else {
		if (magic.get_target_type() == "Single") {
			std::cout << "Select the enemy to debuff:\n";
			do {
				std::cin >> index_enemy;
			} while (index_enemy < 0 || index_enemy >= enemies.size());
			apply_buff_enemy(enemies[index_enemy], stat_to_boost, stat_boost_amount);
			std::cout << chara->get_name() << " casts " << magic.get_name() << "!\n";
			std::cout << "Decreased " << stat_to_boost << " of " << enemies[index_enemy].get_name() << " by " << stat_boost_amount << "x!\n";
		}
		else {
			std::cout << chara->get_name() << " casts " << magic.get_name() << "!\n";
			for (int i = 0; i < enemies.size(); i++) {
				apply_buff_enemy(enemies[i], stat_to_boost, stat_boost_amount);
				std::cout << "Decreased " << stat_to_boost << " of " << enemies[i].get_name() << " by " << stat_boost_amount << "x!\n";
			}
		}
	}
	return;
}

void Battle::apply_buff_ally(Character& chara, std::string stat, float amount)
{
	if (stat == "STRENGTH") {
		int new_strength = static_cast<int>(chara.get_strength() * amount);
		chara.set_current_strength(new_strength);
	}
	else if (stat == "INTELLIGENCE") {
		int new_intelligence = static_cast<int>(chara.get_intelligence() * amount);
		chara.set_current_intelligence(new_intelligence);
	}
	else if (stat == "SPEED") {
		int new_speed = static_cast<int>(chara.get_speed() * amount);
		chara.set_current_speed(new_speed);
	}
	else if (stat == "DEFENSE") {
		int new_defense = static_cast<int>(chara.get_defense() * amount);
		chara.set_current_defense(new_defense);
	}
	else if (stat == "MAGIC_DEFENSE") {
		int new_magic_defense = static_cast<int>(chara.get_magic_defense() * amount);
		chara.set_current_magic_defense(new_magic_defense);
	}
}

void Battle::apply_buff_enemy(Enemy& enemy, std::string stat, float amount)
{
	if (stat == "STRENGTH") {
		int new_strength = static_cast<int>(enemy.get_strength() * amount);
		enemy.set_current_strength(new_strength);
	}
	else if (stat == "INTELLIGENCE") {
		int new_intelligence = static_cast<int>(enemy.get_intelligence() * amount);
		enemy.set_current_intelligence(new_intelligence);
	}
	else if (stat == "SPEED") {
		int new_speed = static_cast<int>(enemy.get_speed() * amount);
		enemy.set_current_speed(new_speed);
	}
	else if (stat == "DEFENSE") {
		int new_defense = static_cast<int>(enemy.get_defense() * amount);
		enemy.set_current_defense(new_defense);
	}
	else if (stat == "MAGIC_DEFENSE") {
		int new_magic_defense = static_cast<int>(enemy.get_magic_defense() * amount);
		enemy.set_current_magic_defense(new_magic_defense);
	}
}


// items

void Battle::healing_item(std::vector<Character>& characters, PlayerVars& playervars, int item_index) {
	int index_ally;
	if (playervars.get_inventory()[item_index].get_target_type() == "Single") {
		std::cout << "Select the ally to use << " << playervars.get_inventory()[item_index].get_name()<< " on:\n";
		for (int i=0; i < characters.size(); i++) {
			std::cout << i << ". " << characters[i].get_name() << " - HP: " << characters[i].get_current_hp() << "/" << characters[i].get_max_hp() << "\n";
		}

		do {
			std::cin >> index_ally;
		} while (index_ally < 0 || index_ally >= characters.size());
		int heal_amount = playervars.get_inventory()[item_index].get_amount();
		characters[index_ally].set_current_hp(characters[index_ally].get_current_hp() + heal_amount);
		if (characters[index_ally].get_current_hp() > characters[index_ally].get_max_hp()) {
			characters[index_ally].set_current_hp(characters[index_ally].get_max_hp());
		}
		std::cout << "Healed " << heal_amount << " HP for " << characters[index_ally].get_name() << "!\n";

	}
	else {
		std::cout << "Using " << playervars.get_inventory()[item_index].get_name() << " on all allies!\n";
		for (int i = 0; i < characters.size(); i++) {
			int heal_amount = playervars.get_inventory()[item_index].get_amount();
			characters[i].set_current_hp(characters[i].get_current_hp() + heal_amount);
			if (characters[i].get_current_hp() > characters[i].get_max_hp()) {
				characters[i].set_current_hp(characters[i].get_max_hp());
			}
			std::cout << "Healed " << heal_amount << " HP for " << characters[i].get_name() << "!\n";
		}
	}

	playervars.remove_item(playervars.get_inventory()[item_index], 1);
}

void Battle::mana_item(std::vector<Character>& characters, PlayerVars& playervars, int item_index) {
	int index_ally;
	if (playervars.get_inventory()[item_index].get_target_type() == "Single") {
		std::cout << "Select the ally to use << " << playervars.get_inventory()[item_index].get_name() << " on:\n";
		for (int i = 0; i < characters.size(); i++) {
			std::cout << i << ". " << characters[i].get_name() << " - MP: " << characters[i].get_current_mp() << "/" << characters[i].get_max_mp() << "\n";
		}
		do {
			std::cin >> index_ally;
		} while (index_ally < 0 || index_ally >= characters.size());
		int mana_amount = playervars.get_inventory()[item_index].get_amount();
		characters[index_ally].set_current_mp(characters[index_ally].get_current_mp() + mana_amount);
		if (characters[index_ally].get_current_mp() > characters[index_ally].get_max_mp()) {
			characters[index_ally].set_current_mp(characters[index_ally].get_max_mp());
		}
		std::cout << "Restored " << mana_amount << " MP for " << characters[index_ally].get_name() << "!\n";
	}
	else {
		std::cout << "Using " << playervars.get_inventory()[item_index].get_name() << " on all allies!\n";
		for (int i = 0; i < characters.size(); i++) {
			int mana_amount = playervars.get_inventory()[item_index].get_amount();
			characters[i].set_current_mp(characters[i].get_current_mp() + mana_amount);
			if (characters[i].get_current_mp() > characters[i].get_max_mp()) {
				characters[i].set_current_mp(characters[i].get_max_mp());
			}
			std::cout << "Restored " << mana_amount << " MP for " << characters[i].get_name() << "!\n";
		}
	}
	playervars.remove_item(playervars.get_inventory()[item_index], 1);
}

void Battle::revive_item(std::vector<Character>& characters, PlayerVars& playervars, int item_index) {
	// go back if no one is dead?
	int index_ally;
	if (playervars.get_inventory()[item_index].get_target_type() == "Single") {
		std::cout << "Select the ally to use << " << playervars.get_inventory()[item_index].get_name() << " on:\n";
		for (int i = 0; i < characters.size(); i++) {
			std::cout << i << ". " << characters[i].get_name() << " - HP: " << characters[i].get_current_hp() << "/" << characters[i].get_max_hp() << "\n";
		}

		do {
			std::cin >> index_ally;
		} while (index_ally < 0 || index_ally >= characters.size());

		if (characters[index_ally].get_current_hp() == 0) {
			int revive_amount = 1; // fixed revive amount for now, can be changed to item amount later //
			characters[index_ally].set_current_hp(revive_amount);
			std::cout << "Revived " << characters[index_ally].get_name() << "!\n";
			playervars.remove_item(playervars.get_inventory()[item_index], 1);
		}
		else {
			std::cout << characters[index_ally].get_name() << " is not dead!\n";
		}
	}
	else {
				std::cout << "Using " << playervars.get_inventory()[item_index].get_name() << " on all allies!\n";
		for (int i = 0; i < characters.size(); i++) {
			if (characters[i].get_current_hp() == 0) {
				int revive_amount = 1; // fixed revive amount for now, can be changed to item amount later //
				characters[i].set_current_hp(revive_amount);
				std::cout << "Revived " << characters[i].get_name() << "!\n";
			}
		}
		playervars.remove_item(playervars.get_inventory()[item_index], 1);
	}
}

void Battle::damaging_item(std::vector<Enemy>& enemies, PlayerVars& playervars, int item_index) {
	int index_enemy;
	if (playervars.get_inventory()[item_index].get_target_type() == "Single") {
		if (enemies.size() == 1) {
			index_enemy = 0;
		}
		else {
			do {
				std::cout << "Choose an enemy to attack:\n";
				std::cin >> index_enemy;
			} while (index_enemy < 0 || index_enemy >= enemies.size());
		}
		int damage_amount = playervars.get_inventory()[item_index].get_amount();
		enemies[index_enemy].set_current_hp(enemies[index_enemy].get_current_hp() - damage_amount);
		std::cout << "Dealt " << damage_amount << " damage to " << enemies[index_enemy].get_name() << "!\n";
	}
	else {
		std::cout << "Using " << playervars.get_inventory()[item_index].get_name() << " on all enemies!\n";
		for (int i = 0; i < enemies.size(); i++) {
			int damage_amount = playervars.get_inventory()[item_index].get_amount();
			enemies[i].set_current_hp(enemies[i].get_current_hp() - damage_amount);
			std::cout << "Dealt " << damage_amount << " damage to " << enemies[i].get_name() << "!\n";
		}
	}
	playervars.remove_item(playervars.get_inventory()[item_index], 1);
}


std::vector<std::string> Battle::check_speed(std::vector<Character> characters, std::vector<Enemy> enemies) {
	std::vector<int> speed_values;
	std::vector<std::string> speed_names;
	// put characters in arrays (speed and name)
	for (int i=0; i<characters.size(); i++) {
		speed_values.push_back(characters[i].get_speed());
		speed_names.push_back(characters[i].get_name());
	}
	// add enemies in arrays (speed and name)
	for (int i=0; i<enemies.size(); i++) {
		speed_values.push_back(enemies[i].get_speed());
		speed_names.push_back(enemies[i].get_name());
	}
	//sort arrays
	bubble_sort(speed_values, speed_names);
	return speed_names;
}

void Battle::bubble_sort(std::vector<int> &speed_values, std::vector<std::string> &speed_names) {
	int size = speed_values.size();
	int c;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (speed_values[j] < speed_values[j + 1]) {
				std::swap(speed_values[j], speed_values[j + 1]);
				std::swap(speed_names[j], speed_names[j + 1]);
			}
		}
	}
}

int Battle::attack_calc(Character* chara, Enemy enemy) {
	int dmg;
	// type check for different weapon types (in the future)

	dmg = chara->get_current_strength() - enemy.get_current_defense();
	if (dmg < 0) {
		dmg = 0;
	}
	return dmg;
}

int Battle::stat_scaling(Character* chara, std::string stat) {
	int stat_value;
	if (stat == "STRENGTH") {
		stat_value = chara->get_current_strength();
	}
	else if (stat == "INTELLIGENCE") {
		stat_value = chara->get_current_intelligence();
	}
	else if (stat == "SPEED") {
		stat_value = chara->get_current_speed();
	}
	else if (stat == "DEFENSE") {
		stat_value = chara->get_current_defense();
	}
	else if (stat == "MAGIC_DEFENSE") {
		stat_value = chara->get_current_magic_defense();
	}
	else {
		stat_value = 1;
	}
	return stat_value;
}

int Battle::enemy_scaling(Enemy* enemy, std::string stat) {
	int stat_value;
	if (stat == "STRENGTH") {
		stat_value = enemy->get_current_strength();
	}
	else if (stat == "INTELLIGENCE") {
		stat_value = enemy->get_current_intelligence();
	}
	else if (stat == "SPEED") {
		stat_value = enemy->get_current_speed();
	}
	else if (stat == "DEFENSE") {
		stat_value = enemy->get_current_defense();
	}
	else if (stat == "MAGIC_DEFENSE") {
		stat_value = enemy->get_current_magic_defense();
	}
	else {
		stat_value = 1;
	}
	return stat_value;
}
