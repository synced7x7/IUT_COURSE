#include <iostream>
#include <vector>
using namespace std;

void preProcessing(int A[], int n, vector<int> &prefix_0, vector<int> &prefix_1)
{
    for (int i = 1; i <= n; i++)
    {
        prefix_0[i] = prefix_0[i - 1];
        prefix_1[i] = prefix_1[i - 1];

        if (A[i - 1] == 0)
            prefix_0[i]++;  
        if (A[i - 1] == 1)
            prefix_1[i]++;  
    }
}

void noOfFlips(int L, int R, vector<int> &prefix_0, vector<int> &prefix_1)
{
    int count_0 = prefix_0[R] - prefix_0[L - 1];
    int count_1 = prefix_1[R] - prefix_1[L - 1];

    int len = R - L + 1;
    if (len % 2 != 0)
    {
        cout << "-1" << endl;
    }
    else if (count_0 == count_1)
    {
        cout << "0" << endl;
    }
    else
    {
        cout << abs(count_0 - count_1) / 2 << endl; 
    }
}

int main()
{
    int n, q;
    cin >> n >> q;
    int A[n];
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }

    vector<int> prefix_0(n + 1, 0), prefix_1(n + 1, 0);
    preProcessing(A, n, prefix_0, prefix_1);

    int L, R;
    while (q--)
    {
        cin >> L >> R;
        noOfFlips(L, R, prefix_0, prefix_1);
    }

    return 0;
}
