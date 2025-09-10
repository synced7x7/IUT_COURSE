#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct Point
{
    int x,y;
};

double getSlope(Point & p1, Point & p2)
{
    int dy = p2.y - p1.y;
    int dx = p2.x - p1.x;

    if(dx == 0) return -1.00; //vertical line, infinite slope
    if (dy==0) return 0.00; //horizontal line , 0 slope

    double slope = (double) dy/dx;
    return slope;
}

double getIntercept(Point& p, double slope)
{
    return p.y - slope * p.x; // y = mx + c --> c=y-mx
}

void max_points(vector <Point> & points)
{
    unordered_map < double, int > mpp;
    int count = -1;
    int max_count = -1;
    double slope , intercept;
    string maxLine;

    for(int i=0; i<points.size(); i++)
    {
        for(int j=i+1; j<points.size(); j++)
        {
            slope = getSlope(points[i], points[j]);
            cout << "x1 = " <<points[i].x << " y1 = " << points[i].y << " x2 = " <<  points[j].x << " y2 = " << points[j].y  << " Slope = " << slope << endl;

            mpp[slope]++;
        }

        for (const auto &it : mpp)
        {
            count = it.second;
            cout << "count = " << count << endl;

            if (count > max_count)
            {
                max_count = count;
                slope = it.first;
                intercept = getIntercept(points[i], slope);
                cout << "Slope = " << slope << " || max_count = " << max_count << endl;
                maxLine = "y = " + to_string(slope) + "x + " + to_string(intercept); //y = mx+c
                cout << "MaxLine = " << maxLine << endl;
            }
        }
    }
    cout << maxLine << endl;
    cout << max_count << endl;
}


int main()
{
    int n;
    cin >> n;
    vector <Point> points(n);

    for (int i=0; i< n; i++)
    {
        cin >> points[i].x  >> points[i].y;
    }

    max_points(points);


    return 0;
}
