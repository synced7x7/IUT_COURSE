#include <iostream>

using namespace std;
int max_size;
int front = -1;
int rear = -1;
int arr[100];

bool isFull()
{
    return (front == (rear+1)  % max_size);
}

bool isEmpty()
{
    return front == -1;
}



void enQueue(int number)
{
    if (isFull())
    {
        cout << "Overflow" << endl;
    }
    else
    {
        if(isEmpty())
        {
            front = rear = 0;
        }
        else
        {
            rear = (rear+1) % max_size;

        }
        arr[rear] = number;

    }

}

void deQueue()
{
    if(isEmpty())
    {
        cout << "Underflow" << endl;

    }
    if (front == rear)
        front = rear = -1;
    else
    {
        front = (front+1)% max_size;
    }

}

int size()
{
    if (isEmpty())
        return 0;
    if (rear >= front)
        return rear - front + 1;
    else
        return max_size - front + rear + 1;
}

int main()
{
    cin >> max_size;
    cin.ignore();
    int ID=0;
    int number;
    while (ID!=-1)
    {
        cin >> ID;
        if (ID == 1)
        {
            cin >> number;
            cout << "Enqueue: ";
            enQueue(number);

        }
        else if (ID ==2)
        {
            cout << "Dequeue: ";
            deQueue();
        }
        else if (ID == 3)
        {
            if(isEmpty())
            {
                cout << "is Empty: True" << endl;
            }
            else
                cout << "is Empty: False" << endl;
        }
        else if (ID == 4)
        {
            if(isFull())
            {
                cout << "is Full: True" << endl;
            }
            else
                cout << "is Full: False" << endl;
        }
        else if (ID == 5)
        {
            cout << "Size: " << size() << endl;
        }
        else if (ID == 6)
        {
            cout << "Front: " << arr[front] << endl;
        }
        if(ID == 1 || ID ==2)
        {
            int i = front;
            while(true)
            {
                cout << arr[i] << " ";
                if(i==rear)
                    break;
                i=(i+1)%max_size;
            }
            cout << endl;
        }
    }
    if(ID == -1)
        cout << "EXIT" << endl;


    return 0;
}
