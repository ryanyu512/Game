#include<iostream>
#include "SnakeGame.h"

int main() {

	SnakeGame snake_game(20, 20);
	while(1){
		snake_game.Run();
	}
	std::getchar(); std::getchar();
	return 0;
}

