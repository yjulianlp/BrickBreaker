#include "pch.h"
#include "gameitems.h"
#include "gameinfo.h"
#include "render.h"
#include "updateposition.h"
#include <iostream>
#include <vector>

class BallTest : public ::testing::Test {
protected:
	Ball ball = Ball(BALL_RADIUS, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, INITIAL_BALL_SPEED, INITIAL_BALL_ANGLE);
};
TEST_F(BallTest, InitialBallPositionTest) {
	std::vector<int> pos = ball.getCenter();
	EXPECT_EQ(pos[0], SCREEN_WIDTH / 2);
	EXPECT_EQ(pos[1], SCREEN_HEIGHT / 4);
}

TEST_F(BallTest, InitialBallRadiusTest) {
	EXPECT_EQ(ball.getRadius(), BALL_RADIUS);
}

TEST_F(BallTest, InitialBallSpeedTest) {
	EXPECT_EQ(ball.getSpeed(), INITIAL_BALL_SPEED);
}

TEST_F(BallTest, InitialBallAngleTest) {
	EXPECT_NEAR(ball.getAngle(), INITIAL_BALL_ANGLE, 0.001);
}

TEST_F(BallTest, InitialBallVelocityTest) {
	std::vector<int> velocity = ball.getVelocity();
	EXPECT_EQ(velocity[0], (int) (ball.getSpeed() * cos(ball.getAngle())));
	EXPECT_EQ(velocity[1], (int) (ball.getSpeed() * sin(ball.getAngle())));
}