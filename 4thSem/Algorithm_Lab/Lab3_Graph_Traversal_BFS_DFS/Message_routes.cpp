//https://cses.fi/problemset/task/1667

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<bool> visited(n + 1, false);
    vector<int> parent(n + 1, -1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    queue<int> q;
    q.push(1);
    visited[1] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int neighbor : adj[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }

    if (!visited[n]) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        vector<int> path;
        for (int cur = n; cur != -1; cur = parent[cur]) {
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());
        cout << path.size() << endl;
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
