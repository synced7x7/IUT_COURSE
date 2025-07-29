//https://codeforces.com/problemset/problem/449/B

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
 
typedef long long int ll;
 
vector<vector<vector<int>>> constructAdj(vector<vector<int>> &roads, vector<vector<int>> &trains, int V)
{
    vector<vector<vector<int>>> adj(V + 1); // 1-based indexing
 
    for (auto &e : roads)
    {
        int u = e[0], v = e[1], w = e[2];
        adj[u].push_back({v, w, 0});
        adj[v].push_back({u, w, 0}); // 0 indicates road
    }
 
    for (auto &e : trains)
    {
        int v = e[0], w = e[1];
        adj[1].push_back({v, w, 1});
        adj[v].push_back({1, w, 1});
    }
 
    return adj;
}
 
int dijkstra(int V, vector<vector<vector<int>>> &adj, vector<ll> &dist, vector<bool> &isTrain)
{
    priority_queue<vector<ll>, vector<vector<ll>>, greater<vector<ll>>> pq;
    dist[1] = 0;
    pq.push({0, 1});
 
    // int redundantTrains = 0;
 
    while (!pq.empty())
    {
        ll d = pq.top()[0];
        int u = pq.top()[1];
        pq.pop();
 
        if (d > dist[u])
            continue;
 
        for (auto &x : adj[u])
        {
            int v = x[0];
            int weight = x[1];
            int trainFlag = x[2];
 
            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                isTrain[v] = trainFlag;
                pq.push({dist[v], v});
            }
            else if (dist[u] + weight == dist[v])
            {
                if (trainFlag == 0 && isTrain[v])
                {
                    isTrain[v] = false;
                }
            }
        }
    }
 
    return 0;
}
 
int main()
{
    int n, m, k;
    cin >> n >> m >> k;
 
    vector<vector<int>> roads(m, vector<int>(3));
    vector<vector<int>> usedTrain(n + 1);
    for (int i = 0; i < m; ++i)
        cin >> roads[i][0] >> roads[i][1] >> roads[i][2];
 
    vector<vector<int>> trains(k, vector<int>(2));
    for (int i = 0; i < k; ++i)
        cin >> trains[i][0] >> trains[i][1]; // v and weight (from 1 to v)
 
    vector<vector<vector<int>>> adj = constructAdj(roads, trains, n);
 
    vector<ll> dist(n + 1, LLONG_MAX);
    vector<bool> isTrain(n + 1, false);
 
    dijkstra(n, adj, dist, isTrain);
 
    // Count how many train paths were unused
    int usedTrainCount = 0;
    for (int i = 0; i < k; ++i)
    {
        int v = trains[i][0];
        int w = trains[i][1];
        if (dist[v] == w && isTrain[v])
        {
            usedTrainCount++;
            isTrain[v] = false; // prevent counting multiple times
        }
    }
    cout << k - usedTrainCount << endl;
 
    return 0;
}
