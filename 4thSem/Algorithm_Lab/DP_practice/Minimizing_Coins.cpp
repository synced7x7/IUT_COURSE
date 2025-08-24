// https://cses.fi/problemset/task/1634

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int main()
{
    int n, x;
    cin >> n >> x;

    vector<int> coins(n);
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    vector<int> dp(x + 1, INF);
    dp[0] = 0;

    for (int c : coins)
    {
        for (int s = 0; s < c; s++)
        {
            /*  if (dp[s] != INF)
                 cout << dp[s] << " ";
             else
                 cout << "X "; */
        }
        for (int s = c; s <= x; s++)
        {
            dp[s] = min(dp[s], dp[s - c] + 1);
            /* if (dp[s] != INF)
                cout << dp[s] << " ";
            else
                cout << "X "; */
        }
        // cout << endl;
    }

    if (dp[x] == INF)
        cout << -1 << endl;
    else
        cout << dp[x] << endl;

    return 0;
}
