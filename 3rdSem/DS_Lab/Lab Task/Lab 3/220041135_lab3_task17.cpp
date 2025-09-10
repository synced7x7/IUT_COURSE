#include <iostream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;



vector<tuple<string, int, string, int>> heap;
int insertion_index = 0;


void heapify(int i, int max_size)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;


    if (left < max_size && (get<1>(heap[left]) > get<1>(heap[largest]) ||
                            (get<1>(heap[left]) == get<1>(heap[largest]) && get<3>(heap[left]) < get<3>(heap[largest])))) //get<3> refers to insertion index and the smaller the index the earlier the insertion which gets more priority
        largest = left;

    if (right < max_size && (get<1>(heap[right]) > get<1>(heap[largest]) ||
                             (get<1>(heap[right]) == get<1>(heap[largest]) && get<3>(heap[right]) < get<3>(heap[largest]))))
        largest = right;

    if (largest != i)
    {
        swap(heap[i], heap[largest]);
        heapify(largest, max_size);
    }
}


void insert(string name, int age, string house)
{

    heap.push_back(make_tuple(name, age, house, insertion_index++));


    int i = heap.size() - 1;
    while (i != 0 && (get<1>(heap[(i - 1) / 2]) < get<1>(heap[i]) ||
                      (get<1>(heap[(i - 1) / 2]) == get<1>(heap[i]) && get<3>(heap[(i - 1) / 2]) > get<3>(heap[i]))))
    {
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}


void serve()
{
    if (heap.empty())
    {
        cout << "No wizards to serve." << endl;
        return;
    }


    auto wizard = heap[0];
    cout << "Name: " << get<0>(wizard) << ", Age: " << get<1>(wizard) << ", House: " << get<2>(wizard) << endl;


    heap[0] = heap.back();
    heap.pop_back();


    heapify(0, heap.size());
}

int main()
{
    char command;
    string name, house;
    int age;

    while (true)
    {
        cin >> command;

        if (command == 'I')
        {
            cin.ignore();
            getline(cin, name, ',');
            cin >> age;
            cin.ignore();
            getline(cin, house);
            insert(name, age, house);
        }
        else if (command == 'S')
        {
            serve();
        }
        else if (command == 'X')
        {
            break;
        }
    }

    return 0;
}

