#include <bits/stdc++.h>
using namespace std;
#define YES cout << "YES" << endl;
#define NO cout << "NO" << endl;
#define optimize() ios::sync_with_stdio(false); cin.tie(nullptr);
using ll = long long;
const int MAXN = 1e5 + 5;
const int LOG = 18;

int sparse[MAXN][LOG], arr[MAXN], logVal[MAXN];

void preprocessLog(int n) {
    logVal[1] = 0;
    for (int i = 2; i <= n; ++i) {
        logVal[i] = logVal[i / 2] + 1;
    }
}

void constructSparseTable(int n) {
    for (int i = 0; i < n; ++i) sparse[i][0] = arr[i];
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i) {
            sparse[i][j] = sparse[i][j - 1] | sparse[i + (1 << (j - 1))][j - 1];
        }
    }
}

int getRangeOR(int left, int right) {
    int j = logVal[right - left + 1];
    return sparse[left][j] | sparse[right - (1 << j) + 1][j];
}

void executeQueries() {
    int n, queries;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    
    preprocessLog(n);
    constructSparseTable(n);
    
    cin >> queries;
    while (queries--) {
        int l, r, idx;
        cin >> l >> r >> idx;
        int result = getRangeOR(l, r);
        if (result == arr[idx]) {
            YES;
        } else {
            NO;
        }
    }
}

int main() {
    optimize();
    int testCases = 1;
    while (testCases--) {
        executeQueries();
    }
    return 0;
}
