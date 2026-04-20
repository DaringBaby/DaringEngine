#pragma once
#include <string>
class Item
{
	private:
		std::string name;
		std::string description;
		int price;
		std::string type;// KEY, HEALING, MANA, REVIVE, DAMAGING
		int amount; // amount of HP/MP restored or damage dealt
		std::string target_type; // SINGLE, ALL
	public:
		Item(std::string name, std::string description, int price, std::string type, int amount, std::string target_type);

		std::string get_name();
		std::string get_description();
		int get_price();
		std::string get_type();
		int get_amount();
		std::string get_target_type();

		void set_name(std::string name);
		void set_description(std::string description);
		void set_price(int price);
		void set_type(std::string type);
		void set_amount(int amount);
		void set_target_type(std::string target_type);
};

