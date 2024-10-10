#include "gameinfo.h"
#include "gameitems.h"
#include <iostream>

void updateBall(Ball& ball, float time) {
	std::vector<int> pos = ball.getCenter();
	std::cout << "angle: " << ball.getAngle();
	ball.setXVelocity(ball.getSpeed() * cos(ball.getAngle()));
	ball.setYVelocity(ball.getSpeed() * sin(ball.getAngle()));
	std::vector<int> velo = ball.getVelocity();

	ball.movePosition(time);
}