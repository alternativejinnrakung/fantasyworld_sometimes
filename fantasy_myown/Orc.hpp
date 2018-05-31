#pragma once
#include<iostream>

class Orc
{
	int orc_hp;
	int orc_atk;
	std::string orc_type;
public:
	Orc();
	~Orc();
	int getHP();
	int getATK();
	std::string getType();
	void setHP(int input_hp);
	void setATK(int input_atk);
	void setType(std::string input_type);
};