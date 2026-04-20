#include "scripts/classes/Equip.h"

Equip::Equip(std::string name, std::string description, int price, int strength_bonus, int intelligence_bonus, int speed_bonus, int defense_bonus, int magic_defense_bonus, int luck_bonus)
    : Item(name, description, price, "EQUIP", 0, "") // chiamata esplicita al costruttore di Item
{
    this->strength_bonus = strength_bonus;
    this->intelligence_bonus = intelligence_bonus;
    this->speed_bonus = speed_bonus;
    this->defense_bonus = defense_bonus;
    this->magic_defense_bonus = magic_defense_bonus;
	this->luck_bonus = luck_bonus;
}
int Equip::get_strength_bonus(){
    return this->strength_bonus;
}
int Equip::get_intelligence_bonus(){
    return this->intelligence_bonus;
}
int Equip::get_speed_bonus(){
    return this->speed_bonus;
}
int Equip::get_defense_bonus(){
    return this->defense_bonus;
}
int Equip::get_magic_defense_bonus(){
    return this->magic_defense_bonus;
}
int Equip::get_luck_bonus(){
    return this->luck_bonus;
}
void Equip::set_strength_bonus(int strength_bonus){
    this->strength_bonus = strength_bonus;
}
void Equip::set_intelligence_bonus(int intelligence_bonus){
    this->intelligence_bonus = intelligence_bonus;
}
void Equip::set_speed_bonus(int speed_bonus){
    this->speed_bonus = speed_bonus;
}
void Equip::set_defense_bonus(int defense_bonus){
    this->defense_bonus = defense_bonus;
}
void Equip::set_magic_defense_bonus(int magic_defense_bonus){
    this->magic_defense_bonus = magic_defense_bonus;
}
void Equip::set_luck_bonus(int luck_bonus){
    this->luck_bonus = luck_bonus;
}
