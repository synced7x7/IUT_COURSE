#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main ()
{

    queue <int> que_students;
    queue <int> que_dishes;
    int n;
    cin >> n;
    cin.ignore();
    string students;
    string dishes;

    int i,j;

    getline(cin, students);
    for(char c: students)
    {
        if(isdigit(c))
        {
            int students_value = c-'0';
            que_students.push(students_value);
        }
    }



    getline(cin, dishes);
    for(char c: dishes)
    {
        if(isdigit(c))
        {
            int dishes_value = c-'0';
            que_dishes.push(dishes_value);
        }
    }


    for(i=0; i<n*n; i++)
    {
        if(que_dishes.empty())
        {
            cout << que_dishes.size() << endl;
            return 0;
        }
        else if(que_students.front()!= que_dishes.front())
        {
            //cout << "no matching dish for students" << endl;
            que_students.push(que_students.front());
            que_students.pop();
        }
        else
        {
            //cout << "matching dish for students" << endl;
            que_dishes.pop();
            que_students.pop();
        }


    }

    cout << que_dishes.size() << endl;




    return 0;
}
