#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};


Node* insertBST(Node* root, int val)
{
    if (!root) return new Node(val);
    if (val < root->data) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}


int height(Node* node)
{
    return node ? node->height : 0;
}

int getBalance(Node* node)
{
    return node ? height(node->left) - height(node->right) : 0;
}

Node* rotateRight(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* rotateLeft(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Node* insertAVL(Node* node, int val)
{
    if (!node) return new Node(val);
    if (val < node->data) node->left = insertAVL(node->left, val);
    else if (val > node->data) node->right = insertAVL(node->right, val);
    else return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && val < node->left->data) return rotateRight(node);
    if (balance < -1 && val > node->right->data) return rotateLeft(node);
    if (balance > 1 && val > node->left->data)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && val < node->right->data)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}


int diameter(Node* root, int& diameterVal)
{
    if (!root) return 0;
    int leftHeight = diameter(root->left, diameterVal);
    int rightHeight = diameter(root->right, diameterVal);
    diameterVal = max(diameterVal, leftHeight + rightHeight);
    //cout << "Diameter value = " << diameterVal << " return value = " << 1 + max(leftHeight, rightHeight) << " root value: " << root->data << " left_height= " << leftHeight << " right height = " << rightHeight << endl;
    return 1 + max(leftHeight, rightHeight); //height
}

int calculateDiameter(Node* root)
{
    int diameterVal = 0;
    diameter(root, diameterVal);
    return diameterVal;
}

int main()
{
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    vector<int> nodes(n);
    cout << "Enter node values: ";
    for (int i = 0; i < n; ++i) cin >> nodes[i];


    Node* bstRoot = nullptr;
    for (int val : nodes) bstRoot = insertBST(bstRoot, val);
    cout << "BST " << endl;
    int bstDiameter = calculateDiameter(bstRoot);


    Node* avlRoot = nullptr;
    for (int val : nodes) avlRoot = insertAVL(avlRoot, val);
    cout << "AVL " << endl;
    int avlDiameter = calculateDiameter(avlRoot);

    int difference = abs(bstDiameter - avlDiameter);

    cout << "BST Diameter = " << bstDiameter << endl;
    cout << "AVL Diameter = " << avlDiameter << endl;
    cout << "Difference = " << difference << endl;

    return 0;
}
