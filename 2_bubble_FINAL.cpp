#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
using namespace std;





// Sequential Bubble Sort
void bubbleSortSeq(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}



// Parallel Bubble Sort
void bubbleSortPar(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
#pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


int main(){
    vector<int>arr={5,6,23,1,7,900};

    for(auto i:arr){
        cout<<i<<" ";
    }
    cout<<endl;

    bubbleSortPar(arr);

    for(auto i:arr){
        cout<<i<<" ";
    }
    cout<<endl;







    return 0;
}



