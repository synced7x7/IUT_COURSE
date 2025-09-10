#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

const string morseCodes[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."
};
unordered_map <string, int> mpp;

string getMorseTransformation(string & word)
{
    string transformation;
    for(char ch: word)
    {
        transformation+=morseCodes[ch - 'a'];
    }
    //cout << "transformation= " << transformation << endl;
    return transformation;

}




int main()
{
    int n;
    cin >> n;
    vector <string> word(n);
    string transformed;

    for (int i=0; i<n ; i++)
    {
        cin >> word[i];
    }

    for (string w : word)
    {
        transformed = getMorseTransformation(w);
        mpp[transformed]++;
    }

    cout << mpp.size() << endl;

    for ( auto &entry : mpp)
    {
        cout << entry.first <<  endl;
    }




    return 0;
}
