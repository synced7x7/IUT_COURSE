// https://github.com/ir-rafio/iut-algorithms-lab-1a-summer-23-24/blob/main/Lab%206/Lab%20Handout.pdf
// Wiring the street

#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
    {
        ll n;
        cin >> n;
        string s;
        cin >> s;
        vector<ll> x(n);
        for (ll i = 0; i < n; i++)
            cin >> x[i];

        vector<ll> left(n, LLONG_MAX), right(n, LLONG_MAX);

        ll lastPowered = -1;
        for (ll i = 0; i < n; i++)
        {
            if (s[i] == '1')
                lastPowered = x[i];
            else if (lastPowered != -1)
                left[i] = x[i] - lastPowered;
        }

        lastPowered = -1;
        for (ll i = n - 1; i >= 0; i--)
        {
            if (s[i] == '1')
                lastPowered = x[i];
            else if (lastPowered != -1)
                right[i] = lastPowered - x[i];
        }

        ll res = 0;
        for (ll i = 0; i < n; i++)
        {
            if (s[i] == '0')
            {
                ll d1 = left[i], d2 = right[i];
                ll mind = min(d1, d2);
                res += mind;
            }
        }
        cout << res << "\n";
    }
}
