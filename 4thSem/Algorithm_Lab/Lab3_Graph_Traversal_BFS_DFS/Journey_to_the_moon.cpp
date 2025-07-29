//https://github.com/ir-rafio/iut-algorithms-lab-1a-summer-23-24/blob/main/Lab%203/Lab%20Handout.pdf

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef long long int ll;

void dfsRec(vector<vector<ll>> &adjList, vector<ll> &res, ll source, vector<bool> &visited)
{
    visited[source] = true;
    res.push_back(source);

    for (auto &x : adjList[source])
    {
        if (!visited[x])
            dfsRec(adjList, res, x, visited);
    }
}

vector<ll> dfs(vector<vector<ll>> adjList, ll Vertex, ll source, vector<bool> &visited)
{

    vector<ll> result;
    dfsRec(adjList, result, source, visited);
    return result;
}

int main()
{
    ll V, r, u, v;
    cin >> V >> r;
    vector<vector<ll>> adjList(V);
    vector<bool> visited(V, false);
    vector<ll> res;
    vector<ll> gs;
    for (ll i = 0; i < r; i++)
    {
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            res = dfs(adjList, V, i, visited);
            gs.push_back(res.size());
        }
    }

    ll totalPairs = (ll)V * (V - 1) / 2;
    ll sameCountryPairs = 0;
    for (int size : gs) {
        sameCountryPairs += (ll)size * (size - 1) / 2;
    }

    ll result = totalPairs - sameCountryPairs;
    cout << result << endl;


    return 0;
}
