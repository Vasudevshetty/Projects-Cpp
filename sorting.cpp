#include<bits/stdc++.h>
using namespace std;

void bubbleSort(int* A, int n){
    bool swapped;
    for(int i = 0; i < n - 1; i++){
        swapped = false;
        for(int j = 0; j < n - 1 - i; j++){
            if(A[j] > A[j+1]){
                int temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
                swapped = true;
            }
        }
        if(!swapped) break;
    }
}

void insertionSort(int* A, int n){
    for(int i = 1; i < n; i++){
        int x = A[i];
        int j = i - 1;
        while(j > -1 && A[j] > x){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = x;
    }
}

void selectionSort(int* A , int n){
    int i, j, k;
    for(i = 0; i < n-1; i++){
        for(j = k = i; j < n; j++){
            if(A[j] < A[k]) k = j;
        }
        int temp = A[i];
        A[i] = A[k];
        A[k] = temp;
    }
}

void swap(int &x, int &y){
    int temp = x;
    x = y;
    y = temp;
}

int partition(int* A, int l, int h){
    int i = l, j = h;
    int pivot = A[l];
    do{
        do{i++;}while(A[i] <= pivot);
        do{j--;}while(A[j] > pivot);

        if(i<j) swap(A[i], A[j]);
    }while(i<j);
    swap(A[l], A[j]);
    return j;
}

void quickSort(int* A, int l, int h){
    if(l<h){
        int j = partition(A, l, h);
        quickSort(A, l, j-1);
        quickSort(A, j+1, h);
    }
}

void merge(int* A, int l, int mid, int h) {
    int i = l, j = mid + 1, k = 0;
    int* B = new int[h - l + 1]; // Correct the array size

    while (i <= mid && j <= h) { // Use <= in the conditions
        if (A[i] < A[j]) B[k++] = A[i++];
        else B[k++] = A[j++];
    }

    while (i <= mid) B[k++] = A[i++];
    while (j <= h) B[k++] = A[j++];

    for (int i = 0, j = l; i <= h - l; i++, j++) // Use <= in the loop condition
        A[j] = B[i];

    delete[] B; // Don't forget to release the memory
}


void mergeSort(int* A ,int l, int h){
    if(l < h){
        int mid = (h+l)/2;
        mergeSort(A, l, mid);
        mergeSort(A, mid+1, h);

        merge(A, l, mid, h);
    }
}

int main(){
    int a[] = {25,58,96,47,56,54,88,76,36,43}, n = 10;
    mergeSort(a, 0, n-1);
    for(int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}