//https://dmoj.ca/problem/dmpg15s4

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

vector<vector<int>> pos;
vector<int> range;

void buildAdjMatrix(vector<vector<int>> &adjMatrix, int V)
{
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			if (i == j)
				continue;

			int x1 = pos[i][0], y1 = pos[i][1]; //Vertex Pos (i indicates vertex in adjMatrix) similar to x=adj[u] then u = x.first 
			int x2 = pos[j][0], y2 = pos[j][1]; //Neighbour pos of vertex (j indicates neighbour in adjMatrix)

			int dist2 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2); // (x-h)^2 + (y-k)^2 = r^2
			if (dist2 <= range[i] * range[i])
				adjMatrix[i][j] = 1;
			else
				adjMatrix[i][j] = 0;
		}
	}
}

void printMatrix(const vector<vector<int>> &adjMatrix, int V)
{
	cout << "Adj Matrix:" << endl;
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			cout << adjMatrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool canReach(int start, int target, const vector<vector<int>> &adjMatrix, int V)
{
	vector<bool> visited(V, false);
	queue<int> q;
	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		if (u == target)
			return true;

		for (int v = 0; v < V; ++v)
		{
			if (adjMatrix[u][v] && !visited[v])
			{
				visited[v] = true;
				q.push(v);
			}
		}
	}

	return false;
}

int main()
{
	int V, q;
	cin >> V >> q;

	pos.resize(V);
	range.resize(V);
	vector<vector<int>> adjMatrix(V, vector<int>(V, 0));

	for (int i = 0; i < V; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;
		pos[i] = {x, y};
		range[i] = w;
	}

	buildAdjMatrix(adjMatrix, V);
	printMatrix(adjMatrix, V);
	while (q--)
	{
		int m, n;
		cin >> m >> n;
		m--;//0 based indexing
		n--;

		if (canReach(m, n, adjMatrix, V))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}
