//https://github.com/ir-rafio/iut-algorithms-lab-1b-summer-23-24/blob/main/Lab%208/2025%20-CSE_4404_Lab8_1B-2A.pdf

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <unordered_set>

typedef long long int ll;
using namespace std;

string nice(string s){
	int Stringsize = s.size();
	if(Stringsize<2) return "";

	unordered_set<char> chars(s.begin(), s.end());

	for (int i=0; i<Stringsize; i++){
		
		char c = s[i];
		if(chars.count(tolower(c)) && chars.count(toupper(c))) continue;
	
		string left = nice(s.substr(0,i));
		string right = nice(s.substr(i+1));
		return left.size()>right.size()? left: right;
	}
	return s;
}

int main(){
	string s;
	cin >> s;
	cout << nice(s)  << endl;

	return 0;
}