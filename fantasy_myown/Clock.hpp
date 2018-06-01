#pragma once
#include <ctime>
#include <conio.h>

class Clock
{
	char input;
public:
	Clock();
	~Clock();

	bool summon_world_clock(bool gameover);
	char setInput();
	int roundup(const double number);
};