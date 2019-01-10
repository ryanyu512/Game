#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include<vector>

struct Pt2i {
	Pt2i() {
		x = y = 0;
	}

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

	bool is_game_over, is_ate_fruit;

	int display_width, display_height;

	int scores;

	int snake_move_dir, last_snake_move_dir;

	std::vector<Pt2i> snake_pos;

	std::vector<std::vector<short>> map;

	Pt2i fruit_pos;

private:

	void Input();

	void Logic();

	void Display();

	void ResetFruitPos();

	void UpdateSnakePos();

	Pt2i GetNewSnakeHeadPos(const int dir);

	bool CheckBodyCollision();

	bool CheckBoundaryCollision();

	void UpdateGameMap();

	void ResetMap();

public:

	SnakeGame(const int display_width, const int display_height);

	void Run();
};

#endif
