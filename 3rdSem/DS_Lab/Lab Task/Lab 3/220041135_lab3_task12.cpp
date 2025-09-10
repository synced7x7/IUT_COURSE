#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    int num;

    while (true)
    {

        priority_queue<int, vector<int>, greater<int>> minHeap;


        while (true)
        {
            cin >> num;
            if (num == -1) break;
            minHeap.push(num);
        }


        if (minHeap.empty()) break;

        int totalCost = 0;


        while (minHeap.size() > 1)
        {

            int first = minHeap.top();
            minHeap.pop();
            int second = minHeap.top();
            minHeap.pop();

            cout << "first = " << first << " second = " << second << endl;


            int sum = first + second;
            totalCost += sum;
            cout << "sum = " << sum << " total cost = " << totalCost << endl;


            minHeap.push(sum);
        }


        cout << "Minimum Cost: " << totalCost << endl;
    }

    return 0;
}
