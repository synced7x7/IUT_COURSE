#include <iostream>
#include <vector>
#include <sstream>
#include <climits>
using namespace std;

struct TrieNode
{
    TrieNode* childNode[2];

    TrieNode()
    {
        for (int i = 0; i < 2; i++)
        {
            childNode[i] = NULL;
        }
    }
};

TrieNode* root = new TrieNode();

void insert_key(TrieNode* root, int num)
{
    TrieNode* currentNode = root;

    for (int i = 31; i >= 0; i--)//32 bit binary representation
    {
        int bit = (num >> i) & 1; //extract the i-th bit
        cout << bit << endl;
        if (currentNode->childNode[bit] == NULL)
        {
            currentNode->childNode[bit] = new TrieNode();
        }
        currentNode = currentNode->childNode[bit];
    }
    cout << endl;
}


int find_max_xor(TrieNode* root, int num)
{
    TrieNode* currentNode = root;
    int maxXor = 0;

    for (int i = 31; i >= 0; i--) /// remember XOR value will be maximum when we complement
    {
        int bit = (num >> i) & 1;
        int oppositeBit = 1 - bit; // complement  //complementing since it will give the max value
        //checking whether the complement is present in the tree
        if (currentNode->childNode[oppositeBit] != NULL) //complement present
        {
            maxXor = (maxXor << 1) | 1; //append 1 at lsb
            currentNode = currentNode->childNode[oppositeBit];
        }
        else //complement absent
        {
            maxXor = (maxXor << 1); //append 0 at lsb
            currentNode = currentNode->childNode[bit];
        }
    }

    return maxXor;
}

int main()
{
    string str;

    getline(cin, str);
    vector<int> nums;

    stringstream stream(str);
    string word;
    while (stream >> word)
    {
        nums.push_back(stoi(word));
    }

    for (int n : nums)
    {
        insert_key(root, n);
    }

    int maxResult = 0;
    for (int n : nums)
    {
        maxResult = max(maxResult, find_max_xor(root, n));
    }

    cout << maxResult << endl;

    return 0;
}
