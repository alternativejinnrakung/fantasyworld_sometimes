#include "Map.hpp"

using namespace std;

Map::Map()
{
	REQUIRE(MAP_WIDTH * MAP_HEIGHT > MONS_AMOUNT);

	worldmap.resize(MAP_WIDTH, vector<int>(MAP_HEIGHT));
	playermap.resize(MAP_WIDTH, vector<int>(MAP_HEIGHT));

	for (int j = 0; j < MAP_HEIGHT; j++) {
		for (int i = 0; i < MAP_WIDTH; i++) {
			worldmap[i][j] = 0;
			playermap[i][j] = 0;
		}
	}
	this->monster_initiation();
	player->setLocation(MAP_WIDTH / 2, MAP_HEIGHT / 2);
	playermap[player->getLocX()][player->getLocY()] = player->getHP();
	this->createWorld();
	this->drawMap();
	while (!gameover) {
		gameover = worldclock->summon_world_clock(gameover);
		input = worldclock->setInput(); 
		this->updateMap();
	}
	std::cout << std::endl << "Game Over";
	worldclock->setInput();
}

Map::~Map()
{
}

void Map::monster_initiation() {
	SpawnPoint<vector<shared_ptr<Monster>>> monsterlist(monsters);
	monsterlist.setMonster(MONS_AMOUNT);
	monsters = monsterlist.getMonster();
	player = make_shared<Player>();
	worldclock = make_shared<Clock>();
}

void Map::createWorld() {
	for (int i = 0; i < MONS_AMOUNT; i++) {
		monsters[i]->setLocation(worldmap);
		worldmap[monsters[i]->getLocX()][monsters[i]->getLocY()] = monsters[i]->getHealth();
	}
}

void Map::drawMap() {
	for (int i = 0; i < 10 / 3; i++) {
		cout << endl << endl << endl << endl;
	}
	cout << static_cast<char>(TOPLEFT_MAP);
	for (int i = 0; i < MAP_WIDTH - 1; i++) {
		cout << static_cast<char>(MID_MAP) << static_cast<char>(MID_MAP) << static_cast<char>(TOPMID_MAP);
	}
	cout << static_cast<char>(MID_MAP) << static_cast<char>(MID_MAP) << static_cast<char>(TOPRIGHT_MAP) << endl;
	for (int j = 0; j < MAP_HEIGHT; j++) {
		cout << static_cast<char>(SPLITTER);
		for (int i = 0; i < MAP_WIDTH; i++) {
			if (playermap[i][j] > 0) {
				cout << "H";
			}
			else {
				cout << "-";
			}
			if (worldmap[i][j] > 0) {
				cout << "M";
			}
			else {
				cout << "-";
			}
			cout << static_cast<char>(SPLITTER);
		}
		cout << endl;
	}
	cout << static_cast<char>(BOTLEFT_MAP);
	for (int i = 0; i < MAP_WIDTH - 1; i++) {
		cout << static_cast<char>(MID_MAP) << static_cast<char>(MID_MAP) << static_cast<char>(BOTMID_MAP);
	}
	cout << static_cast<char>(MID_MAP) << static_cast<char>(MID_MAP) << static_cast<char>(BOTRIGHT_MAP) << endl;
}

void Map::updateMap() {
	this->activeInput();
	for (int i = 0; i < MONS_AMOUNT; i++) {
		this->respawnWhenDie(i);
		this->movementRandomizer(i);
	}
	this->drawMap();
	for (int i = 0; i < MONS_AMOUNT; i++) {
		this->enterDialogue(i);
	}
	input = 0;
}

void Map::activeInput() {
	playermap[player->getLocX()][player->getLocY()] = 0;
	if (input == 'a') {
		if (player->getLocX() > 0) {
			player->setLocation(player->getLocX() - 1, player->getLocY());
		}
	}
	else if (input == 'w') {
		if (player->getLocY() > 0) {
			player->setLocation(player->getLocX(), player->getLocY() - 1);
		}
	}
	else if (input == 'd') {
		if (player->getLocX() < MAP_WIDTH - 1) {
			player->setLocation(player->getLocX() + 1, player->getLocY());
		}
	}
	else if (input == 's') {
		if (player->getLocX() < MAP_HEIGHT - 1) {
			player->setLocation(player->getLocX(), player->getLocY() + 1);
		}
	}
	playermap[player->getLocX()][player->getLocY()] = player->getHP();
}

