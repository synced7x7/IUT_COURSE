#include <iostream>
#include <queue>

using namespace std;

struct Node
{
    int data;
    Node * left;
    Node * right;
    Node * parent;

};

Node * tree_root = nullptr;

Node * create_node(int key)
{
    Node * new_node = new Node();
    new_node->data = key;
    new_node->left = new_node->right = new_node->parent = nullptr;

    return new_node;
}

void insert_node(int key)
{
    Node * new_node = create_node(key);
    Node * temp = tree_root;
    Node * target = nullptr;
    if(temp == nullptr)
    {
        tree_root = new_node; //if no element is present in the tree
        return;
    }

    while(temp!=nullptr)
    {
        target = temp;
        if (new_node->data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    new_node->parent = target;
    if(new_node->data > target->data)
        target->right = new_node;
    else
        target->left = new_node;

    Node *current = target;

}

Node * search_node(int key)
{
    Node * temp = tree_root;
    while (temp != nullptr && temp->data != key)
    {
        if (key < temp->data)
        {
            temp = temp->left;
        }
        else
            temp = temp->right;

    }
    return temp;
}



int main()
{
    int n, number;
    cin >> n;
    for(int i=0; i< n; i++)
    {
        cin >> number;
        insert_node(number);
    }
    int q, q1, q2;
    cin >> q;
    for(int i=0; i<q; i++)
    {
        cin >> q1 >> q2;
        Node * node1 = search_node(q1);
        Node * node2 = search_node(q2);
        if(node1->parent->data==node2->parent->data)
        {
            cout << node1->parent->data << endl;
        }

    }


    return 0;
}
