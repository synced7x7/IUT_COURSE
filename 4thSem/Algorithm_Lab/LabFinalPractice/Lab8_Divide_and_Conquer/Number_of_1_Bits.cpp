// https://leetcode.com/problems/number-of-1-bits/?envType=problem-list-v2&envId=divide-and-conquer

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <unordered_set>

typedef long long int ll;
using namespace std;

class Solution
{
public:
	string decimalToBinary(int decimal)
	{
		if (decimal == 0)
		{
			return "0";
		}

		string binaryString = "";
		while (decimal > 0)
		{
			int remainder = decimal % 2;
			binaryString += to_string(remainder);
			decimal /= 2;
		}

		std::reverse(binaryString.begin(), binaryString.end());
		return binaryString;
	}
	int findRes(string bin, int l, int r)
	{
		if(l==r){
			return bin[l] == '1' ? 1 : 0;
		} 
		int m = (l+r)/2;
		l = findRes(bin, l, m);
		r = findRes(bin, m+1, r);

		return l+r;

	}

	int hammingWeight(int n)
	{
		string bin = decimalToBinary(n);
		return findRes(bin, 0, bin.size());
	}
};