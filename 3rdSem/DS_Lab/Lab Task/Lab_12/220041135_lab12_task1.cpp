#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

struct Node
{
    int distance;
    int predecessor;
    char color; // 'W' = White (unvisited), 'G' = Gray (visited), 'B' = Black (processed)
};

void BFS(map<int, vector<int>> &adjList, int s)
{
    map<int, Node> nodes;
    vector<int> bfsOrder;
    vector<pair<int, int>> bfsTreeEdges;

    for (const auto &pair : adjList)
    {
        int v = pair.first;
        nodes[v] = {-1, -1, 'W'}; // unvisited, no predecessor, white.
    }

    queue<int> q;
    nodes[s].distance = 0;
    nodes[s].color = 'G';

    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        bfsOrder.push_back(u);

        for (int v : adjList[u])
        {
            if (nodes[v].color == 'W')
            {
                nodes[v].color = 'G';
                nodes[v].distance = nodes[u].distance + 1;
                nodes[v].predecessor = u;
                q.push(v);
                bfsTreeEdges.push_back({u, v});
            }
        }
        nodes[u].color = 'B';
    }

    cout << "BFS order: ";
    for (int v : bfsOrder)
    {
        cout << v << " ";
    }
    cout << endl;

    cout << "Distance from source:" << endl;
    for (const auto &pair : nodes)
    {
        if (pair.second.distance != -1) //unreachable
            cout << pair.first << "(" << pair.second.distance << ") ";
    }
    cout << endl;

    cout << "Paths from source:" << endl;
    for (const auto &pair : nodes)
    {
        int v = pair.first;
        if (nodes[v].distance == -1) // unreachable
        {
            continue;
        }
        vector<int> path;
        for (int cur = v; cur != -1; cur = nodes[cur].predecessor)
        {
            path.push_back(cur);
        }
        cout << v << ": ";
        for (int i = path.size() - 1; i >= 0; i--)
        {
            cout << path[i];
            if (i > 0)
                cout << "->";
        }
        cout << endl;
    }

    cout << "Edges of BFS tree:\n";
    for (const auto &edge : bfsTreeEdges)
    {
        cout << edge.first << " " << edge.second << endl;
    }

    
}

void printAdjacencyList(map<int, vector<int>> &adjList)
{
    cout << "Adjacency List: " << endl;
    for (auto &vertex : adjList)
    {
        cout << vertex.first << ": ";
        for (auto &adj : vertex.second)
        {
            cout << adj << " ";
        }
        cout << endl;
    }
}

int main()
{
    int V, E, s;
    cin >> V >> E >> s;
    map<int, vector<int>> adjList;
    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    printAdjacencyList(adjList);
    BFS(adjList, s);

    return 0;
}