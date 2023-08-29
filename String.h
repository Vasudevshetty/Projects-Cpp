#include<bits/stdc++.h>
using namespace std;

#ifndef String_H

class String{
private:
    char* A;    
    int length;
    int size;
    void swap(int x, int y){
        char temp = A[x];
        A[x] = A[y];
        A[y] = temp;
    }
public:
    String(){
        size = 10;
        A = new char[size];
        length = 0;
    }
    String(int sz){
        this->size = sz;
        A = new char[size];
        length = 0;
    }
    void insert(int idx, char x){
        if(idx >= 0 && idx <= length){
            for(int i = length; i > idx; i--) A[i] = A[i-1];
            A[idx] = x;
            length++;
        }
        A[length] = '\0';
    }
    void print(){
        for(int i = 0; i < length; i++)
            cout << A[i];
        cout << endl;
    }
    void printAtidx(int idx){
        if(idx < 0 || idx > length) return;
        cout << A[idx] << endl;
    }
    void toUpper(){
        for(int i = 0; i < length; i++) 
            if(A[i] >= 97 && A[i] <= 122) A[i] -= 32;
    }
    void toLower(){
        for(int i = 0; i < length; i++) 
            if(A[i] >= 65 && A[i] <= 90) A[i] += 32;
    }
    int vowel(){
        int vc = 0;
        for(int i = 0; i < length; i++){
            if(A[i] == 'a' || A[i] == 'e' || A[i] == 'i' || A[i] == 'o' || A[i] == 'u' || 
            A[i] == 'A' || A[i] == 'E' || A[i] == 'I' || A[i] == 'E' || A[i] == 'U')
                vc++;
        }
        return vc;
    }
    int words(){
        int wc = 0;
        for(int i = 0; i < length; i++){
            if(A[i] == ' ' && A[i - 1] != ' ') wc++;
        }
        return wc;
    }
    char Delete(int idx){
        char x = '\0';
        if(idx >= 0 && idx < length){
            x = A[idx];
            for(int i = idx; i < length - 1; i++) A[i] = A[i+1];
            length--;
        }
        return x; 
    }
    bool isAlpha(){
        for(int i = 0; A[i] != '\0'; i++){
            if((A[i] >= 65 && A[i] <= 90) || (A[i] >= 97 && A[i] <= 122))
                return true;
        }
        return false;
    }

    bool isNum(){
        for(int i = 0; A[i] != '\0'; i++){
            if(A[i] >= 48 && A[i] <= 57)
                return true;
        }
        return false;
    }

    bool valid(){
        return isNum() && isAlpha();
    }
    bool equal(char* b){
        return (compare(b) == 0);
    }
    int compare(char* B){
        for(int i = 0, j = 0; A[i] != '\0' || B[j] != '\0'; i++, j++){
            if(A[i] != B[j])
            return A[i] - B[j];
        }
        return 0;
    }
    void reverse(){
        int i, j;
        for(i = 0; A[i] != '\0'; i++);
        i -=1;
        for(j = 0; j < i; j++, i--) 
            swap(j, i);
    }
    char* Reverse(){
        int i, j;
        char *B = new char[length];
        for(i = 0; A[i] != '\0'; i++);
        i -=1;
        for(j = 0; i >= 0; j++, i--) B[j] = A[i];

        B[j] = '\0';
        return B;
    }
    bool palindrome(){
        char *B = Reverse();
        bool result = equal(B);
        delete []B;
        return result;
    }
    void duplicates(){
        vector<int> H(26,0);
        for(int i = 0; A[i] != '\0'; i++) H[A[i]-'a']++;
        for(int i = 0; i < 26; i++){
            if(H[i] > 1) cout << (char)('a' + i) << " is repeated " << H[i] << " times\n";
        }
    }
    void duplicatesBitwise(){
        long int H, x;
        H = x = 0;
        for(int i = 0; A[i] != '\0'; i++){
            x = 1;
            x = x << (A[i] - 'a');
            if((x & H) > 0) cout << A[i] << " has a duplicate\n";
            else H = x|H;
        }
    }
    bool anagram(char* B){
        int l = 0;
        for(; B[l] != '\0'; l++);
        if(length != l) return false;
        vector<int> H(26,0);
        for(int i = 0; A[i] != '\0'; i++){
            H[A[i] - 'a']++;
            H[B[i] - 'a']++;
        }
        for(int i = 0; i < (int)H.size(); i++){
            if(H[i] % 2 == 0) return true;
        }
        return false;
    }
    void perm(){ permR(0); }

    void permR(int k){
        static int a[10] = {0};
        static char res[10];
        int i;
        if(A[k] == '\0'){
            res[k] = '\0';
            cout << res << endl;
        }
        for(i = 0; A[i] != '\0'; i++){
            if(a[i] == 0){
                res[k] = A[i];
                a[i] = 1;
                permR(k+1);
                a[i] = 0;
            }
        }
    }
    void perR(int l, int h){
        if(l == h) cout << A << endl;
        for(int i = 0; A[i] != '\0'; i++){
            swap(l,i);
            perR(l+1,h);
            swap(l,i);
        }
    }
};

#endif