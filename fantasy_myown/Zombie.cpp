#include "Zombie.hpp"

Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

int Zombie::getHP() {
	return zombie_hp;
}

int Zombie::getATK() {
	return zombie_atk;
}

std::string Zombie::getType() {
	return zombie_type;
}

void Zombie::setHP(int input_hp) {
	zombie_hp = input_hp;
}

void Zombie::setATK(int input_atk) {
	zombie_atk = input_atk;
}

void Zombie::setType(std::string input_type) {
	zombie_type = input_type;
}