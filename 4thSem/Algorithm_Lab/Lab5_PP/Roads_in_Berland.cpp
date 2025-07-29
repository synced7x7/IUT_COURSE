//https://codeforces.com/contest/25/problem/C

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

typedef long long int ll;

void floydWarshall(vector<vector<ll>> &dist, ll V, ll c, ll a, ll b) 
{
    for (ll i = 1; i <= V; i++)
    {
        for (ll j = 1; j <= V; j++)
        {
            if(i==j) continue;
            ll viaNewEdge = min(
                dist[i][a] + c + dist[b][j],
                dist[i][b] + c + dist[a][j]);

            if (dist[i][j] > viaNewEdge)
            {
                dist[i][j] = viaNewEdge;
            }
        }
    }
}

void printAdjacentMatrix(vector<vector<ll>> &adjMatrix, ll n)
{
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= n; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    ll n;
    cin >> n;
    vector<vector<ll>> adjMatrix(n + 1, vector<ll>(n + 1));
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= n; j++)
        {
            cin >> adjMatrix[i][j];
        }
    }

    /*  cout << endl
          << "Initial Matrix: " << endl;

     printAdjacentMatrix(adjMatrix, n); */

    ll q;
    cin >> q;

    while (q--)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        if (adjMatrix[a][b] > c)
        {
            adjMatrix[a][b] = c;
            adjMatrix[b][a] = c;
            floydWarshall(adjMatrix, n, c, a, b);
        }

         cout << endl
              << "Final Matrix: " << endl;
         printAdjacentMatrix(adjMatrix, n);

        ll result = 0;
        for (ll i = 1; i <= n; i++)
        {
            for (ll j = i + 1; j <= n; j++)
            {
                result += adjMatrix[i][j];
            }
        }
        // cout << "Final Result: " << result << endl;
        cout << result << " ";
    }
    cout << endl;

    return 0;
}