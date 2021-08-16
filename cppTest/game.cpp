#define is_down(b) input -> buttons[b].is_down
#define pressed(b) (input -> buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input -> buttons[b].is_down && input->buttons[b].changed)

float player_1_p, player_1_dp, player_2_p, player_2_dp;
float arena_half_size_x = 85, arena_half_size_y = 45;
float player_half_size_x = 2.5, player_half_size_y = 12, player_1_x = -80, player_2_x = 80;
float ball_p_x, ball_p_y, ball_dp_x = 100, ball_dp_y = 50, ball_half_size = 1;
int waiting = 0;


internal void wait() {	
	ball_dp_x = 0;
	ball_dp_y = 0;
	if (waiting == 0){
		waiting = 1;
		}
}


internal void check_direction(float player) {
	if (ball_p_y > player) {
		if (ball_dp_y < 0) {
			ball_dp_y *= -(1.1 + (ball_p_y - player) / player_half_size_y);
		}
		else {
			ball_dp_y *= (1.1 + (ball_p_y - player) / player_half_size_y);
		}
	}
	if (ball_p_y < player) {
		if (ball_dp_y > 0) {
			ball_dp_y *= -(1.1 + (player - ball_p_y) / player_half_size_y);
		}
		else {
			ball_dp_y *= (1.1 + (player - ball_p_y) / player_half_size_y);
		}
	}
}

internal void ball_hits(float ball_x, float ball_y, float player_1, float player_2) {
	float bottom_p_1, top_p_1, left_p_1, right_p_1, bottom_p_2, top_p_2, left_p_2, right_p_2, left_ball, right_ball, top_ball, bottom_ball;
	bottom_p_1 = player_1 - player_half_size_y;
	top_p_1 = player_1 + player_half_size_y;
	left_p_1 = player_1_x - player_half_size_x;
	right_p_1 = player_1_x + player_half_size_x;
	bottom_p_2 = player_2 - player_half_size_y;
	top_p_2 = player_2 + player_half_size_y;
	left_p_2 = player_2_x - player_half_size_x;
	right_p_2 = player_2_x + player_half_size_x;
	bottom_ball = ball_y - ball_half_size;
	top_ball = ball_y + ball_half_size;
	left_ball = ball_x - ball_half_size;
	right_ball = ball_x + ball_half_size;

	// For player 1's paddle
	// "Front" the paddle
	if (right_p_1 > left_ball && right_p_1 < right_ball &&
		(bottom_ball < top_p_1 && top_ball > bottom_p_1)) {
		ball_p_x = right_p_1 + ball_half_size;
		ball_dp_x *= -1.1;
		check_direction(player_1_p);
	}
	// "Behind" the paddle
	if (left_p_1 < right_ball && left_p_1 > left_ball &&
		(bottom_ball < top_p_1 && top_ball>bottom_p_1)) {
		ball_p_x = left_p_1 - ball_half_size;
		ball_dp_x *= -1.1;
		check_direction(player_1_p);
	}
	// "Top" of the paddle
	if (top_p_1 < top_ball && top_p_1 > bottom_ball &&
		(left_ball<right_p_1 && right_ball>left_p_1)) {
		ball_p_y = top_p_1 + ball_half_size;
		ball_dp_y *= -1.1;
		//check_direction(player_1_p);
	}
	// "Bottom" of the paddle
	if (bottom_p_1 < top_ball && bottom_p_1 > bottom_ball &&
		(left_ball<right_p_1 && right_ball>left_p_1)) {
		ball_p_y = bottom_p_1 - ball_half_size;
		ball_dp_y *= -1.1;
		//check_direction(player_1_p);
	}
	// "Inside" the paddle
	if (bottom_p_1 < top_ball && top_p_1 > bottom_ball && left_p_1 > right_ball && right_p_1 < left_ball) {
		ball_p_x = right_p_1 + ball_half_size;
		ball_p_y = player_1;
	}
	// For player 2's paddle
	// "Behind" the paddle
	if (right_p_2 > left_ball && right_p_2 < right_ball &&
		(bottom_ball < top_p_2 && top_ball > bottom_p_2)) {
		ball_p_x = right_p_2 + ball_half_size;
		ball_dp_x *= -1.1;
		check_direction(player_2_p);
	}
	// "Front" of the paddle
	if (left_p_2 < right_ball && left_p_2 > left_ball &&
		(bottom_ball < top_p_2 && top_ball>bottom_p_2)) {
		ball_p_x = left_p_2 - ball_half_size;
		ball_dp_x *= -1.1;
		check_direction(player_2_p);
	}
	// "Top" of the paddle
	if (top_p_2 < top_ball && top_p_2 > bottom_ball &&
		(left_ball<right_p_2 && right_ball>left_p_2)) {
		ball_p_y = top_p_2 + ball_half_size;
		ball_dp_y *= -1.1;
		//check_direction(player_2_p);
	}
	// "Bottom" of the paddle
	if (bottom_p_2 < top_ball && bottom_p_2 > bottom_ball &&
		(left_ball<right_p_2 && right_ball>left_p_2)) {
		ball_p_y = bottom_p_2 - ball_half_size;
		ball_dp_y *= -1.1;
		//check_direction(player_2_p);
	}
	// "Inside" the paddle
	if (bottom_p_2 < top_ball && top_p_2 > bottom_ball && left_p_2 > right_ball && right_p_2 < left_ball) {
		ball_p_x = right_p_2 + ball_half_size;
		ball_p_y = player_2;
	}
	if (ball_dp_x > 200) {
		ball_dp_x = 200;
	}
	if (ball_dp_y > 150) {
		ball_dp_y = 150;
	}
}

