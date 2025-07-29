//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long int ll;

ll visitedCount = 0;

ll spanningTree(ll V, ll E, vector<vector<pair<ll, ll>>> &adj, ll s)
{
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    vector<bool> visited(V + 1, false);
    ll res = 0;
    pq.push({0, s});

    while (!pq.empty())
    {
        auto p = pq.top();
        pq.pop();

        ll wt = p.first; // Weight
        ll u = p.second; // Vertex connected to the edge

        if (visited[u] == true)
        {
            continue;
        }

        res += wt;
        visited[u] = true;
        visitedCount++;

        for (auto v : adj[u])
        {
            ll x = v.first, w = v.second;
            if (visited[x] == false)
            {
                pq.push({w, x});
            }
        }
    }

    return res;
}

int main()
{
    ll n, m;
    cin >> n >> m;
    ll u, v, w;

    vector<vector<pair<ll, ll>>> adj(n + 1);
    for (int i = 1; i <= m; i++)
    {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    ll r = spanningTree(n, m, adj, 1);
    if (visitedCount < n)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
        cout << r << endl;

    return 0;
}