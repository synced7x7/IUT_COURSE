#include <iostream>

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



void insert_back(int key)
{
    if (head == nullptr)   // if list is empty
    {
        Node *new_node = create_new_node(key);
        head = new_node;
        tail = new_node;
        return;
    }
    // if list is not empty
    Node *new_node = create_new_node(key);
    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;
}


void remove_duplicates()
{
    if (head == nullptr) return;

    Node *temp = head;
    while (temp->next != nullptr)
    {
        if (temp->data == temp->next->data)
        {
            Node* duplicate = temp->next;
            temp->next = duplicate->next;

            if (duplicate->next != nullptr)//if not the last element
            {
                duplicate->next->prev = temp;
            }
            else
            {
                tail = temp;
            }

            delete duplicate;
        }
        else
        {
            temp = temp->next;
        }
    }
}

int main()
{
    int n = 0;
    while (true)
    {
        cin >> n;
        if (n == -1) break;
        insert_back(n);
    }


    //print_forward();

    remove_duplicates();

    print_forward();

    return 0;
}
