#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
unordered_map <int , int > mpp;
vector < int > vec;
vector<pair<int, int>> result;
void pair_checker(int & target)
{
    for(int num : vec)
    {
        mpp[num]++;
    }

    for (int num : vec)
    {
        int complement = target - num;

        if(mpp[complement]>0)
        {
            if(num!=complement && mpp[complement]>0 || num == complement && mpp[complement]>1)
            {
                result.emplace_back(num, complement);
                mpp[num]--;
                mpp[complement]--;
            }

        }
    }

    if(result.empty())
    {
        cout << "No pairs found" << endl;
    }
    else
    {
        for(const auto & it : result)
        {
            cout << "(" << it.first << "," << it.second << "), ";
        }
    }



}



int main()
{
    int n= 0;
    while(true)
    {
        if ( n== -1) break;
        cin >> n;
        vec.push_back(n);
    }
    int target;
    cin >> target;
    pair_checker(target);

    return 0;
}
