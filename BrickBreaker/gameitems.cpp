#include "gameitems.h"
#include "gameinfo.h"
#include <vector>

Paddle::Paddle(int x, int y, int w, int h) {
	paddle = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	if (paddle != NULL) {
		*paddle = { x, y, w, h };
	}
}

SDL_Rect* Paddle::getPaddle() {
	return paddle;
}

void Paddle::setPaddle(SDL_Rect* new_paddle) {
	paddle = new_paddle;
}

bool Paddle::isColliding(SDL_Rect* object) {
	return (SDL_HasIntersection(paddle, object));
}

Ball::Ball(int ball_radius, int ball_center_x, int ball_center_y, int ball_x_velocity, int ball_y_velocity) {
	hitbox = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	if (hitbox != NULL) {
		*hitbox = { ball_center_x, ball_center_y, ball_radius*2, ball_radius*2 };
	}
	radius = ball_radius;
	center_x = ball_center_x;
	center_y = ball_center_y;
	x_velocity = ball_x_velocity;
	y_velocity = ball_y_velocity;
}

SDL_Rect* Ball::getHitbox() {
	return hitbox;
}
int Ball::getRadius() {
	return radius;
}

std::vector<int> Ball::getCenter() {
	std::vector<int> center = { center_x, center_y };
	return center;
}

std::vector<int> Ball::getVelocity() {
	std::vector<int> velocity = { x_velocity, y_velocity };
	return velocity;
}

Brick::Brick(int x, int y, int w, int h) {
	brick = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	if (brick != NULL) {
		*brick = {x, y, w, h};
	}
}

SDL_Rect* Brick::getBrick() {
	return brick;
}