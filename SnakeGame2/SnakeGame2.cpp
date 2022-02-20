#include <iostream>
#include <conio.h>

using namespace std;

enum Direction 
{ Stop=0,Left,Rigth,Up,Down};

Direction SnakeDirection;
const int Width = 20;
const int Heigth = 20;

int FruitX, FruitY, X, Y ,Score= 0;
int ChildX[100], ChildY[100];
int nChild;

bool GameOver;

char Wall;

void SetUp()
{
	GameOver = false;
	Wall = '#';

	X = Width / 2;
	Y = Heigth / 2;

	FruitX = rand() % Width;
	FruitY = rand() % Heigth;

	Score = 0;
}
void Draw() 
{
	system("cls");

	for (int i = 0; i < Width; i++)
		cout << Wall;
	cout << endl;

	for(int y = 0; y < Heigth ; y++)
	{
		for(int x = 0;x < Width ; x++)
		{
			if (x == 0)
				cout << Wall;
			else if (x == X && y == Y)
				cout << 'O';
			else if (x == FruitX && y == FruitY)
				cout << 'F';	
			else if (x == Width-1)
				cout << Wall;
			else
			{
				bool appear = false;
				for(int i = 0;i< nChild;i++)
				{
					if(ChildX[i] == x && ChildY[i] == y)
					{
						cout << 'o';
						appear = true;
					}
					
				}
				if(!appear)
					cout << ' ';

			}
		}
		cout << endl;

	}
	for (int i = 0; i < Width; i++)
		cout << Wall;
	cout << endl;
	
}
void Input() 
{
	if(_kbhit())
	{
		switch (_getch())
		{
			case 'a':
				SnakeDirection = Left;
				break;
			case 'd':
				SnakeDirection = Rigth;
				break;
			case 'w':
				SnakeDirection = Up;
				break;
			case 's':
				SnakeDirection = Down;
				break;
			case 'x':
				GameOver = true;
				break;
		}
	}
}
void Logic() 
{
	for (int i = nChild; i > 0; i--)
	{
		ChildX[i] = ChildX[i - 1];
		ChildY[i] = ChildY[i - 1];
	}

	ChildX[0] = X;
	ChildY[0] = Y;

	switch (SnakeDirection)
	{
		case Left:
			X--;
			break;
		case Rigth:
			X++;
			break;
		case Up:
			Y--;
			break;
		case Down:
			Y++;
			break;
		default:
			break;
	}

	if (X > Width || X < 0 || Y > Heigth || Y < 0)
		GameOver = true;

	if(X == FruitX && Y == FruitY)
	{
		FruitX = rand() % Width;
		FruitY = rand() % Heigth;
		nChild++;
		Score += 10;
	}

	for(int i = 0 ; i < nChild ; i++)
	{
		if (X == ChildX[i] && Y == ChildY[i])
			GameOver = true;
	}

	cout << "Score : " << Score;


}
void Junction() 
{
	Draw();
	Input();
	Logic();
}

int main()
{
	SetUp();
	while (!GameOver)
	{
		Junction();
	}
	return 0;
}