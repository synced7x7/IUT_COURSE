#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    priority_queue <int> max_heap;
    priority_queue <int> temp_max_heap;

    int n;
    cin >> n;
    int count =1;
    int sum = 1;

    for (int i=0 ; i<n; i++)
    {
        int number;
        cin >> number;
        max_heap.push(number);
        if(count <=2)
        {
            count++;
            cout << "-1" << endl;
        }
        else
        {
            temp_max_heap = max_heap;


            for(int j=0; j<3 ; j++)
            {
                sum*=temp_max_heap.top();
                temp_max_heap.pop();
            }
            cout << sum << endl;

            while(!temp_max_heap.empty())
            {

                temp_max_heap.pop();
            }

        }

        sum = 1;


    }


    return 0;
}
