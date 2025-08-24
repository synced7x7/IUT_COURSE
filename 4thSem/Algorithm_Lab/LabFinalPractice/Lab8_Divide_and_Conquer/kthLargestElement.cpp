// https://leetcode.com/problems/kth-largest-element-in-an-array/?envType=problem-list-v2&envId=divide-and-conquer

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
	int partition(vector<int> &nums, int l, int r)
	{
		int x = nums[r], i = l;
		for (int j = l; j < r; j++)
		{
			if (nums[j] > x)
			{
				swap(nums[i], nums[j]);
				i++;
			}
		}
		swap(nums[i], nums[r]);
		return i;
	}

	int quickSelect(vector<int> &nums, int l, int r, int k)
	{
		if (k > 0 && k <= r - l + 1)
		{
			int idx = partition(nums, l, r);
			if (idx == k - 1)
				return nums[idx];
			if (idx > k - 1)
				return quickSelect(nums, l, idx - 1, k); // searching in leftSubarray
			return quickSelect(nums, idx+1, r, k-(idx-l+1)); // searching in right Subarray
		}
		return INT_MAX;
	}

	int findKthLargest(vector<int> &nums, int k)
	{
		return quickSelect(nums, 0, nums.size() -1, k);
	}
};