#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

vector<char> topologicalSort(vector<vector<int>> &adj, int V, vector<char> &indexToChar) {
    vector<int> indegree(V, 0);

    // Compute in-degrees
    for (int i = 0; i < V; i++) {
        for (int neighbor : adj[i]) {
            indegree[neighbor]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<char> result;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(indexToChar[node]);

        for (int neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // If a cycle exists, return empty result
    if (result.size() != V) {
        cout << "[]\n";  // Cycle detected
        return {};
    }

    return result;
}

int main() {
    int n, edges;
    cin >> n >> edges;

    unordered_map<char, int> charToIndex;
    vector<char> indexToChar(n);
    vector<vector<int>> adj(n);

    // Read edges and build graph
    for (int i = 0; i < edges; i++) {
        char u, v;
        cin >> u >> v;

        // Assign index if not already assigned
        if (charToIndex.find(u) == charToIndex.end()) {
            charToIndex[u] = charToIndex.size();
            indexToChar[charToIndex[u]] = u;
        }
        if (charToIndex.find(v) == charToIndex.end()) {
            charToIndex[v] = charToIndex.size();
            indexToChar[charToIndex[v]] = v;
        }

        adj[charToIndex[u]].push_back(charToIndex[v]);
    }

    vector<char> result = topologicalSort(adj, n, indexToChar);

    // Print result if no cycle
    if (!result.empty()) {
        for (char ch : result) {
            cout << ch << " ";
        }
        cout << endl;
    }

    return 0;
}
