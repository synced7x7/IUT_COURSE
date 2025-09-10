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

Node * tree_root = NULL;

Node* create(int key)
{
    Node* new_node = new Node();
    new_node->data = key;
    new_node->left = new_node->right = new_node->parent = NULL;
    return new_node;
}

void insert_node(int key) //O(h)
{
    Node * new_node = create(key);
    if(tree_root == NULL)
    {
        tree_root = new_node;
        return;
    }
    Node* temp = tree_root;
    Node * target = NULL;
    while(temp!= NULL)//setting child
    {
        target = temp;
        if(new_node->data < target->data)
            temp = temp->left;
        else
            temp = temp->right;
    }
    new_node->parent = target; // setting parent
    if(new_node->data < target->data)
        target->left = new_node;
    else
        target->right = new_node;

    //height tracker
    Node * current = target;
    while(current != NULL)
    {
        int left_height = (current->left)? current->left->height: -1;
        int right_height = (current->right)? current->right->height: -1;
        current->height = 1 + max(left_height, right_height);
        current = current->parent;
    }
}

void inorder_traversal(Node* node) //O(h)
{
    cout << "Inorder : " << endl;
    if(node == NULL)
        return;
    inorder_traversal(node->left);
    cout << node->data << " ";
    inorder_traversal(node->right);
}

Node* tree_search(int key)
{
    Node* node = tree_root;
    while (node!= NULL && node->data!= key)
    {
        if(key< node->data)
            node= node->left;
        else
            node = node->right;
    }
    return node;
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

Node* find_min(Node * node) //O(h)
{
    Node*temp = node;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}

Node* find_max(Node * node)//O(h)
{
    Node*temp = node;
    while (temp->right != NULL)
        temp = temp->right;
    return temp;
}

void level_order()
{
    cout << "Level Order: " << endl;
    Node * curr = NULL;
    queue <Node*> q;
    q.push(tree_root);
    while(!q.empty())
    {
        curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if(curr ->left !=NULL)
            q.push(curr->left);
        else
            q.push(curr->right);
    }
}

void transplant(Node * u, Node* v)
{
    if(u->parent == NULL)
        tree_root = v;
    else if (u== u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if(v!=NULL)
        v->parent = u->parent;
}

void tree_delete(int key)
{
    Node* z = tree_search(key);
    if(z->left == NULL) //1st case: no left child
        transplant(z, z->right);
    else if(z->right == NULL)  //2nd case: no right child
        transplant(z, z->right);
    else
        Node * y = find_min(z->right);
    if (y->parent != z)
    {
        transplant(y, y->right);
        y->right = z->right;
        z->right->parent = y;
    }
}

int height_of_node(int key) //use height tracker //more effecient
{
    Node* node = tree_search(key);
    if(node == NULL)
    {
        cout << "Node Not found" << endl;
        return -1;
    }
    return node->height;
}




int main()
{

    return 0;
}
