#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 50000;
const int LOG = 16;

int sparse[MAXN][LOG];
vector<int> heights;

void buildSparseTable(int n)
{
    for (int i = 0; i < n; i++)
        sparse[i][0] = heights[i];

    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 0; i + (1 << j) - 1 < n; i++)
        {
            int nextIdx = i + (1 << (j - 1));
            sparse[i][j] = max(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int queryMax(int L, int R)
{
    int length = R - L + 1;
    int k = log2(length);
    return max(sparse[L][k], sparse[R - (1 << k) + 1][k]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    heights.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin >> heights[i];
    }

    buildSparseTable(n);

    cout << "Sparse Table after construction:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; (1 << j) <= n; j++)
        {
            cout << sparse[i][j] << " ";
        }
        cout << endl;
    }

    int count = 0;
    cout << "Queries and their results:" << endl;
    for (int i = 0; i < m; i++)
    {
        int A, B;
        cin >> A >> B;
        A--, B--;

        if (A > B)
            swap(A, B);

        if (A == B)
        {
            cout << "Query-" << (i + 1) << ": Min=" << heights[A] << " min([" << A << "," << A << "],[" << A << "," << A << "])" << endl;
            continue;
        }

        int maxBetween = queryMax(A + 1, B);
        if (heights[A] >= max(heights[A], heights[B]) && heights[A] >= queryMax(A + 1, B))
        {
            cout << "Query-" << (i + 1) << ": Min=" << heights[B] << " min([" << A + 1 << "," << B << "],[" << A + 1 << "," << B << "])" << endl;
        }
        else
        {
            cout << "Query-" << (i + 1) << ": No catapult possible" << endl;
        }
    }

    return 0;
}
