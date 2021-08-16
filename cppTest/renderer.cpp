int p_1_score = 0;
int p_2_score = 0;

internal void clear_screen(u32 colour) {
	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = colour;
		}
	}
}


internal void draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 colour) {
	
	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);
	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y*render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = colour;
		}
	}
}

global_variable float render_scale = 0.01f;

internal void draw_rect(float x, float y, float half_size_x, float half_size_y, u32 colour) {
	
	x *= render_state.height*render_scale;
	y *= render_state.height*render_scale;
	half_size_x *= render_state.height*render_scale;
	half_size_y *= render_state.height*render_scale;


	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	//change to pixels
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	draw_rect_in_pixels(x0, y0, x1, y1, colour);
}
internal void win() {
	LPCWSTR str1 = TEXT("You Win!");
	LPCWSTR str2 = TEXT("Game Over");
	MessageBox(0, str1, str2, MB_OK);
	running = false;
}
internal void declare_start() {
	LPCWSTR str1 = TEXT("W and S to move, first to 6 wins");
	LPCWSTR str2 = TEXT("Game Start");
	MessageBox(0, str1, str2, MB_OK);
}

internal void lose() {
	LPCWSTR str2 = TEXT("Game Over");
	LPCWSTR str1 = TEXT("You Lose!");
	MessageBox(0, str1, str2, MB_OK);
	running = false;
}


internal void declare_winner(float player) {
	if (player > 0) {
		lose();
	}
	else if (player < 0) {
		win();
	}
}

internal void score_point(float player, bool scored) {
	if (player < 0) {
		if (scored) { p_1_score++; }
		if (p_1_score == 1) {
			draw_rect(player + 40, 20, .5, 3, 0x000000);
		}
		else if (p_1_score == 2) {
			draw_rect(player + 40, 22.5, 2, 0.5, 0x000000);
			draw_rect(player + 40, 17.5, 2, 0.5, 0x000000);
			draw_rect(player + 41.5, 21.5, .5, .5, 0x000000);
			draw_rect(player + 41.2, 21.5, .5, .5, 0x000000);
			draw_rect(player + 40.4, 20.5, .5, .5, 0x000000);
			draw_rect(player + 39.6, 19.5, .5, .5, 0x000000);
			draw_rect(player + 38.8, 18.5, .5, .5, 0x000000);
			draw_rect(player + 38.5, 18.5, .5, .5, 0x000000);
		}
		else if (p_1_score == 3) {
			draw_rect(player + 41.5, 20, .5, 3, 0x000000);
			draw_rect(player + 40, 22.5, 1.5, 0.5, 0x000000);
			draw_rect(player + 40, 20, 1.5, .5, 0x000000);
			draw_rect(player + 40, 17.5, 1.5, .5, 0x000000);
		}
		else if (p_1_score == 4) {
			draw_rect(player + 41.5, 20, .5, 3, 0x000000);
			draw_rect(player + 38.5, 21.5, .5, 1.5, 0x000000);
			draw_rect(player + 40, 20, 2, .5, 0x000000);
		}
		else if (p_1_score == 5) {
			draw_rect(player + 40, 22.5, 2, 0.5, 0x000000);
			draw_rect(player + 40, 20, 2, 0.5, 0x000000);
			draw_rect(player + 40, 17.5, 2, 0.5, 0x000000);
			draw_rect(player + 38.5, 21.5, .5, 1.5, 0x000000);
			draw_rect(player + 41.5, 18.5, .5, 1.5, 0x000000);
		}
		else {
			draw_rect(player + 40, 20, 2, 3, 0x000000);
			draw_rect(player + 40, 20, 1, 2, 0xffffff);
		}
	}
	if (player > 0) {
		if (scored) { p_2_score++; }
		if (p_2_score == 1) {
			draw_rect(player - 40, 20, .5, 3, 0x000000);
		}
		else if (p_2_score == 2) {
			draw_rect(player - 40, 22.5, 2, 0.5, 0x000000);
			draw_rect(player - 40, 17.5, 2, 0.5, 0x000000);
			draw_rect(player - 38.5, 21.5, .5, .5, 0x000000);
			draw_rect(player - 38.8, 21.5, .5, .5, 0x000000);
			draw_rect(player - 39.6, 20.5, .5, .5, 0x000000);
			draw_rect(player - 40.4, 19.5, .5, .5, 0x000000);
			draw_rect(player - 41.2, 18.5, .5, .5, 0x000000);
			draw_rect(player - 41.5, 18.5, .5, .5, 0x000000);
		}
		else if (p_2_score == 3) {
			draw_rect(player - 38.5, 20, .5, 3, 0x000000);
			draw_rect(player - 40, 22.5, 2, 0.5, 0x000000);
			draw_rect(player - 40, 20, 2, .5, 0x000000);
			draw_rect(player - 40, 17.5, 2, .5, 0x000000);
		}
		else if (p_2_score == 4) {
			draw_rect(player - 38.5, 20, .5, 3, 0x000000);
			draw_rect(player - 41.5, 21.5, .5, 1.5, 0x000000);
			draw_rect(player - 40, 20, 2, .5, 0x000000);
		}
		else if (p_2_score == 5) {
			draw_rect(player - 40, 22.5, 2, 0.5, 0x000000);
			draw_rect(player - 40, 20, 2, 0.5, 0x000000);
			draw_rect(player - 40, 17.5, 2, 0.5, 0x000000);
			draw_rect(player - 41.5, 21.5, .5, 1.5, 0x000000);
			draw_rect(player - 38.5, 18.5, .5, 1.5, 0x000000);
		}
		else{
			draw_rect(player - 40, 20, 2, 3, 0x000000);
			draw_rect(player - 40, 20, 1, 2, 0xffffff);
		}
	}
	if (scored && (p_2_score > 5 || p_1_score > 5 )) {
		declare_winner(player);
	}
}


internal void draw_points(float player_1, float player_2) {
	draw_rect(player_1 + 40, 20, 10, 5, 0xff5500);
	draw_rect(player_1 + 40, 20, 9, 4, 0xffffff);
	draw_rect(player_2 - 40, 20, 10, 5, 0xff5500);
	draw_rect(player_2 - 40, 20, 9, 4, 0xffffff);
	score_point(player_1, false);
	score_point(player_2, false);
	
}


