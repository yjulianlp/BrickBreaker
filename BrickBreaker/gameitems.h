#pragma once
#include <SDL.h>
#include <vector>

class Paddle {
private:
	SDL_Rect* paddle;
public:
	Paddle(int x, int y, int w, int h);
	SDL_Rect* getPaddle();
	void setPaddle(SDL_Rect* new_paddle);
	bool isColliding(SDL_Rect* object);
	void moveX(int speed);
};

class Ball {
private:
	SDL_Rect* hitbox;
	int radius;
	int center_x;
	int center_y;
	int speed;
	int x_velocity;
	int y_velocity;
	float angle;
public:
	Ball(int radius, int center_x, int center_y, int speed, float angle);
	SDL_Rect* getHitbox();
	int getRadius();
	std::vector<int> getCenter();
	std::vector<int> getVelocity();
	int getSpeed();
	void setSpeed(int new_speed);
	void setXVelocity(int new_x_velocity);
	void setYVelocity(int new_y_velocity);
	float getAngle();
	void setAngle(float new_angle);
	void movePosition(float time);
};

class Brick {
private:
	SDL_Rect* brick;
public:
	Brick(int x, int y, int w, int h);
	SDL_Rect* getBrick();
};