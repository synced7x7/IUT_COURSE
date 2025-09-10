#include <iostream>
using namespace std;

int arr[100];
int front = -1;
int rear = -1;
int max_size;
int count = 0;

bool isFull()
{
    return ((rear + 1) % max_size == front);
}

bool isEmpty()
{
    return (front == -1);
}

void push_front(int number)
{
    if (isFull())
    {
        cout << "FULL" << endl;
    }
    else
    {
        if (isEmpty())
        {
            front = rear = 0;
        }
        else
        {
            front = (front - 1 + max_size) % max_size;
        }
        arr[front] = number;
    }
}

void push_back(int number)
{
    if (isFull())
    {
        cout << "FULL" << endl;
    }
    else
    {
        if (isEmpty())
        {
            front = rear = 0;
        }
        else
        {
            rear = (rear + 1) % max_size;
        }
        arr[rear] = number;
    }
}

void pop_front()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << endl;
        return;
    }

    if (front == rear)
    {
        front = rear = -1; // Reset
    }
    else
    {
        front = (front + 1) % max_size;
    }
}

void pop_back()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << endl;
        return;
    }

    if (front == rear)
    {
        front = rear = -1; // Reset
    }
    else
    {
        rear = (rear -1 + max_size) % max_size;
    }

}

int main()
{
    cin >> max_size;
    cin.ignore();
    string command;

    while (command != "E")
    {
        cin >> command;
        if (command == "PF")
        {
            int number;
            cin >> number;
            push_front(number);
        }
        else if (command == "PB")
        {
            int number;
            cin >> number;
            push_back(number);
        }
        else if (command == "DF")
        {
            pop_front();
        }
        else if (command == "DB")
        {
            pop_back();
        }
        else if (command == "STAT")
        {
            if(isEmpty())
                cout << "Empty" << endl;
            else if(isFull())
                cout << "Full" << endl;
            else
                cout << "None" << endl;
        }
        else if (command == "S")
        {
            if (isEmpty())
            {
                count = 0;
            }
            else if (rear >= front)
            {
                count = rear - front + 1;
            }
            else
            {
                count = (max_size - front) + (rear + 1);//Elements from front to the end of the array (max_size - front elements).
                                                    //Elements from the start of the array to rear (rear + 1 elements).
            }
            cout << count << endl;
        }

        else if (command ==  "F")
        {
            cout << front << endl;
        }
        else if (command ==  "R")
        {
            cout << rear << endl;
        }


        cout << "front = " << front << " rear = " << rear << endl;

        if (!isEmpty() && (command == "PF" || command == "PB" || command == "DB" || command == "DF"))
        {

            int i = front; //for max_size of 5 front will be 0, 4 ,3 ,2 ,1. for PF
            while (true)
            {
                cout << arr[i] << " ";

                if (i == rear) break;
                //cout << "front ** = " << front << "rear ** = " << rear << endl;
                i = (i + 1) % max_size;
            }
            cout << endl;
        }
    }

    return 0;
}
