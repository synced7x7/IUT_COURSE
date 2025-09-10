#include <iostream>

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
    while (current != nullptr)
    {

        int left_height = (current->left) ? current->left->height : -1; // Height of left child
        //cout << "  ||Left height = " << left_height;

        int right_height = (current->right) ? current->right->height : -1; // Height of right child
        //cout << "  ||  Right height = " << right_height;
        current->height = 1 + std::max(left_height, right_height); // Update current node's height

        //cout << " ||  Current data = " << current->data;
        //if (current->left != nullptr)
            //cout << "||  Current left = " << current->left->data;
        //if(current->right!=nullptr)
            //cout << "||  Current right = " << current->right->data;


        current = current->parent; // Move up to parent
       // cout << "  ||  Current height = " << 1 + std::max(left_height, right_height) << endl;
    }
}



void inorder_traversal(Node * node)
{
    if(node == nullptr)
        return;
    inorder_traversal(node->left);
    cout<< node->data << " ";
    inorder_traversal(node->right);
}

void inorder_traversal_before_after(Node* node, int key, Node*& before, Node*& after, Node*& target)
{
    if (node == nullptr)//whether i have reached the end of the node
        return;

    inorder_traversal_before_after(node->left, key, before, after, target);
    if (target != nullptr && after == nullptr)
    {
        after = node;
        return;
    }


    if (node->data == key)
    {
        target = node;
    }
    else if (target == nullptr)
    {
        before = node;
    }


    inorder_traversal_before_after(node->right, key, before, after, target);
}


void print_before_after(int key)
{
    Node* before = nullptr;
    Node* after = nullptr;
    Node* target = nullptr;

    inorder_traversal_before_after(tree_root, key, before, after, target);

    if (target == nullptr)
    {
        cout << "Node with key " << key << " not found." << endl;
    }
    else
    {
        if (before != nullptr)
            cout << before->data << " ";
        else
            cout << "Null ";

        if (after != nullptr)
            cout << after->data << " " << endl;
        else
            cout << "Null" << endl;
    }
}



Node * search_node(int key)
{
    Node * temp = tree_root;
    while (temp != nullptr && temp->data != key)
    {
        if (key < temp->data)
        {
            temp = temp->left;
        }
        else
            temp = temp->right;

    }
    return temp;
}

int height_of_node(int key)
{
    Node *node = search_node(key);
    if (node == nullptr)
    {
        cout << "Node not found." << endl;
        return -1;
    }
    return node->height;
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
    inorder_traversal(tree_root);
    cout << endl;
    while(true)
    {
        cin >> command;
        if (command == 3)
        {
            cin >> key;
            Node * current = search_node(key);
            if (current == nullptr)
                cout << "Not present" << endl;
            else
            {
                cout << "Present" << endl;
                if (current->parent == nullptr)
                    cout << "Parent (Null), ";
                else
                    cout << "Parent (" << current->parent->data << "), ";

                if (current->left == nullptr)
                    cout << "Left (Null), ";
                else
                    cout << "Left (" << current->left->data << "), ";

                if (current->right == nullptr)
                    cout << "Right (Null)" << endl;
                else
                    cout << "Right (" << current->right->data << ")" << endl;
            }

        }
        else if (command == 4)
        {
            cin >> key;
            cout << height_of_node(key) << endl;

        }
        else
        {
            cin >> key;
            print_before_after(key);

        }
    }


    return 0;
}
