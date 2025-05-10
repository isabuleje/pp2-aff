#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

// Class Node
template<typename T> class Node {
private:
    T item;

public:
    Node<T> *next;
    Node<T> *prev;
    T getItem();
    Node();
    Node(T item);
};

template<typename T> Node<T>::Node() 
{
    next = nullptr;
    prev = nullptr;
}

template<typename T> Node<T>::Node(T item) 
{
    this->item = item;
    next = nullptr;
    prev = nullptr;
}

template<typename T> T Node<T>::getItem() { return item; }

template<typename T> class ListNavigator;

// Class List
template<typename T> class List {
private:
    Node<T> *pHead;
    Node<T> *pBack;
    int numItems;
    void succ(Node<T> *&p);
    void pred(Node<T> *&p);

public:
    void insertFront(T item);
    void insertBack(T item);
    void removeFront();
    void removeBack();
    T getItemFront();
    T getItemBack();
    ListNavigator<T> getListNavigator() const;
    int size();
    bool empty();
    List();
};

template<typename T> List<T>::List() 
{
    pHead = new Node<T>();
    pBack = pHead;
    pHead->next = nullptr;
    numItems = 0;
}

template<typename T> void List<T>::succ(Node<T> *&p) { p = p->next; }

template<typename T> void List<T>::pred(Node<T> *&p) 
{
    Node<T> *q = pHead;
    while (q->next != p) {
      succ(q);
    }
    p = q;
}

template<typename T> void List<T>::insertFront(T item) 
{
    Node<T> *pNew = new Node<T>(item);
    pNew->next = pHead->next;
    pHead->next = pNew;

    if (pBack == pHead) {
      pBack = pNew;
    }
    numItems++;
}

template<typename T> void List<T>::insertBack(T item) 
{
    Node<T> *pNew = new Node<T>(item);
    pBack->next = pNew;
    pBack = pNew;
    numItems++;
}

template<typename T> void List<T>::removeFront() 
{
    if (empty()) {
      cout << "List is empty" << endl;
    }

    Node<T> *temp = pHead->next;
    pHead->next = temp->next;

    if (pBack == temp) {
      pBack = pHead;
    }

    delete temp;
    numItems--;
}

template<typename T> void List<T>::removeBack() 
{
    if (empty()) {
      cout << "List is empty" << endl;
    }

    Node<T> *temp = pBack;
    pred(pBack);
    pBack->next = nullptr;

    delete temp;

    if (pHead == pBack) {
      pHead = pBack;
    }
    numItems--;
}

template<typename T> T List<T>::getItemFront() 
{
    if (empty()) {
      return T();
    }

    return pHead->next->getItem();
}

template<typename T> T List<T>::getItemBack() 
{
    if (empty()) {
      return T();
    }

    return pBack->getItem();
}

template<typename T> ListNavigator<T> List<T>::getListNavigator() const 
{
    return ListNavigator<T>(pHead->next);
}

template<typename T> int List<T>::size() { return numItems; }

template<typename T> bool List<T>::empty() { return pBack == pHead; }

// ListNavigator
template<typename T> class ListNavigator {
private:
    Node<T> *current;
    Node<T> *start;
    int currentPosition;

public:
    bool end();
    void next();
    void reset();
    bool getCurrentItem(T &item);
    int  getCurrentPosition() const;
    ListNavigator(Node<T> *current);
};

template<typename T> ListNavigator<T>::ListNavigator(Node<T> *current) 
{
    this->current = current;
    this->start = current;
}

template<typename T> bool ListNavigator<T>::end() { return current == nullptr; }

template<typename T> void ListNavigator<T>::next() { current = current->next; }

template<typename T> void ListNavigator<T>::reset() { current = start; }

template<typename T> bool ListNavigator<T>::getCurrentItem(T &item) 
{
    if (current == nullptr) {
      return false;
    }
    item = current->getItem();
    return true;
}

template<typename T> int ListNavigator<T>::getCurrentPosition() const { return currentPosition; }

template<typename T> class Queue {
private:
    List<T> list;

public:
    void enqueue(T item);
    void dequeue();
    T front();
    int size();
    bool empty();
    Queue(List<T>);
};

template<typename T> Queue<T>::Queue(List<T> list) { this->list = list; }

template<typename T> void Queue<T>::enqueue(T item) { list.insertBack(item); }

template<typename T> void Queue<T>::dequeue() 
{
    if (empty()) {
      cout << "Queue is empty" << endl;
    }
    list.removeBack();
}

template<typename T> T Queue<T>::front() 
{
    if (empty()) {
      return T();
    }
    return list.getItemBack();
}

template<typename T> int Queue<T>::size() { return list.size(); }

template<typename T> bool Queue<T>::empty() { return list.empty(); }

// Class Stack
template<typename T> class Stack {
private:
    List<T> list;

public:
    void push(T item);
    void pop();
    T top();
    int size();
    bool empty();
    Stack(List<T>);
};

template<typename T> Stack<T>::Stack(List<T> list) { this->list = list; }

template<typename T> void Stack<T>::push(T item) { list.insertFront(item); }

template<typename T> void Stack<T>::pop() 
{
    if (empty()) {
      cout << "Stack is empty" << endl;
    }
    list.removeFront();
}

template<typename T> T Stack<T>::top() 
{
    if (empty()) {
      return T();
    }
    return list.getItemFront();
}

template<typename T> int Stack<T>::size() { return list.size(); }

