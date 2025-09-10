#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
    Node* parent;
    int height;
};

Node* root = NULL;
int is_balance = 1;

int height(Node* x)
{
    return (x == NULL) ? -1 : x->height;
}

void update_height(Node* x)
{
    x->height = 1 + max(height(x->left), height(x->right));
}

int balance_factor(Node* x)
{
    return height(x->left) - height(x->right);
}

Node* right_rotate(Node*& root, Node* z)
{
    Node* y = z->left;
    Node* yR = y->right;

    if (z == root) root = y;

    y->parent = z->parent;
    if (z->parent != NULL)
    {
        if (z == z->parent->right) z->parent->right = y;
        else z->parent->left = y;
    }

    y->right = z;
    z->parent = y;
    z->left = yR;

    if (yR != NULL) yR->parent = z;

    update_height(z);
    update_height(y);

    return y;
}

Node* left_rotate(Node*& root, Node* z)
{
    Node* y = z->right;
    Node* yL = y->left;

    if (z == root) root = y;

    y->parent = z->parent;
    if (z->parent != NULL)
    {
        if (z == z->parent->left) z->parent->left = y;
        else z->parent->right = y;
    }

    y->left = z;
    z->parent = y;
    z->right = yL;

    if (yL != NULL) yL->parent = z;

    update_height(z);
    update_height(y);

    return y;
}

void inorder_with_balance(Node* root);

void balance_node(Node*& root, Node* z)
{
    int b_fact = balance_factor(z);

    if (b_fact > 1)
    {
        inorder_with_balance(root);
        cout << endl;
        if (balance_factor(z->left) >= 0)   // LL Case
        {
            is_balance =  0;
            cout << "Imbalance at node: " << z->data << endl;
            cout << "LL Case" << endl;
            cout << "right_rotate(" << z->data << ")" << endl;
            right_rotate(root, z);
        }
        else     // LR Case
        {
            is_balance =  0;
            cout << "Imbalance at node: " << z->data << endl;
            cout << "LR Case" << endl;
            cout << "left_rotate(" << z->left->data << ")" << endl;
            left_rotate(root, z->left);
            cout << "right_rotate(" << z->data << ")" << endl;
            right_rotate(root, z);
        }
    }
    else if (b_fact < -1)
    {
        inorder_with_balance(root);
        cout << endl;
        if (balance_factor(z->right) <= 0)   // RR Case
        {
            is_balance =  0;
            cout << "Imbalance at node: " << z->data << endl;
            cout << "RR Case" << endl;
            cout << "left_rotate(" << z->data << ")" << endl;
            left_rotate(root, z);
        }
        else     // RL Case
        {
            is_balance =  0;
            cout << "Imbalance at node: " << z->data << endl;
            cout << "RL Case" << endl;
            cout << "right_rotate(" << z->right->data << ")" << endl;
            right_rotate(root, z->right);
            cout << "left_rotate(" << z->data << ")" << endl;
            left_rotate(root, z);
        }
    }
}

Node* insert(Node* root, Node* parent, int key)
{
    if (root == NULL)
    {
        return new Node{key, NULL, NULL, parent, 0};
    }

    if (key < root->data)
    {
        root->left = insert(root->left, root, key);
    }
    else if (key > root->data)
    {
        root->right = insert(root->right, root, key);
    }

    update_height(root);
    int b_fact = balance_factor(root);
    if (b_fact > 1 || b_fact < -1)
    {
        balance_node(root, root);
    }

    return root;
}

void inorder_with_balance(Node* root)
{
    if (root != NULL)
    {
        inorder_with_balance(root->left);
        cout << root->data << "(" << balance_factor(root) << ") ";
        inorder_with_balance(root->right);
    }
}

void insert_key(int key)
{
    root = insert(root, NULL, key);

    if (is_balance)
    {
        inorder_with_balance(root);
        cout << endl;
        cout << "Balanced" << endl;
    }
    else
    {
        cout << "Status: ";
        inorder_with_balance(root);
        cout << endl;
    }
    cout << "Root= " << root->data << endl;
    is_balance = 1;
}

Node * min_value(Node * node)
{
    Node * curr = node;
    while(curr->left != NULL)
    {
        curr = curr->left;
    }
    return curr;
}

Node* avl_delete(Node* root, int key)
{
    if (!root) return root;

    if (key < root->data)
    {
        root->left = avl_delete(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = avl_delete(root->right, key);
    }
    else
    {
        if (!root->left || !root->right)
        {
            Node* temp = root->left ? root->left : root->right;
            if (!temp)
            {
                temp = root;
                root = NULL;
                delete temp;
            }
            else
            {
                root = temp;
                delete temp;
            }
        }
        else
        {
            Node* temp = min_value(root->right);
            root->data = temp->data;
            root->right = avl_delete(root->right, temp->data);
        }
    }

    if (!root) return root;
    update_height(root);
    balance_node(root, root);

    return root;
}

void delete_key(int key)
{
    root = avl_delete(root, key);
    if (is_balance)
    {
        inorder_with_balance(root);
        cout << endl;
        cout << "Balanced" << endl;
    }
    else
    {
        cout << "Status: ";
        inorder_with_balance(root);
        cout << endl;
    }
    cout << "Root= " << (root ? root->data : -1) << endl;
    is_balance = 1;
}

int main()
{
    int n;
    string comm;
    while (true)
    {
        cin >> comm;
        if (comm == "-1") break;
        cin >> n;

        if(comm == "Insert")
        {
            insert_key(n);
        }
        else if (comm == "Delete")
        {
            delete_key(n);
        }
    }
    cout << "Status: ";
    inorder_with_balance(root);
    cout << endl;
    return 0;
}
