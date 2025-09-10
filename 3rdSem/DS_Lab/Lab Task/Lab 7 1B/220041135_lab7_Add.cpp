#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    int height;
};

Node* root = nullptr;

int height(Node* x) {
    if (x == nullptr) return -1;
    return x->height;
}

void update_height(Node* x) {
    x->height = 1 + max(height(x->left), height(x->right));
}

int balance_factor(Node* x) {
    return height(x->left) - height(x->right);
}

void update_ancestor_heights(Node* z) {
    Node* temp = z;
    while (temp != nullptr) {
        update_height(temp);
        temp = temp->parent;
    }
}

Node* find_max(Node* root) {
    while (root->right != nullptr)
        root = root->right;
    return root;
}

Node* find_min(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

Node* find_predecessor(Node* root, int key) {
    Node* pred = nullptr;
    while (root) {
        if (key > root->data) {
            pred = root;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return pred;
}

Node* find_successor(Node* root, int key) {
    Node* succ = nullptr;
    while (root) {
        if (key < root->data) {
            succ = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return succ;
}

void right_rotate(Node*& root, Node* z) {
    Node* y = z->left;
    Node* yR = y->right;

    if (z == root) root = y;

    y->parent = z->parent;
    if (z->parent != nullptr) {
        if (z == z->parent->right) z->parent->right = y;
        else z->parent->left = y;
    }

    y->right = z;
    z->parent = y;
    z->left = yR;

    if (yR != nullptr) yR->parent = z;

    update_ancestor_heights(z);
}

void left_rotate(Node*& root, Node* z) {
    Node* y = z->right;
    Node* yL = y->left;

    if (z == root) root = y;

    y->parent = z->parent;
    if (z->parent != nullptr) {
        if (z == z->parent->left) z->parent->left = y;
        else z->parent->right = y;
    }

    y->left = z;
    z->parent = y;
    z->right = yL;

    if (yL != nullptr) yL->parent = z;

    update_ancestor_heights(z);
}

void balance_node(Node*& root, Node* z) {
    int b_fact = balance_factor(z);

    if (b_fact > 1) {
        if (balance_factor(z->left) >= 0) {
            right_rotate(root, z);
        } else {
            left_rotate(root, z->left);
            right_rotate(root, z);
        }
    } else if (b_fact < -1) {
        if (balance_factor(z->right) <= 0) {
            left_rotate(root, z);
        } else {
            right_rotate(root, z->right);
            left_rotate(root, z);
        }
    }
}

Node* insert(Node* root, Node* parent, int key) {
    if (root == nullptr) {
        Node* newNode = new Node{key, nullptr, nullptr, parent, 0};
        return newNode;
    }

    if (key < root->data) {
        root->left = insert(root->left, root, key);
    } else if (key > root->data) {
        root->right = insert(root->right, root, key);
    }

    update_height(root);
    int b_fact = balance_factor(root);
    if (b_fact > 1 || b_fact < -1) {
        balance_node(root, root);
    }

    return root;
}

void insert_key(int key) {
    Node* pred = find_predecessor(root, key);
    Node* succ = find_successor(root, key);
    root = insert(root, nullptr, key);

    cout << "Inserted " << key << ": ";
    if (pred) cout << "Before: " << pred->data << " ";
    else cout << "Before: None ";

    if (succ) cout << "After: " << succ->data;
    else cout << "After: None";
    cout << endl;
}

int main() {
    int n = 0;
    while (true) {
        cin >> n;
        if (n == -1) break;
        insert_key(n);
    }
    return 0;
}
