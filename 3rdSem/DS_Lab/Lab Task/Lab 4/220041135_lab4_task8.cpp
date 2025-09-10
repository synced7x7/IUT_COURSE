#include <iostream>
#include <string>

using namespace std;

struct Node
{
    int data;
    Node *next;
    Node *prev;
};

Node *head = nullptr;
Node *tail = nullptr;

Node *create_new_node(int key)
{
    Node *new_node = new Node();
    new_node->data = key;
    new_node->next = nullptr;
    new_node->prev = nullptr;
    return new_node;
}

void print_forward()
{
    if (head == nullptr)
    {
        cout << "EMPTY" << endl;
        return;
    }

    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void insert_back(int key)
{
    if (head == nullptr)   // if empty
    {
        Node *new_node = create_new_node(key);
        head = new_node;
        tail = new_node;
        return;
    }
    // if not empty
    Node *new_node = create_new_node(key);
    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;
}

void rearranged()
{
    if (!head || !head->next) return;

    Node *oddHead = nullptr, *oddTail = nullptr;
    Node *evenHead = nullptr, *evenTail = nullptr;
    Node *temp = head;


    while (temp != nullptr && temp->next !=nullptr)
    {
        Node *next = temp->next;
        if (temp->data % 2 == 1)
        {
            if (oddHead == nullptr)
            {
                oddHead = oddTail = temp;
            }
            else
            {
                oddTail->next = temp;
                temp->prev = oddTail;
                oddTail = temp;
            }
        }
        else      // Even index
        {
            if (evenHead == nullptr)
            {
                evenHead = evenTail = temp;
            }
            else
            {
                evenTail->next = temp;
                temp->prev = evenTail;
                evenTail = temp;
            }
        }





        temp = next;

    }


    if (oddTail)
    {
        oddTail->next = evenHead;
        if (evenHead)
            evenHead->prev = oddTail;
    }


    head = oddHead;
}

int main()
{
    string n = "A";
    while (true)
    {
        cin >> n;
        if (n == "NULL") break;
        int value = stoi(n);
        insert_back(value);
    }
    print_forward();

    rearranged();

    print_forward();

    return 0;
}
