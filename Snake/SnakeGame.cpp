#include "SnakeGame.h"

#include<ctime>
#include<conio.h>
#include<Windows.h>

#include<iostream>

SnakeGame::SnakeGame(const int display_width, const int display_height) {

	this->display_width = display_width;
	this->display_height = display_height;

	snake_move_dir = last_snake_move_dir = 0;

	snake_pos.resize(1);
	snake_pos[0].x = this->display_width / 2;
	snake_pos[0].y = this->display_height / 2;

	UpdateGameMap();

	ResetFruitPos();

	scores = 0;
}

void SnakeGame::Run() {
	Input();
	Display();
}

void SnakeGame::Display() {

	system("cls");
	for (int i = 0, k = 0; i < display_height; i++) {
		for (int j = 0; j < display_width; j++) {

			bool is_draw_snake = false;
			for (int k = 0; k < snake_pos.size(); k++) {
				if (i == snake_pos[k].y && j == snake_pos[k].x) {
					std::cout << "@";
					is_draw_snake = true;
					break;
				}
			}

			if (is_draw_snake)
				continue;

			if (i == fruit_pos.y && j == fruit_pos.x) {
				std::cout << "m";
				continue;
			}
			if (i == 0 || i == display_height - 1)
				std::cout << "#";
			else {
				if (j == 0 || j == display_width - 1)
					std::cout << "#";
				else
					std::cout << " ";
			}

		}
		std::cout << std::endl;
	}

	std::cout << "scores: " << this->scores << std::endl;

	if (is_game_over)
		std::cout << "game over!" << std::endl;

	Sleep(50);
}

void SnakeGame::Input() {

	if (is_game_over)
		return;

	last_snake_move_dir = snake_move_dir;

	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			snake_move_dir = UP;
			break;
		case 'a':
			snake_move_dir = LEFT;
			break;
		case 's':
			snake_move_dir = DOWN;
			break;
		case 'd':
			snake_move_dir = RIGHT;
			break;
		default:
			break;
		}
	}

	UpdateSnakePos();

	Logic();

	return;
}

void SnakeGame::Logic() {

	UpdateGameMap();

	if (snake_pos[0].x == fruit_pos.x && snake_pos[0].y == fruit_pos.y) {
		is_ate_fruit = true;
		scores += 10;
		ResetFruitPos();
	}

	is_game_over = (CheckBoundaryCollision() || CheckBodyCollision()) ? true : false;
}

void SnakeGame::ResetFruitPos() {
	std::srand(time(NULL));
	bool is_okay = true;

	int num_of_unoccupied_grid = 0;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] == 1) continue;
			if (i == 0 || i == display_height - 1) continue;
			if (j == 0 || j == display_width - 1) continue;
			num_of_unoccupied_grid++;
		}
	}

	std::vector<std::pair<int, int>> unoccupied_grid_idx(num_of_unoccupied_grid);

	for (int i = 0, k = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] == 1) continue;
			if (i == 0 || i == display_height - 1) continue;
			if (j == 0 || j == display_width - 1) continue;
			unoccupied_grid_idx[k++] = std::pair<int, int>(i, j);
		}
	}


	int rand_idx = rand() % num_of_unoccupied_grid;
	fruit_pos.y = unoccupied_grid_idx[rand_idx].first;
	fruit_pos.x = unoccupied_grid_idx[rand_idx].second;

}

void SnakeGame::UpdateSnakePos() {

	if (snake_move_dir == STOP)
		return;

	Pt2i new_snake_pos = GetNewSnakeHeadPos(snake_move_dir);

	//avoid moving in opposite dwirection directly
	if (snake_pos.size() > 1.f && new_snake_pos.x == snake_pos[1].x && new_snake_pos.y == snake_pos[1].y) {
		new_snake_pos = GetNewSnakeHeadPos(last_snake_move_dir);
		snake_move_dir = last_snake_move_dir;
	}

	if (is_ate_fruit) {
		Pt2i temp;
		snake_pos.push_back(temp);
		is_ate_fruit = false;
	}

	for (int i = snake_pos.size() - 1; i >= 1; i--)
		snake_pos[i] = snake_pos[i - 1];
	snake_pos[0] = new_snake_pos;

	return;
}

Pt2i SnakeGame::GetNewSnakeHeadPos(const int dir) {

	Pt2i new_pos = snake_pos[0];

	if (dir == LEFT)
		new_pos.x--;
	else if (dir == RIGHT)
		new_pos.x++;
	else if (dir == UP)
		new_pos.y--;
	else if (dir == DOWN)
		new_pos.y++;
	else
		return new_pos;

	new_pos.x = (new_pos.x < 0) ? 0 : new_pos.x;
	new_pos.y = (new_pos.y < 0) ? 0 : new_pos.y;
	new_pos.x = (new_pos.x > display_width - 1) ? display_width - 1 : new_pos.x;
	new_pos.y = (new_pos.y > display_height - 1) ? display_height - 1 : new_pos.y;

	return new_pos;
}

bool SnakeGame::CheckBoundaryCollision() {

	bool is_collision = false;

	is_collision = (snake_pos[0].x == display_width - 1 || snake_pos[0].x == 0 ||
		snake_pos[0].y == display_height - 1 || snake_pos[0].y == 0) ? true : false;

	return is_collision;
}

bool SnakeGame::CheckBodyCollision() {

	bool is_collision = false;
	Pt2i snake_head_pos = snake_pos[0];

	for (int i = 1; i < snake_pos.size(); i++) {
		if (snake_pos[i].x == snake_head_pos.x && snake_pos[i].y == snake_head_pos.y) {
			is_collision = true;
			break;
		}
	}

	return is_collision;
}

void SnakeGame::UpdateGameMap() {

	ResetMap();

	for (int i = 0; i < snake_pos.size(); i++)
		map[snake_pos[i].y][snake_pos[i].x] = 1;

}

void SnakeGame::ResetMap() {

	if (map.empty()) {
		map.resize(this->display_height);
		for (int i = 0; i < map.size(); i++)
			map[i].resize(this->display_width, 0);
	}
	else {
		for (int i = 0; i < map.size(); i++) {
			for (int j = 0; j < map[i].size(); j++) {
				map[i][j] = 0;
			}
		}
	}
}