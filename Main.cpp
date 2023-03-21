#include "Game.h"
#include <sys/timeb.h>

int mode;
int record;
sf::Mouse mouse;
sf::Vector2f vec(29, 29);
sf::Vector2i v(300, 300);
sf::Vector2i vec2(300, 300);
Game game;
time_t tw;

/*
bool isMine(int x, int y, bool index) {
	for (int i = 0; i < game.MINES; i++) {
		if ((game.Mine[i][0] == x) && (game.Mine[i][1] == y)) {
			 game.index = i; return true;
		}
	}
	return false;
}
bool isMine(int x, int y) {
	for (int i = 0; i < game.MINES; i++) {
		if ((game.Mine[i][0] == x) && (game.Mine[i][1] == y)) {
			return true;
		}
	}
	return false;
}*/

int findMine(int x, int y) {
	for (int i = 0; i < game.MINES; i++){
		if (game.Mine[i][0] == x && game.Mine[i][1] == y) return i;
	}
}

int findFlagSize() {
	for (int i = 0; i < game.MINES; i++) {
		if (game.Flag[i][1] == NULL) return i;
	}
}

bool isFlag(int x, int y) {
	for (int i = 0; i < game.MINES; i++) {
		if ((game.Flag[i][0] == x) && (game.Mine[i][1] == y)) {
			return true;
		}
	}
	return false;
}

void showMine() {
	game.show = true;
}

void lose() {
	game.lose = true;
	tw = time(NULL);
}
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa
int isWin() {
	int count = 0;
	for (int i = 0; i < game.WIDTH; i++)
	{
		for (int j = 0; j < game.HEIGHT; j++)
		{
			if (game.Grid[i][j] == "p") count++;
		}
	}
	//std::cout << count << std::endl;
	return count;
}

int isWinFlag() {
	int count = 0;
	for (int i = 0; i < game.WIDTH; i++)
	{
		for (int j = 0; j < game.HEIGHT; j++)
		{
			if (game.Grid[i][j] == "m") count++;
		}
	}
	//std::cout << count << std::endl;
	return count;
}

void setMine(int(mine)[40][2]){
	mine[0][0] = rand() % game.WIDTH; mine[0][1] = rand() % game.HEIGHT;
	game.Grid[mine[0][0]][mine[0][1]] = "m";
	for (int i = 1; i < game.MINES; i++) {
		int x, y;
		x = rand() % game.WIDTH; y = rand() % game.HEIGHT;
		if (x == mine[i - 1][0] && y == mine[i - 1][1]) {
			x = rand() % game.WIDTH; y = rand() % game.HEIGHT;
		}
		mine[i][0] = x;  mine[i][1] = y;
		game.Grid[mine[i][0]][mine[i][1]] = "m";
	}
}
/*
int getAroundMine(int x, int y) {
	int count = 0;
	if (x - 1 >= 0 && y - 1 >= 0) if (game.isMine(x - 1, y - 1)) count++;
	if (y - 1 >= 0) if (game.isMine(x , y - 1)) count++;
	if (x+1 < game.WIDTH && y - 1 >= 0) if (game.isMine(x + 1, y - 1)) count++;
	if (x-1 >= 0) if (game.isMine(x - 1, y)) count++;
	if (x + 1 < game.WIDTH) if (game.isMine(x + 1, y)) count++;
	if (x + 1 < game.WIDTH  && y + 1 < game.HEIGHT) if (game.isMine(x + 1, y + 1)) count++;
	if (y + 1 < game.HEIGHT) if (game.isMine(x, y + 1)) count++;
	if (y + 1 < game.HEIGHT && x - 1 >= 0) if (game.isMine(x - 1, y + 1)) count++;

	return count;
}
*/

void win() {
	game.win = true;
	tw = time(NULL);
}

/*
void openAround(int x, int y,Game game) {
	if (!game.isMine(x, y)) {
		if (game.getAroundMine(x, y) != 0) {
			game.Grid[x][y] = std::to_string(game.getAroundMine(x, y));
		}
		if (game.getAroundMine(x, y) == 0)
		{

			game.Grid[x][y] = "o";
			openSpace(x, y,game);
		}
	}
}
*/
/*
void openSpace(int x, int y) {
	if (x - 1 >= 0 && y - 1 >= 0) openAround(x - 1, y - 1);
	if (y - 1 >= 0) openAround(x, y - 1);
	if (x + 1 < game.WIDTH && y - 1 >= 0) openAround(x + 1, y - 1);
	if (x - 1 >= 0) openAround(x - 1, y);
	if (x + 1 < game.WIDTH) openAround(x + 1, y);
	if (x + 1 < game.WIDTH && y + 1 < game.HEIGHT) openAround(x + 1, y + 1);
	if (y + 1 < game.HEIGHT) openAround(x, y + 1);
	if (y + 1 < game.HEIGHT && x - 1 >= 0) openAround(x - 1, y + 1);
}
*/

time_t t;
time_t e;
int diff;


