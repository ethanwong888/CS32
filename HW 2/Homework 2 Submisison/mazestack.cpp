#include <iostream>
#include <stack>
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
	stack<Coord> coordStack;

	Coord begin(sr, sc);

	//Push the starting coordinate(sr, sc) onto the coordinate stack and
	//update maze[sr][sc] to indicate that the algorithm has encountered it

	coordStack.push(begin);
	maze[sr][sc] = 'w';

	while (!coordStack.empty())
	{
		//Pop the top coordinate off the stack. This gives you the current
		//(r, c) location that your algorithm is exploring.

		Coord current = coordStack.top();
		coordStack.pop();

		//If the current(r, c) coordinate is equal to the ending coordinate,
		//then we've solved the maze so return true! 

		if (current.c() == ec && current.r() == er)
		{
			return true;
		}


		else
		{
			//If you can move EAST and haven't encountered that cell yet,
			//then push the coordinate(r, c + 1) onto the stack and update
			//maze[r][c + 1] to indicate the algorithm has encountered it.
			if (current.c() < nCols)
			{
				if (maze[current.r()][current.c() + 1] == '.')
				{
					Coord east(current.r(), current.c() + 1);
					coordStack.push(east);
					maze[current.r()][current.c() + 1] = 'w';
				}
			}

			//If you can move SOUTH and haven't encountered that cell yet,
			//then push the coordinate(r + 1, c) onto the stack and update
			//maze[r + 1][c] to indicate the algorithm has encountered it.
			if (current.r() < nRows)
			{
				if (maze[current.r() + 1][current.c()] == '.')
				{
					Coord south(current.r() + 1, current.c());
					coordStack.push(south);
					maze[current.r() + 1][current.c()] = 'w';
				}
			}
			
			//If you can move WEST and haven't encountered that cell yet,
			//then push the coordinate(r, c - 1) onto the stack and update
			//maze[r][c - 1] to indicate the algorithm has encountered it.
			if (current.c() > 0)
			{
				if (maze[current.r()][current.c() - 1] == '.')
				{
					Coord west(current.r(), current.c() - 1);
					coordStack.push(west);
					maze[current.r()][current.c() - 1] = 'w';
				}
			}

			//If you can move NORTH and haven't encountered that cell yet,
			//then push the coordinate(r - 1, c) onto the stack and update
			//maze[r - 1][c] to indicate the algorithm has encountered it.
			if (current.r() > 0)
			{
				if (maze[current.r() - 1][current.c()] == '.')
				{
					Coord north(current.r() - 1, current.c());
					coordStack.push(north);
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