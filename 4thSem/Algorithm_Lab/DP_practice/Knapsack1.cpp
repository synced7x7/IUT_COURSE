#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main()
{
	ll n, W;
	cin >> n >> W;

	vector<ll> weight(n), value(n);
	for (ll i = 0; i < n; i++)
	{
		cin >> weight[i] >> value[i];
	}

	vector<ll> dp(W + 1, 0);

	for (ll i = 0; i < n; i++)
	{
		for (ll w = W; w >= weight[i]; w--)
		{
			dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
		}
	}

	ll answer = 0;
	for (ll w = 0; w <= W; w++)
	{
		answer = max(answer, dp[w]);
	}

	cout << answer << endl;

	return 0;
}
