#include <iostream>
#include <list>
#include <iterator>
using namespace std;

void print_list(const list<int>& l)
{
    for (int val : l)
    {
        cout << val << " ";
    }
    cout << endl;
}

list<int> find_intersection(const list<int>& list1, const list<int>& list2)
{
    list<int> intersection;

    auto it1 = list1.begin();
    auto it2 = list2.begin();

    // Use set_intersection algorithm to find common elements in both lists
    while (it1 != list1.end() && it2 != list2.end())
    {
        if (*it1 == *it2)
        {
            intersection.push_back(*it1);  // Common element found
            ++it1;
            ++it2;
        }
        else if (*it1 < *it2)
        {
            ++it1;  // Move to next in list1
        }
        else
        {
            ++it2;  // Move to next in list2
        }
    }

    return intersection;
}

int main()
{
    list<int> list1, list2;
    int input;

    // Input the first sorted list
    while (cin >> input && input != -1)
    {
        list1.push_back(input);
    }

    // Input the second sorted list
    while (cin >> input && input != -1)
    {
        list2.push_back(input);
    }

    // Find the intersection of the two lists
    list<int> intersection = find_intersection(list1, list2);

    // Print the result
    if (!intersection.empty())
    {
        print_list(intersection);
    }
    else
    {
        cout << "empty" << endl;
    }

    return 0;
}
