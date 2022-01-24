// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include <stdlib.h>  

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
  // Function : Insertion sort
  for (int i = 1; i <= data.size(); i++)
    {
      int index = i-1;
      int key = data[i];
      while (index >= 0 && data[index] >= key)
	{
	  data[index + 1] = data[index];
	  index--;
	}
      data[index+1] = key;

    }
}
// *******************************  QS  *******************************************
// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(low<high)
    {
    int q=Partition(data, low, high);
    // if(q>0)
    QuickSortSubVector(data, low, q-1);
    // if(q<data.size() - 1)
    QuickSortSubVector(data, q+1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171

    //randomized here and put it to the right
    int r = rand() % (high-low) + low; 
    swap(data[high],data[r]);

    int x = data[high];
    int i = low-1;
    for (int j = low; j < high; j++)
    {
        if(data[j]<=x){
            i++;
            // int temp = data[i];
            // data[i]= data[j];
            // data[j]=temp;
            swap(data[i],data[j]);
        }
    }
    // data[high]=data[i+1];
    // data[i+1]=x;
    swap(data[i+1],data[high]);
    
    return i+1;    
    
}
// *******************************  MS  *******************************************
// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low<high){
        int q=(low+high)/2;
        MergeSortSubVector(data,low, q);
        MergeSortSubVector(data,q+1, high);
        Merge(data,low,q,q+1,high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1=(middle2-low);
    vector<int> L;

    int n2= (high-middle1);
    vector<int> R;

    for (int i = 0; i < n1; i++)
    {
       L.push_back(data[low+i]);
    }
    for (int i = 0; i < n2; i++)
    {
       R.push_back(data[middle2+i]);
    }
    L[n1]=500000000; R[n2]=500000000;
    int indexL=0, indexR=0;

    for (int k = low; k<=high; k++)
    {
        if(L[indexL]<=R[indexR]){
        data[k]=L[indexL];
        indexL++;
        }
        else{
            data[k]=R[indexR];
            indexR++;
        }
    }
    
}
// *******************************  HS  *******************************************
// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

// //Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int leftI=((root+1)*2-1);
    int rightI=(root+1)*2;
    int largest= root;
    if (leftI < heapSize && data[leftI] > data[root]){
        largest = leftI;
    }
    
    if (rightI < heapSize && data[rightI] > data[largest]){
        largest=rightI;
    }

    if (largest != root){
        swap(data[root], data[largest]);// datum in [root] becaome the largest 
        MaxHeapify(data, largest); 
    }

}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i=heapSize/2-1; i>=0; i--){
        MaxHeapify(data, i);
    }
}


