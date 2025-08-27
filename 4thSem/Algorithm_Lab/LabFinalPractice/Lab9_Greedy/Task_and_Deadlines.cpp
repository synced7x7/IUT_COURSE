//https://cses.fi/problemset/task/1630/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

typedef long long int ll;
using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<pair<int, int>> task;
	for(int i=0; i<n; i++) {
		int duration, deadline;
		cin >> duration >> deadline;
		task.push_back({duration, deadline});
	}

	sort(task.begin(), task.end());


	ll fin = 0;
	ll reward = 0;
	for (auto t: task) {
		fin += t.first;
		reward += t.second - fin;
	}

	cout << reward << endl;


	return 0;
}