#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

#include <chrono>
using namespace std::chrono;


// Merge function for merging two sorted sub-arrays
void merge(vector<int> &arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    vector<int> L(n1), R(n2);

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)    L[i] = arr[l + i];

    for (j = 0; j < n2; j++)    R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Sequential Merge Sort
void sequentialMergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        sequentialMergeSort(arr, l, m);
        sequentialMergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            {
                // Sort first half
                parallelMergeSort(arr, l, m);
            }
#pragma omp section
            {
                // Sort second half
                parallelMergeSort(arr, m + 1, r);
            }
        }

        merge(arr, l, m, r);
    }
}

int main()
{
    vector<int> arr = {9, 7, 1, 3, 5, 8, 2, 4};
                 

    cout << "Original Array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    // Sequential Merge Sort
    vector<int> seqArr = arr; // Create a copy of the original array
    auto start = high_resolution_clock::now();

    sequentialMergeSort(seqArr, 0, seqArr.size() - 1);
    
    auto end = high_resolution_clock::now();

    cout << "Sequential Merge Sort: ";
    for (int num : seqArr)
        cout << num << " ";
    cout << endl;

    auto duration = duration_cast<microseconds>(end - start);
    cout << "Sequential Merge Sort Execution Time: " << duration.count() << " seconds" << endl;

    // Parallel Merge Sort
    vector<int> parArr = arr; // Create a copy of the original array

    start = high_resolution_clock::now();

    parallelMergeSort(parArr, 0, parArr.size() - 1);

    end = high_resolution_clock::now();

    cout << "P Merge Sort: ";
    for (int num : parArr)      
        cout << num << " ";
    cout << endl;

    duration = duration_cast<microseconds>(end - start);
    cout << "P Merge Sort Execution Time: " << duration.count() << " seconds" << endl;

    return 0;
}
