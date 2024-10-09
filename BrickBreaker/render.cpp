#include <vector>
#include "gameitems.h"

void renderBrick(SDL_Renderer* renderer, Brick& brick) {
	SDL_RenderDrawRect(renderer, brick.getBrick());
}

void renderBricks(SDL_Renderer* renderer, std::vector<Brick> bricks) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
	for (int i = 0; i < bricks.size(); i++) {
		renderBrick(renderer, bricks[i]);
	}
	SDL_RenderPresent(renderer);
}