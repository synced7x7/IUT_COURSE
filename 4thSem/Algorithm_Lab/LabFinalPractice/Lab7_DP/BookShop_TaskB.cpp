//https://cses.fi/problemset/task/1158

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

typedef long long int ll;
using namespace std;

int main()
{
	int n, w;
	cin >> n >> w;
	vector<int> prices(n+1);
	vector<int> pages(n+1);
	vector<int> dp(w+1, 0);
	for (int i=0; i<n; i++) {
		cin >> prices[i];
	}
	for (int i=0; i<n; i++) {
		cin >> pages[i];
	}

	for(int i=0; i<n; i++) {
		/* for(int j=0; j<prices[i]; j++) {
			cout << dp[j] << " ";
		} */
		for(int j=w; j>=prices[i]; j--) {
			dp[j] = max(dp[j], dp[j-prices[i]]+pages[i]);
			//cout << dp[j] << " ";
		}
		//cout << endl;
	}

	cout << dp[w] << endl;

	

	return 0;
}