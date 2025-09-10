#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
    Node* parent;
    int height;
};

struct RBNode
{
    int data;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    char color;
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

void balance_node(Node*& root, Node* z)
{
    int b_fact = balance_factor(z);

    if (b_fact > 1)
    {
        if (balance_factor(z->left) >= 0)   // LL Case
        {
            right_rotate(root, z);
        }
        else     // LR Case
        {
            left_rotate(root, z->left);
            right_rotate(root, z);
        }
    }
    else if (b_fact < -1)
    {
        if (balance_factor(z->right) <= 0)   // RR Case
        {
            left_rotate(root, z);
        }
        else     // RL Case
        {
            right_rotate(root, z->right);
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
}

RBNode* convert_to_rb(Node* avlNode, RBNode* parent, char color)
{
    if (!avlNode) return nullptr;


    RBNode* rbNode = new RBNode{avlNode->data, nullptr, nullptr, parent, color};


    if (rbNode->parent == nullptr)
    {
        rbNode->color = 'B';
    }
    else if (rbNode->parent->color == 'B')
    {
        rbNode->color = 'R';
    }
    else
    {
        rbNode->color = 'B';
    }

    //cout << "RB Node data = " << rbNode->data << ", Color = " << rbNode->color << endl;
    rbNode->left = convert_to_rb(avlNode->left, rbNode, rbNode->color);
    rbNode->right = convert_to_rb(avlNode->right, rbNode, rbNode->color);

    return rbNode;
}



void level_order_rb(RBNode * root)
{
    if (!root) return;

    queue<RBNode*> q;
    q.push(root);

    while (!q.empty())
    {
        RBNode* node = q.front();
        q.pop();

        cout << "(" << node->data << "," << node->color << ") ";

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
    cout << endl;
}

int main()
{
    string line;
    getline(cin, line);
    stringstream ss(line);
    int n;
    while (ss >> n)
    {
        insert_key(n);
    }

    RBNode* rbRoot = convert_to_rb(root, nullptr, 'B');
    level_order_rb(rbRoot);

    return 0;
}
