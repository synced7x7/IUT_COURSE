#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;


bool canSegment(string& target, unordered_set<string>& wordSet)
{
    int n = target.size();
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            cout << "substr(" << j <<", " << i << "-" << j << "=" << i-j << ")  = " <<target.substr(j, i - j) << endl;
            if (dp[j] && wordSet.find(target.substr(j, i - j)) != wordSet.end()) // if target is present in word set.
            {
                cout << "Matched.";
                cout << endl;
                dp[i] = true;
                break;
            }
        }
    }
    return dp[n];
}

int main()
{
    string input;
    unordered_set<string> wordSet;

    // Read words until "-1"
    while (true)
    {
        cin >> input;
        if (input == "-1")
            break;
        wordSet.insert(input);
    }

    string target;
    cin >> target;

    // Check if the target can be segmented
    if (canSegment(target, wordSet))
    {
        cout << "TRUE" << endl;
    }
    else
    {
        cout << "FALSE" << endl;
    }

    return 0;
}
