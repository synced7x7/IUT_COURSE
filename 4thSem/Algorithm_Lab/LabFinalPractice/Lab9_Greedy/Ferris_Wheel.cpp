// https://cses.fi/problemset/task/1090/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

typedef long long int ll;
using namespace std;

int main()
{
	ll n, w;
	cin >> n >> w;
	vector<ll> kid(n);

	for(ll i=0; i<n; i++) {
		cin >> kid[i];
	}

	sort(kid.begin(), kid.end());
	ll res = 0;
	ll j=0;
	for(ll i=n-1; i>=0; i--) {
		if(i<j) {
			break;
		}
		else if (i==j) {
			res++; break;
		}
		ll end = kid[i];
		res++;
		ll start = kid[j];
		if(start+end <=w) {
			j++;
		}

		//cout << "end = " << end << " start = " << start << " res = " << res << endl;
	}

	cout << res << endl;

	return 0;
}