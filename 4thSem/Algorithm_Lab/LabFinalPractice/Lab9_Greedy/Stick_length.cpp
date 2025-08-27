//https://cses.fi/problemset/task/1074/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

typedef long long int ll;
using namespace std;

int main()
{
	ll n;
	cin >> n;
	vector<ll> len(n);
	for(ll i=0; i<n; i++) {
		cin >> len[i];
	}

	sort(len.begin(), len.end());
	ll median = n/2;
	median = len[median];
	//cout << "Avg = " << avg <<  endl;
	ll res = 0;

	for (ll l : len) {
		//cout << "l = " << l << " res || " <<abs(avg - l) << endl;
		res+= abs(median - l);
		
	}

	cout << res;



	return 0;
}