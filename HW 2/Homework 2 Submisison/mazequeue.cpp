#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	queue<Coord> coordQueue;
	Coord begin(sr, sc);

	coordQueue.push(begin);
	maze[sr][sc] = 'w';

	
	if (coordQueue.empty())
	{
		return false;
	}
	
	while (!coordQueue.empty())
	{
		Coord current = coordQueue.front();
		coordQueue.pop();

		if (current.c() == ec && current.r() == er)
		{
			return true;
		}

		else
		{
			//EAST
			if (current.c() < nCols)
			{
				if (maze[current.r()][current.c() + 1] == '.')
				{
					Coord east(current.r(), current.c() + 1);
					coordQueue.push(east);
					maze[current.r()][current.c() + 1] = 'w';
				}
			}

			//SOUTH
			if (current.r() < nRows)
			{
				if (maze[current.r() + 1][current.c()] == '.')
				{
					Coord south(current.r() + 1, current.c());
					coordQueue.push(south);
					maze[current.r() + 1][current.c()] = 'w';
				}
			}

			//WEST
			if (current.c() > 0)
			{
				if (maze[current.r()][current.c() - 1] == '.')
				{
					Coord west(current.r(), current.c() - 1);
					coordQueue.push(west);
					maze[current.r()][current.c() - 1] = 'w';
				}
			}

			//NORTH
			if (current.r() > 0)
			{
				if (maze[current.r() - 1][current.c()] == '.')
				{
					Coord north(current.r() - 1, current.c());
					coordQueue.push(north);
					maze[current.r() - 1][current.c()] = 'w';
				}
			}
		}
	}
	return false;
}

/*
int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X...X..X.X",
		"X.XXX....X",
		"X.X.XXXX.X",
		"XXX......X",
		"X...X.XX.X",
		"X.X.X..X.X",
		"X.XXXX.X.X",
		"X..X...X.X",
		"XXXXXXXXXX"


	};

	if (pathExists(maze, 10, 10, 4, 3, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}
*/