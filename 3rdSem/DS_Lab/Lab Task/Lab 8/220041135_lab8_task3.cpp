#include <iostream>
#include <sstream>
#include <unordered_map>
#include <cctype>
#include <string>
using namespace std;


string cleanWord(const string& word)
{
    string clean;
    for (char c : word)
    {
        if (isalpha(c) || isdigit(c))
        {
            clean += tolower(c);
        }
    }
    return clean;
}

int main()
{
    string sentence;
    unordered_map<string, int> wordCount;


    getline(cin, sentence);


    stringstream ss(sentence);
    string word;
    while (ss >> word)
    {
        word = cleanWord(word);
        if (!word.empty())
        {
            wordCount[word]++;
        }
    }



    for (const auto& entry : wordCount)
    {
        if (entry.second > 1)
        {
            cout << entry.first << " " << entry.second << endl;
        }
    }


    return 0;
}
