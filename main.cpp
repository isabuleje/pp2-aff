#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <cmath>

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

template<typename T> void List<T>::succ(Node<T> *&p) {
    if (p -> next == nullptr || p -> next == pBack) {
      return;
    } else {
      p = p->next;
    }
}

template<typename T> void List<T>::pred(Node<T> *&p) 
{
    if (p -> prev == nullptr || p -> prev == pHead) {
      return;
    } else {
      p = p->prev;
    }
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
    void removeCurrentItem();
    ListNavigator(Node<T> *current);
    T getCurrentItem();
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

template<typename T> T ListNavigator<T>::getCurrentItem() { return current->getItem();}

template<typename T> int ListNavigator<T>::getCurrentPosition() const { return currentPosition; }

template<typename T> void ListNavigator<T>::removeCurrentItem() 
{
    if (current == nullptr) {
      return;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;   
}

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
    last = T();
}

//conversor das letras aliens pra alfabeto da forma mais literal possivel
//(switchcase nao funciona com string, so com char)
//(tem alguma outra forma de fazer isso?)
string algoritmoConcersorAlienAlfanumerico(string alien) {
    if (alien == ":::") {
        return "A";
    } else if (alien == ".::") {
        return "B";
    } else if (alien == ":.:") {
        return "C";
    } else if (alien == "::.") {
        return "D";
    } else if (alien == ":..") {
        return "E";
    } else if (alien == ".:.") {
        return "F";
    } else if (alien == "..:") {
        return "G";
    } else if (alien == "...") {
        return "H";
    } else if (alien == "|::") {
        return "I";
    } else if (alien == ":|:") {
        return "J";
    } else if (alien == "::|") {
        return "K";
    } else if (alien == "|.:") {
        return "L";
    } else if (alien == ".|:") {
        return "M";
    } else if (alien == ".:|") {
        return "N";
    } else if (alien == "|:.") {
        return "O";
    } else if (alien == ":|.") {
        return "P";
    } else if (alien == ":.|") {
        return "Q";
    } else if (alien == "|..") {
        return "R";
    } else if (alien == ".|.") {
        return "S";
    } else if (alien == "..|") {
        return "T";
    } else if (alien == ".||") {
        return "U";
    } else if (alien == "|.|") {
        return "V";
    } else if (alien == "||.") {
        return "W";
    } else if (alien == "-.-") {
        return "X";
    } else if (alien == ".--") {
        return "Y";
    } else if (alien == "--.") {
        return "Z";
    } else if (alien == "---") {
        return " ";
    } else if (alien == "~") {
        return "~";
    } else if (alien == ":__") {
        return "|__";
    } else {
        return "?";
    }
}


template<typename Key, typename T> 
class HashTable {
private:
    List<Pair<Key, T>> *table;
public:
    HashTable(const int capacity); //n sei se e assim q faz o construtor
    long unsigned int size;

    ~HashTable();

    long unsigned int getSize();
    void insert(Key key, T item);
    void insert(Pair<Key, T> pair); 
    bool remove(Key key);
    bool search(Key key, T item);
    T findItemFromKey(Key key);
    int length();
    bool empty();
    int loadFactor();
    long unsigned int hash(const Key& key);
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
long unsigned int HashTable<Key, T>::getSize(){
    return size;
}

template<typename Key, typename T>
void HashTable<Key, T>::insert(Key key, T item){
    //cout << "entrou na funcao insert" << endl;
    long unsigned int index = hash(key);
    cout << "index: " << index << endl;
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
int HashTable<Key, T>::loadFactor(){
    return length() / table->capacity;
}

template<typename Key, typename T>
T HashTable<Key, T>::findItemFromKey(Key key) {
    long unsigned int index = hash(key);
    List<Pair<Key, T>>& target = table[index];
    ListNavigator<Pair<Key, T>> nav = target.getListNavigator();
    Pair<Key, T> currentItem;
    while (!nav.end()) {
        currentItem = nav.getCurrentItem();
        if (currentItem.getFirst() == key) {
            return currentItem.getLast();
        }
        nav.next();
    }
    return T();
}
    

//Transforma a chave para um index da tabela
template<typename Key, typename T>
long unsigned int HashTable<Key, T>::hash(const Key& key) {
    long unsigned int hashValue = 0;
    long unsigned int n = key.length();
    for (size_t i = 0; i < n; ++i) {
        hashValue += key[i] * static_cast<size_t>(pow(128, n - i - 1));
        hashValue %= this->getSize(); // Aplica o modulo a cada iteracao
    }
    return hashValue;
}




//criador de instancia da hashtable de dicionario alien usando o conversor de substrings
HashTable<string, string> createAlienDict(int hashsize) {
    //cout << "tentando criar a coisa" << endl;
    HashTable<string, string> alienDict(hashsize);
    string keys[29] = {":::",".::",":.:","::.",":..",".:.","..:","...","|::",":|:","::|","|.:",".|:",".:|","|:.",":|.",":.|","|..",".|.","..|",".||","|.|","||.","-.-",".--","--.","---","~",":__"};
    for (int i = 0; i < 29; i++) {
        //cout << "adicionando par de simbolo e letra na coisa" << endl;
        alienDict.insert(keys[i], algoritmoConcersorAlienAlfanumerico(keys[i]));
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
string translateString(string str, HashTable<string, string> alienDict) {
    int strlen = str.length();
    int overflowlen = strlen % 3;
    strlen = strlen - overflowlen;

    string result = "";

    for (int i = 0; i < strlen; i += 3) {
        string key = str.substr(i, 3);
        string value = alienDict.findItemFromKey(key);
        result += value;
    }

    if (overflowlen > 0) {
        string key = str.substr(strlen, overflowlen);
        string value = alienDict.findItemFromKey(key);
        result += value;
    }

    return result;
}






//NAO MEXE AQ PRA BAIXO Q TA PRONTO D:



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
        line = trim(line);

        if (line == "~" || line.empty()) {
            break;  
        }

    
        if (line.find("DESENFILEIRA") != string::npos) {
            if (!lettersQueue.empty()) {
                string value = lettersQueue.front();
                cout << "DESENFILEIRA: " << value << endl;
                lettersQueue.dequeue();
            }
        }
        else if (line.find("ENFILEIRA") != string::npos) {
                string character = line.substr(line.find("ENFILEIRA") + 9);
                character = trim(character);
                lettersQueue.enqueue(character);
                cout << "ENFILEIRA: " << character << endl;
            }
        else if (isCodeFunction(line)) {
            if (callStack.contains(line)) {
                cout << "Ta repetindor na funcaor " << line << endl;
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
            cout << "chama" << line << endl;
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
/*
int main() {
    List<string> codeList;
    string line;

    while (getline(cin, line) && line != "~") {
      codeList.insertBack(line);
    }

    codeExecutionStacker(codeList);

    return 0;
}
*/

int main() {
    HashTable<string, string> alienDict = createAlienDict(10);
    cout << "Tabela Hash criada com sucesso!" << endl << endl;
    string str1 = "|:.|.::::---.::|:..|:---::.|::::::__";
    string str2 = "------------::.:...:::.:.:::.:.:::::::.:::::::::::::::..:.:::.:..:::.:.:";
    cout << "usando TABELA HASH MANEIRA DE ALIEN pra traduzir " << str1 << " a seguir:" << endl; 
    cout << translateString(str1, alienDict) << endl;
    cout << "usando TABELA HASH MANEIRA DE ALIEN pra traduzir " << str2 << " a seguir:" << endl;
    cout << translateString(str2, alienDict) << endl;
}

/*
C :
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
~
*/

//mds deu certo...