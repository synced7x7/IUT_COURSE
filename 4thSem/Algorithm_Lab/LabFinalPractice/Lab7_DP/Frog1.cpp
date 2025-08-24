// https://atcoder.jp/contests/dp/tasks/dp_a

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

    vector<int> h(n+1);

    for(int i=1; i<=n; i++) {
        cin >> h[i];
    }

    vector<int> dp(n+1);

    dp[1] = 0;
    dp[2] = abs(h[2] - h[1]);
    dp[3] = min(dp[2] + abs(h[3] - h[2]), dp[1] + abs(h[3] - h[1]));
    for(int i=4; i<=n; i++) {
        dp[i] = min(dp[i-1] + abs(h[i] - h[i-1]), dp[i-2] + abs(h[i]- h[i-2]));
    }

    /* for(int i=1; i<=n ; i++) {
        cout << dp[i] << " ";
    }
    cout << endl; */

    cout << dp[n] << endl;

    return 0;
}
