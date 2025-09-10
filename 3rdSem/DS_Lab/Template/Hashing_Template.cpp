#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> X;
vector<int> Y;
unordered_map<float, unordered_map<float, int>> slope; // slope -> {intercept -> count}

void slopeFinder(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            cout << endl
                 << endl;
            if ((X[j] - X[i]) == 0)
            {
                cout << "The equation of slope = (" << Y[j] << " " << showpos << Y[i] << ") / (" << X[j] << " " << showpos << X[i] << ") = Infinite" << endl;
                cout << "Slope is infinite" << endl;
                continue;
            }
            float sl = (float)(Y[j] - Y[i]) / (X[j] - X[i]);
            cout << "float = " << sl << endl;
            cout << "The equation of slope = (" << Y[j] << " " << showpos << Y[i] << ") / (" << X[j] << " " << showpos << X[i] << ") = " << sl << endl;

            float c = Y[i] - sl * X[i]; // Change to float for precision
            cout << "c = " << c << endl;
            cout << "The equation of the straight line: y = " << sl << "x " << showpos << c << endl;

            slope[c][sl]++; // Store slope as the primary key
        }
    }
}

int main()
{
    int n, x, y, count;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;
        X.push_back(x);
        Y.push_back(y);
    }
    slopeFinder(n);
    float maxSlope;
    float max_c;
    float maxCount = INT_MIN;
    // Correct way to print slope map
    cout << "\nStored slope-intercept counts:\n";
    for (const auto &it : slope)
    {
        float c = it.first;
        cout << "Hello" <<  endl << endl;
        for (const auto &inner : it.second)
        {
            float sl = inner.first;
            count = inner.second;
            cout << "Slope = " << sl << ", Intercept = " << c << ", Count = " << count << endl;
            if(count > maxCount)
            {
                maxCount = count;
                maxSlope = sl;
                max_c = c;
            }
        }
    }
    cout << "Maximum Slope = " << maxSlope << endl;
    cout << "Max C = " << max_c << endl;

    cout << "Final result: " << endl << "--------------" << endl;

    if(max_c == 0) cout << "y = " << noshowpos << maxSlope << "x" << endl;
    else cout << "y = " << noshowpos << maxSlope << "x" << showpos << max_c << endl;

    int maxpointsPassing = 0;
    for (int i=0; i<n; i++)
    {
        if(Y[i]-maxSlope*X[i] == max_c) maxpointsPassing++;
    }
    cout << noshowpos <<  maxpointsPassing;

    return 0;
}
