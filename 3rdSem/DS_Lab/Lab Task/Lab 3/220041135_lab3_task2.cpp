#include <iostream>
#include <vector>

using namespace std;

vector<int> heap;
int max_size;

int Heap_Minimum(vector<int>& heap)
{
    return heap[0];
}



void heapify(vector<int>& heap, int i, int max_size)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;


    if (left < max_size && heap[left] < heap[smallest])
        smallest = left;

    if (right < max_size && heap[right] < heap[smallest])
        smallest = right;


    if (smallest != i)
    {
        swap(heap[i], heap[smallest]);
        heapify(heap, smallest, max_size);
    }
}

int Heap_extract_min(vector<int>& heap)
{
    if (heap.size() <= 0)
    {
        cout << "Underflow" << endl;
        return -1;
    }
    else
    {
        int MIN = heap[0];
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        max_size--;
        heapify(heap, 0, max_size);
        return MIN;
    }
}

void build_min_heap(vector<int>& heap, int max_size)
{
    for (int i = max_size / 2 - 1; i >= 0; i--)
    {
        heapify(heap, i, max_size);
    }
}

void min_heap_insert(int value)
{
    heap.push_back(value);
    max_size++;
    int i = max_size - 1;


    while (i > 0 && heap[(i - 1) / 2] > heap[i])
    {
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void decrease_key(int position ,int value)
{
    heap[position]-=value;
    while (position >=0 && heap[position/2] > heap[position])
    {

            swap(heap[position/2], heap[position]);
            position = position /2;
    }
}

void increase_key(int position, int new_value)
{
    heap[position] += new_value;
    int heap_size = heap.size();


    while (true)
    {
        int left_child = 2 * position + 1;
        int right_child = 2 * position + 2;
        int smallest = position;


        if (left_child < heap_size && heap[left_child] < heap[smallest])
        {
            smallest = left_child;
        }


        if (right_child < heap_size && heap[right_child] < heap[smallest])
        {
            smallest = right_child;
        }


        if (smallest == position)
        {
            break;
        }


        swap(heap[position], heap[smallest]);
        position = smallest;
    }
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


    build_min_heap(heap, max_size);

    cout << "Min heap: ";
    print_heap();


    int ID = 0;
    while (ID != -1)
    {

        cin >> ID;

        if (ID == 1)
        {
            cout << Heap_Minimum(heap) << endl;
        }
        else if (ID == 2)
        {
            int minElement = Heap_extract_min(heap);
            cout<< minElement << endl;
            print_heap();
        }
        else if (ID == 3)
        {
            int value;
            cin >> value;
            min_heap_insert(value);
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
