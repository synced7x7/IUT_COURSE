#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int parent[N];
int size[N];
int maxSize = 0;
int distinctCount = 0;

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
	a = find(a);
	b = find(b);
	if (a != b)
	{
		distinctCount++;
		if (size[a] < size[b])
			swap(a, b);
		parent[b] = a;
		size[a] += size[b];
	}
}

void findMax(int n)
{
	for (int i = 1; i <= n; i++)
	{
		//cout << parent[i] << "(" << size[i] << ") ";
		if (size[i] > maxSize)
			maxSize = size[i];
	}
}

int main()
{
	int cities, lines;
	cin >> cities >> lines;
	for (int i = 1; i <= cities; i++)
	{
		initialize(i);
	}
	int a, b;
	// printState(cities);
	for (int i = 0; i < lines; i++)
	{
		maxSize = 0;
		//distinctCount = 0;
		cin >> a >> b;
		Union(a, b);
		//cout << "Tester: ";
		findMax(cities);
		cout <<  cities - distinctCount << " " << maxSize << endl;
	}
	

	return 0;
}