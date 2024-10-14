#include <SDL.h>
#include <iostream>
#include "gameinfo.h"
#include "gameitems.h"
#include "render.h"
#include "updateposition.h"
#include "player.h"

int main(int argc, char* argv[]) {
	bool running = true;
	SDL_Event event;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "failed to initialize";
	}

	SDL_Window* gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

	std::vector<Brick> breakable_blocks;

	//breakable blocks
	int layers = NUM_BRICKS / (SCREEN_WIDTH / BRICK_WIDTH);
	for (int i = 0; i < layers; i++) {
		int layer_y = i * BRICK_HEIGHT;
		for (int j = 0; j < (SCREEN_WIDTH / BRICK_WIDTH); j++) {
			int brick_x = j * BRICK_WIDTH;
			breakable_blocks.push_back(Brick(brick_x, layer_y, BRICK_WIDTH, BRICK_HEIGHT));
		}
	}

	//paddle
	Paddle paddle = Paddle((SCREEN_WIDTH - PADDLE_WIDTH) / 2, SCREEN_HEIGHT - (SCREEN_HEIGHT / 6), PADDLE_WIDTH, PADDLE_HEIGHT);

	//ball
	Ball ball = Ball(BALL_RADIUS, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, INITIAL_BALL_SPEED, INITIAL_BALL_ANGLE);

	//player
	Player player = Player("player_name", PLAYER_STARTING_SCORE, PLAYER_STARTING_LIVES);

	render(gRenderer, breakable_blocks, paddle, ball);
	std::vector<int> info;
	while (running) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			updatePaddle(paddle, &event);
			
		}
		info = updateBall(ball, paddle, breakable_blocks, 1.0);
		if (info[0] > 0) {
			player.addScore(info[0]);
			ball.adjustSpeed(player);
		}
		player.updateLives(info[1]);
		if (player.getLives() <= 0) {
			gameOver(gRenderer, gWindow);
			SDL_Delay(5000);
			break;
		}
		render(gRenderer, breakable_blocks, paddle, ball);

		SDL_Delay(FRAME_DELAY);
	}

	return 0;
}