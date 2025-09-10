#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node
{
    int distance;
    string predecessor;
    char color; // 'W' = White (unvisited), 'G' = Gray (visited), 'B' = Black (processed)
};

void BFS(unordered_map<string, vector<string>> &adjList, string s, string dest, int k)
{
    unordered_map<string, Node> nodes;
    vector<string> bfsOrder;

    // Initialize nodes
    for (const auto &pair : adjList)
    {
        string v = pair.first;
        nodes[v] = {-1, "NULL", 'W'};
    }

 
    if (adjList.find(s) == adjList.end())
    {
        cout << "Source node not found in the graph!" << endl;
        return;
    }

    queue<string> q;
    nodes[s].distance = 0;
    nodes[s].color = 'G';
    q.push(s);

    while (!q.empty())
    {
        string u = q.front();
        q.pop();
        bfsOrder.push_back(u);

        if (u == dest)
        {
            break;
        }

        for (string v : adjList[u])
        {
            if (nodes[v].color == 'W')
            {
                nodes[v].color = 'G';
                nodes[v].distance = nodes[u].distance + 1;
                nodes[v].predecessor = u;
                q.push(v);
            }
        }
        nodes[u].color = 'B';
    }

   /*  cout << endl;
    
    cout << "BFS order: ";
    for (string v : bfsOrder)
    {
        cout << v << " ";
    }
    cout << endl; */

    cout << endl;
    cout << "Shortest path from " << s << " to " << dest << ": " << endl;

    if (nodes[dest].distance == -1)
    {
        cout << "No path exists from " << s << " to " << dest << "." << endl;
    }
    else
    {
        vector<string> path;
        for (string cur = dest; cur != "NULL"; cur = nodes[cur].predecessor)
        {
            path.push_back(cur);
        }
        cout << "Size of path = " <<path.size() << endl;
        reverse(path.begin(), path.end());
        if(path.size() %k!=0)
        {
            cout << "No" << endl;
            return;
        }
        for (int i = 0; i < path.size(); i+=k)
        {
            cout << path[i];
            if (i < path.size() - 1)
                cout << "->";
        }
        cout << endl;
    }
}

int main()
{
    int V, E, Q;
    cin >> V >> E >> Q;

    unordered_map<string, vector<string>> graph;
    vector<string> cities(V);
    for (int i = 0; i < V; i++)
    {
        cin >> cities[i];
        graph[cities[i]] = {};
    }

    for (int i = 0; i < E; i++)
    {
        string city1, city2;
        cin >> city1 >> city2;
        graph[city1].push_back(city2);
        graph[city2].push_back(city1);
    }

    for (int j = 0; j < Q; j++)
    {
        string src, dest;
        int k;
        cin >> src >> dest >> k;
        BFS(graph, src, dest, k);
        cout << endl;
    }

    return 0;
}