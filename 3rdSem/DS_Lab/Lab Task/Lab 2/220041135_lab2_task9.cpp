#include <iostream>
#include <stack>

using namespace std;
int max_size, queries;

stack <int> stk1;
stack <int> stk2;
int overflow;

void enqueue_operation_using_stack(int number)
{
    if(stk1.size() == max_size)
    {
        cout << "Size:" << stk1.size() << " " << "Elements: Overflow!" << endl;
        overflow=1;
    }
    else
        stk1.push(number);
}

void dequeue_operation_using_stack()
{

    if(!stk1.empty())
    {
        while(!stk1.empty())
        {
            stk2.push(stk1.top());
            stk1.pop();
        }

        stk2.pop();

        while(!stk2.empty())
        {
            stk1.push(stk2.top());
            stk2.pop();
        }
    }
    else
    {
        cout << "Size:0 Elements: Null" << endl;

    }

}

void print_stack()
{
    if (stk1.empty())
    {
        cout << "Size:0 Elements: Null" << endl;
    }
    else
    {
        cout << "Size:" << stk1.size() << " Elements: ";
        stack<int> temp;


        while (!stk1.empty())
        {
            temp.push(stk1.top());
            stk1.pop();
        }


        while (!temp.empty())
        {
            cout << temp.top() << " ";
            stk1.push(temp.top());
            temp.pop();
        }
        cout << endl;
    }
}


int main ()
{
    cin >> max_size;
    cin >> queries;
    cin.ignore();

    for (int i=0; i< queries; i++)
    {

        int command;
        cin >> command;
        if(command == 1)
        {
            int number;
            cin >> number;
            enqueue_operation_using_stack(number);

        }
        else if (command == 2)
        {
            dequeue_operation_using_stack();

        }
        //cout << "Overflow: " << overflow << endl;
        if(stk1.empty() || overflow != 1)
        {
            print_stack();
        }
        else
            overflow=0;
    }







    return 0;
}
