#include<iostream>
using namespace std;

template<class T>
class Node{
    public:
        string key_;
        T value_;
        Node<T>* next_;

        Node(string key , T value){
            key_ = key;
            value_ = value;
            next_ = NULL;
        }

        ~Node(){
            if(next_!=NULL){
                delete next_;
            }
        }
};

template<class T>
class HashTable{
    public:
        Node<T>** table_;
        int curr_size_;
        int table_size_;

        HashTable(int table_size=7){
            curr_size_ = 0;
            table_size_ = table_size;
            table_ = new Node<T>*[table_size_];
            for(int i=0;i<table_size_;i++){
                table_[i] = NULL;
            }
        }

        void rehash(){
            Node<T>** oldTable = table_;
            int oldTableSize = table_size_;
            table_size_ = 2*table_size_;
            table_ = new Node<T>*[table_size_];

            for(int i=0;i<table_size_;i++){
                table_[i] = NULL;
            }
            curr_size_ = 0;

            for(int i=0;i<oldTableSize;i++){
                Node<T>* temp = oldTable[i];
                while(temp!=NULL){
                    insert(temp->key_ , temp->value_ );
                    temp = temp->next_;
                }
                if(oldTable[i]!=NULL){
                    delete oldTable[i];
                }
            }
            delete [] oldTable;

            return;
        }

        int hashFunction(string key){
            int idx = 0;
            int p = 1;
            for(int i=0;i<key.length();i++){
                idx = idx + (key[i]*p)%table_size_;
                idx = idx%table_size_;
                p = (p*27)%table_size_;
            }

            return idx;
        }

        void insert(string key , T value){
            int idx = hashFunction(key);
            
            Node<T>* n = new Node<T>(key,value);
            n->next_ = table_[idx];
            table_[idx] = n;
            curr_size_++;

            float loadFactor = curr_size_/(1.0*table_size_);

            if(loadFactor > 0.75){
                rehash();
            }

            return;
        }

        void print(){
            for(int i=0;i<table_size_;i++){
                cout<<"i :"<<i<<" ";
                if(table_[i]!=NULL){
                    Node<T> *temp = table_[i];
                    while(temp!=NULL){
                        cout<<temp->key_ <<" "<<temp->value_<<"    ";
                        temp = temp->next_;
                    }
                    
                }
                cout<<endl;
            }
        }

        T* search(string key){
            int idx = hashFunction(key);

            Node<T>* temp = table_[idx];
            while(temp!=NULL){
                if(temp->key_ == key){
                    return &temp->value_;
                }
                temp = temp->next_;
            }

            return NULL;
        }

        void erase(string key){
            int idx = hashFunction(key);

            Node<T>* temp = table_[idx];
            // Node<T>* prev  = temp;
            while(temp!=NULL){
                if(temp->key_ == key){
                    // prev->next_ = temp->next_;
                    // temp->next_ = NULL;
                    delete temp;
                    table_[idx] = NULL;
                    return;
                }
                // prev = temp;
                temp= temp->next_;
            }
            return;
        }

        T& operator[](string key){
            int* check = search(key);
            if(check){
                return (*check);
            }else{
                insert(key,0);
                check = search(key);
                return (*check);
            }
        }

};

int main(){
    HashTable<int> h;
    h.insert("mango",100);
    h.insert("apple",150);
    h.insert("orange",50);
    h.insert("melon",250);
    h.insert("pineapple",530);
    h.insert("banana",750);
    h.insert("chickoo",9);
    h.insert("litchi",90);

    // h.print();

    // int * price = h.search("appl");
    // if(price){
    //     cout<<*price<<endl;
    // }else{
    //     cout<<"does not exist";
    // }

    // h.erase("mango");
    // cout<<"h";
    // h.print();
    // cout<<h["mango"]<<endl;
    h["dosa"] = 80;
    h["dosa"] += 80;
    cout<<h["dosa"]<<endl;

    return 0;
}