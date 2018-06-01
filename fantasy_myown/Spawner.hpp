#pragma once
#include "Monster.hpp"

template<class T>
class SpawnPoint {
	T mons;
public:
	SpawnPoint(T input_monsters) {
		mons = input_monsters;
	}
	T getMonster();
	void setMonster(const int monster_quantity);
};

template<class T>
T SpawnPoint<T>::getMonster() {
	return mons;
}

template<class T>
void SpawnPoint<T>::setMonster(const int monster_quantity) {
	for (int i = 0; i < monster_quantity; i++) {
		mons.push_back(make_shared<Monster>());
	}
}

class Spawner
{
public:
	Spawner();
	virtual ~Spawner();
	virtual Monster *spawn() = 0;
};

