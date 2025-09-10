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

void print_forward()
{
    if (head == nullptr)
    {
        cout << "EMPTY" << endl;
        //cout << "NULL (HEAD) (TAIL)" << endl;
        return;
    }
    //cout << head->data << " " << "(HEAD) ";


    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
    //reverse_print();
}

Node *create_new_node(int key)
{
    Node *new_node = new Node();
    new_node->data = key;
    new_node->next = nullptr;
    new_node->prev = nullptr;
    return new_node;
}

void Push_front(int key)
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

void Push_back(int key)
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

void Pop_front()
{
    if (head == nullptr) // if no element is present
    {
        cout << "Underflow" << endl;
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

void Pop_back()
{
    if (head == nullptr) // if no element is present
    {
        cout << "Underflow" << endl;
        print_forward();
        return;
    }

    if (head->next == nullptr) // if only one element is present
    {
        Pop_front();
        return;
    }

    // if more than one element is present
    Node * temp = tail;
    tail = tail->prev;
    tail->next=nullptr;
    delete temp;
    print_forward();
}

void count_size()
{
    Node * temp = head;
    int count=0;
    while(temp!=nullptr)
    {
        temp = temp->next;
        count++;
    }
    cout << count <<endl;
}


int main()
{
    int n, key;
    while (true)
    {
        cin>>n;
        if(n==1)
        {
            cin >> key;
            Push_front(key);
        }
        else if (n==2)
        {
            cin >> key;
            Push_back(key);
        }
        else if (n==3)
        {
            Pop_front();
        }
        else if (n==4)
        {
            Pop_back();
        }
        else if (n==5)
            count_size();
        else if (n==6)
            break;

    }


	return 0;
}
