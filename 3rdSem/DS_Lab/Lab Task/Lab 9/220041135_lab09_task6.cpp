#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
int count =0;
struct TrieNode
{
    TrieNode* childNode[10];
    int wordCount;

    TrieNode()
    {
        wordCount = 0;
        for (int i = 0; i < 10; i++)
        {
            childNode[i] = NULL;
        }
    }
};

TrieNode* root = new TrieNode();

void insert_key(TrieNode* root, string& key)
{
    TrieNode* currentNode = root;

    for (auto c : key)
    {

        if (currentNode->childNode[c - '0'] == NULL)
        {
            TrieNode* newNode = new TrieNode();
            currentNode->childNode[c - '0'] = newNode;
        }
        currentNode = currentNode->childNode[c - '0'];
    }
    currentNode->wordCount++;
}

bool search_key(TrieNode* root, string & key)
{
    TrieNode* currentNode = root;

    for (auto c : key)
    {
        if (currentNode->childNode[c-'0'] == NULL)
        {
            return false;
        }
        currentNode = currentNode->childNode[c - '0'];
    }
    return (currentNode->wordCount > 0);
}

bool isPrefixExist(TrieNode* root, string& key)
{
    TrieNode* currentNode = root;
    for (auto c : key)
    {
        //cout << "Current character: " << c <<endl;
        if (currentNode->childNode[c - '0'] == NULL)
        {
            //cout << c << " not present\n";
            return false;
        }
        currentNode = currentNode->childNode[c - '0'];
        count ++;
    }
    return true;
}

void display(TrieNode* root, char str[], int level)
{
    // If the current node is an end of a word, print the word
    if (root->wordCount > 0)
    {
        str[level] = '\0';
        cout << str << " ";
    }
    for (int i = 0; i < 10; i++)
    {
        if (root->childNode[i] != NULL)
        {
            str[level] = i + '0';
            display(root->childNode[i], str, level + 1);
        }
    }
}


void clear_trie(TrieNode* root)
{
    if (root == NULL) return;

    // Recursively delete all child nodes
    for (int i = 0; i < 10; i++)
    {
        if (root->childNode[i] != NULL)
        {
            clear_trie(root->childNode[i]);
        }
    }

    // Delete the current node
    delete root;
}

int main()
{
    int l1, l2;
    cin >> l1 >> l2;
    string arr1[l1];
    string arr2[l2];
    for(int i=0; i< l1; i++)
    {
        cin >> arr1[i];
    }
    for(int i=0; i<l2; i++)
    {
        cin >> arr2[i];
    }
    int max_count = -1;
    for(int i=0; i<l1; i++)
    {
        //root = new TrieNode();
        insert_key(root, arr1[i]);
        for(int j=0; j<l2; j++)
        {
            isPrefixExist(root, arr2[j]);
            if(count>max_count)
                max_count = count;
            count = 0;
        }
//        clear_trie(root);
//        root = NULL;
    }
    cout << max_count << endl;


    return 0;
}
