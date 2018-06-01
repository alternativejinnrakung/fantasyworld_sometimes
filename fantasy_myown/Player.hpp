#pragma once
#include<iostream>

class Player
{
private:
	const int HEALTH_INIT = 75;
	const int ATTACK_INIT = 15;
	const int HEALTH_RATE = 25;
	const int ATTACK_RATE = 10;

	int health;
	int atk;
	int locX, locY;
public:
	Player();
	~Player();
	void setLocation(const int x, const int y);
	bool receivedDamage(const int damage);
	int getHP();
	int getAtk();
	int getLocX();
	int getLocY();
};