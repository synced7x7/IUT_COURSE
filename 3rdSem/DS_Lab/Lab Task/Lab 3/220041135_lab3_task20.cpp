#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> v1;


int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);

    // Reading input array
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int k;
    cin >> k;


    for(int i = 0; i < n; i++)
    {
        int currSum = 0;
        for(int j = i; j < n; j++)
        {
            currSum += arr[j];
            v1.push_back(currSum);
        }
    }


    sort(v1.begin(), v1.end(), greater<int>());

    // Output the kth largest sum
    cout << v1[k-1] << endl;

    return 0;
}
