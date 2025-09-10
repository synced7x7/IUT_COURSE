#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> topologicalSort(vector<vector<int>> &adj, int V)
{
    vector<int> indegree(V, 0);

    // Compute in-degree for each node
    for (int i = 0; i < V; i++)
    {
        for (auto it : adj[i])
        {
            indegree[it]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> result;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        result.push_back(node);

        for (auto it : adj[node])
        {
            indegree[it]--;
            if (indegree[it] == 0)
            {
                q.push(it);
            }
        }
    }

    // If we could not visit all vertices, there is a cycle
    if (result.size() != V)
    {
        cout << "[]" << endl;
        return {};
    }

    return result;
}

int main()
{
    int N, M;
    cin >> N >> M;

    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    vector<int> result = topologicalSort(adj, N);

    if (!result.empty())
    {
        for (auto i : result)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}