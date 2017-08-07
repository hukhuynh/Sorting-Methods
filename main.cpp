#include <ctime>            //used library to help calculate execution time.
#include <stdlib.h>
#include <iostream>
#include <chrono>

void printArray(int A[], int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        printf("%d ", A[i]);
    }
    printf("///end \n");
}

void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}//end swap

void InsertionSort(int array[], int elements)
{
    int i,j,key;


    for(i=1;i<elements;i++)
    {
        key = array[i];                 //points to second element first
        j = i-1;                        //goes through while loop if element pointed at
                                        //is less than any previous values
        while(j>=0 && key < array[j])   //while loop moves elements over to
        {                               //make room for correct positioning of key value
            array[j+1] = array[j];
            j = j - 1;
        }//end while

        array[j+1] = key;               //else do nothing and increment
    }//end for



}//end of InsertionSort

void merge(int array[],int tmpArr[],int leftPos,int rightPos,int rightEnd)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    while(leftPos<=leftEnd && rightPos<=rightEnd)           //takes left and right array(after split(s)) to
    {                                                       //compare elements
        if(array[leftPos]<=array[rightPos])
        {
            tmpArr[tmpPos++] = array[leftPos++];
        }

        else
        {
            tmpArr[tmpPos++] = array[rightPos++];
        }
    }//end while

    while(leftPos<=leftEnd)                                 //once comparisons are done, rest of right or
    {                                                       //left array is copied on to temporary array
        tmpArr[tmpPos++] = array[leftPos++];
    }//end while

    while(rightPos<=rightEnd)
    {
        tmpArr[tmpPos++] = array[rightPos++];

    }//end while

    for(int i = 0;i<numElements;++i)
    {

        array[rightEnd] = tmpArr[rightEnd];                 //after temp array is sorted, its content is
        --rightEnd;                                         //copied over to array
    }
}//end of merge


void MergeSort(int array[],int tmpArr[],int left,int right)
{

    if(left<right)                                          //continues sorting until left and right overlap
    {
        int mid = (left+right)/2;


        MergeSort(array,tmpArr,left,mid);                     //recursive call to left and right portion of
        MergeSort(array,tmpArr, mid+1 ,right);                    //original array to be merge sorted.
                                                            //continuously until fully spliced to be
                                                            //merged.

        merge(array,tmpArr,left,mid+1, right);
    }



}//end of MergeSort

int partition(int array[], int leftEnd, int rightEnd)
{
    //int randIndex = rand() %(rightEnd+1) + 0;
    int pivot = array[rightEnd];                            //takes the rightmost element as the pivot point

    int i = leftEnd - 1;

    for(int j = leftEnd; j<=rightEnd-1;j++)                 //for loop initiates iterative comparisons of elements
    {                                                       //within array so that elements right of pivot are greater
        if(array[j] <= pivot)                               //than pivot and elements to the left are less than pivot
        {
            i++;
            swap(&array[i],&array[j]);
        }
    }//end for
    swap(&array[i+1],&array[rightEnd]);
    return (i+1);

}//end partition

void QuickSort(int array[],int leftEnd, int rightEnd)
{
    if(leftEnd<rightEnd)
    {
     int pi = partition(array,leftEnd,rightEnd);


      QuickSort(array,leftEnd,pi-1);
      QuickSort(array,pi+1,rightEnd);
    }


}//end QuickSort

void heapify(int arr[], int n, int node)
{
    int root = node;
    int leftChild = 2*node + 1;
    int rightChild = 2*node + 2;

    if(leftChild < n && arr[leftChild] > arr[root])                     //helps create max heap by fixing each subtree
    {                                                                   //so that the parent node is greater than its
        root = leftChild;                                               //children
    }

    if(rightChild < n && arr[rightChild] > arr[root])
    {
        root = rightChild;
    }

    if(root != node)                                                    //if either above conditions met this calls to switch
    {                                                                   //the two nodes(array values) and then calls the heapify
        swap(&arr[node],&arr[root]);                                    //function recursively to make sure other subtrees
        heapify(arr,n,root);                                            //are turned into a max heap, collectively.
    }
}//end heapify

void HeapSort(int arr[], int n)
{
    for(int i = n/2 - 1; i >= 0; i--)
    {
        heapify(arr,n,i);
    }
    for(int i = n-1; i>=0; i--)
    {
        swap(&arr[0],&arr[i]);
        heapify(arr,i,0);
    }

}//end HeapSort

