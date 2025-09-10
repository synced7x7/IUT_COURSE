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
    int size; // New attribute to keep track of subtree size
};

Node* root = nullptr;

int height(Node* x)
{
    return (x == nullptr) ? -1 : x->height;
}

int subtree_size(Node* x)
{
    return (x == nullptr) ? 0 : x->size;
}

void update_height_and_size(Node* x)
{
    x->height = 1 + max(height(x->left), height(x->right));
    x->size = 1 + subtree_size(x->left) + subtree_size(x->right);
    cout << "x->data = " << x->data << " x_size = " << x->size << endl;
}

int balance_factor(Node* x)
{
    return height(x->left) - height(x->right);
}

void right_rotate(Node*& root, Node* z)
{
    Node* y = z->left;
    Node* yR = y->right;

    if (z == root) root = y;

    y->parent = z->parent;
    if (z->parent != nullptr)
    {
        if (z == z->parent->right) z->parent->right = y;
        else z->parent->left = y;
    }

    y->right = z;
    z->parent = y;
    z->left = yR;

    if (yR != nullptr) yR->parent = z;

    update_height_and_size(z);
    update_height_and_size(y);
}

void left_rotate(Node*& root, Node* z)
{
    Node* y = z->right;
    Node* yL = y->left;

    if (z == root) root = y;

    y->parent = z->parent;
    if (z->parent != nullptr)
    {
        if (z == z->parent->left) z->parent->left = y;
        else z->parent->right = y;
    }

    y->left = z;
    z->parent = y;
    z->right = yL;

    if (yL != nullptr) yL->parent = z;

    update_height_and_size(z);
    update_height_and_size(y);
}

void balance_node(Node*& root, Node* z)
{
    int b_fact = balance_factor(z);

    if (b_fact > 1)
    {
        if (balance_factor(z->left) >= 0)   // LL Case
        {
            cout << "Imbalance at node: " << z->data << endl;
            cout << "LL Case" << endl;
            cout << "right_rotate(" << z->data << ")" << endl;
            right_rotate(root, z);
        }
        else     // LR Case
        {
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
        if (balance_factor(z->right) <= 0)   // RR Case
        {
            cout << "Imbalance at node: " << z->data << endl;
            cout << "RR Case" << endl;
            cout << "left_rotate(" << z->data << ")" << endl;
            left_rotate(root, z);
        }
        else     // RL Case
        {
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
    if (root == nullptr)
    {
        return new Node{key, nullptr, nullptr, parent, 0, 1};
    }

    if (key < root->data)
    {
        root->left = insert(root->left, root, key);
    }
    else if (key > root->data)
    {
        root->right = insert(root->right, root, key);
    }

    update_height_and_size(root);
    int b_fact = balance_factor(root);
    if (b_fact > 1 || b_fact < -1)
    {
        balance_node(root, root);
    }

    return root;
}

void insert_key(int key)
{
    root = insert(root, nullptr, key);
}

int lowerCount(Node* root, int query)
{
    int count = 0;
    Node* current = root;

    while (current != nullptr)
    {
        if (query > current->data)
        {
            //cout << current->data << " ";

            count += 1 + subtree_size(current->left);
            cout << "Count= " <<  count << endl;
            current = current->right;
        }
        else // if query == root or less than root
        {
            current = current->left;
        }
    }
    return count;
}

void inorder_with_balance(Node* root)
{
    if (root != nullptr)
    {
        inorder_with_balance(root->left);
        cout << root->data << "(" << balance_factor(root) << ") ";
        inorder_with_balance(root->right);
    }
}

int main()
{
    int n = 0;
    while (true)
    {
        cin >> n;
        if (n == -1) break;
        insert_key(n);
    }

    int query;
    cout << "Enter query numbers (end with -1): " << endl;
    while (true)
    {
        cin >> query;
        if (query == -1) break;
        int count = lowerCount(root, query);
        cout << "Count of numbers less than " << query << ": " << count << endl;
    }

    cout << "Final Tree (Inorder with Balance Factor): ";
    inorder_with_balance(root);
    cout << endl;

    return 0;
}
