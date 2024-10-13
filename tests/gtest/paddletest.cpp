#include "pch.h"
#include "gameitems.h"
#include "gameinfo.h"
#include "render.h"
#include "updateposition.h"
#include <iostream>
#include <vector>

class PaddleTest : public ::testing::Test {
protected:
	Paddle paddle = Paddle((SCREEN_WIDTH - PADDLE_WIDTH) / 2, SCREEN_HEIGHT - (SCREEN_HEIGHT / 6), PADDLE_WIDTH, PADDLE_HEIGHT);
};


TEST_F(PaddleTest, PaddleInitTest) {
	SDL_Rect* paddle_rect = paddle.getPaddle();
	EXPECT_EQ(paddle_rect->x, (SCREEN_WIDTH - PADDLE_WIDTH) / 2);
	EXPECT_EQ(paddle_rect->y, SCREEN_HEIGHT - (SCREEN_HEIGHT / 6));
	EXPECT_EQ(paddle_rect->w, PADDLE_WIDTH);
	EXPECT_EQ(paddle_rect->h, PADDLE_HEIGHT);
}

TEST_F(PaddleTest, PaddleCollideTest) {
	Paddle paddle2 = Paddle(((SCREEN_WIDTH - PADDLE_WIDTH) / 2)+1, (SCREEN_HEIGHT - (SCREEN_HEIGHT / 6))+1, PADDLE_WIDTH, PADDLE_HEIGHT);
	EXPECT_TRUE(paddle.isColliding(paddle2.getPaddle()));
}

TEST_F(PaddleTest, PaddleMoveXTest) {
	SDL_Rect* paddle_rect = paddle.getPaddle();
	int old_x = paddle_rect->x;
	paddle.moveX(5);
	EXPECT_EQ(paddle_rect->x, old_x + 5);

	paddle.moveX(-10);
	EXPECT_EQ(paddle_rect->x, old_x - 5);
}