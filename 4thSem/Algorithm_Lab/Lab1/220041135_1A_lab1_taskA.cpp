#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void bubbleSort(vector <int> & arr)
{
    int size = arr.size();
    for (int i=0; i<size-1; i++)
    {
        for (int j=0; j<size - i -1 ; j++)
        {
            if (arr[j]>arr[j+1])
            {
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

void selectionSort(vector <int> & arr)
{
    int n = arr.size();
    for (int i=0; i<n-1; i++)
    {
        int minIndex = i;
        for (int j=i+1; j<n; j++)
        {
            if(arr[j]<arr[minIndex])
            {
               minIndex = j;
            }
            
        }
        swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(vector <int> & arr)
{
    int n = arr.size();
    for (int i=1; i<n; i++)
    {
        int key = arr[i];
        int j = i-1;
        while(j>=0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void merge(vector<int> &array, int low, int mid, int high)
{
    vector <int> aux (high - low +1 );
    for (int k=low; k<=high; k++)
    {
        aux[k - low] = array[k];
    }

    int i= low, j=mid+1;
    for(int k = low; k<=high; k++)
    {
        if(i>mid)
        {
            array[k] = aux[j-low];
            j++;
        }
        else if (j>high)
        {
            array[k] = aux[i-low];
            i++;
        }
        else if (aux[j-low] < aux[i-low])
        {
            array[k] = aux[j-low];
            j++;
        }
        else
        {
            array[j] = aux [i-low];
            i++;
        }
    }
    aux.clear();
}

void mergeSort(vector<int> &array, int low, int high)
{
    if(low>=high) return;

    int mid = low + (high - low) /2;
    mergeSort(array, low, mid);
    mergeSort(array, mid+1, high);
    merge(array, low, mid, high);

}



int main() {
    vector<int> arr = {12, 11, 13, 5, 6};

    cout << "Original array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    bubbleSort(arr);

    cout << "Bubble Sorted array: ";
    for (int num : arr) cout << num << " ";
    cout << endl << endl;

    arr = {12, 11, 13, 5, 6};

    cout << "Original array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    selectionSort(arr);

    cout << "Selection Sorted array: ";
    for (int num : arr) cout << num << " ";
    cout << endl << endl;

    arr = {12, 11, 13, 5, 6};

    cout << "Original array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    insertionSort(arr);

    cout << "Insertion Sorted array: ";
    for (int num : arr) cout << num << " ";
    cout << endl << endl;

    arr = {12, 11, 13, 5, 6};

    cout << "Original array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;


    int n = arr.size();

    mergeSort(arr, 0, n-1);

    cout << "Merge Sorted array: ";
    for (int num : arr) cout << num << " ";
    cout << endl << endl;

    return 0;
}
