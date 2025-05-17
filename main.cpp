#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <cmath>
#include <vector>

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

template<typename T> 
Node<T>::Node() {
    next = nullptr;
    prev = nullptr;
}

template<typename T> 
Node<T>::Node(T item) {
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
    //int safeSize()const;
    bool empty();
    List();
    //~List();
    Node<T>* getHead();
    //int safeSize() const;
};

template<typename T> List<T>::List() 
{
    pHead = new Node<T>();
    pBack = pHead;
    pHead->next = nullptr;
    numItems = 0;
}

/*
template<typename T> List<T>::~List() 
{
    while (empty() == false) {
        removeFront();
    }
    delete pHead;
    delete pBack;
}
*/

/*template<typename T> void List<T>::succ(Node<T> *&p) {
    if (p -> next == nullptr || p -> next == pBack) {
      return;
    } else {
      p = p->next;
    }
}*/
template<typename T> void List<T>::succ(Node<T> *&p) { p = p->next; }

/*template<typename T> void List<T>::pred(Node<T> *&p)
{
    if (p -> prev == nullptr || p -> prev == pHead) {
      return;
    } else {
      p = p->prev;
    }
}*/
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
    pNew->prev = pHead;

    if (pBack == pHead) {
      pBack = pNew;
    }
    numItems++;
}

template<typename T> void List<T>::insertBack(T item) 
{
    Node<T> *pNew = new Node<T>(item);
    pBack->next = pNew;
    pNew->prev = pBack;
    pBack = pNew;
    numItems++;
}

template<typename T> void List<T>::removeFront() 
{
    if (empty()) {
      cout << "List is empty" << endl;
      return;
    }

    Node<T> *temp = pHead->next;
    pHead->next = temp->next;

    if (pBack == temp) {
      pBack = pHead;
    }

    delete temp;
    numItems--;
}

/*template<typename T> void List<T>::removeBack()
{
    if (empty()) {
      cout << "List is empty" << endl;
    }

    Node<T> *temp = pBack;
    pred(pBack);
    pBack->next = nullptr;

    delete temp;
    numItems--;
}*/
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

template<typename T> int List<T>::size(){
    return numItems; 
}

/*template<typename T> int List<T>::safeSize() const
{
    Node<T>* Current = pHead->next;
    int count = 0;
    while (true) {
        if (Current == nullptr) {
            break;
        } else {
            count++;
            Current = Current->next;
        }
    }
    return count;
}*/

template<typename T> bool List<T>::empty() { return pBack == pHead; }

template<typename T> Node<T>* List<T>::getHead() { return pHead; }

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
    //void removeCurrentItem();
    ListNavigator(Node<T> *current);
    T getCurrentItem();
    Node<T> *getCurrentNode() { return current; }
};

template<typename T> ListNavigator<T>::ListNavigator(Node<T> *current) 
{
    this->current = current;
    this->start = current;
}

template<typename T> bool ListNavigator<T>::end() { return current == nullptr; }

template<typename T> void ListNavigator<T>::next() {
        current = current->next;
}

template<typename T> void ListNavigator<T>::reset() { current = start; }

template<typename T> bool ListNavigator<T>::getCurrentItem(T &item) 
{
    if (current == nullptr) {
      return false;
    }
    item = current->getItem();
    return true;
}

template<typename T> T ListNavigator<T>::getCurrentItem() { return current->getItem();}

template<typename T> int ListNavigator<T>::getCurrentPosition() const { return currentPosition; }

/*template<typename T> void ListNavigator<T>::removeCurrentItem()
{
    if (current == nullptr) {
      return;
    } else if (current->prev == nullptr) {
        current->next->prev = nullptr;
    } else if (current->next == nullptr) {
        current->prev->next = nullptr;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    delete current;   
    this->reset();
}*/

//Class Queue
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
    list.removeFront();
}

