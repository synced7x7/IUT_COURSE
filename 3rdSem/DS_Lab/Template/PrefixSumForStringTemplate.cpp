#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int alphabet = 26;

void prefixFreqLogic(string &str, vector<vector<int>> &FrqArray)
{
    int size = str.length();

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < alphabet; j++)
        {
            FrqArray[j][i + 1] = FrqArray[j][i];
        }
        FrqArray[str[i] - 'a'][i + 1]++;
    }
}

char mostFrequentCharacter(const vector<vector<int>> &prefixFreq, int L, int R)
{
    int maxFreq = 0;
    char result = 'a';

    for (int i = 0; i < alphabet; i++)
    {
        // Ensure R+1 is within bounds
        int rightIndex = min(R + 1, (int)prefixFreq[i].size() - 1);
        int freq = prefixFreq[i][rightIndex] - prefixFreq[i][L];

        if (freq > maxFreq)
        {
            maxFreq = freq;
            result = 'a' + i;
            //cout << "mostFrequent Char= " << result << " Freq = " << maxFreq << endl;
        }
    }

    return result;
}


int main()
{
    string str;
    cin >> str;
    int query;
    cin >> query;
    int n = str.size();
    vector<vector<int>> prefixFreq(alphabet, vector<int>(n + 1, 0));
    prefixFreqLogic(str, prefixFreq);

    while(query--)
    {
        int L,R;
        cin >> L >> R;
        cout << mostFrequentCharacter(prefixFreq, L ,R) << endl;

    }
    
    return 0;
}