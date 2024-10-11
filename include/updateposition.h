#pragma once
#include "gameinfo.h"
#include "gameitems.h"

void updatePaddle(Paddle& paddle, SDL_Event* event);

void updateBall(Ball& ball, Paddle& paddle, std::vector<Brick> bricks, float time);

int checkBallRectIntersection(Ball& ball, SDL_Rect* rect);