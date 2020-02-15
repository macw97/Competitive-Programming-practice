/*
Task
You are at position [0, 0] in maze NxN and you can only move in one of the four cardinal directions (i.e. North, East, South, West).
Return the minimal number of steps to exit position [N-1, N-1] if it is possible to reach the exit from the starting position.
Otherwise, return false in JavaScript/Python and -1 in C++/C#/Java.
Empty positions are marked '.'. Walls are marked W. Start and exit positions are guaranteed to be empty in all test cases.

*/

//=======================================================================================
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
struct position
{
	int x;
	int y;
	int distance;
	position()
	{}
	position(int x, int y, int distance) :x(x), y(y), distance(distance)
	{}
};
bool Valid_move(int row, int col, int N)
{
	if (row >= 0 && row <= N && col >= 0 && col <= N)
		return true;
	return false;
}
int path_finder(string Maze)
{
	int rows = 1;
	for (int i = 0; i < Maze.length(); i++)
	{
		if (Maze[i] == '\n')
		{
			rows++;
		}
	}
	const int N = rows;
	char** maze_c = new char* [N];
	for (int i = 0; i < rows; i++)
	{
		maze_c[i] = new char[N];
	}
	// converting string Maze to char[][]
	int i = 0;
	int k = 0;
	for (int j = 0; j < Maze.size(); j++)
	{
		if (Maze[j] != '\n')
		{
			maze_c[i][k] = Maze[j];
			k++;
		}
		if(Maze[j]=='\n')
		{
			k = 0;
			i++;
		}
	}
	position starting_point(0, 0, 0);
	position finish_point(rows - 1, rows - 1, 0);
	int M_rows[] = { -1,1,0,0 };
	int M_cols[] = { 0,0,1,-1 };
	//bool[][] for checking if coordinate was already visited
	bool** visited = new bool* [N];
	for (int i = 0; i < N; i++)
	{
		visited[i] = new bool[N];
	}
	//initializing all coordinates not visited and changing starting point as visited
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			visited[i][j] = false;

	visited[0][0] = true;
	queue<position> moves;
	position go;
	int row = 0, col = 0;
	moves.push(starting_point);
	
	while (!moves.empty())
	{
		go = moves.front();
		moves.pop();
		cout << go.y << "," << go.x << "," << go.distance << endl;
		if (go.x == (N - 1) && go.y == (N - 1))
		{
			return go.distance;
		}
		
		for (int i = 0; i < 4; i++)
		{
			row = go.y + M_rows[i];
			col = go.x + M_cols[i];
			//Checking if this move is valid,never visited and is a free space
			if (Valid_move(row, col, N - 1) && (!visited[row][col])&& (maze_c[row][col]=='.'))
			{
				visited[row][col] = true;
				moves.push(position(col, row, go.distance + 1));
			}
		}

	}
	return -1;
}
