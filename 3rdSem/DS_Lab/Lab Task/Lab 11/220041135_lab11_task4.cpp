#include <vector>
#include <iostream>
using namespace std;

bool dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, int dest)
{
    if (node == dest)
        return true; 
    visited[node] = true;

    for (int neighbor : adj[node])
    {
        if (!visited[neighbor])
        {
            if (dfs(neighbor, adj, visited, dest))
                return true;
        }
    }
    return false;
}

int main()
{

    int nodes, edges, u, v, src, dest;
    cin >> nodes >> edges;

    vector<vector<int>> adj(nodes + 1);
    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v;
        adj[u].push_back(v);
    }
    cin >> src >> dest;
    vector<bool> visited(nodes + 1, false);

    if (dfs(src, adj, visited, dest))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    return 0;
}
