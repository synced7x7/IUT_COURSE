//https://cses.fi/problemset/task/1631

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
	vector<ll> t(n);
	ll sum = 0;
	ll maximum = -1;
	for(ll i=0; i<n; i++) {
		cin >> t[i];
		sum+=t[i];
		if(t[i]> maximum) maximum = t[i];
	}

	cout << max(sum, 2*maximum) << endl;


	return 0;
}