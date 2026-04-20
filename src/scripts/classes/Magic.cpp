#include "scripts/classes/Magic.h"

Magic::Magic(std::string name, int mp_cost, int base_power, std::string element, std::string type, std::string description, std::string type_target, std::string stat_type, float stat_multiplier) {
	this->name = name;
	this->mp_cost = mp_cost;
	this->base_power = base_power;
	this->element = element;
	this->type = type;
	this->description = description;
	this->type_target = type_target;
	this->stat_type = stat_type;
	this->stat_multiplier = stat_multiplier;
}

std::string Magic::get_name() {
	return this->name;
}

int Magic::get_mp_cost() {
	return this->mp_cost;
}

int Magic::get_base_power() {
	return this->base_power;
}

std::string Magic::get_element() {
	return this->element;
}

std::string Magic::get_type() {
	return this->type;
}

std::string Magic::get_description() {
	return this->description;
}

std::string Magic::get_type_target() {
	return this->type_target;
}

std::string Magic::get_stat_type() {
	return this->stat_type;
}

float Magic::get_stat_multiplier() {
	return this->stat_multiplier;
}

void Magic::set_name(std::string name) {
	this->name = name;
}

void Magic::set_mp_cost(int mp_cost) {
	this->mp_cost = mp_cost;
}

void Magic::set_base_power(int base_power) {
	this->base_power = base_power;
}

void Magic::set_element(std::string element) {
	this->element = element;
}

void Magic::set_type(std::string type) {
	this->type = type;
}

void Magic::set_description(std::string description) {
	this->description = description;
}

void Magic::set_type_target(std::string type_target) {
	this->type_target = type_target;
}

void Magic::set_stat_type(std::string stat_type) {
	this->stat_type = stat_type;
}

void Magic::set_stat_multiplier(float stat_multiplier) {
	this->stat_multiplier = stat_multiplier;
}
