#include<iostream>
#include<vector>
#include<conio.h>
#include<Windows.h>
#include"AStarAlgo.h"
#include<SFML/Graphics.hpp>

struct Pt2i {

public:
	int x, y;

public:
	Pt2i() {};

	Pt2i(const int x, const int y) :x(x), y(y) {};

};

struct Pt2f {

public:
	float x, y;

public:
	Pt2f() {};

	Pt2f(const float x, const float y) :x(x), y(y) {};

};

enum Label {
	WALL = 0,
	OCCUPIED_PATH = 1,
	EMPTY_PATH = 2,
};

short map_arr[31][27] = { 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
{0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
{0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 2, 2, 2, 2, 2, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 2, 2, 2, 2, 2, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
{0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0},
{0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
{0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0},
{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

Pt2f ghost_init_pos(13, 13);
Pt2f player_init_pos(1, 29);

class Object {
private:
	Pt2f pos;

public:
	
	 Object();
	~Object();

	void SetPos(const Pt2f pos);
	Pt2f GetPos();
};

Object::Object() {};
Object::~Object() {};

void Object::SetPos(const Pt2f pos) {
	
	this->pos = pos;

	return;
}

Pt2f Object::GetPos() {
	return pos;
}

class Player:public Object {
private:

public:

	 Player();
	~Player();
};

Player::Player() {};
Player::~Player() {};

class Ghost :public Object {
private:

public:

	 Ghost();
	~Ghost();
};

Ghost:: Ghost() {};
Ghost::~Ghost() {};


class PACMAN {

private:

	int scores;
	int map_width, map_height;
	int player_move_dir;

	Player player;
	std::vector<Ghost> ghost;

	std::vector<std::vector<int>> map;

private:

	sf::RenderWindow window;
	sf::RectangleShape wall_label, empty_path_label;
	sf::CircleShape ghost_label, player_label, fruit_label;

private:

	enum MoveDir {
		STOP = 0,
		LEFT,
		RIGHT,
		UP,
		DOWN
	}dir;

	Label label;

private:

	void UpdatePlayerPos(const int dir);
	void UpdateGhostPos();
	void Display();
	void Logic();
	void Input();
	void SfmlDisplay();
	void SfmlInput();

public:

	PACMAN(const int map_width, const int map_height, const int ghost_size);
	~PACMAN();

	void Run();

};

PACMAN::PACMAN(const int map_width, const int map_height, const int ghost_size) {

	this->map_height = map_height;
	this->map_width = map_width;
	
	ghost.resize(ghost_size);
	ghost[0].SetPos(ghost_init_pos);

	player.SetPos(player_init_pos);

	map.resize(map_height);
	for (int i = 0; i < map.size(); i++) {
		map[i].resize(map_width);
		for (int j = 0; j < map[i].size(); j++) {
			map[i][j] = map_arr[i][j];
		}
	}

	//sfml
	window.create(sf::VideoMode(270, 310), "PACMAN", sf::Style::Close | sf::Style::Resize);

	wall_label.setSize(sf::Vector2f(10.0f, 10.0f));
	wall_label.setFillColor(sf::Color::Blue);

	ghost_label.setRadius(5);
	ghost_label.setFillColor(sf::Color::Red);

	player_label.setRadius(5);
	player_label.setFillColor(sf::Color::Yellow);

	fruit_label.setRadius(2.f);
	fruit_label.setFillColor(sf::Color::White);

	empty_path_label.setSize(sf::Vector2f(10.0f, 10.0f));
	empty_path_label.setFillColor(sf::Color::Black);

}

PACMAN::~PACMAN() {};

void PACMAN::Display() {

	system("cls");

	Pt2f ghost_pos = ghost[0].GetPos();
	Pt2f player_pos = player.GetPos();

	for (int i = 0; i < map_height; i++) {
		std::cout << i << '\t';
		for (int j = 0; j < map_width; j++) {
			if (map[i][j] == WALL)
				std::cout << "#";
			else if (ghost_pos.x == j && ghost_pos.y == i)
				std::cout << "o";
			else if (player_pos.x == j && player_pos.y == i)
				std::cout << "@";
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}

	Sleep(50);

	return;
}

void PACMAN::SfmlDisplay() {

	window.clear();

	Pt2f ghost_pos = ghost[0].GetPos();
	Pt2f player_pos = player.GetPos();

	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			if (map[i][j] == WALL) {
				wall_label.setPosition(sf::Vector2f(j*10.0f, i*10.0f));
				window.draw(wall_label);
			}
			else if (map[i][j] == OCCUPIED_PATH) {
				fruit_label.setPosition(sf::Vector2f(j*10.f + 5.f, i*10.f + 5.f));
				fruit_label.setOrigin(sf::Vector2f(2.f, 2.f));
				window.draw(fruit_label);
			}
			else if (map[i][j] == EMPTY_PATH) {
				empty_path_label.setPosition(sf::Vector2f(j*10.0f, i*10.0f));
				window.draw(empty_path_label);
			}
		}
	}


	player_label.setPosition(sf::Vector2f(player_pos.x*10.0f, player_pos.y*10.0f));
	window.draw(player_label);
	ghost_label.setPosition(sf::Vector2f(ghost_pos.x*10.0f, ghost_pos.y*10.0f));
	window.draw(ghost_label);

	window.display();

}

void PACMAN::Input() {

	player_move_dir = STOP;

	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			player_move_dir = UP;
			break;
		case 'a':
			player_move_dir = LEFT;
			break;
		case 's':
			player_move_dir = DOWN;
			break;
		case 'd':
			player_move_dir = RIGHT;
			break;
		default:
			break;
		}
	}
	
	return;
}

void PACMAN::SfmlInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		player_move_dir = LEFT;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		player_move_dir = RIGHT;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		player_move_dir = UP;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		player_move_dir = DOWN;
	else
		player_move_dir = STOP;

	return;
}

void PACMAN::UpdatePlayerPos(const int dir) {

	Pt2f new_pos = player.GetPos();

	if (dir == LEFT)
		new_pos.x--;
	else if (dir == RIGHT)
		new_pos.x++;
	else if (dir == UP)
		new_pos.y--;
	else if (dir == DOWN)
		new_pos.y++;

	if (map[std::floor(new_pos.y)][std::floor(new_pos.x)] == WALL)
		return;

	player.SetPos(new_pos);

	return;
}

void PACMAN::UpdateGhostPos() {

	AStarSearch a_star(map_height, map_width);

	Pt2f player_pos = player.GetPos();
	Pt2f old_ghost_pos = ghost[0].GetPos();

	std::list<std::pair<int, int>> shortest_path = a_star.Search(map, 
																 std::pair<int, int>(old_ghost_pos.x, old_ghost_pos.y),
																 std::pair<int, int>(player_pos.x, player_pos.y));

	std::list<std::pair<int, int>>::iterator itr = shortest_path.begin();
	if (shortest_path.size() > 1)
		++itr;

	float delta_x = itr->first - old_ghost_pos.x;
	float delta_y = itr->second - old_ghost_pos.y;

	//ghost[0].SetPos(Pt2f(old_ghost_pos.x + delta_x*0.8, old_ghost_pos.y + delta_y*0.8));
	ghost[0].SetPos(Pt2f(itr->first, itr->second));

	return;
}

void PACMAN::Logic() {
	
	UpdatePlayerPos(player_move_dir);

	UpdateGhostPos();

	return;
}

void PACMAN::Run() {

	while(window.isOpen()){

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		SfmlDisplay();
		SfmlInput();
		Logic();
	}

	return;
}

int main() {

	PACMAN pac_man(27, 31, 1);
	pac_man.Run();
	std::getchar(); std::getchar();
	return 0;
}
