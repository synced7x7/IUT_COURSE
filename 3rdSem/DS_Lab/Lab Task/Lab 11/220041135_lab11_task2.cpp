#include <vector>
#include <iostream>
using namespace std;

int main()
{
    int vertex, edges, u, v;
    cin >> vertex >> edges;

    vector<vector<int>> adjList(vertex + 1);

    for (int i = 1; i <= edges; i++)
    {
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    int size = 0;
    int prevSize = 0;
    //cout << "Adjacency List:" << endl;
    for (int i = 1; i <= vertex; i++)
    {
        if (i != 1)
            prevSize = adjList[i - 1].size();
        size = adjList[i].size();
        /* cout << endl
             << "Prev Size: " << prevSize << " Size = " << size << endl;
      */
        if (prevSize != 0 && prevSize != size)
        {
            cout << "No";
            return 0;
        }
        
    }
    cout << endl;
    cout << "Yes";

    return 0;
}
