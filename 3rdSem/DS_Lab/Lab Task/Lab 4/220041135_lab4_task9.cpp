#include <iostream>

using namespace std;
int max_size;
int count = 0;

struct Node
{
    int data;
    Node * next;
};

Node * head = nullptr;
Node * tail = nullptr;

void print_forward()
{

    //cout << "\nCount = " << count << endl;
    //cout << "\n\n";
    if (head == nullptr)
    {
        cout << " " << endl;
        return;
    }

    Node * temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int isempty()
{
    if (count ==0)
        return 1;
    else
        return 0;
}

int isFull()
{
    if (count >=max_size)
        return 1;
    else
        return 0;
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

    if (count>=max_size)
    {
        cout << "EnQueue: Overflow" << endl;
        return;
    }
    count ++;
    cout << "EnQueue: ";
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
        cout << "DeQueue: Underflow" << endl;
        print_forward();
        return;
    }
    count --;
    cout << "DeQueue: ";
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

    count --;
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

int top()
{
    if(head!=nullptr)
    {
        Node * temp = head;
        while (temp!= nullptr && temp->next!= nullptr)
        {
            temp =  temp ->next;

        }
        return temp->data;
    }
}



int main()
{

    cin >> max_size;
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
            insert_back(key);
            break;
        case 2:
            remove_head();
            break;
        case 3:
            if(isempty())
                cout << "isEmpty: True" << endl;
            else
                cout << "isEmpty: False" <<endl;
            break;
        case 4:
            if(isFull())
                cout << "isFull: True" << endl;
            else
                cout << "isFull: False" << endl;
            break;
        case 5:
            cout << "Size: " << count << endl;
            break;
        case 6:
            cout << "Front: " << head->data << endl;
            break;
        case -1:
            return 0;
            break;
        default:
            cout << "Invalid Key" << endl;
            return 0;
        }
    }

    return 0;
}
