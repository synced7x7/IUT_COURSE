#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

typedef long long int ll;

vector<vector<pair<ll, ll>>> minSpanAdjList;
ll maxWeight = 0;

ll spanningTree(ll V, ll E, vector<vector<pair<ll, ll>>> &adj, ll s)
{
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    vector<bool> visited(V + 1, false);
    vector<ll> key(V + 1, LLONG_MAX);
    vector<ll> parent(V + 1, -1);

    ll res = 0;

    key[s] = 0;
    pq.push({0, s});

    while (!pq.empty())
    {
        pair<ll, ll> p = pq.top();
        pq.pop();
        ll u = p.second;

        if (visited[u])
            continue;

        visited[u] = true;
        res += key[u];

        if (parent[u] != -1)
        {
            minSpanAdjList[u].push_back({parent[u], key[u]});
            minSpanAdjList[parent[u]].push_back({u, key[u]});
        }

        for (size_t i = 0; i < adj[u].size(); ++i)
        {
            ll x = adj[u][i].first;
            ll w = adj[u][i].second;

            if (!visited[x] && w < key[x])
            {
                key[x] = w;
                parent[x] = u;
                pq.push({key[x], x});
            }
        }
    }

    return res;
}

void uniqueTreePath(ll s, ll d, ll n)
{
    vector<ll> parent(n + 1, -1);
    vector<bool> visited(n + 1, false);
    queue<ll> q;
    q.push(s);
    visited[s] = true;

    while (!q.empty())
    {
        ll u = q.front();
        q.pop();

        for (ll i = 0; i < minSpanAdjList[u].size(); ++i)
        {
            ll v = minSpanAdjList[u][i].first;
            if (!visited[v])
            {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    // vector<ll> path;
    ll curr = d;
    maxWeight = 0;

    while (curr != -1)
    {
        // path.push_back(curr);
        if (curr == s)
            break;

        ll p = parent[curr];
        for (size_t i = 0; i < minSpanAdjList[curr].size(); ++i)
        {
            if (minSpanAdjList[curr][i].first == p)
            {
                ll w = minSpanAdjList[curr][i].second;
                if (w > maxWeight)
                    maxWeight = w;
                break;
            }
        }

        curr = p;
    }

    /* if (path.back() != s)
    {
        return vector<ll>();
    } */

    // reverse(path.begin(), path.end());

    // cout << "Maximum weight on the path: " << maxWeight << endl;

    // return path;
}

int main()
{
    ll n, m;
    cin >> n >> m;

    vector<vector<pair<ll, ll>>> adj(n + 1);
    minSpanAdjList.resize(n + 1);
    vector<vector<ll>> edges;
    for (ll i = 0; i < m; ++i)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        edges.push_back({u, v, w});
    }

    ll totalCost = spanningTree(n, m, adj, 1);
    // cout << "Minimum Spanning Cost = " << totalCost << endl;

    /* for (ll u = 1; u <= n; ++u)
    {
        cout << "Node " << u << ": ";
        for (size_t i = 0; i < minSpanAdjList[u].size(); ++i)
        {
            ll v = minSpanAdjList[u][i].first;
            ll w = minSpanAdjList[u][i].second;
            cout << "(" << v << ", weight=" << w << ") ";
        }
        cout << endl;
    } */

    for (ll i = 0; i < m; i++)
    {
        ll source = edges[i][0], dest = edges[i][1], w = edges[i][2];
        uniqueTreePath(source, dest, n);

        /* if (path.empty())
        {
            cout << "No path from " << source << " to " << dest << endl;
        }
        else
        {
            cout << "Path from " << source << " to " << dest << ": ";
            for (size_t i = 0; i < path.size(); ++i)
            {
                cout << path[i];
                if (i + 1 < path.size())
                    cout << " -> ";
            }
            cout << endl;
        } */
        cout << totalCost - maxWeight + w << endl;
    }

    return 0;
}
