#include<bits/stdc++.h>
using namespace std;

#include"Trees.h"

template <class T>
void Inorder(BT<T> &t){
    Node<T>* temp = t.getRoot();
    stack<Node<T>*> s;
    while(temp || !s.empty()){
        if(temp){
            s.push(temp);
            temp = temp->lchild;
        }else{
            temp = s.top();
            s.pop();
            cout << temp->data << " ";
            temp = temp->rchild;
        }
    }
}

template <class T>
void Preorder(BT<T> &t){
    Node<T>* temp = t.getRoot();
    stack<Node<T>*> s;
    while(temp || !s.empty()){
        if(temp){
            cout << temp->data << " ";
            s.push(temp);
            temp = temp->lchild;
        }else{
            temp = s.top();
            s.pop();
            temp = temp->rchild;
        }
    }
}

template <class T>
void Postorder(BT<T> &t){
    Node<T>* temp = t.getRoot();
    stack<long int> s;
    long int tr;
    while(temp || !s.empty()){
        if(temp){
            s.push((long int)temp);
            temp = temp->lchild;
        }else{
            tr = s.top();
            s.pop();
            if(tr > 0){
                s.push(-tr);
                temp = (Node<T>*)tr;
                temp = temp->rchild;
            }else{
                cout << ((Node<T>*)-tr)->data << " ";
            }
        }
    }
}

template <class T>
void Levelorder(BT<T> &t){
    Node<T>* temp = t.getRoot();
    queue<Node<T>*> q;
    q.push(temp);
    while(!q.empty()){
        temp = q.front();
        q.pop();
        cout << temp->data << " ";
        if(temp->lchild) q.push(temp->lchild);
        if(temp->rchild) q.push(temp->rchild);
    }
}

template <class T>
Node<T>* generateTreeTraversels(vector<T> &inorder, vector<T> &preorder, int inStart, int inEnd){
    static int preIdx = 0;
    if(inStart > inEnd) return NULL;

    Node<T>* node = new Node<T>(preorder[preIdx++]);

    if(inStart == inEnd) return node;

    int inIdx = inStart;
    while(inorder[inIdx] != node->data) inIdx++;

    node->lchild = generateTreeTraversels(inorder, preorder, inStart, inIdx - 1);
    node->rchild = generateTreeTraversels(inorder, preorder, inIdx + 1, inEnd);

    return node;
}

int main(){
    BT<char> t;
    vector<char> inorder = {'D','B','E','A','F','C','G'};
    vector<char> preorder = {'A','B','D','E','C','F','G'};
    t.setRoot(generateTreeTraversels(inorder, preorder, 0, 6));
    cout << t << endl;
    cout << t.leafNodeCount(t.getRoot()) << endl;
    return 0;
}