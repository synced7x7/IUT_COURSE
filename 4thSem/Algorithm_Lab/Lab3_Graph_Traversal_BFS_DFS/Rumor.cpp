//https://codeforces.com/problemset/problem/893/C

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef long long int ll;

ll dfsMinCost(vector<vector<ll>> &adjList, vector<ll> &money, vector<bool> &visited, ll source)
{
    visited[source] = true;
    ll minCost = money[source];

    for (auto &neighbor : adjList[source])
    {
        if (!visited[neighbor])
        {
            minCost = min(minCost, dfsMinCost(adjList, money, visited, neighbor));
        }
    }
    return minCost;
}

int main()
{
    ll V, r, u, v;
    cin >> V >> r;
    vector<ll> money(V + 1);
    vector<ll> res;
    for (ll i = 1; i <= V; i++)
    {
        cin >> money[i];
    }
    vector<vector<ll>> adjList(V + 1);
    vector<bool> visited(V + 1, false);

    for (ll i = 0; i < r; i++)
    {
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    ll totalCost = 0;
    for (ll i = 1; i <= V; i++)
    {
        if (!visited[i])
        {
            totalCost += dfsMinCost(adjList, money, visited, i);
            /* for (auto it : res)
            {
                cout << it << ", ";
            }
            cout << endl; */
            // res.clear();
        }
    }

    cout << totalCost   <<  endl;

    return 0;
}
