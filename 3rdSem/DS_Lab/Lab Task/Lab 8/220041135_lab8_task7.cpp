#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

// Function to encode a character to a numeric value
int encode(char c) {
    switch (c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
    }
    return -1; // Error case, should not happen with valid input
}

// Function to find repeated DNA sequences
vector<string> findRepeatedDnaSequences(string s) {
    int n = s.length();
    const int LEN = 10; // Length of DNA sequence to match
    const int BASE = 4; // Base for encoding (A, C, G, T)
    const int MOD = 1e9 + 7; // A large prime for modulo operation

    if (n < LEN) return {}; // No sequences of length 10 can exist

    int hash = 0, power = 1; // Hash value and base^LEN-1
    unordered_set<int> seen; // To track hashes of DNA sequences
    unordered_set<string> result; // To track result strings

    // Calculate the hash for the first window
    for (int i = 0; i < LEN; i++) {
        hash = (hash * BASE + encode(s[i])) % MOD;
        if (i < LEN - 1) power = (power * BASE) % MOD;
        //cout << "Hash = " << hash << " Power = " << power << endl;
    }
    seen.insert(hash);

    // Process the remaining windows using rolling hash
    for (int i = LEN; i < n; i++) {
        // Remove the leftmost character and add the new one
        hash = (hash - (encode(s[i - LEN]) * power) % MOD + MOD) % MOD;
        hash = (hash * BASE + encode(s[i])) % MOD;

        // Check if the hash is already seen
        if (seen.count(hash)) {
            result.insert(s.substr(i - LEN + 1, LEN));
        } else {
            seen.insert(hash);
        }
    }

    // Convert result set to vector
    return vector<string>(result.begin(), result.end());
}

int main() {
    // Test Cases
    vector<string> inputs;
    string in;
    cin >> in;
    inputs.push_back(in);
    for (const string& s : inputs) {
        vector<string> output = findRepeatedDnaSequences(s);
//        cout << "Input: " << s << endl;
//        cout << "Output: ";
        for (const string& seq : output) {
            cout << seq << " ";
        }
        cout << endl << endl;
    }

    return 0;
}
