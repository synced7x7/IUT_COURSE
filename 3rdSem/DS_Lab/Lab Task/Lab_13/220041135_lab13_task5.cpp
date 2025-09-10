#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 1000;
const int LOG = 10;

int sparse[MAXN][LOG];
vector<int> input;

int count = 0;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void buildSparseTable(int n)
{
    cout << "Ranges to be stored in Sparse Table: " << endl;
    for (int i = 0; i < n; i++)
    {
        sparse[i][0] = i;
        cout << "(" << i << "," << i << ") " << endl;
    }
    cout << endl;
    for (int j = 1; (1 << j) <= n; j++) // col
    {
        for (int i = 0; i + (1 << j) - 1 < n; i++) // row
        {
            sparse[i][j] = gcd(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
            cout << "(" << i << "," << i + (1 << j) - 1 << ") " << endl;
             //cout << "i = " << i << " j-1 = " << j-1 << endl;
            // cout << "i + (1<<(j-1))= " << i + (1<<(j-1)) << " j - 1= " << j - 1 <<endl;
            // cout << "left = " << left << " right = " << right << endl;
            // cout << "input[left] = " <<input[left] << " input[right]" << input [right] << endl;
        }
        cout << endl;
    }

    cout << "Status of Sparse Table: " << endl;
    for (int i = 0; i < n; i++) // row
    {
        for (int j = 0; (1 << j) <= n; j++) // col
        {
            if (i + (1 << j) - 1 < n)
                cout << input[sparse[i][j]] << " ";
        }
        cout << endl;
    }
}

void queryGCD(int L, int R)
{
    int length = R - L + 1;
    int k = log2(length);
    cout << "k= " << k << endl;
    int leftGCD = sparse[L][k];
    int rightGCD = sparse[R - (1 << k) + 1][k];
    count++;
    cout << "Query-" << count << ": GCD= " << input[gcd(leftGCD, rightGCD)];
    cout << " min([" << L << "," << L + (1 << k) - 1 << "],[" 
         << R - (1 << k) + 1 << "," << R << "])\n";
}

int main()
{
    int n, q;
    cin >> n;
    input.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin >> input[i];
    }

    buildSparseTable(n);
    cin >> q;
    while (q--)
    {
        int L, R;
        cin >> L >> R;

        queryGCD(L, R);
    }

    return 0;
}
