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

    Node(int key) : data(key), left(NULL), right(NULL), parent(NULL), height(0) {}
};
void inorder_traversal(Node* node);

Node* tree_root = NULL;

int get_height(Node* node)
{
    return (node == NULL) ? -1 : node->height;
}

int balance_factor(Node* node)
{
    return get_height(node->left) - get_height(node->right);
}

void update_ancestor_height(Node* current)
{
    while (current != NULL)
    {
        current->height = 1 + max(get_height(current->left), get_height(current->right));
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
        //cout << "Number = " << temp->data << " Balance Factor = " << bFact << endl;
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
    cout << "Data = ";
    cout << node->data << endl;
    cout << "Balance factor = " ;
    cout << "(" << balance_factor(node) << ") ";
    cout << "Height = " << node->height << " ";
    cout << endl;
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

int main()
{
    int n;
    while(true)
    {
        cin >> n;
        if(n==-1)
            break;
        insert_node(n);
        inorder_traversal(tree_root);
        cout << endl;
    }

    return 0;
}
