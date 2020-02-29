/*You are at position [0, 0] in maze NxN and you can only move in one of the four cardinal directions (i.e. North, East, South, West). Return true if you can reach position [N-1, N-1] or false otherwise.

Empty positions are marked .. Walls are marked W. Start and exit positions are empty in all test cases.*/

#include <iostream>
#include <string>
#include <queue>

using namespace std;
struct position
{
	int x;
	int y;
	position()
	{}
	position(int x,int y):x(x),y(y)
	{}
};

bool safe_move(char** maze, int x, int y,int N)
{
	if (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == '.')
		return true;
	return false;
}
bool path_finder(std::string maze)
{
	int count = 0;
	int M_rows[] = { -1,1,0,0 };
	int M_cols[] = { 0,0,1,-1 };
	for (char& c : maze)
		if (c != '\n')
			count++;
		else
			break;
	const int N = count;
	char** maze_c = new char* [N];
	for (int i = 0; i < N; i++)
		maze_c[i] = new char[N];

	int i = 0, k = 0;
	for (int j = 0; j < maze.size(); j++)
	{
		if (maze[j] != '\n')
		{
			maze_c[i][k] = maze[j];
			k++;
		}
		else
		{
			k = 0;
			i++;
		}
	}
	bool** visited = new bool* [N];
	for (int i = 0; i < N; i++)
		visited[i] = new bool[N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			visited[i][j] = false;
	position starting_point(0, 0);
	position finish_point(N - 1, N - 1);
	queue<position> moves;
	position go;
	moves.push(starting_point);
	int row = 0, col = 0;
	while (!moves.empty())
	{
		go = moves.front();
		moves.pop();
		cout << go.x << "," << go.y << endl;
		if (go.x == (N - 1) && go.y == (N - 1))
			return true;

		for (int i = 0; i < 4; i++)
		{
			row = go.x + M_rows[i];
			col = go.y + M_cols[i];
			if (safe_move(maze_c, row, col, N) && (!visited[row][col]))
			{
				visited[row][col] = true;
				moves.push(position(row, col));
			}
		}
	}
	return false;
}
