#pragma once
#include <vector>
#include "gameitems.h"

void drawBrick(SDL_Renderer* renderer, Brick& brick);

void drawBricks(SDL_Renderer* renderer, std::vector<Brick> bricks);

void drawPaddle(SDL_Renderer* renderer, Paddle& paddle);

void drawBall(SDL_Renderer* renderer, Ball& ball);

void drawBallPoints(SDL_Renderer* renderer, int center_x, int center_y, int x_diff, int y_diff);

void drawHitbox(SDL_Renderer* renderer, SDL_Rect* hitbox);

void render(SDL_Renderer* renderer, std::vector<Brick> bricks, Paddle& paddle, Ball& ball);

void gameOver(SDL_Renderer* renderer, SDL_Window* window);