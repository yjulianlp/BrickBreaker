#include <SDL.h>
#include <iostream>
#include "gameinfo.h"
#include "gameitems.h"
#include "render.h"
#include "updateposition.h"

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

	render(gRenderer, breakable_blocks, paddle, ball);

	while (running) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}
		updateBall(ball, 1.0);
		render(gRenderer, breakable_blocks, paddle, ball);

		SDL_Delay(FRAME_DELAY);
	}

	return 0;
}