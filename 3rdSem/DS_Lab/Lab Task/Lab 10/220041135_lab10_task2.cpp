#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int parent[N];
int Rank[N];

void initialize(int v)
{
	parent[v] = v;
	Rank[v] = 0;
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
		if (Rank[a] <= Rank[b])
			swap(a, b); 

		parent[b] = a; 

		if (Rank[a] == Rank[b])
			Rank[a]++;
	}
}

void printState(int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << parent[i] << "(" << Rank[i] << ") ";
	}
	cout << endl;
}

int main()
{
	int n, command, item, i, j;
	cin >> n;
	cin >> command;
	if (command == 1)
	{
		for (int i = 0; i < n; i++)
		{
			initialize(i);
		}
	}
	else
	{
		cout << "Error Initializing" << endl;
		return 0;
	}

	printState(n);
	while (cin >> command)
	{

		if (command == 2)
		{
			cin >> item;
			// cout << "Res = ";
			cout << find(item) << endl;
		}
		else if (command == 3)
		{
			cin >> i >> j;
			Union(i, j);
			// cout << "Res = ";
			printState(n);
		}
		else
		{
			printState(n);
		}
	}

	return 0;
}