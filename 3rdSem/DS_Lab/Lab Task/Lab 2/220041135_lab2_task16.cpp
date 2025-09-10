#include <iostream>

using namespace std;

int queue[100];
int front = -1;
int rear = -1;

bool isFull(int n)
{
    return (front == (rear + 1) % n);
}

bool isEmpty()
{
    return (front == -1);
}

void enqueue(int value, int n)
{
    if (isFull(n))
    {
        cout << "Queue is full" << endl;
        return;
    }

    if (isEmpty())
    {
        front = 0;
    }

    rear = (rear + 1) % n;
    queue[rear] = value;
}

void dequeue(int n)
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
        front = (front + 1) % n;
    }
}

int frontElement()
{
    if (isEmpty())
    {
        return -1;
    }
    return queue[front];
}

int rearElement()
{
    if (isEmpty())
    {
        return -1;
    }
    return queue[rear];
}



int main()
{
    int n;
    cin >> n;

    string command;
    cin.ignore();

    while (true)
    {
        cin >> command;
        if (command == "-1")
        {
            break;
        }

        if (command[0] == 'E')
        {
            int value;
            cin >> value;
            enqueue(value, n);
        }
        else if (command == "D")
        {
            dequeue(n);
        }

        cout << "Current Size : " << (isEmpty() ? 0 : rear - front + 1) << endl;
        cout << "Full? : " << (isFull(n) ? "Yes" : "No") << endl;
        cout << "Empty? : " << (isEmpty() ? "Yes" : "No") << endl;
        cout << "Front Element : " << frontElement() << endl;
        cout << "Front Index : " << front << endl;
        cout << "Rear Element : " << rearElement() << endl;
        cout << "Rear Index : " << rear << endl;
        cout << "Queue Elements : ";


        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
        }

        int idx = front;
        while (true)
        {
            cout << queue[idx] << " ";
            if (idx == rear) break;
            idx = (idx + 1) % n;
        }
        cout << endl;
    }

    return 0;
}
