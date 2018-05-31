#include "Orc.hpp"


Orc::Orc()
{
}


Orc::~Orc()
{
}

int Orc::getHP() {
	return orc_hp;
}

int Orc::getATK() {
	return orc_atk;
}

std::string Orc::getType() {
	return orc_type;
}

void Orc::setHP(int input_hp) {
	orc_hp = input_hp;
}

void Orc::setATK(int input_atk) {
	orc_atk = input_atk;
}

void Orc::setType(std::string input_type) {
	orc_type = input_type;
}