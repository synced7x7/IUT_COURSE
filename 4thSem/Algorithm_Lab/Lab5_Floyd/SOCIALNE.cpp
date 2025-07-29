#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

const int INF = 1e8; 

void floydWarshall(vector<vector<int>> &dist, int V)
{
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(); 
    while (t--)
    {
        string s;
        getline(cin, s);
        int n = s.size();

        vector<vector<int>> adjMatrix(n, vector<int>(n));

        for (int j = 0; j < n; j++)
        {
            adjMatrix[0][j] = (s[j] == 'Y') ? 1 : (j == 0 ? 0 : INF);
        }

        for (int i = 1; i < n; i++)
        {
            getline(cin, s);
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    adjMatrix[i][j] = 0;
                else if (s[j] == 'Y')
                    adjMatrix[i][j] = 1;
                else
                    adjMatrix[i][j] = INF;
            }
        }

        floydWarshall(adjMatrix, n);
        /* cout << "Initial Matrix:" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adjMatrix[i][j] == INF)
                    cout << "INF ";
                else
                    cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }

        

        cout << "\nFinal Matrix after Floyd-Warshall:" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adjMatrix[i][j] == INF)
                    cout << "INF ";
                else
                    cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        } */
        int possibleFriendCount = 0;
        int maxPossibleFriend = -1;
        int maxCountVertex = -1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adjMatrix[i][j] == 2 )
                {
                    possibleFriendCount++;
                }
            }
            if (possibleFriendCount > maxPossibleFriend)
            {
                maxPossibleFriend = possibleFriendCount;
                maxCountVertex = i;
            }
            possibleFriendCount = 0;
        }
        //cout << endl << endl << "Final Result: " << endl;
        cout << maxCountVertex << " " << maxPossibleFriend << endl;
    }

    return 0;
}
