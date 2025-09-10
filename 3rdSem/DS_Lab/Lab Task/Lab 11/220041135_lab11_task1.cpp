#include <vector>
#include <iostream>
using namespace std;


int main()
{
    int vertex, edges ,  u, v;
    cin >> vertex >> edges;

    vector<vector <int> > adjList(vertex+1);
    vector<vector <int> > adjMatrix(vertex+1, vector<int> (vertex+1, 0));
    //v+1 rows for every vertex(outer) , v+1 col for every rows and initialized to zero

    for(int i=1; i<=edges ; i++)
    {
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);

        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    cout << "Adjacency List:" << endl;
    for (int i=1; i<=vertex; i++)
    {
        cout << i << ": ";
        for (int neighbor : adjList[i]) { 
            cout << neighbor << " ";
        }
        cout << endl;
    }
    cout << endl;

    for(int i=1; i<=vertex; i++)
    {
        for(int j=1; j<=vertex ; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
