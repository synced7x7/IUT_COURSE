#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int Case;

void constructAdjacency(vector<vector<vector<int>>> &adjList, int r, vector<vector<int>> &edges)
{
	for (int i = 1; i <= r; i++)
	{
		int u = edges[i][0];
		int v = edges[i][1];
		int w = edges[i][2];
		adjList[u].push_back({v, w});
		adjList[v].push_back({u, w});
	}
}

vector<int> Dijkstra(vector<vector<vector<int>>> &adjList, int n, int s, vector<int> &bicycle)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	int totalCost = 0;
	vector<int> dist(n + 1, INT_MAX);
	int cycleCost = INT_MAX;
	dist[s] = 0;
	pq.push({0, s});

	while (!pq.empty())
	{
		bool cycleChanged = false;
		//cout << endl;
		int u = pq.top().second;
		if (cycleCost > bicycle[u])
		{
			cycleCost = bicycle[u];
			//cout << "Cycle Changed!!!" << endl;
			//cout << "Current Motorcycle Cost : " << cycleCost << endl;
			cycleChanged = true;
		}

		int currentDistance = pq.top().first;
		pq.pop();
		//cout << "Current Vertex: " << u << ", Current Distance: " << currentDistance << ", Dist[u] = " << dist[u] << endl;

		for (auto &x : adjList[u])
		{
			int v = x[0];
			int weight = x[1];
			int newDist = currentDistance + cycleCost * weight;
			//cout << "Adjacent Vertex: " << v << ", Weight: " << weight << ", newDist: " << newDist << endl;
			if (newDist < dist[v])
			{
				dist[v] = newDist;
				pq.push({dist[v], v});
			}
			else if (cycleChanged && v!=n)
			{
				dist[v] = newDist;
				pq.push({dist[v], v});
			}
			//else
				//cout << "Vertex " << v << " not inserted into the queue" << endl;
		}
	}
	return dist;
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, r;
		cin >> n >> r;
		vector<vector<int>> edges(r + 1, vector<int>(3));
		vector<vector<vector<int>>> adjList(n + 1);
		vector<int> bicycle(n + 1);
		for (int i = 1; i <= r; i++)
		{
			cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
		}
		for (int i = 1; i <= n; i++)
		{
			cin >> bicycle[i];
		}
		constructAdjacency(adjList, r, edges);
		vector<int> dist = Dijkstra(adjList, n, 1, bicycle);
		/* for (int i = 1; i <= n; i++)
		{
			cout << dist[i] << ", ";
		}
		cout << endl; */
		cout << dist[n] << endl;
		edges.clear();
		adjList.clear();
	}

	return 0;
}