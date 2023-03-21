#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <ctime>
#include <stdlib.h>
#include <string>
#include "Open.h"

class Game {
public:
	int WIDTH = 16;
	int HEIGHT = 16;
	int MINES = 40;

	std::string Grid[31][31];
	int (Mine)[100][2];
	int (Flag)[186][2];
	bool show = false;
	int flags = 0;
	int index = 0;
	bool win = false;
	bool lose = false;
	
	sf::Vector2f spawnMine() {
		int x = rand() % MINES-1 + 1;
		int y = rand() % MINES-1 + 1;
		return sf::Vector2f();
	}
	void drawGrid(sf::RectangleShape square, sf::RenderWindow* window, sf::Text text) {
		if (!win ^ !lose) {}else{
			for (int i = 0; i < WIDTH; i++)
			{
				for (int j = 0; j < HEIGHT; j++)
				{
					bool fl = false;
					if (Grid[i][j] == "p") square.setFillColor(sf::Color::Blue);
					if (Grid[i][j] == "o") square.setFillColor(sf::Color::White);
					if (Grid[i][j] == "1") { square.setFillColor(sf::Color::Cyan); text.setString("1"); fl = true; }
					if (Grid[i][j] == "2") { square.setFillColor(sf::Color::Magenta); text.setString("2"); fl = true; }
					if (Grid[i][j] == "3") { square.setFillColor(sf::Color::Yellow); text.setString("3"); fl = true; }
					if (Grid[i][j] == "4") { square.setFillColor(sf::Color(-28, -127, 67, 100)); text.setString("4"); fl = true; }
					if (Grid[i][j] == "f") square.setFillColor(sf::Color::Green);
					if (show) {
						if (Grid[i][j] == "m") square.setFillColor(sf::Color::Red);
						/*
						for (int h = 0; h < 10; h++) {
							if (!Mine[h][2]) { if (Mine[h][0] == i && Mine[h][1] == j) square.setFillColor(sf::Color::Red); }//else square.setFillColor(sf::Color::Green);
						}*/
					}
					else {
						if (Grid[i][j] == "m") square.setFillColor(sf::Color::Blue);
					}
					square.setPosition(j * 30.f, i * 30.f);
					text.setPosition(j * 30.f, i * 30.f);
					window->draw(square);
					if (fl) window->draw(text);
				}
			}
		}
	}

	void openSpace(int x, int y) {
		if (x - 1 >= 0 && y - 1 >= 0) this->openAround(x - 1, y - 1);
		if (y - 1 >= 0) this->openAround(x, y - 1);
		if (x + 1 < this->WIDTH && y - 1 >= 0) this->openAround(x + 1, y - 1);
		if (x - 1 >= 0) this->openAround(x - 1, y);
		if (x + 1 < this->WIDTH) this->openAround(x + 1, y);
		if (x + 1 < this->WIDTH && y + 1 < this->HEIGHT) this->openAround(x + 1, y + 1);
		if (y + 1 < this->HEIGHT) this->openAround(x, y + 1);
		if (y + 1 < this->HEIGHT && x - 1 >= 0) this->openAround(x - 1, y + 1);
	}

	int getAroundMine(int x, int y) {
		int count = 0;
		if (x - 1 >= 0 && y - 1 >= 0) if ( isMine(x - 1, y - 1)) count++;
		if (y - 1 >= 0) if ( isMine(x, y - 1)) count++;
		if (x + 1 <  WIDTH && y - 1 >= 0) if ( isMine(x + 1, y - 1)) count++;
		if (x - 1 >= 0) if ( isMine(x - 1, y)) count++;
		if (x + 1 <  WIDTH) if ( isMine(x + 1, y)) count++;
		if (x + 1 <  WIDTH  && y + 1 <  HEIGHT) if ( isMine(x + 1, y + 1)) count++;
		if (y + 1 <  HEIGHT) if ( isMine(x, y + 1)) count++;
		if (y + 1 <  HEIGHT && x - 1 >= 0) if ( isMine(x - 1, y + 1)) count++;

		return count;
	}

	void openAround(int x, int y) {
		if (!this->isMine(x, y)) {
			if (this->getAroundMine(x, y) != 0) {
				this->Grid[x][y] = std::to_string(this->getAroundMine(x, y));
			}
			if (this->getAroundMine(x, y) == 0)
			{

				this->Grid[x][y] = "o";
			}
		}
	}


	bool isMine(int x, int y, bool index) {
		for (int i = 0; i <  MINES; i++) {
			if (( Mine[i][0] == x) && ( Mine[i][1] == y)) {
				 index = i; return true;
			}
		}
		return false;
	}
	bool isMine(int x, int y) {
		for (int i = 0; i <  MINES; i++) {
			if (( Mine[i][0] == x) && ( Mine[i][1] == y)) {
				return true;
			}
		}
		return false;
	}

};
