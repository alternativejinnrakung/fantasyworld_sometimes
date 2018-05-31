#include "Player.hpp"

Player::Player()
{
	health = rand() % HEALTH_RATE + HEALTH_INIT;
	atk = rand() % ATTACK_RATE + ATTACK_INIT;
}

Player::~Player()
{
}

void Player::setLocation(int x, int y) {
	locX = x;
	locY = y;
}

bool Player::receivedDamage(int damage) {
	health -= damage;
	if (health <= 0) {
		health = 0;
		return true;
	}
	return false;
}

int Player::getHP() {
	return health;
}

int Player::getAtk() {
	return atk;
}

int Player::getLocX() {
	return locX;
}

int Player::getLocY() {
	return locY;
}