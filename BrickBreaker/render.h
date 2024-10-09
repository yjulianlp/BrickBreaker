#pragma once
#include <vector>
#include "gameitems.h"

void renderBrick(SDL_Renderer* renderer, Brick& brick);

void renderBricks(SDL_Renderer* renderer, std::vector<Brick> bricks);