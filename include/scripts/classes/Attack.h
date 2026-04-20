#pragma once
#include <string>
class Attack
{
private:
	std::string name;
	int base_power;
	float multiplier;
	std::string magic_type; // ATTACK, HEAL, BUFF (REVIVE?)
	std::string stat_scaling;
	std::string def_type;
	std::string element;
	std::string param_cost;
	std::string desc;
	std::string target_type;
	std::string stat_boost;
	float stat_boost_amount;
	int cost;
public:
	Attack(std::string name, int base_power, float multiplier, std::string stat_scaling, std::string element, std::string param_cost, int cost, std::string desc, std::string target_type, std::string stat_boost, float stat_boost_amount, std::string magic_type, std::string def_type);
	std::string get_name();
	int get_base_power();
	float get_multiplier();
	std::string get_stat_scaling();
	std::string get_element();
	std::string get_param_cost();
	int get_cost();
	std::string get_desc();
	std::string get_target_type();
	std::string get_stat_boost();
	float get_stat_boost_amount();
	std::string get_magic_type();
	std::string get_def_type();
	void set_name(std::string name);
	void set_base_power(int base_power);
	void set_multiplier(float multiplier);
	void set_stat_scaling(std::string stat_scaling);
	void set_element(std::string element);
	void set_param_cost(std::string param_cost);
	void set_cost(int cost);
	void set_desc(std::string desc);
	void set_target_type(std::string target_type);
	void set_stat_boost(std::string stat_boost);
	void set_stat_boost_amount(float stat_boost_amount);
	void set_magic_type(std::string magic_type);
	void set_def_type(std::string def_type);

};
