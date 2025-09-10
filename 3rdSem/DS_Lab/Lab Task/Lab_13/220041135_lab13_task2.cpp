#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 1000;
const int LOG = 10;

int sparse[MAXN][LOG];
vector<int> input;

int count =0;

void buildSparseTable(int n)
{
    cout << "Ranges to be stored in Sparse Table: " << endl;
    for (int i = 0; i < n; i++)
    {
        sparse[i][0] = i;
        cout << "(" << i << "," << i << ") " << endl;
    }
   
    for (int j = 1; (1 << j) <= n; j++) //col
    {
        for (int i = 0; i + (1 << j) - 1 < n; i++) //row
        {
            int left = sparse[i][j - 1];
            int right = sparse[i + (1 << (j - 1))][j - 1];

            sparse[i][j] = (input[left] <= input[right]) ? left : right;
            cout << "(" << i << "," << i+ (1<<j)-1 << ") " << endl;
            // cout << "i = " << i << " j-1 = " << j-1 << endl;
            // cout << "i + (1<<(j-1))= " << i + (1<<(j-1)) << " j - 1= " << j - 1 <<endl;
            // cout << "left = " << left << " right = " << right << endl;
            // cout << "input[left] = " <<input[left] << " input[right]" << input [right] << endl; 
        }
        cout << endl;
    }

    cout << "Status of Sparse Table: " << endl;
    for (int i = 0; i < n; i++) // row
    {
        for (int j = 0; (1 << j) <= n; j++) //col
        {
            if (i + (1 << j) - 1 < n)
                cout << input[sparse[i][j]] << " ";
        }
        cout << endl;
    }
}


void querySparseTable(int L, int R)
{
    count++;
    int length = R - L + 1;
    int k = log2(length);

    int leftIndex = sparse[L][k];
    int rightIndex = sparse[R - (1 << k) + 1][k];

    int leftValue = input[leftIndex];
    int rightValue = input[rightIndex];

    int minValue = (leftValue <= rightValue) ? leftValue : rightValue;

    cout << "Query-" << count << ": Min = " << minValue;
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

        querySparseTable(L,R);
    }

    return 0;
}
