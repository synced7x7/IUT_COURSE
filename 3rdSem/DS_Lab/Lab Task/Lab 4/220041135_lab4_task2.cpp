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

void reverse_print()
{
    if (tail == nullptr)
    {
        cout << "List is empty" << endl;
        return;
    }

    cout << "Reverse print: ";
    Node *temp1 = tail;


    while (temp1 != nullptr)
    {
        cout << temp1->data << " ";
        temp1 = temp1->prev;
    }

    cout << endl;
}

void print_forward()
{
    if (head == nullptr)
    {
        cout << "EMPTY" << endl;
        cout << "NULL (HEAD) (TAIL)" << endl;
        return;
    }
    cout << head->data << " " << "(HEAD) ";


    Node *temp = head;
    temp = temp->next;
    while (temp != nullptr)
    {
        cout << "-> ";
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "(TAIL)";
    cout << endl;
    //reverse_print();
}

void insert_front(int key)
{
    if (head == nullptr)
    {
        Node *new_node = create_new_node(key);
        head = new_node;
        tail = new_node;
        print_forward();
        return;
    }
    // if not empty
    Node *new_node = create_new_node(key);
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
    print_forward();
}

void insert_back(int key) //2cases
{
    if (head == nullptr)//if empty
    {
        Node * new_node = create_new_node(key);
        head = new_node;
        tail = new_node;
        print_forward();
        return;
    }
    //if not empty
    Node * new_node = create_new_node(key);
    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;
    print_forward();
}

void Insert_after_node(int key, int v)
{
    Node *new_node = create_new_node(key);
    Node *temp = head;

    while (temp != nullptr)
    {
        if (temp->data == v)
        {
            new_node->next = temp->next;
            if (temp->next != nullptr)
            {
                temp->next->prev = new_node;
            }
            else
            {
                tail = new_node;
            }
            new_node->prev = temp;
            temp->next = new_node;
            print_forward();
            return;
        }
        temp = temp->next;
    }


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
        //cout << "Underflow" << endl;
        print_forward();
        return;
    }

    if(head->next == nullptr) // if one element is present
    {
        delete head;
        head=nullptr;
        tail=nullptr;
        print_forward();
        return;
    }

    Node* temp = head;
    head = head->next;
    head->prev = nullptr;
    delete temp;

    print_forward();
}

void remove_element(int key)
{
    if (head == nullptr) //no element present
    {
        cout << "Value not found" << endl;
        print_forward();
        return;
    }

    if (head->data == key) //if first element is the key
    {
        remove_head();
        return;
    }

    Node * temp = head;
    while (temp != nullptr)
    {
        if (temp->data == key) // if found
        {
            temp->prev->next = temp->next;
            if(temp->next !=nullptr)//if not the last element
                temp->next->prev = temp->prev;
            if (temp == tail)//if its the last element we have to set tail to its previous value
            {
                tail = temp->prev;
            }
            delete temp;
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
    Node * temp = tail;
    tail = tail->prev;
    tail->next=nullptr;
    delete temp;
    print_forward();
}

int main()
{
    while (true)
    {
        string command;
        cin >> command;
        cin.ignore();
        int key, v;
        if (command == "INSERT_FRONT" )
        {
            cin >> key;
            insert_front(key);
        }
        else if (command == "INSERT_BACK" )
        {
            cin >> key;
            insert_back(key);
        }
        else if (command == "INSERT_AFTER" )
        {
            cin >> key >> v;
            Insert_after_node(key, v);
        }
        else if (command == "UPDATE" )
        {
           cin >> key >> v;
            Update_node(key, v);
        }
        else if (command == "REMOVE_HEAD" )
        {
           remove_head();
        }
        else if (command ==  "REMOVE" )
        {
           cin >> key;
            remove_element(key);
        }
        else if (command ==  "REMOVE_END" )
        {
            Remove_end();
        }
        else if (command == "EXIT")
        {
            return 0;
        }
    }

    return 0;
}
