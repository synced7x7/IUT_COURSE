//https://judge.yosupo.jp/problem/shortest_path

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

int destination_distance;
vector<int> shortestPath(vector<vector<vector<int>>> &adjList, int n, int s, int d)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	vector<int> dist(n, INT_MAX);
	vector<int> parent(n, -1);
	dist[s] = 0;
	pq.push({0, s});
	while (!pq.empty())
	{
		int currDist = pq.top().first;
		int u = pq.top().second;
		pq.pop();

		if (currDist > dist[u])
			continue;

		for (auto &x : adjList[u])
		{
			int v = x[0];
			int weight = x[1];
			int newDist = dist[u] + weight;

			if (newDist < dist[v])
			{
				dist[v] = newDist;
				parent[v] = u;
				pq.push({dist[v], v});
			}
		}
	}

	destination_distance = dist[d];
	if (destination_distance == INT_MAX)
	{
		return {};
	}
	return parent;
}

int main()
{
	int n, e, s, d, u, v, w;
	cin >> n >> e >> s >> d;
	vector<vector<vector<int>>> adjList(n);
	for (int i = 0; i < e; i++)
	{
		cin >> u >> v >> w;
		adjList[u].push_back({v, w});
	}

	vector<int> parent = shortestPath(adjList, n, s, d);
	if (parent.empty())
	{
		cout << -1 << endl;
		return 0;
	}
	cout << destination_distance << " ";
	// cout << "Shortest distance from " << s << " to " << d << " = " << destination_distance << endl;
	vector<pair<int, int>> pathEdges;
	for (int curr = d; parent[curr] != -1; curr = parent[curr])
	{
		pathEdges.emplace_back(parent[curr], curr);
	}
	cout << pathEdges.size() << endl;

	for (auto it = pathEdges.rbegin(); it != pathEdges.rend(); ++it)
	{
		cout << it->first << " " << it->second << endl;
	}

	return 0;
}
