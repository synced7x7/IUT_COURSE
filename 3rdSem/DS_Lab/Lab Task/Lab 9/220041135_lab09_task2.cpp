#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

struct TrieNode
{
    TrieNode* childNode[26];
    int wordCount;

    TrieNode()
    {
        wordCount = 0;
        for (int i = 0; i < 26; i++)
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

        if (currentNode->childNode[c - 'a'] == NULL)
        {
            TrieNode* newNode = new TrieNode();
            currentNode->childNode[c - 'a'] = newNode;
        }
        currentNode = currentNode->childNode[c - 'a'];
    }
    currentNode->wordCount++;
}

bool search_key(TrieNode* root, string& key)
{
    TrieNode* currentNode = root;

    for (auto c : key)
    {
        if (currentNode->childNode[c - 'a'] == NULL)
        {
            return false;
        }
        currentNode = currentNode->childNode[c - 'a'];
    }

    return (currentNode->wordCount > 0);
}

bool delete_key(TrieNode* root, string& word)
{
    TrieNode* currentNode = root;
    TrieNode* lastBranchNode = NULL;
    char lastBrachChar = 'a';

    for (auto c : word)
    {
        if (currentNode->childNode[c - 'a'] == NULL)
        {
            return false;
        }
        else
        {
            int count = 0;
            for (int i = 0; i < 26; i++)
            {
                if (currentNode->childNode[i] != NULL)
                    count++;
            }

            if (count > 1)    //more than one child
            {
                lastBranchNode = currentNode;
                lastBrachChar = c;
                //cout << "LastBrachChar = " << lastBrachChar << endl;
            }
            currentNode = currentNode->childNode[c - 'a'];
        }
    }

    int count = 0;
    for (int i = 0; i < 26; i++)
    {
        if (currentNode->childNode[i] != NULL)
            count++;
    }
    //cout << "count = " << count << endl;
    //cout << "word count = " << currentNode->wordCount << endl;

    // Case 1: The deleted word is a prefix of other words
    if (count > 0)
    {
        currentNode->wordCount--;
        //cout << "word count after deletion= " << currentNode->wordCount << endl;
        return true;
    }
    // Case 2: The deleted word shares a common prefix with other words in Trie.
    if (lastBranchNode != NULL)
    {
        lastBranchNode->childNode[lastBrachChar] = NULL;
        return true;
    }
    // Case 3: The deleted word does not share any common prefix with other words in Trie.
    else
    {
        root->childNode[word[0]] = NULL;
        return true;
    }
}

void display(TrieNode* root, char str[], int level)
{
    // If the current node is an end of a word, print the word
    if (root->wordCount > 0)
    {
        str[level] = '\0';
        cout << str << " ";
    }
    for (int i = 0; i < 26; i++)
    {
        if (root->childNode[i] != NULL)
        {
            str[level] = i + 'a';
            display(root->childNode[i], str, level + 1);
        }
    }
}

int word_checker(TrieNode* curr, string q)
{
    int count = 0;


    for (char& c : q)
    {
        c = tolower(c);
        int index = c - 'a'; // Calculate index

        // Check if the current character node exists
        if (curr->childNode[index] == NULL)
        {
            return 0; // Prefix not found, return 0
        }

        // Move to the next node
        curr = curr->childNode[index];
    }

    queue <TrieNode*> qNodes;
    qNodes.push(curr);

    while (!qNodes.empty())
    {
        TrieNode* node = qNodes.front();
        qNodes.pop();

        if(node->wordCount>0)
            count++;
        for (int i = 0; i < 26; i++)
        {
            if (node->childNode[i] != NULL)
            {
                qNodes.push(node->childNode[i]);
            }
        }
    }

    return count;
}



int main()
{
    vector<string> inputStrings;

    int N, Q;
    cin >> N >> Q;

    for (int i = 0; i < N; i++)
    {
        string sentence;
        cin >> sentence;
        for (auto& ch : sentence)
        {
            ch = tolower(ch);
        }
        inputStrings.push_back(sentence);
    }

    for (string& word : inputStrings)
    {
        insert_key(root, word);
    }

//    char str[100];
//    display(root, str, 0);

    string queries;

    for (int i=0; i<Q; i++)
    {
        cin >> queries;
        for (char & ch : queries)
        {
            ch = tolower(ch);
        }
        cout << word_checker(root, queries) << endl;


    }


    return 0;
}
