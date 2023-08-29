#include<bits/stdc++.h>
using namespace std;

#include"Linkedlist.h"

#define f(i,a,b) for(int i = a; i < b; i++)

template <class T>
class Queue{
private:
    T* Q;
    int front;
    int rear;
    int size;
public:
    Queue() : size(0) , front(-1), rear(-1), Q(NULL) {}
    Queue(int size){
        front = rear = -1;
        this->size = size;
        Q = new T[size];
    }    
    Queue(T* Q, int size){
        front = 0;
        rear = size - 1;
        this->Q = Q;
        this->size = size;
    }
    bool isFull(){
        return rear == size - 1 ? true : false;
    }
    bool isEmpty(){
        return front == rear ? true : false;
    }
    void enqueue(T x){
        if(isFull()){
            cout << "Queue is full\n";       
            return;
        }
        if(rear == -1) front++;
        rear++;
        Q[rear] = x;
    }
    T dequeue(){
        if(isEmpty()){
            cout << "No elements to delete\n";
            return T();
        }
        T x = Q[front];
        front++;
        return x;
    }
    T first(){ return Q[front]; }
    T last(){ return Q[rear]; }
    friend istream & operator>>(istream &is, Queue<T> &q){
        T x;
        cout << "Enter the size of the queue : ";
        cin >> q.size;
        cout << "Enter element of the queue\n";
        f(i, 0, q.size){
            cin >> x;
            q.enqueue(x);
        }
        return is;
    }
    friend ostream & operator<<(ostream &os, Queue<T> &q){
        if(q.isEmpty()){
            os << "Queue is empty\n";
            return os;
        }
        cout << "Elements in the queue are, \n";
        int f = q.front;
        while(f <= q.rear){
            os << q.Q[f] << " ";
            f++;
        }
        return os;
    }
    ~Queue(){ delete []Q; }
};

template <class T>
class CircularQueue{
private:   
    T* Q;
    int front;
    int rear;
    int size;
public:
    CircularQueue() : front(0), rear(0), size(10) {
        Q = new T[size];
    }
    CircularQueue(int size){
        this->size = size;
        front = rear = 0;
        Q = new T[this->size];
    }
    bool isFull(){
        return (rear+1)%size == front ? true : false;
    }
    bool isEmpty(){
        return rear == front ? true : false;
    }
    void enqueue(T x){
        if(isFull()){
            cout << "Queue is full \n";
            return;
        }
        rear = (rear+1)%size;
        Q[rear] = x;
    }
    T dequeue(){
        if(isEmpty()){
            cout << "Queue is empty\n";
            return T();
        }
        T x = Q[front];
        front = (front + 1) % size;
        return x;
    }
    friend istream & operator>>(istream &is, CircularQueue &q){
        cout << "Enter size of the queue : ";
        is >> q.size;
        cout << "Enter elements of the queue : \n";
        T x;
        int sz = q.size;
        while(sz > 1){
            is >> x;
            q.enqueue(x);
            sz--;
        }
        return is;
    }
    friend ostream & operator<<(ostream &os, CircularQueue &q){
        if(q.isEmpty()){
            os << "No elements in the queue\n";
            return os;
        }
        os << "Elements of the queue are : ";
        int f = q.front + 1;
        do{
            os << q.Q[f] << " ";
            f = (f+1)%q.size;
        }while(f != (q.rear+1)%q.size);
        return os;
    }
    ~CircularQueue(){ delete []Q; }
};

template <class T>
class QueueLL{
private:
    Node<T>* front;
    Node<T>* rear;
public:
    QueueLL() : front(NULL), rear(NULL) {}
    QueueLL(Node<T>* head){
        front = head;
        Node<T>* temp = head;
        while(temp && temp->getNext()) temp = temp->getNext();
        rear = temp;
    }
    bool isEmpty(){
        return front == NULL;
    }
    void enqueue(T x){
        Node<T>* temp = new Node<T>(x);
        if(isEmpty()){
            front = rear = temp;
        }else{
            rear->setNext(temp);
            rear = temp;
        }
    }
    T dequeue(){
        T x = T();
        if(isEmpty()){
            cout << "Queue is empty\n";
        }else{
            Node<T>* temp = front;
            front = front->getNext();
            x = temp->getdata();
            delete temp;
        }
        return x;
    }
    friend istream & operator>>(istream &is, QueueLL<T> &q){
        int size;
        cout << "Enter the size of the Queue : ";
        is >> size;
        T* x = new T[size];
        cout << "Enter elements of the queue :\n";
        f(i,0,size){
            is >> x[i];
            q.enqueue(x[i]);
        }
        delete []x;
        return is;
    }
    friend ostream & operator<<(ostream &os, QueueLL<T> &q){
        Node<T>* temp = q.front;
        if(q.isEmpty()){
            os << "Queue is empty\n";
            return os;
        }
        os << "Elements of the queue are, \n";
        while(temp){
            os << temp->getdata() << " ";
            temp = temp->getNext();
        }
        return os;
    }
    ~QueueLL(){
        while(!isEmpty()) dequeue();
    }
};