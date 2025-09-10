#include <iostream>
#include <algorithm> // For std::sort
#include <string>
#include <deque>

int front = -1;
int rear = -1;



using namespace std;

int main()
{
    string str1;
    string str2;
    string store_str1;
    string store_str2;
    int rotations =0;

    deque <char> dq1;
    deque <char> dq2;

    cin >> str1;
    store_str1 = str1;
    cin.ignore();

    cin >> str2;
    store_str2 = str2;

    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());

    //cout << "string 1 = " << str1 << endl;
    //cout << "string 2 = " << str2 << endl;


    if (str1 != str2)
    {
        cout << "No" << endl;
        return 0;
    }
    else if (store_str1 == store_str2)
    {
        cout << "Yes. Rotation not needed." << endl;
        return 0;
    }
    else
    {
        for (char c: store_str1)
        {
            dq1.push_back(c);
        }
        for (char c: store_str2)
        {
            dq2.push_back(c);
        }

        cout << "Characters in the deque1: ";
        for (char c : dq1)
        {
            cout << c << " ";
        }
        cout << endl;

        cout << "Characters in the deque2: ";
        for (char c : dq2)
        {
            cout << c << " ";
        }
        cout << endl;

        int n = store_str1.size();
        while(rotations < n)
        {
            if (dq1 == dq2)
                break;
            else if(dq1.front() != dq2.front())
            {
                dq1.push_front(dq1.back());
                dq1.pop_back();
                rotations++;
            }
            else
            {
                dq1.pop_front();
                dq2.pop_front();
            }

        }




    }
    cout << "Yes. After " << rotations << " clockwise rotation." << endl;

    return 0;
}
