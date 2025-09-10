#include <iostream>
#include <vector>
#include <string>

using namespace std;

void dfs(vector<vector<char>> &grid, int i, int j)
{
    int m = grid.size();
    int n = grid[0].size();
    //cout << "i = " << i  << " j= " << j << " m= " << m << " n= " << n << endl;
    // out of bounds or water
    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0')
    {
        return;
    }

    grid[i][j] = '0';

    dfs(grid, i + 1, j); //rows+1 //down
    dfs(grid, i - 1, j); //rows -1 // up
    dfs(grid, i, j + 1); //col +1 //right
    dfs(grid, i, j - 1); //col -1 //left
}

int numIslands(vector<vector<char>> &grid, int m, int n)
{
   
    int islandCount = 0;
    //cout << m << " " << n << endl;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == '1')
            {
                dfs(grid, i, j);
                islandCount++;
            }
        }
    }

    return islandCount;
}

int main()
{
    int m, n;
    cin >> m >> n;

    vector<vector<char>> grid(m, vector<char>(n));

    for (int i = 0; i < m; i++)
    {
        string row;
        cin >> row;
        for (int j = 0; j < n; j++)
        {
            grid[i][j] = row[j];
        }
    }

    int result = numIslands(grid, m , n);
    cout << result << endl;

    return 0;
}