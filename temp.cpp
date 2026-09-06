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
