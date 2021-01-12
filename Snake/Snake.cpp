
#include <iostream>
#include <conio.h>
using namespace std;

bool gameOver;;			//переменная окончания игры
const int width = 20;	//ширина поля
const int height = 10;		//высота поля
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;	//количество элементов хвоста
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
void Setup()			//настройка игры
{
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw()				//отрисовка карты
{
	system("cls");		//очищение терминала
	for (int i = 0; i < width + 1; i++)	//граница поля верхняя
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)	//боковые границы поля
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				cout << "#";

			if (i == fruitY && j == fruitX)
				cout << "f";
			else if (i == y && j == x)
				cout << "0";
			else {
				bool print = false;		//отрисовка хвоста
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
				}
				if (!print)
				cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)	//граница поля нижняя
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input()			//ввод пользователя
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic()			//логика игры
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)	//запись хвоста
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{

	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	if (x > width || x < 0 || y>height || y < 0)
		gameOver = true;
	if (x >= width-1)	//сквозь стенки
		x = 0;
	else if (x < 0)
		x = width - 2;
	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}
	if (x == fruitX && y == fruitY)	//поедание фруктов
	{
		score += 5;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
}