//https://github.com/ir-rafio/iut-algorithms-lab-1a-summer-23-24/blob/main/Lab%206/Lab%20Handout.pdf

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

class DSU
{
    vector<ll> parent, rank;

public:
    DSU(ll n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 1);
        for (ll i = 1; i <= n; i++)
            parent[i] = i;
    }
    ll findParent(ll i)
    {
        return (parent[i] == i) ? i : (parent[i] = findParent(parent[i]));
    }
    void unite(ll x, ll y)
    {
        ll s1 = findParent(x), s2 = findParent(y);
        if (s1 != s2)
        {
            if (rank[s1] < rank[s2])
                parent[s1] = s2;
            else if (rank[s1] > rank[s2])
                parent[s2] = s1;
            else
                parent[s2] = s1, rank[s1]++;
        }
    }
};

bool comparator(vector<ll> &a, vector<ll> &b)
{
    return a[2] < b[2];
}

ll kruskalsMST(ll V, vector<vector<ll>> &edges)
{
    sort(edges.begin(), edges.end(), comparator);

    DSU dsu(V);
    ll cost = 0, count = 0;
    for (auto &e : edges)
    {
        ll u = e[0], v = e[1], w = e[2];
        if (dsu.findParent(u) != dsu.findParent(v))
        {
            dsu.unite(u, v);
            cost += w;
            if (++count == V - 1)
                break;
        }
    }
    if (count != V - 1)
    {
        return -1;
    }

    return cost;
}

int main()
{
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> edges;
    for (ll i = 1; i <= m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    ll res = kruskalsMST(n, edges);
    if (res != -1)
        cout << res << endl;
    else
        cout << "IMPOSSIBLE" << endl;
        
    return 0;
}