template<typename T> T Queue<T>::front() 
{
    if (empty()) {
      return T();
    }
    return list.getItemFront();
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
    bool contains(T item);
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

template <typename T>
bool Stack<T>::contains(T item) {
    ListNavigator<T> nav = list.getListNavigator();
    T currentItem;
    while (!nav.end()) {
        if (nav.getCurrentItem(currentItem) && currentItem == item) {
            return true;
        }
        nav.next();
    }
    return false;
}

//Classe Pair
//basicamente classe de tupla tamanho 2, professor pediu pra uma nos casos de colisao
template<typename T, typename U>
class Pair {
private:
    T first;
    U last;
public:
    Pair(T item1, U item2);
    Pair(T item);
    Pair();

    T getFirst() {
        return first;
    }
    U getLast() {
        return last;
    }
    void setAll(T item1, U item2) {
        first = item1;
        last = item2; 
    }
    void setFirst(T item) {
        first = item;
    }
    void setLast(U item) {
        last = item;
    }
};


template<typename T, typename U>
Pair<T, U>::Pair(T item) {
    first = item;
    last = U();
}

template<typename T, typename U>
Pair<T, U>::Pair(T item1, U item2) {
    first = item1;
    last = item2;
}

template<typename T, typename U>
Pair<T, U>::Pair() {
    first = T();
    last = U();
}


string algorithmConvetor(string alien){
    List<string> alienLetters;
    List<string> humanLetters;

    vector<string> vectorHumanLetters = {"A","B", "C", "D", "E",
        "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P",
        "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", " ", "~", ":"
    };

    vector<string> vectorAlienLetters = {
    ":::",".::",":.:","::.",":..",".:.","..:","...","|::",":|:","::|",
    "|.:",".|:",".:|","|:.",":|.",":.|","|..",".|.","..|",".||","|.|",
    "||.","-.-",".--","--.","---","~",":"
    };

    for (const auto& letter : vectorHumanLetters) {
        humanLetters.insertBack(letter);
    }

    for (const auto& letter : vectorAlienLetters) {
        alienLetters.insertBack(letter);
    }


    ListNavigator<string> navAlien = alienLetters.getListNavigator();
    ListNavigator<string> navHuman = humanLetters.getListNavigator();

    while (!navAlien.end()) {
        if (alien == navAlien.getCurrentItem()) {
            return navHuman.getCurrentItem();

        }
        navAlien.next();
        navHuman.next();
    }
    return "?";
}


//class HashTable
template<typename Key, typename T> 
class HashTable {
private:
    List<Pair<Key, T>> *table;
public:
    HashTable(const int capacity);
    long unsigned int size;

    ~HashTable();

    long unsigned int getSize() const;
    void insert(Key key, T item);
    void insert(Pair<Key, T> pair); 
    bool remove(Key key);
    bool search(Key key, T item);
    T findItemFromKey(Key key) const;
    bool empty();
    long unsigned int hash(const Key& key) const;
};

template<typename Key, typename T>
HashTable<Key, T>::HashTable(const int capacity){
    table = new List<Pair<Key, T>>[capacity];
    size = capacity;
}

template<typename Key, typename T>
HashTable<Key, T>::~HashTable(){
    delete[] table;
}

template<typename Key, typename T>
long unsigned int HashTable<Key, T>::getSize() const{
    return size;
}

template<typename Key, typename T>
void HashTable<Key, T>::insert(Key key, T item){
    //cout << "entrou na funcao insert" << endl;
    long unsigned int index = hash(key);

    table[index].insertBack(Pair<Key, T>(key, item));
}

template<typename Key, typename T>
void HashTable<Key, T>::insert(Pair<Key, T> pair){
    long unsigned int index = hash(pair.getFirst());
    table[index].push(pair);
}

template<typename Key, typename T>
bool HashTable<Key, T>::remove(Key key) {
    long unsigned int index = hash(key);
    List<Pair<Key, T>>& target = table[index];
    ListNavigator<Pair<Key, T>> nav = target.getListNavigator();
    Pair<Key, T> currentItem;
    while (!nav.end()) {
        currentItem = nav.getCurrentItem();
        if (currentItem.getFirst() == key) {
            nav.removeCurrentItem();
            return true;
        }
        nav.next();
    }
    return false;
}

template<typename Key, typename T>
bool HashTable<Key, T>::search(Key key, T item){
    long unsigned int index = hash(key);
    List<Pair<Key, T>>& target = table[index];
    ListNavigator<Pair<Key, T>> nav = target.getListNavigator();
    Pair<Key, T> currentItem;
    while (!nav.end()) {
        currentItem = nav.getCurrentItem();
        if (currentItem.getFirst() == key && currentItem.getLast() == item) {
            cout << item << " found at index " << index << endl;
            return true;
        }
    }
    cout << key << " not found" << endl;
    return false;
}

template<typename Key, typename T>
bool HashTable<Key, T>::empty(){
    for (int i=0; i < table->capacity; i++){
        if(!table){
            return false;
        }else{
            return true;
        }
    }
}


template<typename Key, typename T>
T HashTable<Key, T>::findItemFromKey(Key key) const {
    //cout << "entrou na funcao findItemFromKey" << endl;
    long unsigned int index = hash(key);
    //List<Pair<Key, T>>& target = table[index];
    //cout << "index: " << index << endl;
    Node<Pair<Key, T>>* currentNode  = table[index].getHead();
    //cout << "tamanho da lista usando size: " << target.size() << endl;
    //cout << "tamanho da lista usando safeSize: " << target.safeSize() << endl;
    while (true) {
        //cout << "sequencia do loop do while iniciada" << endl;
        if (currentNode == nullptr || currentNode->next == nullptr) {
            break;
        }
        currentNode = currentNode->next;
        //cout << "item foi avancado" << endl;
        if (currentNode->getItem().getFirst() == key) {
            //cout << "encontrado" << endl;
            return currentNode->getItem().getLast();
        }
        //cout << "nao encontrado" << endl;
    }
    //cout << "nao achou nada" << endl;
    return T();
}
    

//Transforma a chave para um index da tabela
template<typename Key, typename T>
long unsigned int HashTable<Key, T>::hash(const Key& key) const{
    long unsigned int hashValue = 0;
    long unsigned int n = key.length();
    for (size_t i = 0; i < n; ++i) {
        hashValue += key[i] * static_cast<size_t>(pow(128, n - i - 1));
        //cout << "hashValue: " << hashValue << endl;
        hashValue %= this->getSize(); // Aplica o modulo a cada iteracao
    }
    return hashValue;// %= this->getSize();
}




//criador de instancia da hashtable de dicionario alien usando o conversor de substrings
//hashsize = tamanho da tabela, vai funcionar contanto que seja maior que 0
HashTable<string, string> createAlienDict(int hashsize) {
    //cout << "tentando criar a coisa" << endl;
    HashTable<string, string> alienDict(hashsize);
    string keys[29] = {":::",".::",":.:","::.",":..",".:.","..:","...","|::",":|:","::|","|.:",".|:",".:|","|:.",":|.",":.|","|..",".|.","..|",".||","|.|","||.","-.-",".--","--.","---","~",":__"};
    for (int i = 0; i < 29; i++) {
        //cout << "adicionando par de simbolo e letra na coisa" << endl;
        alienDict.insert(keys[i], algorithmConvetor(keys[i]));
        //cout << "adicionado" << endl;
    }
    return alienDict;
}


//chamar essa funcao com a string de codigo alien e o DICIONARIO COMPLETO
//O CRIADO PELA FUNCAO DE CRIAR TABELA HASH DE DICIONARIO COMPLETO
//ex: 
//HashTable<string, string> alienDict = createAlienDict(10);
//translateString("------------::.:...:::.:.:::.:.:::::::.:::::::::::::::..:.:::.:..:::.:.:", alienDict)
//translateString retorna "    DEBCBCBADAAAAAGBCGDC"
string translateString(string str, const HashTable<string, string>& alienDict) {
    int strlen = str.length();
    int overflowlen = strlen % 3;
    strlen = strlen - overflowlen;

    string result;

    for (int i = 0; i < strlen; i += 3) {
        string key = str.substr(i, 3);
        //cout << "key: " << key << endl;
        string value = alienDict.findItemFromKey(key);
        //cout << "value: " << value << endl;
        result += value;
    }

    if (overflowlen == 1) {
        string key = str.substr(strlen, 1);
        string value = alienDict.findItemFromKey(key);
        result += key;
    }


    return result;
}





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
    return (line.size() == 1 || (line.size() > 1 && line[1] != ':' ) ) ;
}

