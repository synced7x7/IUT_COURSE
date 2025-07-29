//https://www.spoj.com/problems/ROHAAN/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int Case = 1;
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

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<vector<int>> adjMatrix(n + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cin >> adjMatrix[i][j];
            }
        }
        floydWarshall(adjMatrix, n);
        ///////////
        /* cout << "Final List: " << endl;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        } */
        ///////////
        int count = 0;
        int R, s, d;
        cin >> R;
        for (int i = 0; i < R; i++)
        {
            cin >> s >> d;
            count += adjMatrix[s][d];
        }

        cout << "Case #" << Case << ": " << count << endl;
        Case++;
        adjMatrix.clear();
    }
    return 0;
}