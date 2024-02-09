#include<bits/stdc++.h>
using namespace std;
#ifndef ARRAY_H
#define ARRAY_H

#define  f(i,a,b) for(int i = a; i < b; i++) 

template<class T>
class Array{
private:
    T *A;
    int size;
    int length;
public:
    T sum;
    Array(){
        size = 10;
        A = new T[size];
        length = 0;
        sum = 0;
    }
    Array(int sz){
        size = sz;
        A = new T[size];
        length = 0;
        sum = 0;
    }
    void Insert(int idx, T x);
    T Delete(int idx);
    void Display();
    T* rotate(int k);
    int Search(T key);
    int Search(T key,int st, int end);
    void append(T x);
    int Length(){ return length; }
    void swap(int x, int y);
    bool isEmpty(){
        return (length == 0 || length < size) ? true : false; 
    }
    bool isSorted();
    bool isSortR(int i);
    void Set(int idx, T x);
    T Get(int idx);
    T Max();
    T Min();
    T sumR(int n);
    T Sum(){ return sumR(length - 1); } 
    T SumR(int i);
    T* Reverse();
    void Rotate(int k);
    void Rev();
    void Sort();
    float Avg(){ return (float)Sum()/length; }
    void Copy(T* R);
    void RightShift();
    void LeftShift();
    int findIdx(T x);
    void negPos();
    void InsertAtSort(T x){ Insert(findIdx(x), x); }
    void minMax();
    void Missing();
    void duplicates();
    void pairSum(int k);
    ~Array(){ delete []A; }
};

template <class T>
void Array<T>::pairSum(int k){
    T h = Max();
    vector<int> H(h+1,0);
    if(isSorted()){
        f(i,0,length)
            if(H[k - A[i]] != 0) cout << A[i] << " + " << k - A[i] << " = " << k << endl; else H[A[i]]++;
    }else{
        int i = 0, j = length - 1;
        while(i < j){
            if(A[i] + A[j] == k) {
                cout << A[i] << " + " << A[j] << " = " << k << endl;
                i++; j--;
            }else if(A[i] + A[j] < k) i++;
            else j--;
        }
    }
}

template <class T>
void Array<T>::duplicates(){
    T h = Max();
    vector<int> H(h+1,0);
    f(i,0,length) H[A[i]]++;
    f(i,0,h+1){
        if(H[i] > 1)
         cout << i << " is repated " << H[i] << " times " << endl;
    }
}

template<class T>
void Array<T>::Missing(){
    T l, h, diff, s;
    h = Max();
    if(isSorted()){
        if(h - length > 1){
            l = Min();
            diff = l;
            f(i, 0 , length){
            if(A[i] - i != diff){
                while(diff < A[i] - i){
                    cout << i + diff << " ";
                    diff++;
                }
            }
        }
        cout << endl;
        }else{
            s = h*(h+1)/2;
            cout << s - sum << endl;
        }
    }else{
        vector<int> H(h+1,0);
        f(i,0,length) H[A[i]]++;
        f(i,0,(int)H.size()+1){
            if(H[i] == 0) cout << i << " ";
        } 
        cout << endl;
    }
}

template <class T>
void Array<T>::minMax(){
    T min, max;
    min = max = A[0];
    f(i,1,length)
        (A[i] < min) ? min = A[i] : (A[i] > max) ? max = A[i]: 0;
    cout << min << " " <<  max << endl;
}

template <class T>
void Array<T>::Rotate(int k){
    T* B = new int[length];
    f(i,0,length) B[i] = A[(i+k) % length];
    f(i,0,length) A[i] = B[i];
    delete []B;
}

template <class T>
T* Array<T>::rotate(int k){
    T* B = new int[length];
    for(int i = 0; i < length; i++){
        B[i] = A[(i+k)%length];
    }
    return B;
    delete B;
}

template <class T>
void Array<T>::negPos(){
    int i = 0, j = length - 1;
    while(i < j){  
    while(A[i] < 0) i++;
    while(A[j] >= 0) j--;
    if(i < j)
    swap(i, j);
    }
}

template <class T>
int Array<T>::findIdx(T x){
    for(int i = 0; i < length; i++){
        if(A[i] > x) return i; 
    }
}

template <class T>
void Array<T>::Rev(){
    int i = 0, j = length - 1;
    while(i < j){
        swap(i,j);
        i++; j--;
    }
}
template <class T>
void Array<T>::Copy(T* R){
    f(i,0,length) A[i] = R[i];
    delete []R;
}
template <class T> 
T* Array<T>::Reverse(){
    T* R = new int[length];
    f(i, 0 , length){
        R[i] = A[length - 1 - i];
    }
    f(i,0,length) A[i] = R[i];
    delete []R;
    return A;
}
template <class T> 
T Array<T>::sumR(int n){
    if(n < 0) return 0;
    else return sumR(n - 1) + A[n];
}
template <class T>
T Array<T>::Min(){
    T min = A[0];
    for(int i = 0; i < length; i++){
        if(A[i] < min) min = A[i];
    }
    return min;
}
template <class T>
T Array<T>::SumR(int i){
    static T sum = 0;
    if(i >= length) {
        T result = sum;
        sum = 0;
        return result;
    }else{
        sum += A[i];
    return SumR(i+1);
    }
}
template <class T>
T Array<T>::Max(){
    T max = A[0];
    for(int i = 0; i < length; i++){
        if(A[i] > max) max = A[i];
    }
    return max;
}
template <class T>
T Array<T>::Get(int idx){
    if(idx < 0 || idx > length) return -1;
    return A[idx];
}
template <class T>
void Array<T>::Set(int idx, T x){
    if(idx < 0 || idx > length) return;
    A[idx] = x;
}
template <class T>
bool Array<T>::isSorted(){
    if(length<=1) return true;
    return isSortR(0);
}
template <class T>
bool Array<T>::isSortR(int i){
    if(i > length) return true;
    if(A[i+1] < A[i]) return false;
    return isSortR(i+1);
}
template <class T>
int Array<T>::Search(T key){
    f(i,0,length){
        if(A[i] == key) return i;
    }
    return -1;
}
template <class T>
int Array<T>::Search(T key, int st, int end){
    if(st >= end) return -1;
    int mid = (st+end)/2;
    if(A[mid] == key) return mid;
    else if (A[mid] > key) return Search(key, st, mid - 1);
    else return Search(key, mid + 1, end);
}
template <class T> 
void Array<T>::Insert(int idx, T x){
    if(idx >= 0 && idx <= length){
        for(int i = length; i > idx; i--)
            A[i] = A[i - 1];
        A[idx] = x;
        length++;
    }
    sum += A[idx];
}

template <class T>
void Array<T>::swap(int x, int y){
    if(x < 0 || x > length || y < 0 || y > length ) return;
    T temp = A[x];
    A[x] = A[y];
    A[y] = temp;
}
template <class T>
void Array<T>::append(T x){
    if(length < size){
        A[length++] = x;
    }
    cout << "Array full\n";
    return;
}
template <class T>
void Array<T>:: Display(){
    f(i,0,length) cout << A[i] << " ";
    cout << endl;
}
template <class T>
T Array<T>:: Delete(int idx){
    T x = 0;
    sum -= A[idx];
    if(idx >= 0 && idx < length){
        x = A[idx];
        f(i,idx,length - 1) A[i] = A[i+1];
        length--;
    }
    return x;
}

#endif