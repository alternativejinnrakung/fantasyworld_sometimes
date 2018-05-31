#include "Clock.hpp"

Clock::Clock()
{
}


Clock::~Clock()
{
}

bool Clock::summon_world_clock(bool gameover) {
	clock_t t1, t2;
	float diff;
	t1 = clock();
	while (true) {
		t2 = clock();
		diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
		if (diff > 0.0) {
			t1 = clock();
			return false;
		}
		if (gameover) {
			this->setInput();
			return true;
		}
	}
	return true;
}

char Clock::setInput() {
	return static_cast<char>(_getche());
}