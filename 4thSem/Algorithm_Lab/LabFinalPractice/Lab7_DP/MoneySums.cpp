// https://cses.fi/problemset/task/1745

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <numeric>

using namespace std;

int main()
{

    int n;
    cin >> n;
    vector<int> money(n + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> money[i];
    }

    int w = accumulate(money.begin(), money.end(), 0);
    vector<int> dp(w + 1, -1);
    dp[0] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = w; j >= money[i]; j--)
        {
            if (dp[j] == -1)
            {
                if (dp[j - money[i]] == -1)
                    dp[j] = -1;
                else if (dp[j - money[i]] == 0)
                    dp[j] = money[i];
                else
                    dp[j] = dp[j - money[i]] + money[i];
            }
        }
        /* for (int j = 0; j <= w; j++)
        {
            cout << dp[j] << " ";
        }
        cout << endl; */
    }

    vector<int> res;
    for (int j = 0; j <= w; j++)
    {
        if(dp[j]!=0 && dp[j]!=-1)
            res.push_back(dp[j]);
    }

    cout << res.size() << endl;
    for(int result :res) {
        cout << result << " ";
    }
    cout << endl;

    return 0;
}
