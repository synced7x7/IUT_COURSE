//https://codeforces.com/problemset/problem/20/C

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;
typedef long long int ll;


vector<ll> shortestPath(vector<vector<vector<ll>>> &adjList, ll n, ll s, ll d, vector<ll> &dist)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	
	vector<ll> parent(n+1 , -1);
	dist[s] = 0;
	pq.push({0, s});
	while (!pq.empty())
	{
		ll currDist = pq.top().first;
		ll u = pq.top().second;
		pq.pop();

		if (currDist > dist[u])
			continue;

		for (auto &x : adjList[u])
		{
			ll v = x[0];
			ll weight = x[1];
			ll newDist = dist[u] + weight;

			if (newDist < dist[v])
			{
				dist[v] = newDist;
				parent[v] = u;
				pq.push({dist[v], v});
			}
		}
	}

	return parent;
}

int main()
{
	ll n, e, u, v, w;
	cin >> n >> e;
	vector<vector<vector<ll>>> adjList(n+1);
	vector<ll> dist(n+1, LLONG_MAX);
	for (ll i = 0; i < e; i++)
	{
		cin >> u >> v >> w;
		adjList[u].push_back({v, w});
		adjList[v].push_back({u, w});
	}

	vector<ll> parent = shortestPath(adjList, n, 1, n, dist);
	if (parent[n] == -1)
	{
		cout << -1 << endl;
		return 0;
	}
	
	vector<ll> paths;
	for (ll curr = n; parent[curr] != -1; curr = parent[curr])
	{
		paths.push_back(curr);
	}
	cout << 1 << " ";
	reverse(paths.begin(), paths.end());
	for(auto &it : paths)
	{
		cout << it << " ";
	}

	return 0;
}
