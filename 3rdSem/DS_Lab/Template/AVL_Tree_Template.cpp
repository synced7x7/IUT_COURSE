#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
    Node* parent;
    int height;
    int size;

    Node(int key) : data(key), left(NULL), right(NULL), parent(NULL), height(0), size(1) {}
};

Node* tree_root = NULL;

void print_before_after(int key);

int get_height(Node* node)
{
    return (node == NULL) ? -1 : node->height;
}

int balance_factor(Node* node)
{
    return (node == NULL) ? 0 : get_height(node->left) - get_height(node->right);
}
int subtree_size(Node* x)
{
    return (x == nullptr) ? 0 : x->size;
}

void update_ancestor_height(Node* current)
{
    while (current != NULL)
    {
        current->height = 1 + max(get_height(current->left), get_height(current->right));
        current->size = 1 + subtree_size(current->left) + subtree_size(current->right);
        current = current->parent;
    }
}

void left_rotate(Node* z)
{
    Node* y = z->right;
    Node* yL = y->left;

    if (z == tree_root) tree_root = y;

    y->parent = z->parent;
    if (z->parent)
    {
        if (z == z->parent->left) z->parent->left = y;
        else z->parent->right = y;
    }

    y->left = z;
    z->parent = y;
    z->right = yL;
    if (yL) yL->parent = z;

    update_ancestor_height(z);
}

void right_rotate(Node* z)
{
    Node* y = z->left;
    Node* yR = y->right;

    if (z == tree_root) tree_root = y;

    y->parent = z->parent;
    if (z->parent)
    {
        if (z == z->parent->left) z->parent->left = y;
        else z->parent->right = y;
    }

    y->right = z;
    z->parent = y;
    z->left = yR;
    if (yR) yR->parent = z;

    update_ancestor_height(z);
}

void balance_node(Node* z)
{
    int bFact = balance_factor(z);

    if (bFact > 1)   // Left Heavy
    {
        if (balance_factor(z->left) >= 0)   // LL case
        {
            right_rotate(z);
        }
        else     // LR case
        {
            left_rotate(z->left);
            right_rotate(z);
        }
    }
    else if (bFact < -1)     // Right Heavy
    {
        if (balance_factor(z->right) <= 0)   // RR case
        {
            left_rotate(z);
        }
        else     // RL case
        {
            right_rotate(z->right);
            left_rotate(z);
        }
    }
}

void insert_node(int key)
{
    Node* new_node = new Node(key);
    if (tree_root == NULL)
    {
        tree_root = new_node;
        return;
    }

    Node* temp = tree_root;
    Node* target = NULL;
    while (temp != NULL)
    {
        target = temp;
        if (key < temp->data) temp = temp->left;
        else temp = temp->right;
    }

    new_node->parent = target;
    if (key < target->data) target->left = new_node;
    else target->right = new_node;

    update_ancestor_height(new_node);

    temp = new_node;
    while (temp != NULL)
    {
        int bFact = balance_factor(temp);
        if (bFact > 1 || bFact < -1)
        {
            balance_node(temp);
            break;
        }
        temp = temp->parent;
    }
}

void inorder_traversal(Node* node)
{
    if (node == NULL) return;
    inorder_traversal(node->left);
    cout << endl;
    cout << node->data << " ----- ";
    cout << "Balance = (" << balance_factor(node) << ") ";
    cout << "Height = (" << node->height << ") ";
    cout << "Size = (" << node->size << ") ";
    inorder_traversal(node->right);
}

Node* tree_search(int key)
{
    Node* node = tree_root;
    while (node != NULL && node->data != key)
    {
        node = (key < node->data) ? node->left : node->right;
    }
    return node;
}

void level_order()
{
    if (tree_root == NULL) return;

    queue<Node*> q;
    q.push(tree_root);

    while (!q.empty())
    {
        Node* curr = q.front();
        q.pop();

        cout << curr->data << " ";

        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

int height_of_node(int key)
{
    Node* node = tree_search(key);
    return (node == NULL) ? -1 : node->height;
}

Node* find_min(Node* node)
{
    while (node->left != NULL)
        node = node->left;
    return node;
}

void delete_node(int key)
{
    Node* node = tree_search(key);
    if (node == NULL) return;

    Node* to_balance = NULL;

    if (node->left == NULL || node->right == NULL)
    {
        Node* child = (node->left) ? node->left : node->right;

        if (node == tree_root)
            tree_root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;

        if (child) child->parent = node->parent;
        to_balance = node->parent;
        delete node;
    }
    else
    {
        Node* successor = find_min(node->right);
        node->data = successor->data;

        if (successor == node->right)
            node->right = successor->right;
        else
            successor->parent->left = successor->right;

        if (successor->right)
            successor->right->parent = successor->parent;

        to_balance = successor->parent;
        delete successor;
    }

    while (to_balance != NULL)
    {
        update_ancestor_height(to_balance);
        balance_node(to_balance);
        to_balance = to_balance->parent;
    }
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


void printTree()
{
    cout << "Inorder Traversal: ";
    inorder_traversal(tree_root);
    cout << endl;
    cout << "Tree root = " << tree_root->data;
    cout << endl;
    cout << endl;
    cout << endl;
}
int main()
{
    insert_node(12);
    insert_node(9);
    insert_node(5);
    insert_node(11);
    insert_node(20);
    insert_node(15);
    insert_node(7);
    insert_node(3);
    insert_node(6);
    insert_node(27);
    printTree();
    lowerCount(tree_root, 3);
    delete_node(20);
    printTree();
    delete_node(15);
    printTree();

//    cout << "Level Order Traversal: ";
//    level_order();
//    cout << endl;

    return 0;
}


void before_after(Node* node, int key, Node* &before, Node* & after, Node* & target)
{
    if(node == NULL)
        return;
    before_after(node->left, key, before, after, target);

    if (target!= NULL && after == NULL)
        after = node;
    if(node->data == key)
        target = node;
    else if(target!= NULL)
        before = node;

    before_after(node->right, key, before, after, target);
}

void print_before_after(int key)
{
    Node * before = NULL;
    Node * after = NULL;
    Node * target = NULL;
    before_after(tree_root, key, before, after, target);

    if(target == NULL)
        cout << "Target not found" << endl;
    else
    {
        if(before == NULL)
            cout << "Before is null." << endl;
        else
            cout << "Before: " << before->data << endl;
        if(after == NULL)
            cout << "After is null" << endl;
        else
            cout << "After: " << after->data << endl;
    }
}