internal int ai_control() {
	if (ball_p_y > player_2_p+3) {
		return 0;
	}
	if (ball_p_y < player_2_p-3) {
		return 1;
	}
	return 2;
}

internal void simulate_game(Input* input, float dt) {
	clear_screen(0xffaa33);
	draw_rect(0, 0, arena_half_size_x, arena_half_size_y, 0xffffff);
	draw_points(player_1_x, player_2_x);
	for (int y = -arena_half_size_y + 2; y < arena_half_size_y; y += 10) {
		draw_rect(0, y+2.5, 1, 2.5, 0xfc2c03);
	}
	
	
	float player_1_ddp = 0.f; //units per second
	if (is_down(BUTTON_UP)) player_1_ddp += 2000;//acceleration
	if (is_down(BUTTON_DOWN)) player_1_ddp -= 2000;

	float player_2_ddp = 0.f; //units per second
	if (ai_control() == 0) player_2_ddp += 2000;
	if (ai_control() == 1) player_2_ddp -= 2000;
	//if (is_down(BUTTON_UP_2)) player_2_ddp += 2000;//acceleration
	//if (is_down(BUTTON_DOWN_2)) player_2_ddp -= 2000;

	//friction
	player_2_ddp -= player_2_dp * 10.f;
	player_1_ddp -= player_1_dp * 10.f;

	//acceleration equation
	player_1_p = player_1_p + player_1_dp * dt + player_1_ddp * dt * dt * 0.5f;
	player_1_dp = player_1_dp + player_1_ddp * dt;
	player_2_p = player_2_p + player_2_dp * dt + player_2_ddp * dt * dt * 0.5f;
	player_2_dp = player_2_dp + player_2_ddp * dt;

	//collision detection

	if (player_1_p + player_half_size_y > arena_half_size_y) {
		player_1_p = arena_half_size_y - player_half_size_y;
		player_1_dp *= 0;
	}
	if (player_1_p - player_half_size_y < -arena_half_size_y) {
		player_1_p = -arena_half_size_y + player_half_size_y;
		player_1_dp *= 0;
	}
	if (player_2_p + player_half_size_y > arena_half_size_y) {
		player_2_p = arena_half_size_y - player_half_size_y;
		player_2_dp *= 0;
	}
	if (player_2_p - player_half_size_y < -arena_half_size_y) {
		player_2_p = -arena_half_size_y + player_half_size_y;
		player_2_dp *= 0;
	}
	
	ball_p_x += ball_dp_x * dt;
	ball_p_y += ball_dp_y * dt;
	//if (is_down(BUTTON_LEFT)) player_pos_x -= speed*dt;
	//if (is_down(BUTTON_RIGHT)) player_pos_x += speed*dt;
	/*if (pressed(BUTTON_UPLEFT)) {
		player_pos_x -= speed;
		player_pos_y += speed;
	}
	if (pressed(BUTTON_UPRIGHT)) {
		player_pos_x += speed;
		player_pos_y += speed;
	}
	if (pressed(BUTTON_DOWNLEFT)) {
		player_pos_x -= speed;
		player_pos_y -= speed;
	}
	if (pressed(BUTTON_DOWNRIGHT)) {
		player_pos_x += speed;
		player_pos_y -= speed;
	}*/

	// ball
	draw_rect(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 0x000000);

	//arena collision
	//Right Side
	if (ball_p_x + ball_half_size > arena_half_size_x) {
		ball_p_x = 0;
		ball_p_y = 0;
		score_point(player_1_x, true);
		wait();
		waiting = -1;
	}
	//Left Side
	if (ball_p_x - ball_half_size < -arena_half_size_x) {
		ball_p_x = 0;
		ball_p_y = 0;
		score_point(player_2_x, true);
		wait();
		waiting = 1;
	}
	//Bottom
	if (ball_p_y + ball_half_size > arena_half_size_y) {
		ball_p_y = arena_half_size_y - ball_half_size;
		ball_dp_y *= -1;
	}
	//Top
	if (ball_p_y - ball_half_size < -arena_half_size_y) {
		ball_p_y = -arena_half_size_y + ball_half_size;
		ball_dp_y *= -1;
	}

	if (waiting != 0) {
		if (pressed(BUTTON_DOWN) || pressed(BUTTON_UP)) {
			ball_dp_x = 100 * waiting;
			ball_dp_y = 50;
			if ((rand() % 2 - 1) == 0) {
				ball_dp_y = -50;
			}
			waiting = 0;
		}
	}
	//player collision
	ball_hits(ball_p_x, ball_p_y, player_1_p, player_2_p);
		

	draw_rect(player_2_x, player_2_p, player_half_size_x, player_half_size_y, 0xff0000);
	draw_rect(player_1_x, player_1_p, player_half_size_x, player_half_size_y, 0xff0000);
}