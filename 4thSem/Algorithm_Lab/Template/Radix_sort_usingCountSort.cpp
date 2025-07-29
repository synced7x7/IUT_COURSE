#include <iostream>
using namespace std;

// Function to get the maximum value in the array
int getMax(int A[], int n) {
    int max = A[0];
    for (int i = 1; i < n; i++)
        if (A[i] > max)
            max = A[i];
    return max;
}

// Counting Sort used by Radix Sort for a specific digit (pos = 1, 10, 100, ...)
void countSort(int A[], int n, int pos) {
    int count[10] = {0};
    int B[100];  // Output array (assuming max size 100)

    // Step 1: Count frequency of digits at current position
    for (int i = 0; i < n; i++) {
        int digit = (A[i] / pos) % 10;
        count[digit]++;
    }

    // Step 2: Prefix sum to get actual positions
    for (int i = 1; i < 10; i++) {
        count[i] = count[i] + count[i - 1];
    }

    // Step 3: Build the output array (back to front for stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (A[i] / pos) % 10;
        B[--count[digit]] = A[i];
        
    }

    // Step 4: Copy the output array back to A
    for (int i = 0; i < n; i++) {
        A[i] = B[i];
    }
}

// Main Radix Sort function
void radixSort(int A[], int n) {
    int max = getMax(A, n);
    
    // Apply counting sort to each digit position
    for (int pos = 1; max / pos > 0; pos *= 10) {
        countSort(A, n, pos);
    }
}

// Utility function to print the array
void printArray(int A[], int n) {
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
}

// Example usage
int main() {
    int A[] = {432, 88, 530, 90, 88, 231, 11, 45, 677, 199};
    int n = sizeof(A) / sizeof(A[0]);

    cout << "Original array:\n";
    printArray(A, n);

    radixSort(A, n);

    cout << "\nSorted array:\n";
    printArray(A, n);

    return 0;
}
