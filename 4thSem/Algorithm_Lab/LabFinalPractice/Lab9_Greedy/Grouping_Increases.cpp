// https://codeforces.com/problemset/problem/1919/C

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

typedef long long int ll;
using namespace std;

int main()
{
	int t;
	while (t--)
	{
		int n;
		cin >> n;
		vector<int> no(n+1);
		int max = -1;
		int maxPointer;
		for (int i=0; i<n; i++) {
			cin >> no[i];
			if(no[i]>max) {
				max = no[i];
				maxPointer = i;
			}
		}

		cout << "Max = " << max << " Max Pointer = " << maxPointer << endl;
	}
	return 0;
}