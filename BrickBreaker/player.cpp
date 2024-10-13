#include "player.h"
#include <string>

Player::Player(std::string player_name, int player_score, int player_lives) {
	name = player_name;
	score = player_score;
	lives = player_lives;
}

std::string Player::getName() {
	return name;
}

void Player::setName(std::string new_name) {
	name = new_name;
}

int Player::getScore() {
	return score;
}

void Player::setScore(int new_score) {
	score = new_score;
}

void Player::addScore(int hit) {
	score += hit;
}

int Player::getLives() {
	return lives;
}

void Player::setLives(int new_lives) {
	lives = new_lives;
}

void Player::updateLives(int change) {
	lives += change;
}