void timeInsertion(int n)
{
    int* array = new int[n];
    for(int i = 0; i<n; i++)
    {
        array[i] = rand()% 20000 + 1;
    }
    auto start_s = std::chrono::high_resolution_clock::now();
    InsertionSort(array,n);
    auto stop_s = std::chrono::high_resolution_clock::now();
    auto time_s = stop_s - start_s;
    std::cout<<"Unsorted Time"<<"("<<n<<"): "<<std::chrono::duration_cast<std::chrono::microseconds>(time_s).count() << "ms \n";

    auto start_2 = std::chrono::high_resolution_clock::now();
    InsertionSort(array,n);
    auto stop_2 = std::chrono::high_resolution_clock::now();
    auto time_2 = stop_2 - start_2;
    std::cout<<"Sorted Time"<<"("<<n<<"): "<<std::chrono::duration_cast<std::chrono::microseconds>(time_2).count()<<"ms \n";

    delete []array;
}//end timeInsertion

void timeMerge(int n)
{
    int* tmpArr = new int[n];
    int* arr = new int[n];

    for(int i = 0; i<n; i++)
    {
        arr[i] = rand()% 20000 + 1;
    }
     auto start_s = std::chrono::high_resolution_clock::now();
     MergeSort(arr,tmpArr,0,n-1);
     auto stop_s = std::chrono::high_resolution_clock::now();
     auto time_s = stop_s - start_s;
     std::cout<<"Unsorted Time"<<"("<<n<<"): " <<std::chrono::duration_cast<std::chrono::microseconds>(time_s).count() << "ms \n";

     auto start_2 = std::chrono::high_resolution_clock::now();
     MergeSort(arr,tmpArr,0,n-1);
     auto stop_2 = std::chrono::high_resolution_clock::now();
     auto time_2 = stop_2 - start_2;
     std::cout<<"Sorted Time"<<"("<<n<<"): "<<std::chrono::duration_cast<std::chrono::microseconds>(time_2).count()<<"ms \n";

     delete []arr;



}//end timeMerge
void timeQuick(int n)
{
    int* arr = new int[n];
    for(int i = 0; i<n; i++)
    {
        arr[i] = rand() % 20000+1;
    }
    auto start_s = std::chrono::high_resolution_clock::now();
    QuickSort(arr,0,n-1);
    auto stop_s = std::chrono::high_resolution_clock::now();
    auto time_s = stop_s - start_s;
    std::cout<<"Unsorted Time"<<"("<<n<<"): " <<std::chrono::duration_cast<std::chrono::microseconds>(time_s).count() << "ms \n";

    auto start_2 = std::chrono::high_resolution_clock::now();
    QuickSort(arr,0,n-1);
    auto stop_2 = std::chrono::high_resolution_clock::now();
    auto time_2 = stop_2 - start_2;
    std::cout<<"Sorted Time"<<"("<<n<<"): "<<std::chrono::duration_cast<std::chrono::microseconds>(time_2).count()<<"ms \n";

    delete []arr;

}//end timeQuick
void timeHeap(int n)
{
    int* arr = new int[n];
    for(int i = 0; i < n; i++)
    {
        arr[i] = rand() % 20000+1;
    }
     auto start_s = std::chrono::high_resolution_clock::now();
     HeapSort(arr,n);
     auto stop_s = std::chrono::high_resolution_clock::now();
     auto time_s = stop_s - start_s;
     std::cout<<"Unsorted Time"<<"("<<n<<"): " <<std::chrono::duration_cast<std::chrono::microseconds>(time_s).count() << "ms \n";

     auto start_2 = std::chrono::high_resolution_clock::now();
     HeapSort(arr,n);
     auto stop_2 = std::chrono::high_resolution_clock::now();
     auto time_2 = stop_2 - start_2;
     std::cout<<"Sorted Time"<<"("<<n<<"): "<<std::chrono::duration_cast<std::chrono::microseconds>(time_2).count()<<"ms \n";

     delete []arr;





}//end timeHeap


int main()
{

  std::srand(time(0));                          //allows production of different random lists



    std::cout<<"Insertion Sort"<<std::endl;
    timeInsertion(100);
    timeInsertion(500);
    timeInsertion(1000);
    timeInsertion(2000);
    timeInsertion(5000);
    timeInsertion(8000);
    timeInsertion(10000);

    std::cout<<"\n";
    std::cout<<"\n";

    std::cout<<"Merge Sort"<<std::endl;
    timeMerge(100);
    timeMerge(500);
    timeMerge(1000);
    timeMerge(2000);
    timeMerge(5000);
    timeMerge(8000);
    timeMerge(10000);

    std::cout<<"\n";
    std::cout<<"\n";


    std::cout<<"Quick Sort"<<std::endl;
    timeQuick(100);
    timeQuick(500);
    timeQuick(1000);\
    timeQuick(2000);
    timeQuick(5000);
    timeQuick(8000);
    timeQuick(10000);

    std::cout<<"\n";
    std::cout<<"\n";


    std::cout<<"Heap Sort"<<std::endl;
    timeHeap(100);
    timeHeap(500);
    timeHeap(1000);
    timeHeap(2000);
    timeHeap(5000);
    timeHeap(8000);
    timeHeap(10000);


    return 0;
};//end main



