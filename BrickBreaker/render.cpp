#include <vector>
#include "gameitems.h"

void drawBrick(SDL_Renderer* renderer, Brick& brick) {
	SDL_RenderDrawRect(renderer, brick.getBrick());
}

void drawBricks(SDL_Renderer* renderer, std::vector<Brick> bricks) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
	for (int i = 0; i < bricks.size(); i++) {
		drawBrick(renderer, bricks[i]);
	}
}

void drawPaddle(SDL_Renderer* renderer, Paddle& paddle) {
	SDL_RenderFillRect(renderer, paddle.getPaddle());
}

void render(SDL_Renderer* renderer, std::vector<Brick> bricks, Paddle& paddle) {
	drawBricks(renderer, bricks);
	drawPaddle(renderer, paddle);
	//drawBall(renderer, ball);
	SDL_RenderPresent(renderer);


}