#include <iostream>
#include <string>
#include <vector>
#include <sstream>
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




int main()
{
    vector<string> inputStrings;

    string sentence;
    getline(cin , sentence);

    stringstream stream(sentence);
    string word;

    while(stream >> word)
    {
        inputStrings.push_back(word);
    }

    int n = inputStrings.size();

    for (int i = 0; i < n; i++)
    {
        insert_key(root, inputStrings[i]);
    }

    char str1[100];

    display(root, str1, 0);
    cout << endl;

    cin.ignore();

    string sentence2;
    getline(cin , sentence2);

    stringstream stream2(sentence2);
    string word2;

    vector<string> inputPresence;

    while(stream2 >> word2)
    {
        inputPresence.push_back(word2);
    }

    int n2 = inputPresence.size();

    for (int i = 0; i < n2; i++)
    {
        bool ispresent = search_key(root, inputPresence[i]);
        if(ispresent)
            cout << "T ";
        else
            cout << "F ";
    }
    cout << endl;

//    vector<string> searchQueryStrings
//        = { "do", "geek", "bat" };
//
//    int searchQueries = searchQueryStrings.size();
//
//    for (int i = 0; i < searchQueries; i++)
//    {
//        cout << "Query String: " << searchQueryStrings[i]
//             << "\n";
//        if (search_key(root, searchQueryStrings[i]))
//        {
//            cout << "The query string is present in the "
//                 "Trie\n";
//        }
//        else
//        {
//            cout << "The query string is not present in "
//                 "the Trie\n";
//        }
//    }
//
//    vector<string> deleteQueryStrings = { "geek", "ant", "and", "an" };
//
//    int deleteQueries = deleteQueryStrings.size();
//
//    for (int i = 0; i < deleteQueries; i++)
//    {
//        cout << "Query String: " << deleteQueryStrings[i]
//             << "\n";
//        if (delete_key(root, deleteQueryStrings[i]))
//        {
//            cout << "The query string is successfully "
//                 "deleted\n";
//        }
//        else
//        {
//            cout << "The query string is not present in "
//                 "the Trie\n";
//        }
//    }

    return 0;
}
