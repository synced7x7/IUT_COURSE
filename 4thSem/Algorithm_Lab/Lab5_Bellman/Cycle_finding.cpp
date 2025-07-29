//https://cses.fi/problemset/task/1197

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll INF = LLONG_MAX;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<ll>> edges;
    for (int i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<ll> dist(n + 1, 0);
    vector<ll> parent(n + 1, -1);
    int x = -1;

    // Run Bellman-Ford for n times
    for (int i = 1; i <= n; i++)
    {
        x = -1;
        for (auto edge : edges)
        {
            ll u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != INF && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                x = v;
            }
        }
    }

    if (x == -1)
    {
        cout << "NO\n";
    }
    else
    {
        // Reconstruct the cycle
        for (int i = 0; i < n; i++)
        {
            x = parent[x]; // move to a node definitely in the cycle
        }

        vector<int> cycle;
        int cur = x;
        do
        {
            cycle.push_back(cur);
            cur = parent[cur];
        } while (cur != x && cur != -1);

        cycle.push_back(x);
        reverse(cycle.begin(), cycle.end());

        cout << "YES\n";
        for (int node : cycle)
        {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
