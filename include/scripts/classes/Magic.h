#pragma once
#include <string>

class Magic
{
private:
	std::string name;
	int mp_cost;
	int base_power;
	std::string element;
	std::string type;
	std::string description;
	std::string type_target;
	std::string stat_type;
	float stat_multiplier;
public:
	Magic(std::string name, int mp_cost, int base_power, std::string element, std::string type, std::string description, std::string type_target, std::string stat_type, float stat_multiplier);
	std::string get_name();
	int get_mp_cost();
	int get_base_power();
	std::string get_element();
	std::string get_type();
	std::string get_description();
	std::string get_type_target();
	std::string get_stat_type();
	float get_stat_multiplier();
	void set_name(std::string name);
	void set_mp_cost(int mp_cost);
	void set_base_power(int base_power);
	void set_element(std::string element);
	void set_type(std::string type);
	void set_description(std::string description);
	void set_type_target(std::string type_target);
	void set_stat_type(std::string stat_type);
	void set_stat_multiplier(float stat_multiplier);
};

