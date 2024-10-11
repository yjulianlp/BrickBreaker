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

void drawHitbox(SDL_Renderer* renderer, SDL_Rect* hitbox) {
	SDL_SetRenderDrawColor(renderer, 255, 182, 193, 0.2);
	SDL_RenderDrawRect(renderer, hitbox);
}

void drawBallPoints(SDL_Renderer* renderer, int center_x, int center_y, int x_diff, int y_diff) {
	SDL_RenderDrawPoint(renderer, center_x + x_diff, center_y + y_diff);
	SDL_RenderDrawPoint(renderer, center_x + x_diff, center_y - y_diff);
	SDL_RenderDrawPoint(renderer, center_x - x_diff, center_y + y_diff);
	SDL_RenderDrawPoint(renderer, center_x - x_diff, center_y - y_diff);

	SDL_RenderDrawPoint(renderer, center_x + y_diff, center_y + x_diff);
	SDL_RenderDrawPoint(renderer, center_x + y_diff, center_y - x_diff);
	SDL_RenderDrawPoint(renderer, center_x - y_diff, center_y + x_diff);
	SDL_RenderDrawPoint(renderer, center_x - y_diff, center_y - x_diff);
}

void drawBall(SDL_Renderer* renderer, Ball& ball) {
	int x = 0, y = ball.getRadius();
	float decision_param = 1 - y;

	std::vector<int> center = ball.getCenter();
	drawBallPoints(renderer, center[0], center[1], x, y);

	while (y > x) {
		x += 1;

		if (decision_param >= 0) {
			y -= 1;
			decision_param += (x * 2) - (y * 2) + 1;
		}
		else {
			decision_param += (x * 2) + 1;
		}
		drawBallPoints(renderer, center[0], center[1], x, y);
	}
}

void render(SDL_Renderer* renderer, std::vector<Brick> bricks, Paddle& paddle, Ball& ball) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderClear(renderer);
	drawBricks(renderer, bricks);
	drawPaddle(renderer, paddle);
	drawBall(renderer, ball);
	drawHitbox(renderer, ball.getHitbox());
	SDL_RenderPresent(renderer);
}