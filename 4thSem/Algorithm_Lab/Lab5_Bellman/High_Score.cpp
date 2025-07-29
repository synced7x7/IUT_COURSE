//https://cses.fi/problemset/task/1673

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

typedef long long int ll;
const ll INF = LLONG_MIN;

vector<vector<int>> adj;    // Graph: u -> v
vector<vector<int>> revAdj; // Reverse Graph: v -> u (for checking reachability from src)

vector<bool> visitedFromSrc;
vector<bool> visitedToDest;

void dfsFromSrc(int u)
{
    visitedFromSrc[u] = true;
    for (int v : adj[u])
    {
        if (!visitedFromSrc[v])
            dfsFromSrc(v);
    }
}

void dfsToDest(int u)
{
    visitedToDest[u] = true;
    for (int v : revAdj[u])
    {
        if (!visitedToDest[v])
            dfsToDest(v);
    }
}

void bellmanFord(ll V, vector<vector<ll>> &edges, ll src, ll dest)
{
    vector<ll> dist(V + 1, INF);
    dist[src] = 0;

    vector<int> inPositiveCycle;

    for (ll i = 1; i <= V; i++)
    {
        for (auto &edge : edges)
        {
            ll u = edge[0], v = edge[1], wt = edge[2];
            if (dist[u] != INF && dist[u] + wt > dist[v])
            {
                dist[v] = dist[u] + wt;
                if (i == V)
                {
                    inPositiveCycle.push_back(u);
                }
            }
        }
    }

    visitedFromSrc.assign(V + 1, false);
    visitedToDest.assign(V + 1, false);
    dfsFromSrc(src); // Mark all nodes reachable from source
    dfsToDest(dest); // Mark all nodes that can reach dest (reverse graph)

    /* A cycle only affects the final answer if:
    It is reachable from the source, AND
    You can reach the destination from it. */

    for (int u : inPositiveCycle)
    {
        if (visitedFromSrc[u] && visitedToDest[u])
        {
            cout << -1 << endl;
            return;
        }
    }

    cout << dist[dest] << endl;
}

int main()
{
    ll V, E;
    cin >> V >> E;

    vector<vector<ll>> edges;
    adj.assign(V + 1, {});
    revAdj.assign(V + 1, {});

    for (ll i = 0; i < E; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        adj[u].push_back(v);
        revAdj[v].push_back(u); // For reverse DFS
    }

    bellmanFord(V, edges, 1, V);

    return 0;
}
