#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int ll;

class DSU
{
    vector<int> parent, size;

public:
    DSU(int n)
    {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    int find(int i)
    {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    }

    ll unite(int x, int y)
    {
        int rootX = find(x), rootY = find(y);
        if (rootX == rootY)
            return 0;
        ll pairs_formed = 1LL * size[rootX] * size[rootY];

        if (size[rootX] < size[rootY])
            swap(rootX, rootY);
        parent[rootY] = rootX;
        size[rootX] += size[rootY];

        return pairs_formed;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<vector<int>> edges;
    for (int i = 0; i < n - 1; i++) // 0-based
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<vector<int>> queries;
    for (int i = 0; i < q; i++) // 0-based
    {
        int qu;
        cin >> qu;
        queries.push_back({qu, i});
    }

    sort(edges.begin(), edges.end(), [](const vector<int> &a, const vector<int> &b)
         { return a[2] < b[2]; });
    sort(queries.begin(), queries.end(), [](const vector<int> &a, const vector<int> &b)
         { return a[0] < b[0]; });

    DSU dsu(n);
    int edge_ptr = 0;
    ll result = 0;
    vector<ll> answers(q);

    for (int i = 0; i < q; i++)
    {
        int query_value = queries[i][0];
        int query_index = queries[i][1];

        while (edge_ptr < edges.size() && edges[edge_ptr][2] <= query_value)
        {
            int u = edges[edge_ptr][0];
            int v = edges[edge_ptr][1];
            result += dsu.unite(u, v);
            edge_ptr++;
        }

        answers[query_index] = result;
    }

    for (int i = 0; i < q; i++) // 0-based
    {
        cout << answers[i] << " ";
    }
    cout << endl;

    return 0;
}
