#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 10;
int parent[N];
int size[N];
int maxSize = 0;
int reduntantCount = 0;
int resIni;
int res = 0;
int res1;
vector<int> vec;

void initialize(int v)
{
	parent[v] = v;
	size[v] = 1;
}

int find(int v)
{
	if (v == parent[v])
		return v;
	return parent[v] = find(parent[v]); // path collapse //O(α(n))
}

void Union(int a, int b)
{
	int numberA = a;
	int numberB = b;
	a = find(a);
	b = find(b);
	if (a != b)
	{
		if (size[a] < size[b])
			swap(a, b);
		parent[b] = a;
		size[a] += size[b];
	}
	else
	{
		reduntantCount++;
		cout << reduntantCount << endl;
		cout << numberA << " " << numberB << endl;
	}
}

void findRes(int n)
{
	int flag = 0;
	for (int i = 1; i <= n; i++)
	{
		if (parent[1] != parent[i])
		{
			res = i;
			if (!flag)
			{
				res1 = vec[i - 2];
				flag++;
			}
		}
	}
}

void printState(int n)
{

	for (int i = 1; i <= n; i++)
	{
		cout << parent[i] << " ";
	}
	cout << endl;
}

int main()
{

	int n, a, b;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		initialize(i);
	}
	for (int i = 0; i < n - 1; i++)
	{
		cin >> a >> b;
		vec.push_back(a);
		Union(a, b);
		// printState(n);
		// findRes(n);
	}

	if (reduntantCount != 0)
	{
		findRes(n);
		cout << res1 << " " << res << endl;
	}
	else
		cout << "0" << endl;
	return 0;
}