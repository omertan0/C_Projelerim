#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "third_party/raylib/src/raylib.h"

#define GRID_WIDTH 30
#define GRID_HEIGHT 20
#define CELL_SIZE 24
#define PANEL_HEIGHT 80
#define HUD_ALPHA 180
#define SCREEN_WIDTH (GRID_WIDTH * CELL_SIZE)
#define SCREEN_HEIGHT (GRID_HEIGHT * CELL_SIZE + PANEL_HEIGHT)
#define MAX_SNAKE_LENGTH (GRID_WIDTH * GRID_HEIGHT)
#define START_SNAKE_LENGTH 3
#define TARGET_FPS 12
#define GRID_LINE_ALPHA 55

typedef struct {
	int x;
	int y;
} position_t;

typedef enum {
	direction_up,
	direction_down,
	direction_left,
	direction_right
} direction_t;

static int is_position_on_snake(const position_t snake[], int snake_length, int x, int y) {
	int i;

	for (i = 0; i < snake_length; ++i) {
		if (snake[i].x == x && snake[i].y == y) {
			return 1;
		}
	}

	return 0;
}

static position_t create_food(const position_t snake[], int snake_length) {
	position_t food;

	do {
		food.x = GetRandomValue(0, GRID_WIDTH - 1);
		food.y = GetRandomValue(0, GRID_HEIGHT - 1);
	} while (is_position_on_snake(snake, snake_length, food.x, food.y));

	return food;
}

static direction_t update_direction(direction_t current_direction) {
	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
		if (current_direction != direction_down) {
			return direction_up;
		}
	}

	if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
		if (current_direction != direction_up) {
			return direction_down;
		}
	}

	if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
		if (current_direction != direction_right) {
			return direction_left;
		}
	}

	if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
		if (current_direction != direction_left) {
			return direction_right;
		}
	}

	return current_direction;
}

static int check_wall_collision(int x, int y) {
	if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) {
		return 1;
	}

	return 0;
}

static int check_self_collision(const position_t snake[], int snake_length, int next_x, int next_y, int will_grow) {
	int body_limit;
	int i;

	body_limit = snake_length;

	/* Kuyruk hareket edecekse son hücreyi kontrol dışı bırakabiliriz. */
	if (!will_grow && body_limit > 0) {
		--body_limit;
	}

	for (i = 0; i < body_limit; ++i) {
		if (snake[i].x == next_x && snake[i].y == next_y) {
			return 1;
		}
	}

	return 0;
}

static Color make_alpha_color(Color color, unsigned char alpha) {
	color.a = alpha;
	return color;
}

static void draw_background(void) {
	float time_value;
	int x;
	int y;

	time_value = (float)GetTime();

	DrawRectangleGradientV(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){ 14, 23, 44, 255 }, (Color){ 22, 94, 105, 255 });
	DrawCircleGradient((Vector2){ (float)(SCREEN_WIDTH * 0.18f), (float)(SCREEN_HEIGHT * 0.18f) }, 180.0f, (Color){ 255, 255, 255, 40 }, (Color){ 255, 255, 255, 0 });
	DrawCircleGradient((Vector2){ (float)(SCREEN_WIDTH * 0.82f), (float)(SCREEN_HEIGHT * 0.28f) }, 210.0f, (Color){ 255, 182, 77, 28 }, (Color){ 255, 182, 77, 0 });
	DrawCircleGradient((Vector2){ (float)(SCREEN_WIDTH * 0.56f), (float)(SCREEN_HEIGHT * 0.82f) }, 260.0f, (Color){ 120, 76, 255, 18 }, (Color){ 120, 76, 255, 0 });

	for (x = 0; x <= GRID_WIDTH; ++x) {
		float wobble;
		int line_x;

		wobble = sinf(time_value * 1.8f + (float)x * 0.3f) * 1.2f;
		line_x = x * CELL_SIZE;
		DrawLine(line_x, PANEL_HEIGHT, line_x, SCREEN_HEIGHT, make_alpha_color((Color){ 255, 255, 255, 0 }, GRID_LINE_ALPHA));
		if (wobble > 0.0f) {
			DrawLine(line_x + 1, PANEL_HEIGHT, line_x + 1, SCREEN_HEIGHT, make_alpha_color((Color){ 255, 255, 255, 0 }, 20));
		}
	}

	for (y = 0; y <= GRID_HEIGHT; ++y) {
		int line_y;

		line_y = PANEL_HEIGHT + y * CELL_SIZE;
		DrawLine(0, line_y, SCREEN_WIDTH, line_y, make_alpha_color((Color){ 255, 255, 255, 0 }, GRID_LINE_ALPHA));
	}
}