void Map::moveToPlayer_TypeA(const int mons_id) {
	int xpath = worldclock->roundup(static_cast<double>(player->getLocX() - monsters[mons_id]->getLocX()) / MAP_WIDTH);
	int ypath = worldclock->roundup(static_cast<double>(player->getLocY() - monsters[mons_id]->getLocY()) / MAP_HEIGHT);

	worldmap[monsters[mons_id]->getLocX()][monsters[mons_id]->getLocY()] = 0;
	if (worldmap[monsters[mons_id]->getLocX() + xpath][monsters[mons_id]->getLocY()] == 0 && xpath != 0) {
		monsters[mons_id]->setLocX(monsters[mons_id]->getLocX() + xpath);
	}
	else if (worldmap[monsters[mons_id]->getLocX()][monsters[mons_id]->getLocY() + ypath] == 0 && ypath != 0) {
		monsters[mons_id]->setLocY(monsters[mons_id]->getLocY() + ypath);
	}
	worldmap[monsters[mons_id]->getLocX()][monsters[mons_id]->getLocY()] = monsters[mons_id]->getHealth();
}

void Map::moveToPlayer_TypeB(const int mons_id) {
	int xpath = worldclock->roundup(static_cast<double>(player->getLocX() - monsters[mons_id]->getLocX()) / MAP_WIDTH);
	int ypath = worldclock->roundup(static_cast<double>(player->getLocY() - monsters[mons_id]->getLocY()) / MAP_HEIGHT);

	worldmap[monsters[mons_id]->getLocX()][monsters[mons_id]->getLocY()] = 0;
	if (worldmap[monsters[mons_id]->getLocX()][monsters[mons_id]->getLocY() + ypath] == 0 && ypath != 0) {
		monsters[mons_id]->setLocY(monsters[mons_id]->getLocY() + ypath);
	}
	else if (worldmap[monsters[mons_id]->getLocX() + xpath][monsters[mons_id]->getLocY()] == 0 && xpath != 0) {
		monsters[mons_id]->setLocX(monsters[mons_id]->getLocX() + xpath);
	}
	worldmap[monsters[mons_id]->getLocX()][monsters[mons_id]->getLocY()] = monsters[mons_id]->getHealth();
}

void Map::respawnWhenDie(const int i) {
	if (monsters[i]->getHealth() == 0) {
		worldmap[monsters[i]->getLocX()][monsters[i]->getLocY()] = 0;
		monsters[i]->setHP();
		monsters[i]->setLocation(worldmap);
	}
	worldmap[monsters[i]->getLocX()][monsters[i]->getLocY()] = monsters[i]->getHealth();
}

void Map::enterDialogue(const int i) {
	if (monsters[i]->getLocX() == player->getLocX() && monsters[i]->getLocY() == player->getLocY()) {
		cout << "Player fight with " << monsters[i]->getType() << endl;
		cout << monsters[i]->getType() << ": " << monsters[i]->getHealth() << " - " << player->getAtk() << " = ";
		monsters[i]->reduceHP(player->getAtk());
		cout << monsters[i]->getHealth() << endl;
		cout << "Player: " << player->getHP() << " - " << monsters[i]->getAtk() << " = ";
		gameover = player->receivedDamage(monsters[i]->getAtk());
		cout << player->getHP() << endl;
	}
}

void Map::movementRandomizer(const int i) {
	int type_selector = rand() % 2 + 1;
	if (type_selector == 1) {
		this->moveToPlayer_TypeA(i);
	}
	else if (type_selector == 2) {
		this->moveToPlayer_TypeB(i);
	}
}