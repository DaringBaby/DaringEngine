#include "scripts/classes/Enemy.h"

Enemy::Enemy(std::string name, std::string type_enemy, std::string element, int level, int exp_given, int gold_given, int max_hp, int max_mp, int strength, int intelligence, int speed, int defense, int magic_defense, std::vector<Item> drop_items, std::vector<int> drop_chances, std::vector<Attack> attacks) {
	this->name = name;
	this->type_enemy = type_enemy;
	this->element = element;
	this->level = level;
	this->exp_given = exp_given;
	this->gold_given = gold_given;
	this->max_hp = max_hp;
	this->current_hp = max_hp;
	this->max_mp = max_mp;
	this->current_mp = max_mp;
	this->strength = strength;
	this->intelligence = intelligence;
	this->speed = speed;
	this->defense = defense;
	this->magic_defense = magic_defense;
	this->drop_items = drop_items;
	this->drop_chances = drop_chances;
	this->attacks = attacks;
	this->current_strength = strength;
	this->current_intelligence = intelligence;
	this->current_speed = speed;
	this->current_defense = defense;
	this->current_magic_defense = magic_defense;
}

std::string Enemy::get_name() {
	return this->name;
}

std::string Enemy::get_type_enemy() {
	return this->type_enemy;
}

std::string Enemy::get_element() {
	return this->element;
}


int Enemy::get_level() {
	return this->level;
}

int Enemy::get_exp_given() {
	return this->exp_given;
}

int Enemy::get_gold_given() {
	return this->gold_given;
}

int Enemy::get_current_hp() {
	return this->current_hp;
}

int Enemy::get_max_hp() {
	return this->max_hp;
}

int Enemy::get_current_mp() {
	return this->current_mp;
}

int Enemy::get_max_mp() {
	return this->max_mp;
}

int Enemy::get_strength() {
	return this->strength;
}

int Enemy::get_intelligence() {
	return this->intelligence;
}

int Enemy::get_speed() {
	return this->speed;
}

int Enemy::get_defense() {
	return this->defense;
}

int Enemy::get_magic_defense() {
	return this->magic_defense;
}

std::vector<Item> Enemy::get_drop_items() {
	return this->drop_items;
}

std::vector<int> Enemy::get_drop_chances() {
	return this->drop_chances;
}

std::vector<Attack> Enemy::get_attacks() {
	return this->attacks;
}


void Enemy::set_name(std::string name) {
	this->name = name;
}

void Enemy::set_type_enemy(std::string type_enemy) {
	this->type_enemy = type_enemy;
}

void Enemy::set_element(std::string element) {
	this->element = element;
}

void Enemy::set_level(int level) {
	this->level = level;
}

void Enemy::set_exp_given(int exp_given) {
	this->exp_given = exp_given;
}

void Enemy::set_gold_given(int gold_given) {
	this->gold_given = gold_given;
}

void Enemy::set_current_hp(int hp) {
	this->current_hp = hp;
}

void Enemy::set_max_hp(int hp) {
	this->max_hp = hp;
}

void Enemy::set_current_mp(int mp) {
	this->current_mp = mp;
}

void Enemy::set_max_mp(int mp) {
	this->max_mp = mp;
}

void Enemy::set_strength(int strength) {
	this->strength = strength;
}

void Enemy::set_intelligence(int intelligence) {
	this->intelligence = intelligence;
}

void Enemy::set_speed(int speed) {
	this->speed = speed;
}

void Enemy::set_defense(int defense) {
	this->defense = defense;
}

void Enemy::set_magic_defense(int magic_defense) {
	this->magic_defense = magic_defense;
}



void Enemy::set_drop_items(std::vector<Item> drop_items) {
	this->drop_items = drop_items;
}

void Enemy::set_drop_chances(std::vector<int> drop_chances) {
	this->drop_chances = drop_chances;
}

void Enemy::set_attacks(std::vector<Attack> attacks) {
	this->attacks = attacks;
}

void Enemy::set_current_strength(int strength) {
	this->current_strength = strength;
}

void Enemy::set_current_intelligence(int intelligence) {
	this->current_intelligence = intelligence;
}

void Enemy::set_current_speed(int speed) {
	this->current_speed = speed;
}

void Enemy::set_current_defense(int defense) {
	this->current_defense = defense;
}

void Enemy::set_current_magic_defense(int magic_defense) {
	this->current_magic_defense = magic_defense;
}

int Enemy::get_current_strength() {
	return this->current_strength;
}

int Enemy::get_current_intelligence() {
	return this->current_intelligence;
}

int Enemy::get_current_speed() {
	return this->current_speed;
}

int Enemy::get_current_defense() {
	return this->current_defense;
}

int Enemy::get_current_magic_defense() {
	return this->current_magic_defense;
}

void Enemy::add_attack(Attack attack) {
	attacks.push_back(attack);
}
