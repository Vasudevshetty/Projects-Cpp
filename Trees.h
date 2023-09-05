#include<bits/stdc++.h>
using namespace std;

template <class T>
class Node{
public:
    T data;
    Node<T>* rchild;
    Node<T>* lchild;
    Node(): data(0), rchild(NULL), lchild(NULL) {}
    Node(T data){
        this->data = data;
        rchild = lchild = NULL;       
    }
    int height;
    
};


template <class T>
void preOrder(Node<T>* root){
    if(!root) return;
    cout << root->data << " ";
    preOrder(root->lchild);
    preOrder(root->rchild);
}
template <class T>
void inOrder(Node<T>* root){
    if(!root) return;
    inOrder(root->lchild);
    cout << root->data << " ";
    inOrder(root->rchild);
}
template <class T>
void postOrder(Node<T>* root){
    if(!root) return;
    postOrder(root->lchild);
    postOrder(root->rchild);
    cout << root->data << " ";
}
template <class T>
void levelOrder(Node<T>* root){
    queue<Node<T>*> q;
    if(!root){
        cout << "No elemnts in the tree\n"; 
        return;
    }
    q.push(root);
    while(!q.empty()){
        Node<T>* temp = q.front();
        q.pop();
        cout << temp->data << " ";
        if(temp->lchild){
            q.push(temp->lchild);
        }
        if(temp->rchild){
            q.push(temp->rchild);
        }
    }
}

template <class T>
int heightR(Node<T>* root){
    int x , y;
    x = y = 0;
    if(!root) return 0;
    x = heightR(root->lchild);
    y = heightR(root->rchild);
    return x > y ? x + 1 : y + 1;
}
    
template <class T>
class BT{
private:
    Node<T>* root;
public:
    BT() : root(NULL) {}
    void setRoot(Node<T>* root){ this->root = root; }
    BT(Node<T>* root) { this->root = root; }
    Node<T>* getRoot(){ return root; }
    int leafNodeCount(Node<T>* p){
        if(!p) return 0;
        if(!p->lchild && !p->rchild) return 1;
        return leafNodeCount(p->lchild) + leafNodeCount(p->rchild);
    }
    int height(){ return heightR(getRoot()); }
    friend istream & operator>>(istream &is, BT<T> &t){
        Node<T>* curr;
        Node<T>* temp;
        T x;
        queue<Node<T>*> q;
        cout << "Enter root value : ";
        is >> x;
        t.root = new Node<T>(x);
        q.push(t.root);
        while(!q.empty()){
            curr = q.front();
            q.pop();
            cout << "Enter the value of left child : ";
            is>>x;
            if(x != -1){
                temp = new Node<T>(x);
                curr->lchild = temp;
                q.push(temp);
            }
            cout << "Enter the value of right child : ";
            is >> x;
            if(x != -1){
                temp = new Node<T>(x);
                curr->rchild = temp;
                q.push(temp);
            }
        }
        return is;
    } 
    friend ostream & operator<<(ostream &os, BT<T> &t){
        int choice;
        os << "Enter the way it should be displayed\n1.Preorder 2.Inorder 3.Postorder 4.Levelorder\n";
        cin >> choice;
        switch(choice){
            case 1 : preOrder(t.getRoot());
            break;
            case 2 : inOrder(t.getRoot());
            break;
            case 3 : postOrder(t.getRoot());
            break;
            case 4 : levelOrder(t.getRoot());
            break;
            default: os << "Give preferred choices only\n";
        }
        cout << endl;
        return os;
    }
};

template <class T>
class BST{
private:
    Node<T>* root;
public:
    BST() : root(NULL) {}
    void setRoot(Node<T>* root){ this->root = root; }
    Node<T>* getRoot(){ return root; }
    bool Search(T key){
        Node<T>* temp = getRoot();
        return Rsearch(temp, key);
    }
    Node<T>* search(T key){
        Node<T>* temp = getRoot();
        return Rsearch(temp, key);
    }
    Node<T>* Rsearch(Node<T>* temp, T key){
        if(!temp) return NULL;
        if(key == temp->data) return temp;
        else if(key < temp->data) Rsearch(temp->lchild, key);
        else Rsearch(temp->rchild, key);
    }
    void Insert(T data){
        Node<T>* temp = getRoot();
        if(!temp){
            temp = new Node<T>(data);
            setRoot(temp);
            return;    
        }
        Node<T>* tail;
        if(Search(data)) return;
        else{
            Node<T>* node = new Node<T>(data);
            while(temp){
                tail = temp;
                if(data < temp->data) temp = temp->lchild;
                else if(data > temp->data) temp = temp->rchild;
            }
            if(tail->data > node->data) tail->lchild = node;
            else tail->rchild = node;
        }
    }
    void Delete(T key){
        DeleteR(getRoot(), key);
    }
    Node<T>* InPre(Node<T>* p){
        while(p && p->rchild) p = p->rchild;
        return p;
    }
    Node<T>* InSucc(Node<T>* p){
        while(p && p->lchild) p = p->lchild;
        return p;
    }
    int Height(Node<T>* p){
        if(!p) return 0;
        return Height(p->lchild) + Height(p->rchild) + 1;
    }
    Node<T>* DeleteR(Node<T>* p, T key){
        if(!p) return NULL;
        if(!p->lchild && !p->rchild){
            if(p == getRoot())
                setRoot(NULL);
            delete p;
            return NULL;
        }
        if(key < p->data) 
            p->lchild = DeleteR(p->lchild, key);
        else if(key > p->data)
            p->rchild = DeleteR(p->rchild, key);
        else{
                Node<T>* q;
            if(Height(p->lchild) > Height(p->rchild)){
                q = InPre(p->lchild);
                p->data = q->data;
                p->lchild = DeleteR(p->lchild, q->data);
            }else{
                q = InSucc(p->rchild);
                p->data = q->data;
                p->rchild = DeleteR(p->rchild, q->data);
            }
        }
        return p;
    }
    friend istream & operator>>(istream &is, BST<T> &t){
        int size;
        T x;
        cout << "Enter the no of elements of the tree : ";
        is >> size;
        cout << "Enter the elements of the tree : \n";
        while(size--){
            is >> x;
            t.Insert(x);
        }
        return is;
    }
    friend ostream & operator<<(ostream &os, BST<T> &t){
        int choice;
        os << "Enter the way it should be displayed\n1.Preorder 2.Inorder 3.Postorder 4.Levelorder\n";
        cin >> choice;
        switch(choice){
            case 1 : preOrder(t.getRoot());
            break;
            case 2 : inOrder(t.getRoot());
            break;
            case 3 : postOrder(t.getRoot());
            break;
            case 4 : levelOrder(t.getRoot());
            break;
            default: os << "Give preferred choices only\n";
        }
        cout << endl;
        return os;
    }
};

