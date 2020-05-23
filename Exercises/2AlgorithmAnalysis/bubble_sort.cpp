#include <bits/stdc++.h>
#include <windows.h> // use Windows time
#include <math.h>
using namespace std;

//! swap two values
template <typename T>
void swap(T *x, T *y)
{
	T temp = *x;
	*x = *y;
	*y = temp;
}

//! sort an array using bubble sort
template <typename T>
void bubbleSort(T arr[], int n)
{
	int i, j;
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

//! print an array
template <typename T>
void printArray(T arr[], int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

//! random initialize an array of a particular size, whose range is between MIN and MAX
#define MIN 1.0
#define MAX 1000.0
template <typename T>
T *initArray(int size)
{
    T *arr = new T[size];

    srand(time(NULL));
    for(int i=0; i<size; i++)
    {
        arr[i] = MIN + (T)MAX * rand() / (RAND_MAX + 1);
    }
    return arr;
}

//! Time the execution of a bubble sort function.
template <typename T>
void timeBubbleSort(T arr, int size)
{
    LARGE_INTEGER start, end;

    QueryPerformanceCounter(&start);
    bubbleSort(arr, size);
    QueryPerformanceCounter(&end);

    cout << "Sort an array of length " << size
         << " in " << (end.QuadPart - start.QuadPart) << " ns\n";
}

//! calculate average of an array
template <typename T>
T average(T arr[], int size)
{
    T sum = arr[0];
    for(int i=1; i<size; i++){
        sum += arr[i];
    }
    return sum/size;
}

//! partitions an array or vector into two parts: the above-average values and the below-average values.
template <typename T>
void split(T arr[], int size)
{
    int aver = average(arr, size);
    cout <<"the average: "<< aver <<endl;
    bubbleSort(arr, size);
    for(int i=0; i<size; i++){
        if(arr[i]>aver){
            T *above = new T[size-i];
            for(int j=0; j<size-i; j++){
                above[j]=arr[i+j];
            }
            cout << "the above-average values: \n";
            printArray(above, size-i);
            T *below = new T[i];
            for(int k=0; k<i; k++){
                below[k]=arr[k];
            }
            cout << "the below-average values: \n";
            printArray(below, i);
            break;
        }
    }
}

int main()
{

    // run multiple times to plot
    int sizeList[10] = {10, 100, 500, 1000, 2000, 3000, 4000, 5000, 8000, 10000};
    for(int i=0; i<10; ++i){
        int size = sizeList[i];
        int* arr;
        arr = initArray<int>(size);
        timeBubbleSort(arr, size);
    }

    cout << "*********************Optional: Partitioning************************" << endl;
    int size = 10;
    int* arr;
    arr = initArray<int>(size);

    cout<<"Initial array: \n";
    printArray(arr, size);

    bubbleSort(arr, size);

	cout<<"Sorted array: \n";
	printArray(arr, size);

    split(arr, size);

    system("pause");//to show "Press any key to continue" in the console
	return 0;
}

