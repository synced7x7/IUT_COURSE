// https://cses.fi/problemset/task/1092/

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

	ll con = (n * (n + 1)) / 2;
	//cout << "Sum of consecutive number = " << con << endl;
	if (con % 2 != 0)
	{
		cout << "NO" << endl;
		return 0;
	}

	con /= 2;
	//cout << "Con = " << con << endl;
	ll sum = 0;
	vector<ll> res1;
	ll i;
	for (i = 1; i <= n; i++)
	{
		sum += n;
		if (sum > con)
			break;
		res1.push_back(n);
		n--;
		sum += i;
		if (sum > con)
			break;
		res1.push_back(i);
	}
	cout << "YES" << endl;
	//cout << "i = " << i << " n = " << n << endl;
	cout << n - i + 1 << endl;
	for (ll j = i; j <= n; j++)
	{
		cout << j << " ";
	}

	cout << endl;

	cout << res1.size() << endl;
	for (ll res : res1)
	{
		cout << res << " ";
	}
	cout << endl;

	return 0;
}