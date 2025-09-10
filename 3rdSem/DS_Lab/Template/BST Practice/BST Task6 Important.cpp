#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data, height;
    Node* left;
    Node* right;
    Node(int val) : data(val), height(0), left(NULL), right(NULL) {}
};

// Insert into BST and update height efficiently
Node* insert(Node* root, int val) {
    if (!root) return new Node(val);

    if (val < root->data) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);

    root->height = 1 + max(root->left ? root->left->height : -1,
                           root->right ? root->right->height : -1);
    return root;
}

// Inorder traversal to print tree status
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << "(" << root->height << ") ";
    inorder(root->right);
}

// Find LCA in BST
Node* LCA_finder(Node* root, int u, int v) {
    if (!root) return NULL;
    if (u < root->data && v < root->data) return LCA_finder(root->left, u, v);
    if (u > root->data && v > root->data) return LCA_finder(root->right, u, v);
    return root;
}

// Find path from a given node to a target
void findPath(Node* root, int target, vector<int>& path) {
    Node* temp = root;
    while (temp && temp->data != target) {
        path.push_back(temp->data);
        if (target < temp->data) temp = temp->left;
        else temp = temp->right;
    }
    if (temp) path.push_back(temp->data); // Add target node
}

// Print path between two nodes
void printPath(Node* root, int u, int v) {
    Node* lca = LCA_finder(root, u, v);

    vector<int> path1, path2;
    findPath(lca, u, path1);
    findPath(lca, v, path2);

    // Print the combined path
    for (int i = path1.size() - 1; i >= 0; i--) cout << path1[i] << " ";
    for (int i = 1; i < path2.size(); i++) cout << path2[i] << " ";

    cout << endl << "Path Length: " << path1.size() + path2.size() - 1 << endl;
}

int main() {
    int number;
    Node* root = NULL;

    // Insertion
    while (true) {
        cin >> number;
        if (number == -1) break;
        root = insert(root, number);
    }

    // Print tree status
    cout << "Status: ";
    inorder(root);
    cout << endl;

    // Process queries
    int u, v;
    while (cin >> u >> v) {
        printPath(root, u, v);
    }

    return 0;
}
