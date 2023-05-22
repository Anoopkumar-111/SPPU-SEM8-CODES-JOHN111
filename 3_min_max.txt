#include <bits/stdc++.h>
#include <omp.h>
using namespace std;




void max_val(int *arr, int n)
{
    int maximum_val = 0;
    omp_set_num_threads(4);
#pragma omp parallel for reduction(max : maximum_val)
    for (int i = 0; i < n; i++)
    {
        // cout<<"threadId: "<<omp_get_thread_num()<<" i: "<<i<<endl;
        if (arr[i] > maximum_val)
        {
            maximum_val = arr[i];
        }
    }
    cout << "Max number: " << maximum_val << endl;
}



void min_val(int *arr, int n)
{
    int min_num = 1000;
    omp_set_num_threads(4);
#pragma omp parallel for reduction(min : min_num)
    for (int i = 0; i < n; i++)
    {
        // cout<<"threadId: "<<omp_get_thread_num()<<" i: "<<i<<endl;
        if (arr[i] < min_num)
        {
            min_num = arr[i];
        }
    }
    cout << "Min number: " << min_num << endl;
}




void sum(int *arr, int n)
{
    int arr3[n];
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        // cout<<"threadId: "<<omp_get_thread_num()<<" i: "<<i<<endl;
        sum = sum + arr[i];
    }
    cout << "Sum: " << sum << endl;
}



void avg(int *arr, int n)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        // cout<<"threadId: "<<omp_get_thread_num()<<" i: "<<i<<endl;
        sum += arr[i];
    }
    cout << "Average: " << sum / n << endl;
}








int main()
{
    int arr[] = {113, 322, 153, 472, 101, 133, 105, 233, 135, 70, 311, 241,
                 397, 278, 227, 486, 431, 17, 59, 185, 70, 475, 160, 352, 453, 136, 55, 116,
                 384, 318, 128, 151, 335, 500, 58, 332, 461, 265, 162, 240, 295, 409, 4, 251,
                 430, 387, 92, 90, 480, 420, 321, 179, 133, 335, 224, 82, 460, 433, 71, 85,
                 305, 315, 368, 44, 300, 181, 219, 223, 405, 54, 98, 409, 278, 169, 332, 295,
                 253, 394, 277, 308, 79, 426, 449, 174, 124, 451, 6, 316, 239, 135, 126, 45,
                 164, 398, 307, 473, 36, 475, 202, 467};
    int n = 100;
    max_val(arr, n);
    min_val(arr, n);
    sum(arr, n);
    avg(arr, n);
}