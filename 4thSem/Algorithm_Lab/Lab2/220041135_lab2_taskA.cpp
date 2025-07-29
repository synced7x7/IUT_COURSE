#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

typedef long long int ll;
using namespace std;

int main()
{
	ll t, n, cap;
	cin >> t;
	while (t--)
	{
		cin >> n >> cap;
		vector<ll> bottles(n);
		for (ll i = 0; i < n; i++)
		{
			cin >> bottles[i];
		}
		sort(bottles.begin(), bottles.end());
		ll sum = 0;
		ll count = 0;
		for (int i = 0; i < n; i++)
		{
			
			sum += bottles[i];
			//cout << "Sum = " <<  sum << endl;
			if(sum>cap)
				break;
			count++;
		}

		cout << count << endl;
	}
	return 0;
}