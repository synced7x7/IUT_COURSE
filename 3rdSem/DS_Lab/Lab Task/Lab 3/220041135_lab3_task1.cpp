#include <iostream>
#include <vector>
#include <string>


using namespace std;

vector<int> heap;

void heapify(int i, int max_size)
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
        heapify(largest, max_size);
    }
}


void build_max_heap(int max_size)
{

    for (int i = max_size / 2 - 1; i >= 0; i--)
    {
        heapify(i, max_size);
    }
}


void heap_sort()
{
    int max_size = heap.size();


    build_max_heap(max_size);


    cout << "Max heap: ";
    for (int i = 0; i < max_size; i++)
    {
        cout << heap[i] << " ";
    }
    cout << endl;


    for (int i = max_size - 1; i >= 1; i--)
    {

        swap(heap[0], heap[i]);


        heapify(0, i);
    }
}

int main()
{
    char command = NULL;


}