bool isFunctionEnd(string line) 
{
    return line == "" || line == " " || line.empty();
}


void printSecretCode(Queue<string> lettersQueue) 
{    
    while (!lettersQueue.empty()) {
        cout << lettersQueue.front();
        lettersQueue.dequeue();
    }
    cout << endl;
}

bool isCodeMainfunction(string line) {
    return (line == "Z :");
}

void findMainFuction(ListNavigator<string>& nav, Stack<string> callStack){
    string line;

    while (!nav.end()) {
        nav.getCurrentItem(line);
        line = trim(line);
        if (isCodeMainfunction(line)) {
            callStack.push(line);
            nav.next();
            return;
        }
        nav.next();
    }

}
bool executeFunctionByName(string functionName, List<string>& codeList, Queue<string>& lettersQueue, Stack<string>& callStack);

void processFunctionBody(ListNavigator<string>& nav, Queue<string>& lettersQueue, List<string>& codeList, Stack<string>& callStack) {
    string line;

    while (!nav.end()) {
        nav.getCurrentItem(line);

        string originalLine = line;
        line = trim(line);
        if (line == "~" || line.empty()) {
            break;  
        }

    
        if (line.find("DESENFILEIRA") != string::npos) {
            if (!lettersQueue.empty()) {
                string value = lettersQueue.front();

                lettersQueue.dequeue();
            }
        }
        else if (line.find("ENFILEIRA") != string::npos){
            string after = originalLine.substr(11);
            after = trim(after);

            if (after.empty()) {
                lettersQueue.enqueue(" ");
            } else {

                string character = line.substr(line.find("ENFILEIRA") + 9);
                character = trim(character);
                lettersQueue.enqueue(character);
            }

        }
        else if (isCodeFunction(line)) {
            if (callStack.contains(line)) {
                return;
            }
            
            callStack.push(line);
            executeFunctionByName(line, codeList, lettersQueue, callStack);
            callStack.pop();
        }
        nav.next();
    }
    
}

