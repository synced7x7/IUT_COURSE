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

vector<ll> dfs(vector<vector<ll>> &adjList, ll Vertex, ll source, vector<bool> &visited)
{

    vector<ll> result;
    dfsRec(adjList, result, source, visited);
    return result;
}

int main()
{
    ll V, r, u, v;
    cin >> V >> r;
    vector<vector<ll>> adjList(V + 1);
    vector<bool> visited(V + 1, false);
    vector<ll> res;
    vector<ll> finalRes;
    int count = 0;
    for (ll i = 0; i < r; i++)
    {
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    for (int i = 1; i <= V; i++)
    {
        if (!visited[i])
        {
            int startingRoad;
            if (count != 0)
            {
                startingRoad = i;
                //cout << "Starting Road = " << startingRoad << endl;
                finalRes.push_back(startingRoad);
            }
            res = dfs(adjList, V, i, visited);
            count++;
            finalRes.push_back(res.back());
            /* for (auto &x : finalRes)
            {
                cout << "x = " << x << " ";
            } */

            res.clear();
        }
    }
    cout << --count << endl;
    int director = 0;
    for (int i=0; i<count ; i++)
    {
        cout << finalRes[director]  << " " << finalRes[director+1] ;
        cout << endl;
        director+=2;
    }

    return 0;
}
