#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
int totalWords = 0;

struct TrieNode
{
    TrieNode *children[26];
    int wordCount;
};

// Function to create a new Trie node
TrieNode *createNode()
{
    TrieNode *node = new TrieNode;
    node->wordCount = 0;

    for (int i = 0; i < 26; i++)
    {
        node->children[i] = nullptr;
    }
    return node;
}

// Function to insert a key into the Trie
void insert(TrieNode *root, const string &key)
{
    TrieNode *curr = root;
    for (char c : key)
    {
        if (curr->children[c - 'a'] == nullptr)
        {
            curr->children[c - 'a'] = createNode();
        }
        curr = curr->children[c - 'a'];
    }
    curr->wordCount++;
}

// Function to search for a key in the Trie
int search(TrieNode *root, const string &key)
{
    if (root == nullptr)
        return 0;
    TrieNode *curr = root;
    for (char c : key)
    {
        if (curr->children[c - 'a'] == nullptr)
            return false;
        curr = curr->children[c - 'a'];
    }
    return curr->wordCount;
}

// Function to check if a node has children
bool hasChildren(TrieNode *node)
{
    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != nullptr)
        {
            return true;
        }
    }
    return false;
}


bool deleteKey(TrieNode *root, const string &key, int depth = 0)
{
    if (!root)
        return false;

    if (depth == key.size())
    {
        if (!root->wordCount)
            return false;
        root->wordCount--;
        return !hasChildren(root);
    }

    int index = key[depth] - 'a';
    if (!deleteKey(root->children[index], key, depth + 1))
        return false;

    delete root->children[index];
    root->children[index] = nullptr;
    return !root->wordCount && !hasChildren(root);
}

// Function to display words in the Trie
void display(TrieNode *root, char str[], int level)
{
    if (root->wordCount)
    {
        str[level] = '\0';
        cout << str << " ";
        cout << "|| word count = " << root->wordCount << endl;
        totalWords ++;
    }
    for (int i = 0; i < 26; i++)
    {
        if (root->children[i] != NULL)
        {
            str[level] = i + 'a';
            display(root->children[i], str, level + 1);
        }
    }
}

int searchPrefix(TrieNode *root, const string &key)
{
    TrieNode *curr = root;
    int level = 0;
    char str[100] = {0};
    for (char c : key)
    {
        cout << "c= " << c << endl;
        if (curr->children[c - 'a'] == nullptr)
        {
            cout << "No words present under the prefix" << endl;
            return 0;
        }
        str[level++] = c; // Store the prefix
        curr = curr->children[c - 'a'];
    }

    display(curr, str, level);
    return 1;
}

/* int search(TrieNode *root, const string &key)
{
    if (root == nullptr)
        return false;
    TrieNode *curr = root;
    for (char c : key)
    {
        if (curr->children[c - 'a'] == nullptr)
            return false;
        curr = curr->children[c - 'a'];
    }
    return curr->wordCount;
} */

int main()
{
    TrieNode *root = createNode();
    int p, q;
    cin >> p >> q;
    string words[p];
    string prefix[q];
    for (int i = 0; i < p; i++)
    {
        cin >> words[i];
        for (char &ch : words[i])
        {
            ch = tolower(ch);
        }
        /* cout << "The lowered words are: ";
        cout << words[i] << endl; */
        insert(root, words[i]);
    }
    char str[100];
    cout << endl
         << "The required words: " << endl;
    display(root, str, 0);
    cout << endl;
    for (int i = 0; i < q; i++)
    {
        totalWords = 0;
        cin >> prefix[i];
        for (char &ch : prefix[i])
        {
            ch = tolower(ch);
        }
        searchPrefix(root, prefix[i]);
        cout << "Words present under this prefix: " << totalWords << endl;
    }

    return 0;
}


/*int main()
{
    TrieNode *root = createNode();
    string sentence;
    getline(cin, sentence);
    stringstream ss(sentence);
    string words;
    while (ss >> words)
    {
        insert(root, words);
    }
    char str[100] = {0};
    display(root , str, 0);

    

    return 0;
}*/
