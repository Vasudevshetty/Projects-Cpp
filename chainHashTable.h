#ifndef CHAINING_HASHING_TABLE
#define CHAINING_HASHING_TABLE

#include<bits/stdc++.h>
using namespace std;

template <typename KeyType, typename ValueType>
class ChainingHashTable{
private:
    int tableSize;
    vector<list<pair<KeyType, ValueType>>> table;
public:
    ChainingHashTable(int size);

    void Insert(const KeyType& key, const ValueType& value); //const used for preventing unneccessary modification of the value.
    bool search(const KeyType& key, ValueType& result);
    void remove(const KeyType& key);

    int hashFunction(const KeyType& key);
    //All the parameters are referenced bcoz of unneccessary copying of the variable and preventing memory usage and time consumption.
    void displayTable();
};

template<typename KeyType, typename ValueType>
ChainingHashTable<KeyType, ValueType>::ChainingHashTable(int size){
    tableSize = size;
    table.resize(tableSize);
}

template<typename KeyType, typename ValueType>
void ChainingHashTable<KeyType, ValueType>::Insert(const KeyType& key, const ValueType& value){
    int index = hashFunction(key);
    table[index].push_back(make_pair(key, value));
}

template<typename KeyType, typename ValueType>
bool ChainingHashTable<KeyType, ValueType>::search(const KeyType& key, ValueType& result){
    int index = hashFunction(key);
    for(const auto& kvPair: table[index]){
        if(kvPair.first == key){
            result = kvPair.second;
            return true;
        }
    }
    return false;
}

template<typename KeyType, typename ValueType>
void ChainingHashTable<KeyType, ValueType>::remove(const KeyType& key){
    int index = hashFunction(key);
    for(auto it = table[index].begin(); it != table[index].end(); ++it){
        if(it->first == key){
            table[index].erase(it);
            return;
        }
    }
}

template<typename KeyType, typename Valuetype>
int ChainingHashTable<KeyType, Valuetype>::hashFunction(const KeyType& key){
    return hash<KeyType>{}(key) % tableSize;
}

template<typename KeyType, typename Valuetype>
void ChainingHashTable<KeyType, Valuetype>::displayTable(){
    for(int i = 0; i < tableSize; i++){
        cout << "bucket " << i << " : ";
        for(const auto& kvPair : table[i])
            cout << "(" << kvPair.first << ", " << kvPair.second << ")";

        cout << endl;
    }
}

#endif