static void draw_snake_segment(int x, int y, Color color, int shrink) {
	Rectangle segment;
	float inset;

	inset = shrink ? 4.0f : 2.0f;
	segment.x = (float)(x * CELL_SIZE) + inset;
	segment.y = (float)(PANEL_HEIGHT + y * CELL_SIZE) + inset;
	segment.width = (float)CELL_SIZE - inset * 2.0f;
	segment.height = (float)CELL_SIZE - inset * 2.0f;

	DrawRectangleRounded(segment, 0.35f, 6, color);
	DrawRectangleRoundedLinesEx(segment, 0.35f, 6, 2.0f, make_alpha_color(BLACK, 70));
}

static void draw_food(position_t food) {
	float pulse;
	float center_x;
	float center_y;
	float radius;

	pulse = 1.0f + 0.12f * sinf((float)GetTime() * 6.0f);
	center_x = (float)(food.x * CELL_SIZE + CELL_SIZE / 2);
	center_y = (float)(PANEL_HEIGHT + food.y * CELL_SIZE + CELL_SIZE / 2);
	radius = (float)CELL_SIZE * 0.45f * pulse;

	DrawCircleV((Vector2){ center_x, center_y }, radius + 8.0f, make_alpha_color((Color){ 255, 115, 115, 0 }, 55));
	DrawCircleV((Vector2){ center_x, center_y }, radius + 2.0f, make_alpha_color((Color){ 255, 70, 70, 255 }, 120));
	DrawCircleV((Vector2){ center_x, center_y }, radius, (Color){ 255, 89, 73, 255 });
	DrawCircleV((Vector2){ center_x + 3.0f, center_y - 2.0f }, radius * 0.33f, (Color){ 255, 210, 210, 180 });
	DrawRectangleRounded((Rectangle){ center_x - 2.0f, center_y - radius - 6.0f, 4.0f, 8.0f }, 0.8f, 8, (Color){ 117, 79, 46, 255 });
	DrawEllipse((int)(center_x + 6.0f), (int)(center_y - radius - 4.0f), 8.0f, 4.5f, (Color){ 58, 164, 66, 255 });
}

static void draw_game(const position_t snake[], int snake_length, position_t food, int score, int game_over, int game_won) {
	int x;
	int y;
	float time_value;

	time_value = (float)GetTime();

	BeginDrawing();
	ClearBackground((Color){ 10, 16, 30, 255 });
	draw_background();

	DrawRectangle(0, 0, SCREEN_WIDTH, PANEL_HEIGHT, make_alpha_color((Color){ 10, 14, 24, 255 }, HUD_ALPHA));
	DrawRectangleGradientV(0, 0, SCREEN_WIDTH, PANEL_HEIGHT, make_alpha_color((Color){ 255, 255, 255, 18 }, 30), make_alpha_color((Color){ 0, 0, 0, 60 }, 90));
	DrawRectangleLines(8, 8, SCREEN_WIDTH - 16, SCREEN_HEIGHT - 16, make_alpha_color((Color){ 255, 255, 255, 255 }, 80));

	DrawText("Yilan Oyunu", 18, 12, 30, WHITE);
	DrawText(TextFormat("Skor: %d", score), 20, 46, 20, (Color){ 220, 240, 255, 255 });
	DrawText("WASD / Ok tuslari   R: yeniden baslat   ESC: cikis", 164, 46, 18, (Color){ 190, 205, 220, 255 });
	DrawText(TextFormat("Hiz: %d", TARGET_FPS), SCREEN_WIDTH - 90, 46, 18, (Color){ 190, 205, 220, 255 });

	DrawRectangleRounded((Rectangle){ 14, 14, 120, 24 }, 0.45f, 8, make_alpha_color((Color){ 255, 255, 255, 255 }, 18));
	DrawText("Arcade Mode", 24, 17, 16, (Color){ 190, 255, 223, 255 });

	for (y = 0; y < GRID_HEIGHT; ++y) {
		for (x = 0; x < GRID_WIDTH; ++x) {
			Rectangle cell_rect;
			Color base_color;

			cell_rect.x = (float)(x * CELL_SIZE);
			cell_rect.y = (float)(y * CELL_SIZE + PANEL_HEIGHT);
			cell_rect.width = (float)CELL_SIZE;
			cell_rect.height = (float)CELL_SIZE;

			base_color = (Color){ 20, 34, 48, 185 };

			if (((x + y) % 2) == 0) {
				base_color = (Color){ 24, 40, 58, 185 };
			}

			DrawRectangleRec(cell_rect, base_color);
		}
	}

	draw_food(food);

	for (y = snake_length - 1; y >= 0; --y) {
		Color segment_color;
		float fade_factor;

		fade_factor = 1.0f - ((float)y / (float)(snake_length > 0 ? snake_length : 1)) * 0.35f;
		if (y == 0) {
			segment_color = (Color){ 185, 255, 200, 255 };
			draw_snake_segment(snake[y].x, snake[y].y, segment_color, 0);
			DrawCircle((int)(snake[y].x * CELL_SIZE + CELL_SIZE / 2), (int)(PANEL_HEIGHT + snake[y].y * CELL_SIZE + CELL_SIZE / 2), 3, (Color){ 20, 25, 20, 255 });
			DrawCircle((int)(snake[y].x * CELL_SIZE + CELL_SIZE / 2 + 6), (int)(PANEL_HEIGHT + snake[y].y * CELL_SIZE + CELL_SIZE / 2 - 4), 1, (Color){ 20, 25, 20, 255 });
		} else {
			unsigned char alpha;

			alpha = (unsigned char)(220.0f * fade_factor);
			segment_color = (Color){ 58, 214, 128, alpha };
			draw_snake_segment(snake[y].x, snake[y].y, segment_color, 1);
		}
	}

	DrawRectangle((int)(snake[0].x * CELL_SIZE - 8), (int)(PANEL_HEIGHT + snake[0].y * CELL_SIZE - 8), CELL_SIZE + 16, CELL_SIZE + 16, make_alpha_color((Color){ 64, 255, 160, 0 }, (unsigned char)(40 + 20 * sinf(time_value * 8.0f))));

	if (game_over) {
		DrawRectangle(0, SCREEN_HEIGHT / 2 - 60, SCREEN_WIDTH, 120, (Color){ 0, 0, 0, 160 });
		DrawRectangleGradientV(0, SCREEN_HEIGHT / 2 - 60, SCREEN_WIDTH, 120, (Color){ 0, 0, 0, 200 }, (Color){ 0, 0, 0, 120 });
		if (game_won) {
			DrawText("KAZANDIN!", SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 - 32, 38, (Color){ 255, 240, 170, 255 });
			DrawText("Tekrar baslamak icin R", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 14, 22, RAYWHITE);
		} else {
			DrawText("OYUN BITTI", SCREEN_WIDTH / 2 - 118, SCREEN_HEIGHT / 2 - 32, 38, (Color){ 255, 185, 185, 255 });
			DrawText("Tekrar baslamak icin R", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 14, 22, RAYWHITE);
		}
		DrawText("ESC ile cik", SCREEN_WIDTH / 2 - 58, SCREEN_HEIGHT / 2 + 46, 18, (Color){ 210, 220, 230, 255 });
	}

	EndDrawing();
}

