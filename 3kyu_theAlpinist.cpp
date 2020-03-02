#include <iostream>
#include <string>
#include <vector>
#include <queue>
const int NUM = 15000;
int Vertices;
struct position
{
	int vertex;
	int weight;
	position(){}
	position(int vertex, int weight) :vertex{ vertex }, weight{ weight }
	{}
	bool operator<(const position& pos) const
	{
		return weight > pos.weight;
	}
};

int dijkstra(std::vector<position> edge[NUM], int src)
{
	std::priority_queue<position> Move;
	std::vector<int> distance(Vertices, -1);
	distance[src] = 0;
	position go;
	go.vertex = src;
	go.weight = distance[src];
	Move.push(go);
	while(!Move.empty())
	{
		go = Move.top();
		Move.pop();
		int u = go.vertex;
		if (u == Vertices - 1)
			return distance[u];
		for (int i = 0; i < edge[u].size(); i++)
		{
			int vertex = edge[u][i].vertex;
			int weight = edge[u][i].weight;
			if (distance[vertex] == -1 || distance[u] + weight < distance[vertex])
			{
				distance[vertex] = distance[u] + weight;
				go.weight = distance[vertex];
				go.vertex = vertex;
				Move.push(go);
			}
		}
	}
	return distance[Vertices - 1];
}

int path_finder(std::string maze)
{
	int M_x[] = { -1,1,0,0 };
	int M_y[] = { 0,0,1,-1 };
	int count = 0;
	for (char& c : maze)
		if (c != '\n')
			count++;
		else
			break;
	Vertices = count*count;
	std::cout << Vertices << std::endl;
	std::vector<position> edge[NUM];
	for (int i = 0; i < Vertices; i++) edge[i].clear();
	for (int x = 0; x < count; x++)
	{
		for (int y = 0; y < count; y++)
		{
			for (int i = 0; i < 4; i++)
			{
				int nx = x + M_x[i];
				int ny = y + M_y[i];
				if (nx>=0 && nx<count && ny>=0 && ny<count )
				{
					position temporary;
					temporary.vertex = nx * count + ny;
					temporary.weight = std::abs((maze[nx*(count+1)+ny] - '0') - (maze[x*(count+1)+y] - '0'));
					edge[x * count + y].push_back(temporary);
				}
			}
		}
	}
	int src = 0;
	return dijkstra(edge, src);
}