void startGame(){
	srand(time(NULL));
	for (int i = 0; i < game.WIDTH; i++)
	{
		for (int j = 0; j < game.HEIGHT; j++)
		{
			game.Grid[i][j] = "p";
		}
	}
	setMine(game.Mine);
	t = time(NULL);
	game.win = false; game.lose = false;


}

int main()
{

	std::cout << "Enter game difficulty from 1 to 2" << std::endl;
	std::cin >> mode;
	switch (mode)
	{
	case 1: game.WIDTH = 10; game.HEIGHT = 10; game.MINES = 10; break;
	case 2: game.WIDTH = 16, game.HEIGHT = 16; game.MINES = 40; break;
	case 3: game.WIDTH = 30; game.HEIGHT = 16; game.MINES = 99; break;
	default: std::cout << "Enter valid number from 1 to 2" << std::endl; break;
	}

	sf::RenderWindow window(sf::VideoMode(game.WIDTH * 30, (game.HEIGHT * 30) + 60), "Canep");
	
	window.setKeyRepeatEnabled(false);
	sf::Font font;
	font.loadFromFile("Ubuntu.ttf");
	sf::Text text;
	sf::Text timeT;
	timeT.setFont(font);
	sf::Text mineT;
	mineT.setFont(font);
	text.setFont(font);

	timeT.setCharacterSize(16);
	timeT.setPosition(50, (game.HEIGHT*30)+20);
	timeT.setStyle(sf::Text::Bold);

	mineT.setCharacterSize(16);
	mineT.setPosition((game.WIDTH * 30) - 40, (game.HEIGHT * 30) + 20);
	mineT.setStyle(sf::Text::Bold);

	text.setCharacterSize(14);
	text.setFillColor(sf::Color::Black);
	sf::RectangleShape square(vec);
	square.setFillColor(sf::Color::Blue);

	//srand(time(NULL));

	//setMine(game.Mine);
	/*
	for (int i = 0; i < game.MINES; i++)
	{
		std::cout << game.Mine[i][0] << " " << game.Mine[i][1] << std::endl;
	}*/
	//t = time(NULL);
	startGame();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				int x, y;
				sf::Vector2i ve(0, 0);
				ve = mouse.getPosition(window);
				if (((ve.x < game.WIDTH * 30) && (ve.x > 0)) && ((ve.y < game.HEIGHT * 30) && (ve.y > 0))) {
					v = mouse.getPosition(window);
				}
				y = v.x / 30; x = v.y / 30;
				if (game.Grid[x][y] != "f") {
					if (game.Grid[x][y] != "o" || game.Grid[x][y] != "m") {
						if (game.isMine(x, y)) { lose(); }
						if (!game.isMine(x, y)) {
							if (game.getAroundMine(x, y) != 0) {
								game.Grid[x][y] = std::to_string(game.getAroundMine(x, y));
							}
							if (game.getAroundMine(x, y) == 0)
							{

								game.Grid[x][y] = "o";
								game.openSpace(x, y);
							}
						}
					}
					for (int i = 0; i < game.WIDTH; i++)
					{
						for (int j = 0; j < game.HEIGHT; j++) {
							std::cout << game.Grid[i][j];

						}
						std::cout << std::endl;
					}
					std::cout << std::endl;
					std::cout << std::endl;
					if (isWin() == 0) win();
				}
			}
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
			{
				int x, y;
				sf::Vector2i ve(0, 0);
				vec2 = mouse.getPosition(window);
				if (((ve.x < game.WIDTH * 30) && (ve.x > 0)) && ((ve.y < game.HEIGHT * 30) && (ve.y > 0))) {
					vec2 = mouse.getPosition(window);
				}
				y = vec2.x / 30; x = vec2.y / 30;
				if (game.Grid[x][y] == "m" || game.Grid[x][y] == "p") {
					game.Flag[findFlagSize()][0] = x; game.Flag[findFlagSize()][1] = x;
					game.Grid[x][y] = "f";
					game.show = false;
				}
				//PROBLEMA Yje net
				else if (game.Grid[x][y] == "f") {
					if (game.isMine(x, y)) game.Grid[x][y] = "m";
					else game.Grid[x][y] = "p";
					game.Flag[findFlagSize()][0] = NULL; game.Flag[findFlagSize()][1] = NULL;
					game.show = false;
				}
				/*
				for (int i = 0; i < 10; i++)
				{
					std::cout << game.Mine[i][0] << " " << game.Mine[i][1] << std::endl;
				}*/
				if (isWinFlag() == 0) win();
			}
		}
			e = time(NULL);
			if (!game.win && !game.lose) diff = difftime(e, t);
			//std::cout << difftime(e,t) << std::endl;

			if (game.win || game.lose) if(difftime(time(NULL), tw) > 3) startGame();
			window.clear();
			game.drawGrid(square, &window, text);

			mineT.setString(std::to_string(isWinFlag()));

			timeT.setString(std::to_string(diff));
			window.draw(mineT);
			if (game.win) 
			{
			}
			if (game.lose) { 
			}
			window.draw(timeT);
			window.display();
	}

	return 0;
}
