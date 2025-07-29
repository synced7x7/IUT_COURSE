#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void floydWarshall(vector<vector<int>> &dist, int V)
{

    for (int k = 1; k <= V; k++)
    {
        for (int i = 1; i <= V; i++)
        {
            for (int j = 1; j <= V; j++)
            {
                if (dist[i][k] != 1e8 && dist[k][j] != 1e8)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

void printAdjacentMatrix(vector<vector<int>> &adjMatrix, int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<vector<int>> adjMatrix(n + 1, vector<int>(n + 1));

        cout << endl << "Initial Matrix: " << endl;
        printAdjacentMatrix(adjMatrix, n);

        floydWarshall(adjMatrix, n);
        
        cout << endl << "Final Matrix: " << endl;
        printAdjacentMatrix(adjMatrix, n);

        
    }
    return 0;
}