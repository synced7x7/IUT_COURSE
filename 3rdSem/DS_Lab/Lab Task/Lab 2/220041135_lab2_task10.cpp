#include <iostream>
using namespace std;

int arr[100];  // Circular array to implement Deque
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
        return;
    }
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

void push_back(int number)
{
    if (isFull())
    {
        cout << "FULL" << endl;
        return;
    }
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

void pop_front()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << endl;
        return;
    }
    if (front == rear)
    {
        front = rear = -1;  // Reset deque
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
        front = rear = -1;  // Reset deque
    }
    else
    {
        rear = (rear - 1 + max_size) % max_size;
    }
}

int size()
{
    if (isEmpty())
    {
        return 0;
    }
    if (rear >= front)
    {
        return rear - front + 1;
    }
    return (max_size - front) + (rear + 1);
}

void print_deque()
{
    if (isEmpty())
    {
        cout << "Deque is empty" << endl;
        return;
    }

    int i = front;
    while (true)
    {
        cout << arr[i] << " ";
        if (i == rear) break;
        i = (i + 1) % max_size;
    }
    cout << endl;
}

int main()
{
    cout << "Enter the max size of the deque: ";
    cin >> max_size;

    int option, number;

    while (true)
    {

        cin >> option;

        if (option == 1)
        {

            cin >> number;
            push_front(number);
            print_deque();
        }
        else if (option == 2)
        {

            cin >> number;
            push_back(number);
            print_deque();
        }
        else if (option == 3)
        {
            pop_front();
            print_deque();
        }
        else if (option == 4)
        {
            pop_back();
            print_deque();
        }
        else if (option == 5)
        {
            cout << size() << endl;
        }
        else if (option == 6)
        {
            break;
        }
    }

    return 0;
}
