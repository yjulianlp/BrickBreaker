#pragma once
#include <vector>
#include "gameitems.h"

void drawBrick(SDL_Renderer* renderer, Brick& brick);

void drawBricks(SDL_Renderer* renderer, std::vector<Brick> bricks);

void drawPaddle(SDL_Renderer* renderer, Paddle& paddle);

void render(SDL_Renderer* renderer, std::vector<Brick> bricks, Paddle& paddle);