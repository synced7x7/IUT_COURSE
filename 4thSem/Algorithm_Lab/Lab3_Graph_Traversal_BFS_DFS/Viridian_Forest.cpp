//https://codeforces.com/problemset/problem/329/B

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

int indexConverter(int row, int col, int cols)
{
    return row * cols + col;
}

void buildAdjList(const vector<string> &grid, vector<vector<int>> &adjList, int rows, int cols)
{
    int dy[] = {-1, 1, 0, 0};
    int dx[] = {0, 0, -1, 1};

    adjList.assign(rows * cols, {});

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (grid[i][j] == 'T')
                continue;

            int currentIndex = indexConverter(i, j, cols);
            for (int d = 0; d < 4; ++d)
            {
                int ni = i + dy[d];
                int nj = j + dx[d];
                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && grid[ni][nj] != 'T')
                {
                    int neighborIndex = indexConverter(ni, nj, cols);
                    adjList[currentIndex].push_back(neighborIndex);
                }
            }
        }
    }
}

void bfsFromEnd(const vector<vector<int>> &adjList, vector<int> &dist, int endPos)
{
    queue<int> q;
    dist[endPos] = 0;
    q.push(endPos);

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        for (int neighbor : adjList[current])
        {
            if (dist[neighbor] == -1)
            {
                dist[neighbor] = dist[current] + 1;
                q.push(neighbor);
            }
        }
    }
}

int main()
{
    int r, c;
    cin >> r >> c;

    vector<string> grid(r);
    int startPos = -1, endPos = -1;
    unordered_map<int, int> enemyPos;

    for (int i = 0; i < r; ++i)
    {
        cin >> grid[i];
        for (int j = 0; j < c; ++j)
        {
            char cell = grid[i][j];
            int idx = indexConverter(i, j, c);

            if (cell == 'S')
            {
                startPos = idx;
            }
            else if (cell == 'E')
            {
                endPos = idx;
            }
            else if (isdigit(cell) && cell > '0')
            {
                enemyPos[idx] = cell - '0';
            }
        }
    }

    vector<vector<int>> adjList;
    buildAdjList(grid, adjList, r, c);

    vector<int> dist(r * c, -1);
    bfsFromEnd(adjList, dist, endPos);

    int playerSteps = dist[startPos];
    int result = 0;

    for (const auto &enemy : enemyPos)
    {
        int pos = enemy.first;
        int strength = enemy.second;

        if (dist[pos] != -1 && dist[pos] <= playerSteps)
        {
            result += strength;
        }
    }

    cout << result << endl;
    return 0;
}
