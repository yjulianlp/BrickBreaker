#pragma once
#include <SDL.h>
#include <vector>

class Paddle {
private:
	SDL_Rect* paddle;
public:
	Paddle(SDL_Rect* paddle);
	SDL_Rect* getPaddle();
	void setPaddle(SDL_Rect* new_paddle);
	bool isColliding(SDL_Rect* object);
};

class Ball {
private:
	SDL_Rect* hitbox;
	int radius;
	int center_x;
	int center_y;
	int x_velocity;
	int y_velocity;
public:
	Ball(SDL_Rect* hitbox, int radius, int center_x, int center_y, int x_velocity, int y_velocity);
	SDL_Rect* getHitbox();
	int getRadius();
	std::vector<int> getCenter();
	std::vector<int> getVelocity();
};

class Brick {
private:
	SDL_Rect* brick;
public:
	Brick(int x, int y, int w, int h);
	SDL_Rect* getBrick();
};