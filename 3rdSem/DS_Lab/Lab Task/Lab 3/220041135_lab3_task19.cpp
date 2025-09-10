#include <iostream>
#include <vector>

using namespace std;

vector<int> heap;
int max_size;

int Heap_Maximum(vector<int>& heap)
{
    return heap[0];
}



void heapify(vector<int>& heap, int i, int max_size)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;


    if (left < max_size && heap[left] > heap[largest])
        largest = left;

    if (right < max_size && heap[right] > heap[largest])
        largest = right;


    if (largest != i)
    {
        swap(heap[i], heap[largest]);
        heapify(heap, largest, max_size);
    }
}

int Heap_extract_max(vector<int>& heap)
{

        int MAX = heap[0];
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        max_size--;
        heapify(heap, 0, max_size);
        return MAX;

}

void build_max_heap(vector<int>& heap, int max_size)
{
    for (int i = max_size / 2 - 1; i >= 0; i--)
    {
        heapify(heap, i, max_size);
    }
}

void max_heap_insert(int value)
{
    heap.push_back(value);

    int i = heap.size()-1;


    while (i >= 0 && heap[(i - 1) / 2] < heap[i])
    {
        swap(heap[(i - 1) / 2], heap[i]);
        i = (i - 1) / 2;
    }

}

void increase_key(int position, int value)
{
    heap[position] += value;


    while (position > 0 && heap[(position - 1) / 2] < heap[position])
    {
        swap(heap[position], heap[(position - 1) / 2]);
        position = (position - 1) / 2;
    }
}

void decrease_key(int position, int value)
{
    heap[position] -= value;


    heapify(heap, position, heap.size());
}





void print_heap()
{
    for (int i = 0; i < heap.size(); i++)
    {
        cout << heap[i] << " ";
    }
    cout << endl;
}

int main()
{
    int input;


    do
    {
        cin >> input;
        if (input != -1)
            heap.push_back(input);
    }
    while (input != -1);

    max_size = heap.size();


    build_max_heap(heap, max_size);

    cout << "Min heap: ";
    print_heap();


    int ID = 0;
    while (ID != -1)
    {

        cin >> ID;

        if (ID == 1)
        {
            cout << Heap_Maximum(heap) << endl;
            print_heap();
        }
        else if (ID == 2)
        {
            Heap_extract_max(heap);

            print_heap();
        }
        else if (ID == 3)
        {
            int value;
            cin >> value;
            max_heap_insert(value);
            print_heap();

        }
        else if (ID == 4)
        {
            int position, value;
            cin >> position;
            cin >> value;
            decrease_key(position-1, value);
            print_heap();
        }
        else if (ID ==5)
        {
            int position, value;
            cin >> position;
            cin >> value;
            increase_key(position-1, value);
            print_heap();
        }
    }

    return 0;
}
