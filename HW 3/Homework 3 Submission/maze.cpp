//GOOOD


//#include <iostream>
//#include <string>
//using namespace std;

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

//check if there is a path from (sr, sc) to (er, ec) within the maze
bool pathExists(string maze[],int nRows, int nCols, int sr, int sc, int er, int ec)
{
	maze[sr][sc] = 'w';

	if (sr == er && sc == ec)   //started at the finishing location
	{
		return true;
	}

	else
	{
		//EAST
		if (maze[sr][sc + 1] == '.')
		{
			if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
			{
				return true;
			}
		}

		//SOUTH
		if (maze[sr + 1][sc] == '.')
		{
			if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
			{
				return true;
			}
		}

		//WEST
		if (maze[sr][sc - 1] == '.')
		{
			if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
			{
				return true;
			}
		}

		//NORTH
		if (maze[sr - 1][sc] == '.')
		{
			if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
			{
				return true;
			}
		}
	}
	
	return false;
}




//int main()
//{
//	string maze[10] = {
//		"XXXXXXXXXX",
//		"X...X..X.X",
//		"X.XXX....X",
//		"X.X.XXXX.X",
//		"XXX......X",
//		"X...X.XX.X",
//		"X.X.X..X.X",
//		"X.XXXX.X.X",
//		"X..X...X.X",
//		"XXXXXXXXXX"
//	};
//
//	if (pathExists(maze, 10, 10, 4, 3, 1, 8))
//		cout << "Solvable!" << endl;
//	else
//		cout << "Out of luck!" << endl;
//}