template <class T>
class AVLtrees{
private:
    Node<T>* root;
public:
    AVLtrees() : root(nullptr) {}
    void setRoot(Node<T>* root){ this->root = root; }
    Node<T>* getRoot(){ return root; }
    AVLtrees(Node<T>* root){ this->root = root; }
    int nodeHeight(Node<T>* temp){
        int hl, hr;
        hl = temp && temp->lchild ? temp->lchild->height : 0;
        hr = temp && temp->rchild ? temp->rchild->height : 0;
        return hl>hr ? hl + 1 : hr + 1;
    }
    int balanceFactor(Node<T>* temp){
        int hl, hr;
        hl = temp && temp->lchild ? temp->lchild->height : 0;
        hr = temp && temp->rchild ? temp->rchild->height : 0;
        return hl - hr;
    }
    Node<T>* LLRotation(Node<T>* temp){
        Node<T>* tLeft = temp->lchild;
        Node<T>* tlRight = tLeft->rchild;

        tLeft->rchild = temp;
        temp->lchild = tlRight;
        temp->height = nodeHeight(temp);
        tLeft->height = nodeHeight(tLeft);

        if(temp == getRoot()) setRoot(tLeft);
        return tLeft; 
    }
    Node<T>* RRRotation(Node<T>* temp){
        Node<T>* tRight = temp->rchild;
        Node<T>* trLeft = tRight->rchild;

        tRight->lchild = temp;
        temp->rchild = trLeft;
        temp->height = nodeHeight(temp);
        tRight->height = nodeHeight(tRight);

        if(temp == getRoot()) setRoot(tRight);
        return tRight; 
    }
    Node<T>* LRRotation(Node<T>* temp){
        Node<T>* tLeft = temp->lchild;
        Node<T>* tlRight = tLeft->rchild;

        tLeft->rchild = tlRight->lchild;
        temp->lchild = tlRight->rchild;

        tlRight->lchild = tLeft;
        tlRight->rchild = temp;

        tLeft->height = nodeHeight(tLeft);
        tlRight->height = nodeHeight(tlRight);
        temp->height = nodeHeight(temp);

        if(temp == getRoot()) setRoot(tlRight);

        return tlRight;
    }
    Node<T>* RLRotation(Node<T>* temp){
        Node<T>* tRight = temp->rchild;
        Node<T>* trLeft = tRight->lchild;

        tRight->lchild = trLeft->rchild;
        temp->rchild = trLeft->lchild;

        trLeft->lchild = temp;
        trLeft->rchild = tRight;

        tRight->height = nodeHeight(tRight);
        trLeft->height = nodeHeight(trLeft);
        temp->height = nodeHeight(temp);

        if(temp == getRoot()) setRoot(trLeft);

        return trLeft;
    }
    Node<T>* InsertR(Node<T>* curr, T data){
        Node<T>* temp = new Node<T>(data);
        if(!curr){
            temp->height = 1;
            return temp;
        }
        if(data < curr->data) curr->lchild = InsertR(curr->lchild, data);
        else if(data > curr->data) curr->rchild = InsertR(curr->rchild, data);
        curr->height = nodeHeight(curr);

        if(balanceFactor(curr) == 2 && balanceFactor(curr->lchild) == 1) return LLRotation(curr);
        else if(balanceFactor(curr) == 2 && balanceFactor(curr->lchild)== -1) return LRRotation(curr);
        else if(balanceFactor(curr) == -2 && balanceFactor(curr->rchild)== 1) return RRRotation(curr);
        else if(balanceFactor(curr) == -2 && balanceFactor(curr->rchild)== -1) return RLRotation(curr);
        return curr;
    }
    void Insert(T data){
        setRoot(InsertR(getRoot(), data));  
    }

};