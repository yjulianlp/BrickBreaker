#pragma once
#include "gameinfo.h"
#include <SDL.h>
#include <string>

class Player {
private:
	std::string name;
	int score;
	int lives;

public:
	Player(std::string name, int score, int lives);
	std::string getName();
	void setName(std::string name);
	int getScore();
	void setScore(int score);
	void addScore(int hit);
	int getLives();
	void setLives(int lives);
};