bool executeFunctionByName(string functionName, List<string>& codeList, Queue<string>& lettersQueue, Stack<string>& callStack) {
    ListNavigator<string> nav = codeList.getListNavigator();
    string line;

    while (!nav.end()) {
        nav.getCurrentItem(line);
        line = trim(line);
        if (line == functionName + " :") {
            nav.next();
            callStack.push(line);
            processFunctionBody(nav, lettersQueue, codeList, callStack);
            callStack.pop();
            return true;
        }
        nav.next();
    }
    
    return false;
}

void codeExecutionStacker(List<string> codeList) {
    List<string> queueList;
    Queue<string> lettersQueue(queueList);

    List<string> callList;
    Stack<string> callStack(callList);

    ListNavigator<string> nav = codeList.getListNavigator();

    findMainFuction(nav, callStack); 
    processFunctionBody(nav, lettersQueue, codeList, callStack); 

    printSecretCode(lettersQueue);
}

void translateAlien(List<string> alienList) {
    List<string> result;
    string line;

    HashTable<string, string> alienDict = createAlienDict(11);

    ListNavigator<string> nav = alienList.getListNavigator();

    while (!nav.end()){
        nav.getCurrentItem(line);
        string translated = translateString(line, alienDict);
        cout << translated << endl;
        result.insertBack(translated);

        nav.next();
    }

    codeExecutionStacker(result);
}


int main() {
    string line;
    List<string> alienList;

    while (getline(cin, line)) {
        if (line == "~") break;
        alienList.insertBack(line);
    }

    translateAlien(alienList);
    return 0;
}
