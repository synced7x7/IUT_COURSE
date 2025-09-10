#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

int timeCounter = 0;

struct Node
{
    int discovery = 0;
    int finish = 0;
    int predecessor = -1;
    char color = 'W';
};

void DFS_Visit(int u, map<int, vector<int>> &adjList, map<int, Node> &nodes, vector<int> &dfsOrder, vector<pair<int, string>> &edgeClassification)
{
    timeCounter++;
    nodes[u].discovery = timeCounter;
    nodes[u].color = 'G';
    dfsOrder.push_back(u);

    for (int v : adjList[u])
    {
        if (nodes[v].color == 'W')
        {
            nodes[v].predecessor = u;
            edgeClassification.push_back({u * 100 + v, "Tree Edge"});
            DFS_Visit(v, adjList, nodes, dfsOrder, edgeClassification);
        }
        else if (nodes[v].color == 'G')
        {
            edgeClassification.push_back({u * 100 + v, "Back Edge"});
        }
        else if (nodes[v].color == 'B')
        {
            if (nodes[u].discovery < nodes[v].discovery)
            {
                edgeClassification.push_back({u * 100 + v, "Forward Edge"});
            }
            else
            {
                edgeClassification.push_back({u * 100 + v, "Cross Edge"});
            }
        }
    }

    nodes[u].color = 'B';
    timeCounter++;
    nodes[u].finish = timeCounter;
}

void DFS(map<int, vector<int>> &adjList, int V)
{
    map<int, Node> nodes;
    vector<int> dfsOrder;
    vector<pair<int, string>> edgeClassification;

    for (const auto &pair : adjList)
    {
        nodes[pair.first] = Node(); // init
    }

    for (const auto &pair : adjList)
    {
        int u = pair.first;
        if (nodes[u].color == 'W')
        {
            DFS_Visit(u, adjList, nodes, dfsOrder, edgeClassification);
        }
    }

    cout << "DFS order: ";
    for (int v : dfsOrder)
        cout << v << " ";
    cout << endl;

    cout << "Timestamps of Vertex(discovery/finishing):\n";
    for (const auto &pair : nodes)
    {
        cout << pair.first << "(" << pair.second.discovery << "/" << pair.second.finish << ")\n";
    }

    cout << "Edge classification:\n";
    for (const auto &edge : edgeClassification)
    {
        int u = edge.first / 100;
        int v = edge.first % 100;
        cout << u << " " << v << ": " << edge.second << endl;
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
    int V, E;
    cin >> V >> E;
    map<int, vector<int>> adjList;
    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
    }

    printAdjacencyList(adjList);

    DFS(adjList, V);

    return 0;
}