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
		vector<ll> a(n), b(n);
		for(ll i=0; i<n; i++)
		{
			cin >> a[i];
		}
		sort(a.begin(), a.end(), greater<>());
		for(ll i=0; i<n; i++)
		{
			cin >> b[i];
		}
		sort(b.begin(), b.end());
		ll result = 0;
		for(ll i=0; i<n; i++)
		{
			result += a[i]*b[i];
		}
		cout << result << endl;
	}
	return 0;
}