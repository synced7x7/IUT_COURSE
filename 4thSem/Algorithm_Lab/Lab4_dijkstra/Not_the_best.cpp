//https://lightoj.com/problem/not-the-best


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
		adjList[u].push_back({v,w});
		adjList[v].push_back({u,w});
	}
}

int secondShortestDijkstra(vector<vector<vector<int>>> &adjList, int n, int s)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	vector<int> dist(n+1 , INT_MAX);
	vector<int> secondDist(n+1 , INT_MAX);
	
	dist[s] = 0;
	pq.push({0, s});

	while(!pq.empty())
	{
		int u = pq.top().second;
		int currentDistance = pq.top().first;
		pq.pop();

		for (auto &x : adjList[u])
		{
			int v = x[0];
			int weight = x[1];
			int newDist = currentDistance + weight;
			if(newDist < dist[v])
			{
				secondDist[v] = dist[v];
				dist[v] = newDist;
				pq.push({dist[v], v}); 
			}
			else if (newDist > dist[v] && newDist < secondDist[v])
			{
				secondDist[v] = newDist;
				pq.push({secondDist[v], v});
			}
		}
	}
	return secondDist[n];

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
		for (int i = 1; i <= r; i++)
		{
			cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
		}
		constructAdjacency(adjList, r , edges);
		int secondDist  = secondShortestDijkstra(adjList, n , 1);
		cout << "Case " << ++Case << ": " << secondDist << endl;
		edges.clear();
		adjList.clear();
	}

	

	return 0;
}
