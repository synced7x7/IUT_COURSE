#include <iostream>
#include <vector>
#include <algorithm> // for sort

using namespace std;
typedef long long int ll;

int main()
{
	ll t;
	cin >> t;
	while (t--)
	{
		ll n;
		cin >> n;
		vector<ll> start(n), endTimes(n); // renamed to avoid conflict

		for (ll i = 0; i < n; i++)
		{
			cin >> start[i];
		}
		for (ll i = 0; i < n; i++)
		{
			cin >> endTimes[i];
		}

		// Combine and sort based on endTimes
		vector<pair<ll, ll>> intervals(n);
		for (ll i = 0; i < n; i++)
		{
			intervals[i] = {endTimes[i], start[i]};
		}

		sort(intervals.begin(), intervals.end());

		// Extract back
		for (ll i = 0; i < n; i++)
		{
			endTimes[i] = intervals[i].first;
			start[i] = intervals[i].second;
		}

		/* // Print to verify
		for (ll i = 0; i < n; i++)
		{
			cout << "Start: " << start[i] << ", End: " << endTimes[i] << "\n";
		} */

		ll count = 1;
		ll j = 1;
		for (ll i = 0; i < n;)
		{
			//cout << "Comparison betweeen " << endTimes[i] << " and " << start[j] << endl;

			if (endTimes[i] <= start[j])
			{
				count++;
				i=j;
				j++;
				//cout << "Consider it done!!" << endl;
			}
			else
			{
				j++;
				//cout << "Oh I can't!!" << endl;
			}
			//cout << "--------------------------------" << endl;
			if (j == n)
				break;
		}
		cout  << count << endl;
	}
	return 0;
}
