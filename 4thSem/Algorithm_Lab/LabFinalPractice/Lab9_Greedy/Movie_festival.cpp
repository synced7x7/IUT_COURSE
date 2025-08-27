//https://cses.fi/problemset/task/1629/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;
    vector<pair<ll, ll>> movies;
    
    for (ll i = 0; i < n; i++) {
        ll start, end;
        cin >> start >> end;
        movies.push_back({end, start}); 
    }

    sort(movies.begin(), movies.end());

    ll count = 0;
    ll current_end = 0; 

    for (const auto& movie : movies) {
        ll start = movie.second;
        ll end = movie.first;
        
        if (start >= current_end) {
            count++;
            current_end = end; 
        }
    }

    cout << count << endl;
    return 0;
}