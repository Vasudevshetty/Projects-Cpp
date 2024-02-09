#include<bits/stdc++.h>
using namespace std;

#define f(i,a,b) for(int i = a; i < b; i++)


template <class T>
class DiagonalMatrices{
private:
    T* A;
    int n;
public:
    DiagonalMatrices(){
        n = 2;
        A = new T[n];
    }
    DiagonalMatrices(int n){
        this->n = n;
        A = new T[n];
    }
    ~DiagonalMatrices(){ delete []A; }
    void set(int i, int j, T x){
        if(i == j) A[i-1] = x;
    }
    T get(int i, int j){
        if(i == j) return A[i-1];
        else return 0;
    }
    void Display(){
        f(i,0,n){
            f(j,0,n){
                if(i == j) cout << A[i] << " ";
                else cout << "0 ";
            }
            cout << endl;
        }
    }
    int GetDimension(){ return n; }
};

template <class T>
class LowerTri{
private:
    T* A;
    int n;
public:
    LowerTri(){
        this->n = 2;
        A = new T[n*(n+1)/2];
    }
    LowerTri(int n){
        this->n = n;
        A = new T[n*(n+1)/2];
    }
    void set(int i, int j, T x){
        if(i >= j) A[(i*(i-1)/2) + j-1] = x;
        //A[(j-1) *(n - (j-2)/2) + i-j]
    }
    T get(int i, int j){
        if(i < j) return 0;
        else return A[i*(i-1)/2 + j-1];
        //A[(j-1) *(n - (j-2)/2) + i-j]
    }
    void Display(){
        f(i,1,n+1){
            f(j,1,n+1){
                if(i >= j) cout << A[i*(i-1)/2 + j-1] << " ";
            //A[(j-1) *(n - (j-2)/2) + i-j]
                else cout << "0" << " ";
            }
            cout << endl;
        }
    }
};

template <class T>
class UpperTri{
private:
    T* A;
    int n;
public:
    UpperTri(){
        n = 2;
        A = new T[n*(n+1)/2];
    }
    UpperTri(int n){
        this->n = n;
        A = new T[n*(n+1)/2];
    }
    void set(int i, int j, T x){
        if(i <= j) A[n*(i-1) - (i-1)*(i-2)/2 + j-1] = x;
    }
    T get(int i, int j){
        if(i > j) return 0;
        else return A[n*(i-1) - (i-1)*(i-2)/2 + j-1];
    }
    void Display(){
        f(i,1,n+1){
            f(j,1,n+1){
                if(i > j) cout << "0 ";
                else cout << A[n*(i-1) - (i-1)*(i-2)/2 + j-1] << " ";
            }
            cout << endl;
        }
    }
    int getDimension(){ return n; }
};

template <class T>
class TriDiagonal{
private:
    T* A;
    int n;
public:
    TriDiagonal(){
        n = 2;
        A = new T[3*n - 2];
    }
    TriDiagonal(int n){
        this->n = n;
        A = new T[3*n - 2];
    }
    int GetIdx(int i, int j){
        if(i - j == 0) return n - 1 + i - 1;
        else if(i - j == 1) return i - 1;
        else if(i - j == -1) return 2*n - 1 + i - 1;
        else return -1;
    }
    void create(){
        T x;
        f(i,1,n+1){
            f(j,1,n+1){
                cin >> x;
                if(GetIdx(i,j) != -1) A[GetIdx(i,j)] = x;
            }
        }
    }
    void set(int i, int j, T x){
        A[GetIdx(i, j)] = x;
    }
    T get(int i, int j){
        if(i - j == 1) return A[i - 1];
        else if(i - j == 0) return A[n - 1 + i - 1];
        else if(i - j == -1) return A[2*n - 1 + i - 1];
        else return 0;
    }
    void Display(){
        f(i,1,n+1){
            f(j,1,n+1){
                if(GetIdx(i,j) == -1)
                cout << "0 ";
                else cout << A[GetIdx(i,j)] << " ";
            }
            cout << endl;
        }
    }
    int getDimension(){ return n; }
};

template <class T>
class Toeplitz{
private:
    T* A;
    int n;
public:
    Toeplitz(){
        n = 2;
        A = new T[2*n - 1];
    }
    Toeplitz(int n){
        this->n = n;
        A = new T[2*n - 1];
    }
    int GetIdx(int i, int j){
        if(i <= j) return j - i;
        else return n + i - j - 1;
    }
    void set(int i, int j, T x){
        A[GetIdx(i,j)] = x;
    }
    void create(){
        T x;
        f(i,1,n+1){
            f(j,1,n+1){
                cin >> x;
                A[GetIdx(i,j)] = x;
            }
        }
    }
    void Display(){
        f(i, 1, n+1){
            f(j,1,n+1){
                cout << A[GetIdx(i,j)] << " ";
            }
            cout << endl;
        }
    }
};