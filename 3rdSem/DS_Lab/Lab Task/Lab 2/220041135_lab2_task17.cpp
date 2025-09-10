#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int max_size;
    cin >> max_size;
    cin.ignore();
   
    queue<int> que1, que2;
    string command;

    while (true)
    {
        cin >> command;

        if (command == "-1")
        {
            break;
        }
        else if (command == "push")
        {
            int x;
            cin >> x;

            if (que1.size() == max_size)
            {
                cout << "Overflow!!" << endl;
            }
            else
            {
                que1.push(x);


                queue<int> tempque = que1;
                while (!tempque.empty())
                {
                    cout << tempque.front() << " ";
                    tempque.pop();
                }
                cout << endl;
            }
        }
        else if (command == "pop")
        {
            if (que1.empty())
            {
                cout << "Underflow!!" << endl;
            }
            else
            {

                while (que1.size() > 1)
                {
                    que2.push(que1.front());
                   // cout << "pushing elements of que 1 front to que 2" << endl;
                    que1.pop();
                }



                que1.pop();


                swap(que1, que2);

                if (que1.empty())
                {
                    cout << " " << endl;
                }
                else
                {
                    queue<int> tempque = que1;
                    while (!tempque.empty())
                    {
                        cout << tempque.front() << " ";
                        tempque.pop();
                    }
                    cout << endl;
                }
            }
        }
    }

    return 0;
}
