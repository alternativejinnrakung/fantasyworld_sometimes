#include "Monster.hpp"

Monster::Monster() {
	setHP();
}


Monster::~Monster()
{
}

void Monster::reduceHP(const int damage) {
	REQUIRE(health >= 0); //validate input
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}

void Monster::setHP() {
	this->init_monsterdata();
	int type = rand() % (monster_data.size() / 4);

	if (monster_data[type * 4] == "Zombie") {
		std::shared_ptr<Zombie> zom = std::make_shared<Zombie>();
		zom->setType(monster_data[(type * 4) + 1]);
		zom->setHP(stoi(monster_data[(type * 4) + 2]));
		zom->setATK(stoi(monster_data[(type * 4) + 3]));
		health = zom->getHP();
		attack = zom->getATK();
		mons_type = zom->getType();
	}
	else if (monster_data[type * 4] == "Orc") {
		std::shared_ptr<Orc> orc = std::make_shared<Orc>();
		orc->setType(monster_data[(type * 4) + 1]);
		orc->setHP(stoi(monster_data[(type * 4) + 2]));
		orc->setATK(stoi(monster_data[(type * 4) + 3]));
		health = orc->getHP();
		attack = orc->getATK();
		mons_type = orc->getType();
	}
	PROMISE(health >= 0); //validate output

}

void Monster::setLocation(const std::vector<std::vector<int>> worldmap) {
	REQUIRE(!worldmap.empty());
	while (true) {
		locX = rand() % worldmap[0].size();
		locY = rand() % worldmap.size();
		if (worldmap[locX][locY] == 0) {
			break;
		}
	}
}

int Monster::getLocX() {
	return locX;
}

int Monster::getLocY() {
	return locY;
}

int Monster::getHealth() {
	return health;
}

int Monster::getAtk() {
	return attack;
}

std::string Monster::getType() {
	return mons_type;
}

void Monster::init_monsterdata() {
	std::ifstream textfile("monster_data.txt");
	std::string line;
	std::string token;

	while (getline(textfile, line)) {
		std::stringstream stream(line);
		while (getline(stream, token, ' ')) {
			monster_data.push_back(token);
		}
	}
	PROMISE(!monster_data.empty());
}