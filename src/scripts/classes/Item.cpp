#include "scripts/classes/Item.h"

Item::Item(std::string name, std::string description, int price, std::string type, int amount, std::string target) {
	this->name = name;
	this->description = description;
	this->price = price;
	this->type = type;
	this->amount = amount;
	this->target_type = target;
}

std::string Item::get_name() const {
	return this->name;
}

std::string Item::get_description() const {
	return this->description;
}

int Item::get_price() const {
	return this->price;
}

std::string Item::get_type() const {
	return this->type;
}

int Item::get_amount() const {
	return this->amount;
}

std::string Item::get_target_type() const {
	return this->target_type;
}

void Item::set_name(std::string name) {
	this->name = name;
}

void Item::set_description(std::string description) {
	this->description = description;
}

void Item::set_price(int price) {
	this->price = price;
}

void Item::set_type(std::string type) {
	this->type = type;
}

void Item::set_amount(int amount) {
	this->amount = amount;
}

void Item::set_target_type(std::string target_type) {
	this->target_type = target_type;
}
