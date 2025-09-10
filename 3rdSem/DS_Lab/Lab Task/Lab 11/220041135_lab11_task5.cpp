#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

vector<string> topologicalSort(int V, unordered_map<string, vector<string>> adj, unordered_map<string, int> indegree)
{
    queue<string> q;
    vector<string> order;

    for (auto &pair : indegree)
    {
        if (pair.second == 0)
            q.push(pair.first);
    }

    while (!q.empty())
    {
        string node = q.front();
        q.pop();
        order.push_back(node);

        for (string neighbour : adj[node])
        {
            if (--indegree[neighbour] == 0)
            {
                q.push(neighbour);
            }
        }
    }

    if (order.size() == V)
    {
        return order;
    }
    else
    {
        return vector<string>{};
    }
}

int main()
{
    int st, cg, q;
    unordered_map<string, vector<string>> adj;
    unordered_map<string, int> indegree;

    string u, v;
    cin >> st >> cg >> q;
    vector<string> students(st);

    for (int i = 0; i < st; i++)
    {
        cin >> students[i];
        indegree[students[i]] = 0;
    }

    for (int i = 0; i < cg; i++)
    {
        cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
    }

    vector<string> sortedOrder = topologicalSort(st, adj, indegree);
    if (sortedOrder.empty())
    {
        cout << "IMPOSSIBLE" << endl; 
        return 0;
    }

    for (string s : sortedOrder)
    {
        cout << s << " ";
    }
    cout << endl;

    unordered_map<string, int> position;
    for (int i = 0; i < st; i++) 
    {
        position[sortedOrder[i]] = i;
    }

    for (int i = 0; i < q; i++)
    {
        string str1, str2;
        cin >> str1 >> str2;
        if (position[str1] < position[str2]) 
        {
            cout << "NO" << endl;
        }
        else
        {
            cout << "YES" << endl;
        }
    }
}
