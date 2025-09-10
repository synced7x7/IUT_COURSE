#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int parent[N];
int size[N];

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
		/* if (size[a] < size[b])
			swap(a, b); */
		parent[b] = a;
		size[a] += size[b];
	}
}

//Rank based
/* void Union(int a, int b)
{
	a = find(a);
	b = find(b);
	if (a != b)
	{
		if (Rank[a] < Rank[b])
			swap(a, b); 

		parent[b] = a; 

		if (Rank[a] == Rank[b])
			Rank[a]++;
	}
} */

int main()
{
	int n;
	cin >> n;
	for (int i=0; i<n ; i++)
	{
		if (n == 1)
		{
			
		}
	}


	return 0;
}