int main(void) {
	position_t snake[MAX_SNAKE_LENGTH];
	position_t food;
	direction_t current_direction;
	int snake_length;
	int score;
	int game_over;
	int game_won;
	int i;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Yilan Oyunu");
	SetTargetFPS(TARGET_FPS);
	srand((unsigned int)time(NULL));

	snake_length = START_SNAKE_LENGTH;
	score = 0;
	game_over = 0;
	game_won = 0;
	current_direction = direction_right;

	for (i = 0; i < snake_length; ++i) {
		snake[i].x = 5 - i;
		snake[i].y = 5;
	}

	food = create_food(snake, snake_length);

	while (!WindowShouldClose()) {
		if (!game_over) {
			position_t next_head;
			int will_grow;

			if (IsKeyPressed(KEY_ESCAPE)) {
				break;
			}

			current_direction = update_direction(current_direction);

			next_head = snake[0];

			if (current_direction == direction_up) {
				--next_head.y;
			} else if (current_direction == direction_down) {
				++next_head.y;
			} else if (current_direction == direction_left) {
				--next_head.x;
			} else if (current_direction == direction_right) {
				++next_head.x;
			}

			will_grow = (next_head.x == food.x && next_head.y == food.y);

			if (check_wall_collision(next_head.x, next_head.y) || check_self_collision(snake, snake_length, next_head.x, next_head.y, will_grow)) {
				game_over = 1;
			} else {
				if (will_grow) {
					if (snake_length < MAX_SNAKE_LENGTH) {
						++snake_length;
					} else {
						game_over = 1;
						game_won = 1;
					}
				}

				for (i = snake_length - 1; i > 0; --i) {
					snake[i] = snake[i - 1];
				}

				snake[0] = next_head;

				if (will_grow) {
					if (!game_won) {
						++score;
						food = create_food(snake, snake_length);
					}
				}
			}
		} else if (IsKeyPressed(KEY_R)) {
			/* Oyun bitince R ile yeniden başlatmak yeni başlayanlar için rahat bir kullanım sağlar. */
			snake_length = START_SNAKE_LENGTH;
			score = 0;
			game_over = 0;
			game_won = 0;
			current_direction = direction_right;

			for (i = 0; i < snake_length; ++i) {
				snake[i].x = 5 - i;
				snake[i].y = 5;
			}

			food = create_food(snake, snake_length);
		}

		draw_game(snake, snake_length, food, score, game_over, game_won);
	}

	CloseWindow();
	return 0;
}