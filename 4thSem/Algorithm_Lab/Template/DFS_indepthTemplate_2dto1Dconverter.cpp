#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

void bfs(vector<bool> &visited, vector<vector<int>> &adj, vector<int> &parent, int source)
{
    queue<int> q;
    q.push(source);
    visited[source] = true;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        for (int neighbor : adj[curr])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                parent[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }
}

void bfsDistance(const vector<vector<int>> &adj, vector<int> &dist, int source)
{
    queue<int> q;
    dist[source] = 0;
    q.push(source);

    while (!q.empty())
    {
        int curr = q.front(); q.pop();
        for (int neighbor : adj[curr])
        {
            if (dist[neighbor] == -1)
            {
                dist[neighbor] = dist[curr] + 1;
                q.push(neighbor);
            }
        }
    }
}

int indexConverter(int row, int col, int cols)
{
    return row * cols + col;
}

void twoD_to_oneD_converter(vector<string> grid, vector<vector<int>> &adjList, int rows, int columns)
{
    // Directions = {up, down, left, right}
    int dy[] = {-1, 1, 0, 0};
    int dx[] = {0, 0, -1, 1};

    adjList.clear();
    adjList.resize(rows * columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (grid[i][j] == 'T')
                continue;

            int currentIndex = indexConverter(i, j, columns);

            for (int d = 0; d < 4; d++)
            {
                int ni = i + dy[d];
                int nj = j + dx[d];

                if (ni >= 0 && ni < rows && nj >= 0 && nj < columns && grid[ni][nj] != 'T')
                {
                    int neighbourIndex = indexConverter(ni, nj, columns);
                    adjList[currentIndex].push_back(neighbourIndex);
                }
            }
        }
    }
}

int main()
{
    int r, c;
    cin >> r >> c;
    vector<string> grid(r);
    int startPos, endPos;
    unordered_map<int, int> enemyPos;
    vector<bool> visited(r * c, false);
    vector<int> parent(r * c, -1);
    vector<vector<int>> adjList;
    for (int i = 0; i < r; i++)
    {
        cin >> grid[i];
        for (int j = 0; j < c; j++)
        {
            if (grid[i][j] == 'S')
                startPos = indexConverter(i, j, c);
            else if (grid[i][j] == 'E')
                endPos = indexConverter(i, j, c);
            else if (isdigit(grid[i][j]) && grid[i][j] > '0')
            {
                int index = indexConverter(i, j, c);
                enemyPos[index] = grid[i][j] - '0';
            }
        }
    }

    twoD_to_oneD_converter(grid, adjList, r, c);

    /* for (int i = 0; i < adjList.size(); ++i)
    {
        if (!adjList[i].empty())
        {
            printf("Node %d: ", i);
            for (int j = 0; j < adjList[i].size(); ++j)
            {
                printf("%d ", adjList[i][j]);
            }
            printf("\n");
        }
    } */

    // shortest path for the player
    bfs(visited, adjList, parent, startPos);
    int playerSteps = 0;
    //vector<int> playerPath;
    for (int cur = endPos; cur != -1; cur = parent[cur]) // ending position is cur
    {
        playerSteps++;
        //playerPath.push_back(cur);
    }
    /* reverse(playerPath.begin(), playerPath.end());
    cout << "Players Info: " << endl;
    cout << "Path Size: " << playerSteps << endl;
    cout << "Player's Path: ";
    for (int node : playerPath)
    {
        cout << node << " ";
    }
    cout << endl; */
    
    int enemySteps;
    int result = 0;
    for (auto it : enemyPos)
    {
        vector<bool> visited(r * c, false);
        vector<int> parent(r * c, -1);
        int enemySteps = 0;

        bfs(visited, adjList, parent, it.first);

        if (!visited[endPos])
            continue; // Enemy can't reach the end

        for (int cur = endPos; cur != -1; cur = parent[cur])
        {
            enemySteps++;
        }

       // cout << "Enemy at " << it.first << " numbered " << it.second  << " needs " << enemySteps << " steps.\n";

        if (enemySteps <= playerSteps)
        {
            result += it.second;
        }
    }

   // cout << "Finally you have to fight " << result << " enemies." << endl;

    cout << result << endl;

    /////////////////////////////////////////
    /* cout << "My 1D position: " << startPos << endl;
    cout << "Exit: " << endPos << endl;
    cout << "Enemy's 1D pos: " << endl;
    for(auto it : enemyPos)
    {
        cout << "Enemy Position: " << it.first << " EnemyNumber: " << it.second << endl;
    }
    cout << endl; */
    //////////////////////////////////////
    /* int enemyToFace = 0;

    vector<int> path;

    for (int cur = 6; cur != -1; cur = parent[cur]) // ending position is cur
    {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());
    cout << path.size() << endl;
    for (int node : path)
    {
        cout << node << " ";
    }
    cout << endl; */

    return 0;
}