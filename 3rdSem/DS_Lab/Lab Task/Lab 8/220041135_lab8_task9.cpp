#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main()
{
    unordered_map<string, string> dictionary;
    string line;

    while (getline(cin, line) && !line.empty())
    {
        size_t spacePos = line.find(' ');
        string english = line.substr(0, spacePos);
        string foreign = line.substr(spacePos + 1);
        dictionary[foreign] = english;
    }

    string word;
    while (cin >> word)
    {
        //cout << "word = ";
        if (dictionary.count(word)) //returns true if word is present on the unordered map
        {
            cout << dictionary[word] << endl; //here word is the address which prints the english word.
        }
        else
        {
            cout << "eh" << endl;
        }
    }

    return 0;
}
