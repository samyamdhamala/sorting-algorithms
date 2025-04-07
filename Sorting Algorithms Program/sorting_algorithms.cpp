/****************************************************************************************
* @file sorting_algorithms.cpp
*
* @description
* This file implements six different sorting algorithms:
* - Bubble Sort
* - Selection Sort
* - Insertion Sort
* - Merge Sort
* - Quick Sort
* - Shell Sort
*
* Each sorting function operates on a vector of integers and sorts it in ascending order.
* Merge Sort and Quick Sort are implemented recursively, while the others use iterative
* approaches. The file also includes helper functions such as partitioning for Quick Sort
* and merging for Merge Sort.
*
* These algorithms are used in the benchmarking program to compare their performance on
* different datasets.
* Citations and references for the algorithms are provided in the report.
*
* @author: samyam.dhamala
******************************************************************************************/

#include "sorting_algorithms.hpp"
#include <iostream>

using namespace std;

// Bubble Sort: Repeatedly swaps adjacent elements if they are in the wrong order
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {  // Outer loop for passes
        for (int j = 0; j < n - i - 1; j++) {  // Inner loop for comparing adjacent elements
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);  // Swap if elements are out of order
            }
        }
    }
}

//selection sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i; // curr index has min value
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j; // update index for min element
            }
        }
        swap(arr[i], arr[minIdx]); // swap found min with first unsorted element
    }
}

// insertion sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // store curr element
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


// merge function for merge sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    vector<int> L(n1), R(n2);

    // copy data into temp left and right subarrays
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    // merge two halves back into the original array
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];  // copy rem element of L[]
    while (j < n2) arr[k++] = R[j++]; // copy rem element of R[]
}

// merge sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // find mid point
        mergeSort(arr, left, mid); // recursively sort left half
        mergeSort(arr, mid + 1, right); // recursively sort right half
        merge(arr, left, mid, right); // merge the sorted  halves
    }
}

// partion function: place pivot in correct positin
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high], i = low - 1; //pivot is chosen as last element
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) swap(arr[++i], arr[j]);
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

//quick sort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// shellsort
void shellSort(vector<int>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) { // reduce gap size each iteration
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j = i;
            while (j >= gap && arr[j - gap] > temp) { //shift elements for insertion
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp; // insert at correct position
        }
    }
}
