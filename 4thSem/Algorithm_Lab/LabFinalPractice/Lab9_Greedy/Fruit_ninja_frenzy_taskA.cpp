#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

typedef long long int ll;
using namespace std;

int main()
{
	ll t;
	cin >> t;
	while (t--)
	{
		ll n;
		cin >> n;
		vector<ll> t(n);
		vector<ll> p(n);
		for (ll i=0; i<n; i++) {
			cin >> t[i];
		}

		for (ll i=0; i<n; i++) {
			cin >> p[i];
		}

		vector<pair<ll, ll>> fruits;

		for (ll i=0; i<n; i++) {
			fruits.push_back({t[i],p[i]});
		}

		sort(fruits.begin(), fruits.end());
		//sort(fruits.begin(), fruits.end(), greater<pair<int, int>>()); //for descending

		priority_queue<ll,  vector<ll>, greater<ll> > pq;
		ll sum = 0;
		for(ll i=0; i<n; i++) {
			if(pq.size() < fruits[i].first) {
				pq.push(fruits[i].second);
				sum+=fruits[i].second;
			} else {
				if(pq.top() < fruits[i].second){
					sum-=pq.top();
					pq.pop();
					pq.push(fruits[i].second);
					sum+=fruits[i].second;
				}
			}
		}

		cout << sum << endl;



	}
	return 0;
}