template<typename T> bool Stack<T>::empty() { return list.empty(); }

/*
//Classe HashTable
template<typename Key, typename T> 
class HashTable<Key, T> {
private:
    const int tam = 11; //n sei se e pra botar tamanho na tabela, esse slide ta confuso
    List<T>* t;

public:
    HashTable(const int tam); //n sei se e assim q faz o construtor
    ~HashTable();

    void insert(Key key, T item);
    bool remove(Key key);
    bool search(Key key, T item);
    int lenght();
    bool empty();
    int loadFactor();
    int hash(Key key);
};

template<typename Key, typename T>
HashTable<Key, T>::HashTable(const int tam){
    capacity = tam;
    t = new List<T>[capacity];
}

template<typename Key, typename T>
HashTable<Key, T>::~HashTable(){
    delete[] t;
}

template<typename Key, typename T>
void HashTable<Key, T>::insert(Key key, T item){
    //:3
}

template<typename Key, typename T>
bool HashTable<Key, T>::remove(Key key){
    //:3
}

template<typename Key, typename T>
bool HashTable<Key, T>::search(Key key, T item){
    //:3
}

template<typename Key, typename T>
int HashTable<Key, T>::lenght(){
    int total_lenght = 0;
    for (int i = 0; i < capacity; i++){
        total += t[i].size()
    }
}

template<typename Key, typename T>
bool HashTable<Key, T>::empty(){
    for(int i=0; i < capacity; i++){
        if(!t){
            return false;
        }else{
            return true;
        }
    }
}

template<typename Key, typename T>
int HashTable<Key, T>::loadFactor(){
    return lenght() / capacity;
}

template<typename Key, typename T>
int HashTable<Key, T>::hash(Key key){
    return key % capacity;
}
*/























/*

Leitor de Codigo e suas funcoes auxiliares
trim() - remove espacos em branco do inicio e do fim de uma string
isCodeFunction() - verifica se a linha e uma funcao
isCodeEnd() - verifica se a linha e o fim de uma funcao
isMainFunction() - verifica se a linha e a funcao principal
findMainFuction() - encontra a funcao principal
codeExecutionStacker() - executa o leitor de codigo e imprime os resultados

*/
string trim(string str) 
{
    int start = 0;
    int end = str.length() - 1;

    while (start <= end && isspace(str[start])) {
      start++;
    }
    while (end >= start && isspace(str[end])) {
      end--;
    }
    return str.substr(start, end - start + 1);
}

bool isCodeFunction(string line) 
{
    line = trim(line);
    return (line.size() == 1 || (line.size() > 1 && line[1] != ':'));
}

bool isFunctionEnd(string line) 
{
    return line == "" || line == " " || line.empty();
}


void printSecretCode(Stack<string> phrase_letters) 
{
    List<string> temporary;
    Stack<string> temp(temporary);

    while (!phrase_letters.empty()) {
      temp.push(phrase_letters.top());
      phrase_letters.pop();
    }

    while(!temp.empty()){
      string item = temp.top();
      cout << item.substr(6) << " ";
      temp.pop();
    }

}

bool isCodeMainfunction(string line) {
    return (line == "Z :");
}

void findMainFuction(ListNavigator<string>& nav){
    string line;

    while (!nav.end()) {
        nav.getCurrentItem(line);
        line = trim(line);
        if (isCodeMainfunction(line)) {
            nav.next();
            return;
        }
        nav.next();
    }

}
bool executeFunctionByName(string functionName, List<string> codeList, Stack<string>& phrase_letters);

void processFunctionBody(ListNavigator<string>& nav, Stack<string>& phrase_letters, List<string>& codeList){
    string line;

    while (!nav.end()) {
      nav.getCurrentItem(line);
      line = trim(line);

      if (line == "~" || line.empty() ){
          break;  
      }

      if (line.find("ENFILERA")) {
        phrase_letters.push(line);
        executeFunctionByName(line, codeList, phrase_letters);
      }
      else if (line.find("DESENFILERA")){
        phrase_letters.pop();
      }
      nav.next();
    }
}

bool executeFunctionByName(string functionName, List<string> codeList, Stack<string>& phrase_letters){
    ListNavigator<string> nav = codeList.getListNavigator();
    string line;

    while (!nav.end()) {
        nav.getCurrentItem(line);
        line = trim(line);
        if (line == functionName + " :") {
            nav.next();
            processFunctionBody(nav, phrase_letters, codeList);
            return true;
        }
        nav.next();
    }
    return false;

}


void codeExecutionStacker(List<string> codeList) {
    List<string> secret_phrase;
    Stack<string> phrase_letters(secret_phrase); 
    ListNavigator<string> nav = codeList.getListNavigator();

    findMainFuction(nav);
    processFunctionBody(nav,phrase_letters, codeList);

    printSecretCode(phrase_letters);
}

int main() {
    List<string> codeList;
    string line;

    while (getline(cin, line) && line != "~") {
      codeList.insertBack(line);
    }

    codeExecutionStacker(codeList);

    return 0;
}

/*C :
ENFILEIRA T
ENFILEIRA A
ENFILEIRA Q
A :
ENFILEIRA A
C
DESENFILEIRA
DESENFILEIRA
ENFILEIRA U
B :
ENFILEIRA A
ENFILEIRA T
DESENFILEIRA
A
Z :
ENFILEIRA X
ENFILEIRA Q
B
ENFILEIRA E
DESENFILEIRA

2~*/