#include <iostream>
#include "History.h"
using namespace std;

History::History(int nRows, int nCols) 
	:m_nRows(nRows), m_nCols(nCols)
{
	for (int i = 0; i < m_nRows; i++)
	{
		for (int j = 0; j < m_nCols; j++)
		{
			gameHistory[i][j] = 0;
		}
	}
}



bool History::record(int r, int c)
{
	if (r >= MAXROWS || c >= MAXCOLS || r < 1 || c < 1)
		return false;
	gameHistory[r-1][c-1]++;
		return true;
}



void History::display() const
{
	char displayGrid[MAXROWS][MAXCOLS];
	for (int y = 0; y < m_nRows; y++)
		for (int z = 0; z < m_nCols; z++)
			switch (gameHistory[y][z])
			{
			case 0:
				displayGrid[y][z] = '.';
				break;
			case 1:
				displayGrid[y][z] = 'A'; 
				break;
			case 2:
				displayGrid[y][z] = 'B';
				break;
			case 3:
				displayGrid[y][z] = 'C';
				break;
			case 4:
				displayGrid[y][z] = 'D'; 
				break;
			case 5:
				displayGrid[y][z] = 'E';
				break;
			case 6:
				displayGrid[y][z] = 'F'; 
				break;
			case 7:
				displayGrid[y][z] = 'G'; 
				break;
			case 8:
				displayGrid[y][z] = 'H'; 
				break;
			case 9:
				displayGrid[y][z] = 'I'; 
				break;
			case 10:
				displayGrid[y][z] = 'J'; 
				break;
			case 11:
				displayGrid[y][z] = 'K'; 
				break;
			case 12:
				displayGrid[y][z] = 'L'; 
				break;
			case 13:
				displayGrid[y][z] = 'M'; 
				break;
			case 14:
				displayGrid[y][z] = 'N'; 
				break;
			case 15:
				displayGrid[y][z] = 'O'; 
				break;
			case 16:
				displayGrid[y][z] = 'P';
				break;
			case 17:
				displayGrid[y][z] = 'Q'; 
				break;
			case 18:
				displayGrid[y][z] = 'R'; 
				break;
			case 19:
				displayGrid[y][z] = 'S';
				break;
			case 20:
				displayGrid[y][z] = 'T';
				break;
			case 21:
				displayGrid[y][z] = 'U';
				break;
			case 22:
				displayGrid[y][z] = 'V';
				break;
			case 23:
				displayGrid[y][z] = 'W';
				break;
			case 24:
				displayGrid[y][z] = 'X'; 
				break;
			case 25:
				displayGrid[y][z] = 'Y';
				break;
			default:
				displayGrid[y][z] = 'Z'; 
				break;
			}

	clearScreen();
	for (int p = 0; p < m_nRows; p++)
	{
		for (int b = 0; b < m_nCols; b++)
			cout << displayGrid[p][b];
		cout << endl;
	}
	cout << endl;
}
