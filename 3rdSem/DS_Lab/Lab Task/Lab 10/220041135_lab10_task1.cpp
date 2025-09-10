#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int parent[N];
// int size[N];

void initialize(int v)
{
	parent[v] = v;
	// size[v] = 1;
}

int find(int v)
{
	if (v == parent[v])
		return v;
	return find(parent[v]); // path collapse //O(α(n))
}

void Union(int a, int b)
{
	a = find(a);
	b = find(b);
	if (a != b)
	{
		/* if (size[a] < size[b])
			swap(a, b); */
		parent[b] = a;
		// size[a] += size[b];
	}
}

void printState(int n)
{

	for (int i = 0; i < n; i++)
	{
		cout << parent[i] << " ";
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
			//cout << "Res = ";
			cout << find(item) << endl;
		}
		else
		{
			cin >> i >> j;
			Union(i, j);
			//cout << "Res = ";
			printState(n);
		}
	}

	return 0;
}