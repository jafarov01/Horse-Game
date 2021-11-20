/* 
*   Copyright (C) 2021-05 Makhlug Jafarov
*
    
    //github.com/jafarov01
    //https://www.linkedin.com/in/jafarov01/
*/

#define _CRT_SECURE_NO_WARNINGS
#include "std_lib_facilities.h"

string next(string player) {
	return player == "p1" ? "p2" : "p1";
}

void display_board(int playArea[8][8], int size, int h1_posI, int h1_posJ, int h2_posI, int h2_posJ) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	cout << endl << "\t\t\tPLAY AREA" << endl;
	for (int i = 0; i < size * 2 + 3; i++)
	{
		if (i == 0)
			cout << char(201);
		else if (i == size * 2 + 2)
			cout << char(187);
		else
			cout << char(205);
	}

	cout << endl << char(186) << "x" << char(186);
	for (int i = 0; i < size; i++)
		cout << i << char(186);

	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << char(186) << i;
		for (int j = 0; j < size; j++)
		{
			cout << char(186);
			if (h1_posI == i && h1_posJ == j)
				cout << "W";
			else if (h2_posI == i && h2_posJ == j)
				cout << "B";
			else if (playArea[i][j] == 0)
				cout << char(176);
			else if (playArea[i][j] == 2)
				cout << '#';
			else if (playArea[i][j] == 5)
				cout << " ";
		}
		cout << char(186) << endl;
	}
	for (int i = 0; i < size * 2 + 3; i++)
	{
		if (i == 0)
			cout << char(200);
		else if (i == size * 2 + 2)
			cout << char(188);
		else
			cout << char(205);
	}
	cout << endl << endl;
}

void play(int playArea[8][8], int size, int h1_posI, int h1_posJ, int h2_posI, int h2_posJ, string player);

void mark(int playArea[8][8], int size, int x, int y);

vector<pair<int, int>> possibleMovements(int playArea[8][8], int size, int x, int y, string player);

void movement(int playArea[8][8], int size, int& x, int& y, char& key);

void remove(int playArea[8][8]);

bool isWon(int count, string player);

void hlpl();

void menu();

int main()
{
	/*necessary variables, arrays and etc*/
	int playArea[8][8] = { 0 }; // playArea array
	int size = 8; // size of row and column
	int h1_posI = 0; //the positions of horses
	int h1_posJ = 0;
	int h2_posI = 7;
	int h2_posJ = 7;
	menu();

	char key = _getch();

	switch (key)
	{
	case '1':
	{
		string player = "p1";
		system("cls");
		play(playArea, size, h1_posI, h1_posJ, h2_posI, h2_posJ, player);

		break;
	}
	case '2':
	{
		system("cls");
		cout << "RULES:";
		break;
	}
	case '3':
	{
		exit(0);
	}
	default:
		break;
	}

	return 0;
}

void play(int playArea[8][8], int size, int h1_posI, int h1_posJ, int h2_posI, int h2_posJ, string player) {
	char key = ' ';

	mark(playArea, size, h1_posI, h1_posJ);
	mark(playArea, size, h2_posI, h2_posJ);

	while (true) {
		vector<pair<int, int>> possibleMoves;
		bool move_placed = false;
		bool won = false;

		if (player == "p1")
			possibleMoves = possibleMovements(playArea, size, h1_posI, h1_posJ, player);
		else
			possibleMoves = possibleMovements(playArea, size, h2_posI, h2_posJ, player);

		display_board(playArea, size, h1_posI, h1_posJ, h2_posI, h2_posJ);

		won = isWon(possibleMoves.size(), player);

		if (won)
			break;

		while (move_placed == false) {
			key = _getch();

			if (player == "p1")
				movement(playArea, size, h1_posI, h1_posJ, key);
			else
				movement(playArea, size, h2_posI, h2_posJ, key);

			for (pair<int, int> temp : possibleMoves) {
				if (temp.first == h1_posI && temp.second == h1_posJ) {
					mark(playArea, size, h1_posI, h1_posJ);
					move_placed = true;
				}
				else if (temp.first == h2_posI && temp.second == h2_posJ) {
					mark(playArea, size, h2_posI, h2_posJ);
					move_placed = true;
				}
			}
			display_board(playArea, size, h1_posI, h1_posJ, h2_posI, h2_posJ);
		}

		remove(playArea);

		player = next(player);
	}
}

