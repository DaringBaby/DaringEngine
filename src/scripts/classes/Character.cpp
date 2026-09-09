#include "scripts/classes/Character.h"
#include <string>

Character::Character(std::string name, std::string classe, int level, int max_hp, int max_mp, int strength, int intelligence, int speed, int defense, int magic_defense, int luck, std::vector<Attack> attacks, std::string equip){
		this->name = name;
		this->classe = classe;
		this->level = level;
		this->max_hp = max_hp;
		this->current_hp = max_hp;
		this->max_mp = max_mp;
		this->current_mp = max_mp;
		this->exp = 0;
		this->next_level_exp = level * 100; //  formula for next level exp
		this->strength = strength;
		this->intelligence = intelligence;
		this->speed = speed;
		this->defense = defense;
		this->magic_defense = magic_defense;
		this->luck = luck;
		this->attacks = attacks;
		this->current_strength = strength;
		this->current_intelligence = intelligence;
		this->current_speed = speed;
		this->current_defense = defense;
		this->current_magic_defense = magic_defense;
		this->current_luck = luck;
		this->weapon = equip;
		this->body = equip;
		this->head = equip;
		this->greaves = equip;
		this->accessory = equip;

    }

	void Character::set_name(std::string name){
		this->name = name;
	}

	std::string Character::get_name(){
		return this->name;
	}

	void Character::set_classe(std::string classe){
		this->classe = classe;
	}

	std::string Character::get_classe(){
		return this->classe;
	}

	int Character::get_level(){
		return this->level;
	}

	void Character::set_level(int level){
		this->level = level;
	}

	int Character::get_current_hp(){
		return this->current_hp;
	}

	void Character::set_current_hp(int hp){
		this->current_hp = hp;
	}

	int Character::get_max_hp(){
		return this->max_hp;
	}

	void Character::set_max_hp(int hp){
		this->max_hp = hp;
	}

	int Character::get_current_mp(){
		return this->current_mp;
	}

	void Character::set_current_mp(int mp){
		this->current_mp = mp;
	}

	int Character::get_max_mp(){
		return this->max_mp;
	}

	void Character::set_max_mp(int mp){
		this->max_mp = mp;
	}

	int Character::get_exp(){
		return this->exp;
	}

	void Character::set_exp(int exp){
		this->exp = exp;
	}

	int Character::get_next_level_exp(){
		return this->next_level_exp;
	}

	void Character::set_next_level_exp(int exp){
		this->next_level_exp = exp;
	}

	int Character::get_strength(){
		return this->strength;
	}

	void Character::set_strength(int strength){
		this->strength = strength;
	}

	int Character::get_intelligence(){
		return this->intelligence;
	}

	void Character::set_intelligence(int intelligence){
		this->intelligence = intelligence;
	}

	int Character::get_speed(){
		return this->speed;
	}

	void Character::set_speed(int speed){
		this->speed = speed;
	}

	int Character::get_defense(){
		return this->defense;
	}

	void Character::set_defense(int defense){
		this->defense = defense;
	}

	int Character::get_magic_defense(){
		return this->magic_defense;
	}

	void Character::set_magic_defense(int magic_defense){
		this->magic_defense = magic_defense;
	}

	int Character::get_luck(){
		return this->luck;
	}

	void Character::set_luck(int luck){
		this->luck = luck;
	}

	void Character::gain_exp(int exp_gained) {
		this->exp += exp_gained;
		if (this->exp >= this->next_level_exp) {
			this->level_up();
		}
	}

	void Character::level_up() {
		// default increments, can be modified for different classes later
		this->level += 1;
		this->exp -= this->next_level_exp;
		this->next_level_exp = this->level * 100;
		this->max_hp += 10;
		this->current_hp = this->max_hp;
		this->max_mp += 5;
		this->current_mp = this->max_mp;
		this->strength += 2;
		this->intelligence += 2;
		this->speed += 1;
		this->defense += 2;
		this->magic_defense += 2;
		this->luck += 1;
	}

	std::vector<Attack> Character::get_attacks(){
		return this->attacks;
	}

	void Character::set_attacks(std::vector<Attack> attacks){
		this->attacks = attacks;
	}

	int Character::get_current_strength(){
		return this->current_strength;
	}

	void Character::set_current_strength(int strength){
		this->current_strength = strength;
	}

	int Character::get_current_intelligence(){
		return this->current_intelligence;
	}

	void Character::set_current_intelligence(int intelligence){
		this->current_intelligence = intelligence;
	}

	int Character::get_current_speed(){
		return this->current_speed;
	}

	void Character::set_current_speed(int speed){
		this->current_speed = speed;
	}

	int Character::get_current_defense(){
		return this->current_defense;
	}

	void Character::set_current_defense(int defense){
		this->current_defense = defense;
	}

	int Character::get_current_magic_defense(){
		return this->current_magic_defense;
	}

	void Character::set_current_magic_defense(int magic_defense){
		this->current_magic_defense = magic_defense;
	}

	int Character::get_current_luck(){
		return this->current_luck;
	}

	void Character::set_current_luck(int luck){
		this->current_luck = luck;
	}

	void Character::add_attack(Attack attack) {
		this->attacks.push_back(attack);
	}

	std::string Character::get_weapon() {
		return weapon;
	}

	void Character::set_weapon(std::string weapon) {
		this->weapon = weapon;
	}

	std::string Character::get_head() {
		return head;
	}

	void Character::set_head(std::string head) {
		this->head = head;
	}

	std::string Character::get_body() {
		return body;
	}

	void Character::set_body(std::string body) {
		this->body = body;
	}

	std::string Character::get_greaves() {
		return greaves;
	}

	void Character::set_greaves(std::string greaves) {
		this->greaves = greaves;
	}

	std::string Character::get_accessory() {
		return accessory;
	}

	void Character::set_accessory(std::string accessory) {
		this->accessory = accessory;
	}
