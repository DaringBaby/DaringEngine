#include "scripts/classes/Attack.h"

Attack::Attack(std::string name, int base_power, float multiplier, std::string stat_scaling, std::string element, std::string param_cost, int cost, std::string desc, std::string target_type, std::string stat_boost, float stat_boost_amount, std::string magic_type, std::string def_type) {
	this->name = name;
	this->base_power = base_power;
	this->multiplier = multiplier;
	this->stat_scaling = stat_scaling;
	this->element = element;
	this->param_cost = param_cost;
	this->cost = cost;
	this->target_type = target_type;
	this->desc = desc;
	this->stat_boost = stat_boost;
	this->stat_boost_amount = stat_boost_amount;
	this->magic_type = magic_type;
	this->def_type = def_type;
}

std::string Attack::get_name() {
	return this->name;
}

int Attack::get_base_power() {
	return this->base_power;
}

float Attack::get_multiplier() {
	return this->multiplier;
}

std::string Attack::get_stat_scaling() {
	return this->stat_scaling;
}

std::string Attack::get_element() {
	return this->element;
}

std::string Attack::get_param_cost() {
	return this->param_cost;
}

int Attack::get_cost() {
	return this->cost;
}

std::string Attack::get_desc() {
	return this->desc;
}

std::string Attack::get_target_type() {
	return this->target_type;
}

std::string Attack::get_stat_boost() {
	return this->stat_boost;
}

float Attack::get_stat_boost_amount() {
	return this->stat_boost_amount;
}

std::string Attack::get_magic_type() {
	return this->magic_type;
}

std::string Attack::get_def_type() {
	return this->def_type;
}

void Attack::set_name(std::string name) {
	this->name = name;
}

void Attack::set_base_power(int base_power) {
	this->base_power = base_power;
}

void Attack::set_multiplier(float multiplier) {
	this->multiplier = multiplier;
}

void Attack::set_stat_scaling(std::string stat_scaling) {
	this->stat_scaling = stat_scaling;
}

void Attack::set_element(std::string element) {
	this->element = element;
}

void Attack::set_param_cost(std::string param_cost) {
	this->param_cost = param_cost;
}

void Attack::set_cost(int cost) {
	this->cost = cost;
}

void Attack::set_desc(std::string desc) {
	this->desc = desc;
}

void Attack::set_target_type(std::string target_type) {
	this->target_type = target_type;
}

void Attack::set_stat_boost(std::string stat_boost) {
	this->stat_boost = stat_boost;
}

void Attack::set_stat_boost_amount(float stat_boost_amount) {
	this->stat_boost_amount = stat_boost_amount;
}

void Attack::set_magic_type(std::string magic_type) {
	this->magic_type = magic_type;
}

void Attack::set_def_type(std::string def_type) {
	this->def_type = def_type;
}
