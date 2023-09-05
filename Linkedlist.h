#include<bits/stdc++.h>
using namespace std;

template <class T>
class Linkedlist;

template <class T>
class Node{
private:
    T data;
    Node<T>* next;
public:
    Node() : data(T()) , next(NULL) {}
    Node(T val) : data(val) , next(NULL) {}
    T getdata(){ return data; }
    void setdata(T data){ this->data = data; }
    void setNext(Node<T>* next){ this->next = next; }
    Node<T>* getNext(){ return next; }
    friend Linkedlist<T>;
};

template <class T>
class Linkedlist{
private:
    Node<T>* head;
    int count;
public:
    Linkedlist(): head(NULL), count(0) {}
    void printCycle();
    Linkedlist(T* A, int n);
    Linkedlist(T* A, int n, bool circular);
    ~Linkedlist();
    bool loop();
    int getLength(){ return count; }
    void append(Linkedlist<T> &l);
    bool circular();
    Node<T>* getHead(){ return head; }
    void setHead(Node<T>* head){ this->head = head; }
    friend ostream& operator<<(ostream &os, Linkedlist<T> &l){
        Node<T>* temp = l.getHead();
        if(!temp){
            cout << "NULL\n";
        }
        else if(l.circular()){
            do{
                cout << temp->getdata() << "->";
                temp = temp->getNext();
            }while(temp != l.getHead());
            cout << temp->getdata();
            cout << "\nThe linked list is circular\n";
        }
        else if(l.loop())
            l.printCycle();
        else{
            while(temp){
                cout << temp->getdata() << "->";
                temp = temp->getNext();
            }
            cout << "NULL\n";
        }
        return os;
    }
    friend istream& operator>>(istream &is, Linkedlist<T> &l){
        cout << "Enter no of nodes/elements : ";
        cin >> l.count;
        if(l.count < 0) l.head = NULL;
        else{
            T* A = new T[l.count];
            for(int i = 0; i < l.count; i++) cin >> A[i];
            l.head = new Node<T>(A[0]);
            Node<T>* current = l.head;
            for(int i = 0; i < l.count-1; i++){
                Node<T>* temp = new Node<T>(A[i+1]);
                current->setNext(temp);
                current = current->getNext();
            }
            delete []A;
        }
        return is;
    }
    void revDisplay(Node<T>* temp);
    T sum();
    void BreakCycloop();
    T max();
    T min();
    Node<T>* search(T data);
    void Sort();
    void Insert(int pos, T data);
    void Insert(int pos, T data, bool circular);
    void Insert(T data);
    bool isSorted();
    T Delete(int pos);
    void removeDuplicates();
    void reverse();
    void rev(Node<T>* p, Node<T>* q);
    void removeDuplicates(bool nonconsective);
    void merge(Linkedlist<T> &p, Linkedlist<T> &q);
    T Delete(int pos, bool circular);
    Node<T>* middle();
};

template <class T>
Node<T>* Linkedlist<T>::middle(){
    Node<T>* temp, *curr;
    temp = curr = getHead();
    while(temp){
        temp = temp->getNext();
        if(temp) temp = temp->getNext();
        if(temp) curr = curr->getNext();
    }
    return curr;
}

template <class T>
T Linkedlist<T>::Delete(int pos, bool circular){
    T data = T();
    if(pos <= 0 || pos > getLength()){
        cout << "Invalid position for deletion\n";
        return data;
    }
    if(!circular) Delete(pos);
    Node<T>* temp = getHead();
    Node<T>* curr;
    if(pos==1){
        while(temp->getNext() != getHead()) temp = temp->getNext();
        data = temp->getdata();
        if(temp==getHead()){
            delete temp;
            setHead(NULL);
        }else{
            curr = getHead()->getNext();
            temp->setNext(curr);
            setHead(curr);
            delete temp->getNext();
        }
    }else{
        for(int i = 0; i < pos-2; i++) temp = temp->getNext();
        curr = temp->getNext();
        data = curr->getdata();
        temp->setNext(curr->getNext());
        delete curr;
    }
    count--;
    return data;
}

