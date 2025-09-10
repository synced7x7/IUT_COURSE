#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Recursive function for DFS-based Topological Sort
void topologicalSortUtil(int v, vector<vector<int>> &adj, vector<bool> &visited, stack<int> &st) {
    visited[v] = true;
    for (int neighbor : adj[v]) {
        if (!visited[neighbor]) {
            topologicalSortUtil(neighbor, adj, visited, st);
        }
    }
    st.push(v); // Push the vertex to stack after visiting all its neighbors
}

// Function to perform DFS-based Topological Sorting
vector<int> topologicalSort(int V, vector<vector<int>> &adj) {
    vector<bool> visited(V, false);
    stack<int> st; 

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, adj, visited, st);
        }
    }
    
    vector<int> result;
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    
    return result;
}

int main() {
    int nodes, edges, u, v;
    cin >> nodes >> edges;

    vector<vector<int>> adj(nodes);

    // Read edges
    for (int i = 0; i < edges; i++) {
        cin >> u >> v;
        adj[u].push_back(v); // Directed edge from u to v
    }

    // Perform Topological Sorting
    vector<int> sortedOrder = topologicalSort(nodes, adj);

    // Output the result
    for (int node : sortedOrder) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
