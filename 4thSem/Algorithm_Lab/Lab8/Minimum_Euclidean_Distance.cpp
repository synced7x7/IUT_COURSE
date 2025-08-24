// https://github.com/ir-rafio/iut-algorithms-lab-1b-summer-23-24/blob/main/Lab%208/2025%20-CSE_4404_Lab8_1B-2A.pdf

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

typedef long long ll;

struct Point
{
	ll x, y;
};

bool compareX(const Point &a, const Point &b)
{
	return a.x < b.x;
}

bool compareY(const Point &a, const Point &b)
{
	return a.y < b.y;
}

ll distSquared(const Point &a, const Point &b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

ll closestPair(vector<Point> &points, int left, int right)
{
	if (right - left <= 3)
	{
		ll minDist = LLONG_MAX;
		for (int i = left; i < right; ++i)
		{
			for (int j = i + 1; j < right; ++j)
			{
				minDist = min(minDist, distSquared(points[i], points[j]));
			}
		}
		sort(points.begin() + left, points.begin() + right, compareY);
		return minDist;
	}

	int mid = (left + right) / 2;
	ll midX = points[mid].x;

	ll d1 = closestPair(points, left, mid);
	ll d2 = closestPair(points, mid, right);
	ll d = min(d1, d2);

	vector<Point> strip;
	for (int i = left; i < right; ++i)
	{
		if ((points[i].x - midX) * (points[i].x - midX) < d)
		{
			strip.push_back(points[i]);
		}
	}

	sort(strip.begin(), strip.end(), compareY);
	for (int i = 0; i < (int)strip.size(); ++i)
	{
		for (int j = i + 1; j < (int)strip.size() && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < d; ++j)
		{
			d = min(d, distSquared(strip[i], strip[j]));
		}
	}

	return d;
}

int main()
{
	int n;
	cin >> n;
	vector<Point> points(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> points[i].x >> points[i].y;
	}

	sort(points.begin(), points.end(), compareX);
	cout << closestPair(points, 0, n) << endl;
	return 0;
}