template <class T>
void Linkedlist<T>::Insert(int pos, T data, bool circular){
    if(!circular) Insert(pos, data);
    pos = pos > getLength() ? pos % getLength() : pos;
    Node<T>* temp = new Node<T>(data);
    Node<T>* curr = getHead();
    if(pos <= 0){
        if(!getHead()){
            temp->setNext(getHead());
            setHead(temp);
        }
        else{
            while(curr->getNext() != getHead()) curr = curr->getNext();
            curr->setNext(temp);
            temp->setNext(getHead());
            setHead(temp);
        }
    }else{
        for(int i = 1; i < pos; i++) curr = curr->getNext();
        if(curr){
            temp->setNext(curr->getNext());
            curr->setNext(temp);
        }
    }
    count++;
}

template <class T>
bool Linkedlist<T>::circular(){
    Node<T>* temp = getHead();
    if(getLength() == 1) return true;
    do{
        temp = temp->getNext();
        if(!temp) return false;
    }
    while(temp != getHead());
    return true;
}

template <class T>
void Linkedlist<T>::printCycle(){
    Node<T>* temp = getHead();
    unordered_set<Node<T>*> visited;
    while(temp){
        if(visited.count(temp)){
            cout << temp->getdata() << "\nCycle detected at node with data " << temp->getdata() << "\n";
            break;
        }
        visited.insert(temp);
        cout << temp->getdata() << "->";
        temp = temp->getNext();
    }
}

template <class T>
bool Linkedlist<T>::loop(){
    Node<T>* slow = getHead();
    Node<T>* fast = getHead();
    while(fast && fast->getNext()){
        slow = slow->getNext();
        fast = fast->getNext()->getNext();
        if(slow == fast) return true;
    }    
    return true;
}

template <class T>
void Linkedlist<T>::merge(Linkedlist<T> &p, Linkedlist<T> &q){
    Node<T>* temp1 = p.getHead();
    Node<T>* temp2 = q.getHead();
    if(!temp1){
        setHead(temp2);
        count = q.getLength();
        return;
    }
    if(!temp2){
        setHead(temp1);
        count = p.getLength();
        return;
    }
    if(temp1->getdata() > temp2->getdata()){
        setHead(temp2);
        temp2 = temp2->getNext();
    }else {
        setHead(temp1);
        temp1 = temp1->getNext();
    }
    Node<T>* curr = getHead();
    while(temp1 && temp2){
        if(temp1->getdata() < temp2->getdata()){
            curr->setNext(temp1);
            temp1 = temp1->getNext();
        }else{
            curr->setNext(temp2);
            temp2 = temp2->getNext(); 
        }
        curr = curr->getNext();
    }
    if(temp1) curr->setNext(temp1);
    else if(temp2) curr->setNext(temp2);
    count = p.getLength() + q.getLength();
    return;
}

template <class T>
void Linkedlist<T>::append(Linkedlist<T> &l){
    if(l.getHead()) return;
    Node<T>* temp = getHead();
    while(temp->getNext()){
        temp = temp->getNext();
    }
    temp->setNext(l.getHead());
    count += l.getLength();
}

template <class T>
void Linkedlist<T>::rev(Node<T>* q, Node<T>* p){
    if(p){
        rev(p,p->getNext());
        p->setNext(q);
    }else setHead(q);
}

template <class T>
void Linkedlist<T>::reverse(){
    Node<T>* p = getHead();
    Node<T>* q = NULL;
    Node<T>* r = NULL;

    while(p){
        r = q;
        q = p;
        p = p->next;
        q->setNext(r);
    }
    setHead(q);
}

template <class T>
void Linkedlist<T>::removeDuplicates(){
    if(!getHead()) return;
    Node<T>* temp = getHead();
    while(temp && temp->getNext()){
        if(temp->getdata() == temp->getNext()->getdata()){
            Node<T>* curr = temp->getNext();
            temp->setNext(curr->getNext());
            delete curr;
        }
        temp = temp->getNext();
    }
}

template <class T>
void Linkedlist<T>::removeDuplicates(bool nonconsective){
    if(!nonconsective) return;
    Node<T>* temp = getHead();
    Node<T>* curr = NULL;
    unordered_set<T> seen;
    while(temp){
        if(seen.count(temp->getdata())){
            curr->setNext(temp->getNext());
            delete temp;
            temp = curr->getNext();
        }else{
            seen.insert(temp->getdata());
            curr = temp;
            temp = temp->getNext();
        }
    }
}

template <class T>
T Linkedlist<T>::Delete(int pos){
    T Data  = T();
    if(pos < 0 || pos > getLength()){
        cout << "Invalid position for deletion\n";
        return Data;
    }
    Node<T>* temp = getHead();
    if(pos == 0){
        setHead(temp->getNext());
        Data = temp->getdata();
        delete temp;
    }else{
        for(int i = 1; i < pos - 1; i++) temp = temp->getNext();
        Node<T>* curr = temp->getNext();
        Data = curr->getdata();
        temp->setNext(curr->getNext());
        delete curr;
    }
    count--;
    return Data;
}

