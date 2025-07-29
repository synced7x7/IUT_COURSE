//https://github.com/ir-rafio/iut-algorithms-lab-1a-summer-23-24/blob/main/Lab%203/Lab%20Handout.pdf

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef long long int ll;

vector<ll> bfs(vector<vector<int>> &adj, vector<ll> &money, vector<bool> &visited, int s)
{
    queue<ll> q;
    visited[s] = true;
    vector<ll> res;
    q.push(s);

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        res.push_back(curr);

        for (int x : adj[curr])
        {
            if (!visited[x])
            {
                visited[x] = true;
                q.push(x);
            }
        }
    }
    return res;
}

int main()
{
    ll t;
    int Case = 0;
    cin >> t;
    while (t--)
    {
        Case++;
        ll n, m, u, v;
        cin >> n >> m;
        vector<ll> money(n + 1);
        vector<vector<int>> adj(n + 1);
        vector<bool> visited(n + 1, false);
        bool resFlag = false;
        for (ll i = 1; i <= n; i++)
        {
            cin >> money[i];
        }

        for (ll i = 0; i < m; i++)
        {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<ll> res;
        int moneyperPeople = -1;
        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
            {
                res = bfs(adj, money, visited, i);
                int people = res.size();
                // cout << "People = " << people << endl;
                int sumMoney = 0;
                for (int x : res)
                {
                    sumMoney += money[x];
                }
                // cout << "Sum Money = " << sumMoney << endl;

                if (sumMoney % people != 0)
                {
                    cout << "Case " << Case << ": " << "No" << endl;
                    resFlag = true;
                    break;
                }

                if (moneyperPeople != -1 && moneyperPeople != sumMoney / people)
                {
                    cout << "Case " << Case << ": " << "No" << endl;
                    resFlag = true;
                    break;
                }

                moneyperPeople = sumMoney / people;
            }
        }

        if (!resFlag)
            cout << "Case " << Case << ": " << "Yes" << endl;

        money.clear();
        adj.clear();
        res.clear();
        visited.clear();
    }

    return 0;
}
