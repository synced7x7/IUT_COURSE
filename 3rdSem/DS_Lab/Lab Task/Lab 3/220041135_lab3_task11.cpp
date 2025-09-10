#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    priority_queue<int> pq;
    int stone;


    while (true)
    {
        cin >> stone;
        if (stone == -1) break;
        pq.push(stone);
    }


    while (pq.size() > 1)
    {

        int first = pq.top();
        pq.pop();


        int second = pq.top();
        pq.pop();


        if (first != second)
        {
            pq.push(first - second);
        }

    }


    if (!pq.empty())
    {
        cout << pq.top() << endl;
    }
    else
    {
        cout << "0" << endl;
    }

    return 0;
}
