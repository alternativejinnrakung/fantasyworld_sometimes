#pragma once
#include<iostream>
#include<ctime>
#include<assert.h>
#include<memory>
#include<vector>

#include<fstream>
#include<sstream>

#include "Orc.hpp"
#include "Zombie.hpp"

#define REQUIRE(condition) assert(condition)
#define PROMISE(condition) assert(condition)

class Monster
{
private:
	const std::string TEXTNAME = "monster_data.txt";
	const std::string MONSTER_TYPE[2] = { "Zombie","Orc" };
	const int NO_REBORN_STATE = -1;
	int health;
	int attack;
	int locX, locY;
	std::string mons_type;
	std::vector<std::string> monster_data;
public:
	Monster();
	virtual ~Monster();
	void setHP();
	void reduceHP(const int damage);
	void setLocation(const std::vector<std::vector<int>> worldmap);
	int getLocX();
	int getLocY();
	int getHealth();
	int getAtk();
	std::string getType();
	void init_monsterdata();
	void setLocX(const int x);
	void setLocY(const int y);
};