#include <iostream>
#include <vector>

using namespace std;

void heapify(vector<int>& heap, int i, int max_size)
{
    int smallest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= max_size && heap[left] < heap[smallest])
        smallest = left;

    if (right <= max_size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(heap[i], heap[smallest]);
        heapify(heap, smallest, max_size);
    }
}

void build_min_heap(vector<int>& heap, int max_size)
{

    for (int i = max_size / 2; i >= 1; i--)
    {
        heapify(heap, i, max_size);
    }
}

void heap_sort(vector<int>& heap)
{
    int max_size = heap.size() - 1;

    build_min_heap(heap, max_size);

    cout << "Min heap: ";
    for (int i = 1; i <= max_size; i++)
    {
        cout << heap[i] << " ";
    }
    cout << endl;


    for (int i = max_size; i >= 2; i--)
    {
        swap(heap[1], heap[i]);
        heapify(heap, 1, i - 1);
    }
}

int main()
{
    vector<int> heap(1);
    int input;

    do
    {
        cin >> input;
        if (input != -1)
            heap.push_back(input);
    }
    while (input != -1);

    heap_sort(heap);

    cout << "Sorted array: ";
    for (int i = heap.size()-1; i >=1; i--)
    {
        cout << heap[i] << " ";
    }
    cout << endl;

    return 0;
}
