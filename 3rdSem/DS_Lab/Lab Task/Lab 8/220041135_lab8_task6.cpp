#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
    int n, row, col;
    cin >> n >> row >> col;
    cin.ignore();
    string name[n];
    char ch[row][col];
    unordered_map <char, int > mpp;
    unordered_map <string, unordered_map<char, int>> res;

    for (int i=0; i< n ; i++)
    {
        cin >> name[i];
        for (int j=0 ; j<row; j++)
        {

            for (int k=0; k< col; k++)
            {
                cin >> ch[j][k];
                res[name[i]][ch[j][k]]++;
            }
        }
        cin.ignore();

    }

//    for (const auto &it : res)
//    {
//        cout << "Name = " << it.first <<endl;
//        for(const auto &charfreq : it.second)
//        {
//            cout << " " << charfreq.first << " = " << charfreq.second << endl;
//        }
//    }

   vector<bool> visited(n, false);
    for (int i = 0; i < n; i++)
    {
        if (visited[i]) continue;

        vector<string> group = {name[i]};
        visited[i] = true;

        for (int j = i + 1; j < n; j++)
        {
            if (visited[j]) continue;

            if (res[name[i]] == res[name[j]])
            {
                group.push_back(name[j]);
                visited[j] = true;
            }
        }


        for (const auto &grpName : group)
        {
            cout << grpName << " ";
        }
        cout << endl;
    }

    return 0;
}
