#include "gameinfo.h"
#include "gameitems.h"
#include "updateposition.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cassert>

void adjustAngle(float& angle) {
	while (angle < 0) {
		angle += (2 * PI);
	}

	angle *= (180 / PI);

	if (angle < 30) {
		angle = 45;
	}
	else if (angle <= 150 && angle >= 180) {
		angle = 135;
	}
	else if (angle >= 180 && angle <= 210) {
		angle = 225;
	}
	else if (angle >= 330) {
		angle = 315;
	}

	angle *= (PI / 180);
}

void normalizeAngle(Ball& ball) {
	float temp_angle = ball.getAngle();

	while (temp_angle > (2 * PI)) {
		temp_angle -= (2 * PI);
	}

	while (temp_angle < -(2 * PI)) {
		temp_angle += (2 * PI);
	}

	ball.setAngle(temp_angle);
}

void updatePaddle(Paddle& paddle, SDL_Event* event) {
	const Uint8* pressed_keys = SDL_GetKeyboardState(NULL);
	SDL_Rect* paddle_rectangle = paddle.getPaddle();
	if (pressed_keys[SDL_SCANCODE_A]) {
		if (paddle_rectangle->x > 0) {
			paddle.moveX(-PADDLE_MOVEMENT_SPEED);
		}
	}
	else if (pressed_keys[SDL_SCANCODE_D]) {
		if ((paddle_rectangle->x + paddle_rectangle->w) < SCREEN_WIDTH) {
			paddle.moveX(PADDLE_MOVEMENT_SPEED);
		}
	}
}

std::vector<int> updateBall(Ball& ball, Paddle& paddle, std::vector<Brick> bricks, float time) {
	ball.setXVelocity(ball.getSpeed() * cos(ball.getAngle()));
	ball.setYVelocity(ball.getSpeed() * sin(ball.getAngle()));
	std::vector<int> velo = ball.getVelocity();

	float angle = ball.getAngle();
	std::cout << "current ball angle is: " << ball.getAngle() * (180 / PI) << "\n";
	assert(angle >= (0) && angle <= (2 * PI));
	ball.movePosition(time);

	int life = 0;
	std::vector<int> pos = ball.getCenter();
	if (pos[0]-BALL_RADIUS <= 0 || pos[0]+BALL_RADIUS >= SCREEN_WIDTH) {
		ball.setAngle(PI - ball.getAngle());
	}
	if (pos[1] - BALL_RADIUS < 0) {
		ball.setAngle(-ball.getAngle());
	}
	else if (pos[1] + BALL_RADIUS > SCREEN_HEIGHT) {
		ball.setAngle(-ball.getAngle());
		life = -1;
	}

	normalizeAngle(ball);

	SDL_Rect* paddle_rect = paddle.getPaddle();
	int is_intersecting = checkBallRectIntersection(ball, paddle_rect);
	float temp_angle = ball.getAngle(), paddle_section, paddle_section_ranges[3];
	switch (is_intersecting) {
	case 1: //left side
		temp_angle = PI - ball.getAngle();
		ball.setPosition(paddle_rect->x - ball.getRadius() - 5, pos[1]);
		break;
	case 2: //right side
		temp_angle = PI - ball.getAngle();
		ball.setPosition((paddle_rect->x + paddle_rect->w) + ball.getRadius() + 5, pos[1]);
		break;
	case 3: //top
		paddle_section = (paddle_rect->w) / 3;
		paddle_section_ranges[0] = paddle_rect->x;
		paddle_section_ranges[1] = paddle_section_ranges[0] + paddle_section;
		paddle_section_ranges[2] = paddle_section_ranges[1] + paddle_section;
		temp_angle = -ball.getAngle();
		if (pos[0] > paddle_section_ranges[2]) {
			//right
			std::cout << "hit right side of paddle\n";
			temp_angle += 15 * (PI / 180.0);
		}else if(pos[0] > paddle_section_ranges[1]) {
			//middle
			std::cout << "hit middle of paddle\n";
		}
		else {
			//left
			std::cout << "hit left side of paddle\n";
			temp_angle -= 15 * (PI / 180.0);
		}
		ball.setPosition(pos[0], paddle_rect->y - ball.getRadius() - 5);
		break;
	case 4: //bottom
		temp_angle = -ball.getAngle();
		ball.setPosition(pos[0], (paddle_rect->y + paddle_rect->h) + ball.getRadius() + 5);
		break;
	default:
		break;
	}

	adjustAngle(temp_angle);
	ball.setAngle(temp_angle);

	int hit = 0;
	for (int i = 0; i < bricks.size(); i++) {
		int is_hitting_block = checkBallRectIntersection(ball, bricks[i].getBrick());
		if (is_hitting_block) {
			switch (is_hitting_block) {
			case 1: //left side
			case 2: //right side
				temp_angle = PI - ball.getAngle();
				free(bricks[i].getBrick());
				hit++;
				break;
			case 3: //top
			case 4: //bottom
				temp_angle = -ball.getAngle();
				free(bricks[i].getBrick());
				hit++;
				break;
			default:
				break;
			}
			adjustAngle(temp_angle);
			ball.setAngle(temp_angle);
		}
	}
	std::vector<int> return_info = { hit, life };

	return return_info;
}

int checkBallRectIntersection(Ball& ball, SDL_Rect* rect) {
	SDL_Rect* ball_hitbox = ball.getHitbox();
	std::vector<int> ball_pos = ball.getCenter();

	
	if (SDL_HasIntersection(ball_hitbox, rect)) {
		std::cout << "checking for intersection\n";
		std::cout << "current ball angle is: " << ball.getAngle() * (180 / PI) << "\n";
		std::vector<int> close_pos = {ball_pos[0], ball_pos[1]};
		int rect_left_edge = rect->x;
		int rect_right_edge = rect_left_edge + (rect->w);

		int rect_top_edge = rect->y;
		int rect_bottom_edge = rect_top_edge + (rect->h);
		if (ball_pos[0] < rect_left_edge) { //if ball to left of rect
			close_pos[0] = rect_left_edge;
		}
		else if (ball_pos[0] > rect_right_edge) { //ball to right of rect
			close_pos[0] = rect_right_edge;
		}

		if (ball_pos[1] < rect_top_edge) { //ball under rect
			close_pos[1] = rect_top_edge;
		}
		else if (ball_pos[1] > rect_bottom_edge) { //ball over rect
			close_pos[1] = rect_bottom_edge;
		}

		int diff_x = close_pos[0] - ball_pos[0], diff_y = close_pos[1] - ball_pos[1];
		
		if ((pow(diff_x, 2) + pow(diff_y, 2)) <= pow(ball.getRadius(), 2)) {
			if (close_pos[0] == rect_left_edge) {
				std::cout << "hit left side\n";
				return 1;
			}
			else if (close_pos[0] == rect_right_edge) {
				std::cout << "hit right side\n";
				return 2;
			}
			if (close_pos[1] == rect_top_edge) {
				std::cout << "hit top\n";
				return 3;
			}
			else if (close_pos[1] == rect_bottom_edge) {
				std::cout << "hit bottom\n";
				return 4;
			}
			return 0;
		}
		return 0;


	}
	
	return 0;
}