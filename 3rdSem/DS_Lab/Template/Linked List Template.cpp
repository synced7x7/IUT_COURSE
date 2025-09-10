#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node * next;
};

Node * head = nullptr;
Node * tail = nullptr;

void print_forward()
{
    if (head == nullptr)
    {
        cout << "Head=Null, Tail=Null, Empty" << endl;
        return;
    }

    cout << "Head=" << head->data << ", ";
    Node * temp1 = head;
    while (temp1->next != nullptr)
    {
        temp1 = temp1->next;
    }
    cout << "Tail=" << temp1->data << ", ";

    Node * temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

Node * create_new_node(int key)
{
    Node * new_node = new Node();
    new_node->data = key;
    new_node->next = nullptr;
    return new_node;
}

void insert_front(int key)
{
    if (head == nullptr) // if empty
    {
        Node * new_node = create_new_node(key);
        head = new_node;
        tail = new_node;
        print_forward();
        return;
    }
    // if not empty
    Node * new_node = create_new_node(key);
    new_node->next = head;
    head = new_node;
    print_forward();
}

void insert_back(int key)
{
    if (head == nullptr) // if empty
    {
        Node * new_node = create_new_node(key);
        head = new_node;
        tail = new_node;
        print_forward();
        return;
    }
    // if not empty
    Node * new_node = create_new_node(key);
    tail->next = new_node;
    tail = new_node;
    print_forward();
}

void Insert_after_node(int key, int v)
{
    Node * new_node = create_new_node(key);
    Node * temp = head;

    while (temp != nullptr)
    {
        if (temp->data == v) // if found
        {
            new_node->next = temp->next;
            temp->next = new_node;
            if (new_node->next == nullptr)
            {
                tail = new_node;
            }
            print_forward();
            return;
        }
        temp = temp->next;
    }

    // if not found
    cout << "Value not found" << endl;
    print_forward();
}

void Update_node(int key, int v)
{
    Node * temp = head;
    while (temp != nullptr)
    {
        if (temp->data == v) // if found
        {
            temp->data = key;
            print_forward();
            return;
        }
        temp = temp->next;
    }
    // if not found
    cout << "Value not found" << endl;
    print_forward();
}

void remove_head()
{
    if (head == nullptr) // if no element is present
    {
        cout << "Underflow" << endl;
        print_forward();
        return;
    }

    Node* temp = head;
    head = head->next;
    delete temp;
    if (head == nullptr)
    {
        tail = nullptr;
    }
    print_forward();
}

void remove_element(int key)
{
    if (head == nullptr)
    {
        cout << "Value not found" << endl;
        print_forward();
        return;
    }

    if (head->data == key)
    {
        remove_head();
        return;
    }

    Node * temp = head;
    while (temp->next != nullptr)
    {
        if (temp->next->data == key) // if found
        {
            Node* to_delete = temp->next;
            temp->next = temp->next->next;
            if (to_delete == tail)
            {
                tail = temp;
            }
            delete to_delete;
            print_forward();
            return;
        }
        temp = temp->next;
    }
    // if not found
    cout << "Value not found" << endl;
    print_forward();
}

void Remove_end()
{
    if (head == nullptr) // if no element is present
    {
        cout << "Underflow" << endl;
        print_forward();
        return;
    }

    if (head->next == nullptr) // if only one element is present
    {
        remove_head();
        return;
    }

    // if more than one element is present
    Node * temp = head;
    while (temp->next != tail)
    {
        temp = temp->next;
    }

    delete tail;
    tail = temp;
    tail->next = nullptr;
    print_forward();
}

int main()
{
    while (true)
    {
        int command;
        cin >> command;
        cin.ignore();
        int key, v;
        switch (command)
        {
        case 1:
            cin >> key;
            insert_front(key);
            break;
        case 2:
            cin >> key;
            insert_back(key);
            break;
        case 3:
            cin >> key >> v;
            Insert_after_node(key, v);
            break;
        case 4:
            cin >> key >> v;
            Update_node(key, v);
            break;
        case 5:
            remove_head();
            break;
        case 6:
            cin >> key;
            remove_element(key);
            break;
        case 7:
            Remove_end();
            break;
        case 8:
            return 0;
        default:
            cout << "Invalid Key" << endl;
            return 0;
        }
    }

    return 0;
}
