#include "gameinfo.h"
#include "gameitems.h"
#include "updateposition.h"
#include <iostream>
#include <cmath>

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
void updateBall(Ball& ball, Paddle& paddle, float time) {
	std::vector<int> pos = ball.getCenter();
	//std::cout << "current angle: " << ball.getAngle() << "\n";
	ball.setXVelocity(ball.getSpeed() * cos(ball.getAngle()));
	ball.setYVelocity(ball.getSpeed() * sin(ball.getAngle()));
	std::vector<int> velo = ball.getVelocity();

	ball.movePosition(time);

	pos = ball.getCenter();
	if (pos[0]-BALL_RADIUS <= 0 || pos[0]+BALL_RADIUS >= SCREEN_WIDTH) {
		ball.setAngle(PI - ball.getAngle());
	}
	if (pos[1] - BALL_RADIUS < 0 || pos[1] + BALL_RADIUS > SCREEN_HEIGHT) {
		ball.setAngle(-ball.getAngle());
	}

	SDL_Rect* paddle_rect = paddle.getPaddle();
	int is_intersecting = checkBallRectIntersection(ball, paddle_rect);
	if (is_intersecting) {
		ball.setAngle(-ball.getAngle());
	}


}

int checkBallRectIntersection(Ball& ball, SDL_Rect* rect) {
	SDL_Rect* ball_hitbox = ball.getHitbox();
	std::vector<int> ball_pos = ball.getCenter();

	
	if (SDL_HasIntersection(ball_hitbox, rect)) {
		std::cout << "checking for intersection\n";
		std::vector<int> close_pos = {ball_pos[0], ball_pos[1]};
		//int close_x = ball_pos[0], close_y = ball_pos[1];
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