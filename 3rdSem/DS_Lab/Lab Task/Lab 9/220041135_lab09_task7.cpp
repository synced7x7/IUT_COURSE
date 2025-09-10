#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct TrieNode
{
    TrieNode* childNode[58];
    int wordCount;

    TrieNode()
    {
        wordCount = 0;
        for (int i = 0; i <58; i++)
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

        if (currentNode->childNode[c - 'A'] == NULL)
        {
            TrieNode* newNode = new TrieNode();
            currentNode->childNode[c - 'A'] = newNode;
        }
        currentNode = currentNode->childNode[c - 'A'];
    }
    currentNode->wordCount++;
}


bool search_key(TrieNode* root, string& key)
{
    TrieNode* currentNode = root;

    for (auto c : key)
    {
        //cout << "Processing character: " << c << endl;

        if (isupper(c))
        {
            // Match the exact uppercase character
            int index = c - 'A';
            while (currentNode != NULL)
            {
                bool foundLowercase = false;
                for (int j = 0; j < 26; j++) // Traverse lowercase letters
                {
                    if (currentNode->childNode[j + 32] != NULL) // Check for lowercase
                    {
                        //cout << "found lowercase: " << (char)(j+'A'+32) << endl;
                        currentNode = currentNode->childNode[j + 32];
                        foundLowercase = true;
                        break;
                    }
                }
                if (!foundLowercase)
                {
                    break;
                }
            }

            if (currentNode->childNode[index] == NULL)
            {
                //cout << "1: Uppercase letter not found: " << c << ". Returning false." <<  endl;
                return false;
            }
            currentNode = currentNode->childNode[index];
        }
        else
        {
            if(currentNode->childNode[c-'A'] == NULL)
            {
                //cout << c << "not found at the first time. Returning false" << endl;
                return false;
            }
            //cout << "found at the first time" << endl;
            while (currentNode != NULL)
            {
                bool foundLowercase = false;
                for (int j = 0; j < 26; j++) // Traverse lowercase letters
                {
                    if (currentNode->childNode[j + 32] != NULL) // Check for lowercase
                    {
                        //cout << "found lowercase: " << (char)(j+'A'+32) << endl;
                        currentNode = currentNode->childNode[j + 32];
                        foundLowercase = true;
                        break;
                    }
                }

                // Stop when uppercase is found
                if (isupper(c))
                {
                    break;
                }

                // If no more lowercase nodes, break out of the loop
                if (!foundLowercase)
                {
                    break;
                }
            }
        }
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
    for (int i = 0; i < 58; i++)
    {
        if (root->childNode[i] != NULL)
        {
            str[level] = i + 'A';
            display(root->childNode[i], str, level + 1);
        }
    }
}

void clear_trie(TrieNode* root)
{
    if (root == NULL) return;

    // Recursively delete all child nodes
    for (int i = 0; i < 58; i++)
    {
        if (root->childNode[i] != NULL)
        {
            clear_trie(root->childNode[i]);
        }
    }

    // Delete the current node
    delete root;
}

bool check_upper(string & s, string & target )
{
    int s_uppercount =0 ;
    int target_uppercount =0;
    for (char &c: s)
    {
        if(isupper(c))
            s_uppercount++;
    }
    for(char &c: target)
    {
        if(isupper(c))
            target_uppercount++;
    }
    if(s_uppercount == target_uppercount)
        return true;
    else
        return false;
}

int main()
{
    vector <string> res;
    while(true)
    {
        string sentence;
        cin >> sentence;
        if(sentence == "-1") break;
        res.push_back(sentence);
    }

    string target;
    cin >> target;

    for(int i=0; i<res.size(); i++)
    {
        if (!check_upper(res[i], target))
        {
            cout << "F ";
            continue;
        }
        root = new TrieNode();

        insert_key(root, res[i]);

        if(search_key(root, target))
        {
            cout << "T ";
        }
        else
            cout << "F " ;
        clear_trie(root);
        root = NULL;
    }

//    char str[100];
//    display(root, str, 0);

    return 0;
}
