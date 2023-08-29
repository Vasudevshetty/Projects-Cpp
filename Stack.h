#include<bits/stdc++.h>
using namespace std;
#include"Linkedlist.h"

#define MAX 100

template <class T>
class Stack{
private:
    int size;
    T* A;
    int top;
public:
    Stack() : size(0) , A(NULL), top(-1) {}
    Stack(int size) : size(size){
        A = new T[size];
        top = -1;
    }
    bool isEmpty(){
       return top == -1 ? true : false;
    }
    bool isFull(){
        return top == size - 1 ? true : false;
    }
    void push(T data){
        if(isFull()){
            cout << "Stack overflow\n";
            return;
        }
        top++;
        A[top] = data;
    }
    void pop(){
        if(isEmpty()){
            cout << "No elements to pop\n";
            return;
        }
        if(is_pointer<T>::value) delete &A[top];
        top--;
    }
    T StackTop(){ 
        if(top == -1){
            cout << "No elements\n";
            return T();
        }
        return A[top];
    }
    T peek(int pos){ 
        if(top - pos + 1 < 0){
            cout << "Invalid position\n";
            return T();
        }
        return A[top - pos + 1]; }
    ~Stack(){
        for(int i = 0; i <= top; i++){
            if(is_pointer<T>::value) delete &A[i];
        }
        top = -1;
        size = 0;
        delete []A;
    }
};


template <class T>
class stk{
private:
    Linkedlist<T> lstk;
    Node<T>* top;
public:
    stk(){
        lstk.setHead(NULL);
        top = lstk.getHead();
    }
    bool isEmpty(){
        return !top;
    }
    bool isFull(){
        Node<T>* temp = new Node<T>(T());
        return !temp;
    }
    void push(T data){
        if(isFull()){
            cout << "Stack overflow\n";
            return;
        }
        lstk.Insert(0,data);
        top = lstk.getHead();
    }
    void pop(){
        if(isEmpty()){
            cout << "No elements to delete\n";
            return;
        }
        lstk.Delete(0);
        top = lstk.getHead();
    }
    T getTop(){
        if(isEmpty()) {
            cout << "Stack empty\n";
            return T();
        }
        return lstk.getHead()->getdata();
    }
    T peek(int pos){
        Node<T>* temp = top;
        while(pos > 0 && temp){
            temp = temp->getNext();
            pos--;
        }
        if(!temp){
            cout << "\nInvalid position\n"; 
            return T();
        }   
        return temp->getdata();
    }
};

bool isParanthesisOp(char x){
    if(x == '(' || x == '['  || x == '{') return true;
    else return false;
}
bool isMatchingPair(char open, char close){
    return ((open == '(' && close == ')') || (open == '[' && close == ']') || (open == '{' && close == '}'));
}

bool balanced(string exp){
    Stack<char> stk(10);
    for(int i = 0; i < (int)exp.length(); i++){
        if(isParanthesisOp(exp[i])) stk.push(exp[i]);
        if(!stk.isEmpty() && isMatchingPair(stk.StackTop(), exp[i])){
            if(isParanthesisOp(stk.StackTop()) && !stk.isEmpty()) stk.pop();
            else return false;
        }
    }   
    return stk.isEmpty();
}

bool isOpertor(char x){
    return (x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '`' || x == '(');
}

bool isOperand(char x){
    return (x > '0' && x < '9');
}

int precedence(char x){
    if(x == '+' || x == '-') return 1;
    else if(x == '*' || x == '/') return 2;
    else if(x == '^') return 3;
    else if(x == '`') return 4;
    else if(x == '(') return 5;
    return 0;
}

string postfix(string infix){
    if(!balanced(infix)) return "Unbalanced expression";
    Stack<char> stk(20);
    string postfix;
    for(int i = 0; i < (int)infix.length(); i++){
        if(isOpertor(infix[i])){
            while(!stk.isEmpty() && stk.StackTop() != '(' && precedence(stk.StackTop()) >= precedence(infix[i])){
                postfix += stk.StackTop();
                stk.pop();
            }
            stk.push(infix[i]);
        }else if(infix[i] == '(') stk.push(infix[i]);
        else if(infix[i] == ')' && !stk.isEmpty()){
            while(!stk.isEmpty() && stk.StackTop() != '('){
                postfix += stk.StackTop();
                stk.pop();
            }
            stk.pop();
        }else postfix += infix[i];
    }
    while(!stk.isEmpty()){
        postfix += stk.StackTop();
        stk.pop();
    }
    return postfix;
}

int postfixEval(string postfix){
    int res, op1, op2;
    Stack<char> st(10);
    for(int i = 0; i < (int)postfix.length(); i++){
        if(isOperand(postfix[i])){
            st.push(postfix[i] - '0');
        }else if(isOpertor(postfix[i])){
            op1 = st.StackTop();
            st.pop();
            op2 = st.StackTop();
            st.pop();
            switch(postfix[i]){
                case '+' : res = op1 + op2;
                break;
                case '-' : res = op1 - op2;
                break;
                case '*' : res = op1 * op2;
                break;
                case '/' : res = op1 / op2;
                break;
                case '^' : res = pow(op1, op2);
                break;
                st.push(res);
            }
        }
    }
    return res;
}