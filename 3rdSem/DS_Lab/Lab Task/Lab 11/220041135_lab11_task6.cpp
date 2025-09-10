#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

bool isBipartite(int v, vector<vector<int>> adj)
{
    vector<int> color(v, -1);
    for (int start = 0; start < v; start++)
    {
        if (color[start] == -1) 
        {
            queue<int> q;
            q.push(start);
            color[start] = 0;

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                for (int neighbour : adj[node]) 
                {
                    if (color[neighbour] == -1)
                    {
                        color[neighbour] = 1 - color[node]; 
                        q.push(neighbour);
                    }
                    else if (color[neighbour] == color[node])
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

int main()
{
    int v, neigh;
    cin >> v;
    vector<vector<int>> adj(v);
    int edges;
    for (int vertices = 0; vertices < v; vertices++)
    {
        cin >> edges;
        for (int i = 0; i < edges; i++)
        {
            cin >> neigh;
            adj[vertices].push_back(neigh);
        }
    }

    if (isBipartite(v, adj))
    {
        cout << "YES" << endl;
    }
    else
        cout << "NO" << endl;

    return 0;
}