void mark(int playArea[8][8], int size, int x, int y) {
	playArea[x][y] = 5;
}

vector<pair<int, int>> possibleMovements(int playArea[8][8], int size, int x, int y, string player) {

	vector<pair<int, int>> possible_moves;
	if ((x - 2 >= 0) && (y - 1) >= 0 && playArea[x - 2][y - 1] == 0) {
		playArea[x - 2][y - 1] = 2;
		possible_moves.push_back(make_pair(x - 2, y - 1));
	}

	if ((x - 2 >= 0) && (y + 1) <= size && playArea[x - 2][y + 1] == 0) {
		playArea[x - 2][y + 1] = 2;
		possible_moves.push_back(make_pair(x - 2, y + 1));
	}

	if ((x + 2 <= size) && (y + 1) <= size && playArea[x + 2][y + 1] == 0) {
		playArea[x + 2][y + 1] = 2;
		possible_moves.push_back(make_pair(x + 2, y + 1));
	}

	if ((x + 2 <= size) && (y - 1) >= 0 && playArea[x + 2][y - 1] == 0) {
		playArea[x + 2][y - 1] = 2;
		possible_moves.push_back(make_pair(x + 2, y - 1));
	}

	if ((x - 1 >= 0) && (y + 2) <= size && playArea[x - 1][y + 2] == 0) {
		playArea[x - 1][y + 2] = 2;
		possible_moves.push_back(make_pair(x - 1, y + 2));
	}

	if ((x + 1 <= size) && (y + 2) <= size && playArea[x + 1][y + 2] == 0) {
		playArea[x + 1][y + 2] = 2;
		possible_moves.push_back(make_pair(x + 1, y + 2));
	}

	if ((x - 1 >= 0) && (y - 2) >= 0 && playArea[x - 1][y - 2] == 0) {
		playArea[x - 1][y - 2] = 2;
		possible_moves.push_back(make_pair(x - 1, y - 2));
	}

	if ((x + 1 <= size) && (y - 2) >= 0 && playArea[x + 1][y - 2] == 0) {
		playArea[x + 1][y - 2] = 2;
		possible_moves.push_back(make_pair(x + 1, y - 2));
	}

	return possible_moves;
}

void movement(int playArea[8][8], int size, int& x, int& y, char& key) {
	if (key == 'w' && x > 0)
		x--;
	else if (key == 's' && x < size - 1)
		x++;
	else if (key == 'a' && y > 0)
		y--;
	else if (key == 'd' && y < size - 1)
		y++;
}

void remove(int playArea[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (playArea[i][j] == 2)
				playArea[i][j] = 0;
		}
	}
}

bool isWon(int count, string player) {
	if (count == 0) {
		if (player == "p2")
			cout << "HORSE B LOST THE GAME!\n";
		else
			cout << "HORSE W LOST THE GAME!\n";

		return true;
	}
	return false;
}

void hlpl()
{
	cout << "             __    __   __      .______    __          __   \n";
	cout << "            |  |  |  | |  |     |   _  \\  |  |        /_ | \n";
	cout << "            |  |__|  | |  |     |  |_)  | |  |         | | \n";
	cout << "            |   __   | |  |     |   ___/  |  |         | | \n";
	cout << "            |  |  |  | |  `----.|  |      |  `----.    | | \n";
	cout << "            |__|  |__| |_______|| _|      |_______|    |_| \n";
}

void menu()
{
	hlpl();
	cout << "\n\n\t\t\t1 - Start Game\n\n";
	cout << "\t\t\t2 - Rules\n\n";
	cout << "\t\t\t3 - Quit\n\n";
}
