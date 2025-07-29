#include <iostream>
#include <vector>
using namespace std;

vector<int> bellmanFord(int V, vector<vector<int>> &edges, int src)
{
    vector<int> dist(V + 1, 1e8);
    dist[src] = 0;

    for (int i = 1; i <= V; i++)
    {
        for (vector<int> edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            if (dist[u] != 1e8 && dist[u] + wt < dist[v])
            {
                if (i == V)
                    return {-1}; // Negative cycle detected
                dist[v] = dist[u] + wt;
            }
        }
    }

    return dist;
}

int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<int>> edges;

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    int src = 1;

    vector<int> dist = bellmanFord(V, edges, src);

    if (dist.size() == 1 && dist[0] == -1)
        cout << "Negative weight cycle detected";
    else
    {
        for (int i = 1; i <= V; i++)
        {
            //cout << "Distance from " << src << " to " << i << " = ";
            if (dist[i] == 1e8)
                cout << 30000 << " ";
            else
                cout << dist[i] << " ";
        }
    }

    return 0;
}
