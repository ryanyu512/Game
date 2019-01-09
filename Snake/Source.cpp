#include<iostream>
#include<ctime>
#include<conio.h>

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

	Pt2i snake_pos, fruit_pos;

private:

	void ResetFruitPos();

public:

	SnakeGame(const int display_width, const int display_height);
	
	void Display();
	void Input();
	void Logic();
};

int main() {

	SnakeGame snake_game(20, 20);
	while(1){
		snake_game.Display();
		snake_game.Input();
	}
	std::getchar(); std::getchar();
	return 0;
}

SnakeGame::SnakeGame(const int display_width, const int display_height) {

	this->display_width = display_width;
	this->display_height = display_height;

	snake_pos.x = this->display_width / 2;
	snake_pos.y = this->display_height / 2;

	ResetFruitPos();

	scores = 0;
}

void SnakeGame::Display() {

	system("cls");
	for (int i = 0; i < display_height; i ++){
		for (int j = 0; j < display_width; j++) {

			if (i == snake_pos.y && j == snake_pos.x) {
				std::cout << "O"; continue;
			}
			if (i == fruit_pos.y && j == fruit_pos.x){
				std::cout << "m"; continue;
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

	std::cout << "scores: " << this->scores;

}

void SnakeGame::Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			snake_pos.y--;
			break;
		case 'a':
			snake_pos.x--;
			break;
		case 's':
			snake_pos.y++;
			break;
		case 'd':
			snake_pos.x++;
			break;
		default:
			break;
		}
	}

	snake_pos.x = (snake_pos.x < 0) ? 0 : snake_pos.x;
	snake_pos.y = (snake_pos.y < 0) ? 0 : snake_pos.y;
	snake_pos.x = (snake_pos.x > display_width - 1) ? display_width - 1 : snake_pos.x;
	snake_pos.y = (snake_pos.y > display_height - 1) ? display_height - 1 : snake_pos.y;

	Logic();
}

void SnakeGame::Logic() {

	if (snake_pos.x == fruit_pos.x && snake_pos.y == fruit_pos.y){
		scores += 10;
		ResetFruitPos();
	}
}

void SnakeGame::ResetFruitPos() {
	std::srand(time(NULL));
	fruit_pos.x = rand() % this->display_width;
	fruit_pos.y = rand() % this->display_height;
}