template <class T>
bool Linkedlist<T>::isSorted(){
    Node<T>* temp = getHead();
    while(temp && temp->getNext()){
        if(temp->getdata() < temp->getNext()->getdata()) temp = temp->getNext();
        else return false;
    }
    return true;
}

template <class T>
void Linkedlist<T>::Sort(){
    
}

template <class T>
void Linkedlist<T>::Insert(int pos, T data){
    if(pos > count){
        cout << "Invalid position for insertion\n";
        return;
    }
    Node<T>* temp = new Node<T>(data);
    Node<T>* current = getHead();
    if(pos == 0){
        temp->next = getHead();
        head = temp;
    }else{
        for(int i = 0; i < pos - 1; i++) current = current->getNext();
        if(current){
            temp->setNext(current->getNext());
            current->setNext(temp); 
        }
    }
    count++;
}

template <class T>
void Linkedlist<T>::Insert(T data){
    Node<T>* temp = new Node<T>(data);
    Node<T>* current = getHead();
    if(isSorted()){
        while(current && current->getNext()){
                if(current->getNext()->getdata() < temp->getdata()) current = current->getNext();
                else break;
            }
            temp->setNext(current->getNext());
            current->setNext(temp);
            count++;
    }else{
        cout << "The Linked list is not sorted, Insertion failed";
    }
}


template <class T>
Node<T>* Linkedlist<T>::search(T data){
    Node<T>* temp = getHead();
    Node<T>* prev = NULL;
    while(temp){
        if(data == temp->getdata()){ 
            prev->next = temp->next;
            temp->next = getHead();
            head = temp;
            return temp;
        }
        prev = temp;
        temp = temp->getNext();
    }
    return NULL;
}

template <class T>
T Linkedlist<T>::max(){
    Node<T>* temp = getHead();
    T max = INT_MIN;
    while(temp){
        if(temp->getdata() > max) max = temp->getdata();
        temp = temp->getNext();
    }
    return max;
}

template <class T>
T Linkedlist<T>::min(){
    Node<T>* temp = getHead();
    T min = INT_MAX;
    while(temp){
        if(temp->getdata() < min) min = temp->getdata();
        temp = temp->getNext();
    }
    return min;
}

template <class T>
Linkedlist<T>::Linkedlist(T* A, int n){
    head = new Node<T>(A[0]);
    Node<T>* current = head;
    for(int i = 1; i < n; i++){
        Node<T>* temp = new Node<T>(A[i]);
        current->setNext(temp);
        current = current->getNext();
    }
    count = n;
    delete[] A; 
}

template <class T>
Linkedlist<T>::Linkedlist(T* A, int n, bool circular){
    head = new Node<T>(A[0]);
    Node<T>* current = getHead();
    for(int i = 1; i < n; i++){
        Node<T>* temp = new Node<T>(A[i]);
        current->setNext(temp);
        current = current->getNext();
    }
    if(circular && current) current->setNext(getHead());
    count = n;
    delete[] A;
}

template <class T>
void Linkedlist<T>::BreakCycloop(){
    Node<T>* slow = getHead();
    Node<T>* fast = getHead();
    while(fast && fast->getNext()){
        slow = slow->getNext();
        fast = fast->getNext()->getNext();
        if(slow == fast) break;
    }
    if(slow == fast){
        setHead(fast);
        while(slow->getNext() != fast->getNext()){
            slow = slow->getNext();
            fast = fast->getNext();
        }
        slow->setNext(NULL);
    }
}

template <class T>
Linkedlist<T>::~Linkedlist(){
    Node<T>* current = getHead();
    Node<T>* temp = NULL;
    if(circular() || loop()) BreakCycloop();
    while(current){
        temp = current->getNext();
        delete current;
        current = temp;
    }
}

template <class T>
void revDisplay(Node<T>* temp){
    if(temp){
        revDisplay(temp->getNext());
        cout << temp->getdata() << "->";
    }
}

template <class T>
T Linkedlist<T>::sum(){
    T sum = T();
    Node<T>* temp = getHead();
    while(temp){
        sum += temp->getdata();
        temp = temp->getNext();
    }   
    return sum;
}