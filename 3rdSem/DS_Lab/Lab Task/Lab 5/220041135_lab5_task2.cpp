#include <iostream>
#include <queue>

using namespace std;

struct Node
{
    int data;
    Node * left;
    Node * right;
    Node * parent;
    int height = 0;

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



void inorder_traversal(Node * node)
{
    if(node == nullptr)
        return;
    inorder_traversal(node->left);
    cout << node->data;
    cout << "(";
    if (node->parent!=nullptr)
        cout << node->parent->data;
    else
        cout << "null" ;
    cout << ") ";
    inorder_traversal(node->right);
}

void preorder_traversal(Node * node)
{
    if(node == nullptr)
        return;
    cout << node->data;
    cout << "(";
    if (node->parent!=nullptr)
        cout << node->parent->data;
    else
        cout << "null" ;
    cout << ") ";
    preorder_traversal(node->left);
    preorder_traversal(node->right);
}


void postorder_traversal(Node * node)
{
    if(node == nullptr)
        return;

    postorder_traversal(node->left);
    postorder_traversal(node->right);

    cout << node->data;
    cout << "(";
    if (node->parent!=nullptr)
        cout << node->parent->data;
    else
        cout << "null" ;
    cout << ") ";
}

void level_order(Node *node)
{
    if (node == nullptr)
        return;

    queue<Node *> q;
    q.push(node);
    //cout << "size = " << q.size() << endl;
    int level = 1;

    while (!q.empty())
    {
        int node_count = q.size();
        cout << "node count = " << node_count << endl;
        cout << "Level " << level << ": ";

        while (node_count > 0)
        {
            Node *current = q.front();
            q.pop();
            cout << current->data << "(";
            if (current->parent != nullptr)
                cout << current->parent->data;
            else
                cout << "null";
            cout << ") ";

            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);

            node_count--;
        }

        cout << endl;
        level++;
    }
}


int main()
{
    int n, number, command, key;
    cin >> n;
    int i;
    for(i=0; i<n; i++)
    {
        cin >> number;
        insert_node(number);
    }
    while(true)
    {
        cin >> command;
        if (command == 1)
        {
            inorder_traversal(tree_root);
            cout << endl;
        }
        else if (command == 2)
        {
            preorder_traversal(tree_root);
            cout << endl;
        }

        else if (command == 3)
        {
            postorder_traversal(tree_root);
            cout << endl;
        }
        else if (command == 4)
        {
            level_order(tree_root);
            cout << endl;
        }

    }


    return 0;
}
