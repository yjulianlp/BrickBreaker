#include "pch.h"
#include "gameitems.h"
#include "gameinfo.h"
#include "render.h"
#include "updateposition.h"
#include "player.h"
#include <iostream>
#include <vector>

class BallTest : public ::testing::Test {
protected:
	Ball ball = Ball(BALL_RADIUS, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, INITIAL_BALL_SPEED, INITIAL_BALL_ANGLE);
};

class BallMethodTest : public ::testing::Test {
protected:
	Ball ball = Ball(BALL_RADIUS, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, INITIAL_BALL_SPEED, INITIAL_BALL_ANGLE);

	void SetUp() override {
		ball.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4);
		ball.setSpeed(INITIAL_BALL_SPEED);
		ball.setAngle(INITIAL_BALL_ANGLE);
	}
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
	EXPECT_EQ(velocity[0], (int)(ball.getSpeed() * cos(ball.getAngle())));
	EXPECT_EQ(velocity[1], (int)(ball.getSpeed() * sin(ball.getAngle())));
}

TEST_F(BallMethodTest, BallSetSpeedTest) {
	ball.setSpeed(2);
	EXPECT_EQ(ball.getSpeed(), 2);
}

TEST_F(BallMethodTest, BallSetAngleTest) {
	ball.setAngle(PI / 2);
	EXPECT_NEAR(ball.getAngle(), (PI / 2), 0.001);
}

TEST_F(BallMethodTest, BallMovePositionTest) {
	std::vector<int> old_pos = ball.getCenter();
	std::vector<int> velocity = ball.getVelocity();
	ball.movePosition(2.0);
	std::vector<int> new_pos = ball.getCenter();
	EXPECT_EQ(new_pos[0], old_pos[0] + velocity[0] * 2.0);
	EXPECT_EQ(new_pos[1], old_pos[1] + velocity[1] * 2.0);
}

TEST_F(BallMethodTest, BallSetPositionTest) {
	ball.setPosition(1, 3);
	std::vector<int> pos = ball.getCenter();
	EXPECT_EQ(pos[0], 1);
	EXPECT_EQ(pos[1], 3);
}

TEST_F(BallMethodTest, BallSetVelocityTest) {
	ball.setXVelocity(111);
	ball.setYVelocity(123);
	std::vector<int> velocity = ball.getVelocity();
	EXPECT_EQ(velocity[0], 111);
	EXPECT_EQ(velocity[1], 123);
}

TEST_F(BallMethodTest, BallAdjustSpeedTest) {
	Player test_player = Player("test", 7, PLAYER_STARTING_LIVES);
	Player test_player2 = Player("test2", 5, PLAYER_STARTING_LIVES);
	Player test_player3 = Player("test3", 10000, PLAYER_STARTING_LIVES);

	ball.adjustSpeed(test_player);
	EXPECT_EQ(ball.getSpeed(), 7);
	ball.adjustSpeed(test_player2);
	EXPECT_EQ(ball.getSpeed(), 6);
	ball.adjustSpeed(test_player3);
	EXPECT_EQ(ball.getSpeed(), MAX_BALL_SPEED);
}