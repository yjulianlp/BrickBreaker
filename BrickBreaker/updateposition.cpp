#include "gameinfo.h"
#include "gameitems.h"
#include <iostream>

void updateBall(Ball& ball, float time) {
	std::vector<int> pos = ball.getCenter();
	std::cout << "current angle: " << ball.getAngle() << "\n";
	ball.setXVelocity(ball.getSpeed() * cos(ball.getAngle()));
	ball.setYVelocity(ball.getSpeed() * sin(ball.getAngle()));
	std::vector<int> velo = ball.getVelocity();

	ball.movePosition(time);

	pos = ball.getCenter();
	if (pos[0]-BALL_RADIUS <= 0 || pos[0]+BALL_RADIUS >= SCREEN_WIDTH) {
		ball.setAngle(PI - ball.getAngle());
	}
	if (pos[1] - BALL_RADIUS < 0 || pos[1] + BALL_RADIUS > SCREEN_HEIGHT) {
		ball.setAngle(-ball.getAngle());
	}
}