#include "gameitems.h"
#include "gameinfo.h"
#include <vector>
#include <cassert>
#include "player.h"

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

void Paddle::moveX(int speed) {
	paddle->x += speed;
}

Ball::Ball(int ball_radius, int ball_center_x, int ball_center_y, int ball_speed, float ball_angle) {
	hitbox = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	if (hitbox != NULL) {
		int hitbox_side_length = ball_radius * 3;
		*hitbox = { ball_center_x - (hitbox_side_length)/2, ball_center_y - (hitbox_side_length) / 2, hitbox_side_length, hitbox_side_length };
	}
	radius = ball_radius;
	center_x = ball_center_x;
	center_y = ball_center_y;
	speed = ball_speed;
	x_velocity = ball_speed * cos(ball_angle);
	y_velocity = ball_speed * sin(ball_angle);
	angle = ball_angle;
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

void Ball::setXVelocity(int new_x_velocity) {
	x_velocity = new_x_velocity;
}

void Ball::setYVelocity(int new_y_velocity) {
	y_velocity = new_y_velocity;
}

int Ball::getSpeed() {
	return speed;
}

void Ball::setSpeed(int new_speed) {
	speed = new_speed;
}

void Ball::adjustSpeed(Player& player) {
	speed = 5 + (player.getScore() / SPEED_INCREASE_SCORE_AMOUNT);
	if (speed >= MAX_BALL_SPEED) {
		speed = MAX_BALL_SPEED;
	}
}

float Ball::getAngle() {
	return angle;
}

void Ball::setAngle(float new_angle) {
	angle = new_angle;
}

void Ball::movePosition(float time) {
	center_x += x_velocity * time;
	center_y += y_velocity * time;

	hitbox->x += x_velocity * time;
	hitbox->y += y_velocity * time;
}

void Ball::setPosition(int new_x_pos, int new_y_pos) {
	assert(new_x_pos >= 0);
	assert(new_y_pos >= 0);

	center_x = new_x_pos;
	center_y = new_y_pos;
	int hitbox_side_length = radius * 3;
	hitbox->x = center_x - (hitbox_side_length) / 2;
	hitbox->y = center_y - (hitbox_side_length) / 2;
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