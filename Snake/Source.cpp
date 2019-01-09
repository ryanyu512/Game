#include<iostream>
#include<ctime>
#include<conio.h>
#include<vector>
#include <Windows.h>

struct Pt2i{
	int x, y;
};

class SnakeGame {
private:

	enum MoveDir {
		STOP = 0,
		LEFT,
		RIGHT,
		UP,
		DOWN
	}dir;

private:

	bool is_game_over;

	int display_width, display_height;
	
	int scores;

	int snake_move_dir, last_snake_move_dir;

	std::vector<Pt2i> snake_pos;

	Pt2i fruit_pos;

private:

	void ResetFruitPos();
	void UpdateSnakePos();
	Pt2i GetNewSnakeHeadPos(const int dir);
public:

	SnakeGame(const int display_width, const int display_height);
	
	void Display();
	void Input();
	void Logic();
};

int main() {

	SnakeGame snake_game(20, 20);
	while(1){
		snake_game.Input();
		snake_game.Display();
	}
	std::getchar(); std::getchar();
	return 0;
}

SnakeGame::SnakeGame(const int display_width, const int display_height) {

	this->display_width = display_width;
	this->display_height = display_height;
	
	snake_move_dir = last_snake_move_dir = 0;

	snake_pos.resize(5);
	snake_pos[0].x = this->display_width / 2;
	snake_pos[0].y = this->display_height / 2;
	for (int i = 1; i < snake_pos.size(); i++) {
		snake_pos[i].x = snake_pos[i - 1].x + 1;
		snake_pos[i].y = snake_pos[i - 1].y;
	}

	ResetFruitPos();

	scores = 0;
}

void SnakeGame::Display() {

	system("cls");
	for (int i = 0, k = 0; i < display_height; i ++){
		for (int j = 0; j < display_width; j++) {

			if (k < snake_pos.size() && i == snake_pos[k].y && j == snake_pos[k].x) {
				std::cout << "@";
				k++;
				continue;
			}
			if (i == fruit_pos.y && j == fruit_pos.x){
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

	//if (is_game_over)
	//	return;

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

	if (snake_pos[0].x == fruit_pos.x && snake_pos[0].y == fruit_pos.y){
		scores += 10;
		ResetFruitPos();
	}

	is_game_over = (snake_pos[0].x == display_width || snake_pos[0].x < 0 ||
					snake_pos[0].y == display_height || snake_pos[0].y < 0) ? true : false;
}

void SnakeGame::ResetFruitPos() {
	std::srand(time(NULL));
	fruit_pos.x = rand() % this->display_width;
	fruit_pos.y = rand() % this->display_height;
}

void SnakeGame::UpdateSnakePos() {

	if (snake_move_dir == STOP)
		return;

	Pt2i new_snake_pos = GetNewSnakeHeadPos(snake_move_dir);

	//avoid moving in opposite direction directly
	if (new_snake_pos.x == snake_pos[1].x && new_snake_pos.y == snake_pos[1].y) {
		new_snake_pos = GetNewSnakeHeadPos(last_snake_move_dir);
		snake_move_dir = last_snake_move_dir;
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

	new_pos.x = (new_pos.x < 0) ? -1 : new_pos.x;
	new_pos.y = (new_pos.y < 0) ? -1 : new_pos.y;
	new_pos.x = (new_pos.x > display_width) ? display_width : new_pos.x;
	new_pos.y = (new_pos.y > display_height) ? display_height : new_pos.y;

	return new_pos;
}