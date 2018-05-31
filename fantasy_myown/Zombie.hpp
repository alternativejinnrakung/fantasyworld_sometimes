#pragma once
#include<iostream>

class Zombie
{
private:
	int zombie_hp;
	int zombie_atk;
	std::string zombie_type;
public:
	Zombie();
	~Zombie();
	int getHP();
	int getATK();
	std::string getType();
	void setHP(int input_hp);
	void setATK(int input_atk);
	void setType(std::string type);
};