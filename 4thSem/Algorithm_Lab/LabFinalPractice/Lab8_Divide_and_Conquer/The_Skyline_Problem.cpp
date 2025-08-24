// https://leetcode.com/problems/the-skyline-problem/description/?envType=problem-list-v2&envId=divide-and-conquer

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <unordered_set>

typedef long long int ll;
using namespace std;

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        return divideAndConquer(buildings, 0, buildings.size() - 1);
    }
    
private:
    vector<vector<int>> divideAndConquer(vector<vector<int>>& buildings, int start, int end) {
        if (start > end) {
            return {};
        }
        if (start == end) {
            int left = buildings[start][0];
            int right = buildings[start][1];
            int height = buildings[start][2];
            return {{left, height}, {right, 0}};
        }
        
        int mid = start + (end - start) / 2;
        vector<vector<int>> leftSkyline = divideAndConquer(buildings, start, mid);
        vector<vector<int>> rightSkyline = divideAndConquer(buildings, mid + 1, end);
        return mergeSkylines(leftSkyline, rightSkyline);
    }
    
    vector<vector<int>> mergeSkylines(vector<vector<int>>& left, vector<vector<int>>& right) {
        vector<vector<int>> merged;
        int i = 0, j = 0;
        int h1 = 0, h2 = 0; // Current heights from left and right skylines
        int curX = 0, curH = 0;
        
        while (i < left.size() && j < right.size()) {
            // Choose the smallest x
            if (left[i][0] < right[j][0]) {
                curX = left[i][0];
                h1 = left[i][1];
                i++;
            } else if (left[i][0] > right[j][0]) {
                curX = right[j][0];
                h2 = right[j][1];
                j++;
            } else {
                curX = left[i][0];
                h1 = left[i][1];
                h2 = right[j][1];
                i++;
                j++;
            }
            
            // The current height is the maximum of both
            int newH = max(h1, h2);
            if (newH != curH) {
                curH = newH;
                merged.push_back({curX, curH});
            }
        }
        
        // Add the remaining points from left skyline
        while (i < left.size()) {
            merged.push_back(left[i]);
            i++;
        }
        
        // Add the remaining points from right skyline
        while (j < right.size()) {
            merged.push_back(right[j]);
            j++;
        }
        
        return merged;
    }
};