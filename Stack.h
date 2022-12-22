#ifndef PROBLEM8_STACK_H
#define PROBLEM8_STACK_H
#include <iostream>
using namespace std;

template <typename t>
class Stack{
private:
    t *arr;
    int Size;
    int numTop;
public:
    explicit Stack(int Size);
    ~Stack();
    Stack(const Stack<t> &src);
    Stack<t> operator=(const Stack<t> &src);
    t pop();
    int size();
    int emptyPlaces();
    void push(t element);
    bool empty();
    t &top();
    void display();

    friend void manageStack();

    // Exceptions classes
    class StackOverflowException{
    private:
        string errorMessage;
    public:
        StackOverflowException(){
            errorMessage = "Stack Over flow Exception Happen, as You Try to Push to full Stack";
        }
        void pushError(){
            cerr << errorMessage << endl;
        }
    };
    class StackEmptyException{
    private:
        string errorMessage;
    public:
        StackEmptyException(){
            errorMessage = "Stack Empty Exception Happen, as You Try to pop From Empty Stack";
        }
        void pushError(){
            cerr << errorMessage << endl;
        }
    };
};

template <typename t>
Stack<t>::Stack(int sizeStack) {
    if (sizeStack <= 0){
        cerr << "enter valid size" << endl;
        exit(1);
    }
    Size = sizeStack;
    arr = new t[Size];
    numTop = -1;
}

template <typename t>
Stack<t>::~Stack() {
    delete[] arr;
}

template<typename t>
Stack<t>::Stack(const Stack<t> &src) {
    Size = src.Size;
    numTop = src.numTop;

    this->arr = nullptr;
    if (src.arr != nullptr){
        this->arr = new t[Size];
        for (int i = 0; i < Size; ++i) {
            arr[i] = src.arr[i];
        }
    }
}

template<typename t>
Stack<t> Stack<t>::operator=(const Stack<t> &src) {
    numTop = src.numTop;
    if (this != &src) {
        t *newArr = new t[src.Size];
        for (int i = 0; i < src.Size; ++i) {
            newArr[i] = src.arr[i];
        }
        delete[] arr;
        arr = newArr;
        Size = src.Size;
    }
    return *this;
}

template<typename t>
int Stack<t>::size() {
    return Size;
}

template<typename t>
bool Stack<t>::empty() {
    if (numTop == -1){
        return true;
    }
    return false;
}

template <typename t>
t Stack<t>::pop() {
    if (numTop == -1){
        throw (StackEmptyException());
    }
    t lastElement = arr[numTop];
    --numTop;
    return lastElement;
}

template<typename t>
void Stack<t>::push(t element) {
    if (numTop + 1 >= Size){
        throw (StackOverflowException());
    }
    arr[++numTop] = element;
}

template<typename t>
t& Stack<t>::top() {
    if (numTop == -1){
        cerr << "the stack is empty" << endl;
        exit(1);
    }
    return arr[numTop];
}

template<typename t>
void Stack<t>::display() {
    cout << "[";
    for (int i = numTop; i >= 0; --i) {
        cout << arr[i];
    }
    cout << "]" << endl;
}

void displayMenu() {
    cout << "1 - create" << endl;
    cout << "2 - push element" << endl;
    cout << "3 - pop element" << endl;
    cout << "4 - display Stack" << endl;
    cout << "5 - check the stack is empty" << endl;
    cout << "6 - show size of stack" << endl;
    cout << "7 - show how many places are empty in your stack" << endl;
    cout << "8 - Quit" << endl;
}

int choose() {
    int n;
    while (true){
        cout << "enter your choose from the previous given menu : ";
        cin >> n;
        if (n == 1 or n == 2 or n == 3 or n == 4 or n == 5 or n  == 6 or n == 7 or n == 8){
            return n;
        }else{
            cout << "please enter valid input" << endl;
            displayMenu();
        }
    }
}

template<typename ty>
void manageStack(){
    int stackSize;
    ty pushElement;
    Stack<ty> hisStack(1);
    while(true){
        displayMenu();
        int n = choose();
        afterError:
        if (n == 1) {
            while (true) {
                cout << "what's size of your stack ou want it";
                cin >> stackSize;
                Stack<ty>myStack(stackSize);
                if (stackSize > 0) {
                    hisStack = myStack;
                    break;
                } else {
                    cerr << "enter valid size to your stack" << endl;
                }
            }
        }
        else if (n == 2) {
            try {
                cout << "enter the number you want to push it in the stack";
                cin >> pushElement;
                hisStack.push(pushElement);
            }
            catch (Stack<int>::StackOverflowException e) {
                e.pushError();
                exit(3);
            }
        }
        else if (n == 3) {
            try {
                cout << "pop element is : " << hisStack.pop() << endl;
            }
            catch (Stack<int>::StackEmptyException e) {
                e.pushError();
                exit(3);
            }
        }
        else if (n == 4) {
            hisStack.display();
        }
        else if (n == 5){
            if (hisStack.empty()){
                cout << "the stack is empty." << endl;
            }else{
                cout << "the stack not empty." << endl;
            }
        }
        else if(n == 6){
            cout << hisStack.size();
        }
        else if (n == 7){
            cout << "there's " << hisStack.emptyPlaces() << " places are empty" << endl;
        }
        else if (n == 8){
            cout << "quit the program." << endl;
        }
        else{
            cout << "please enter valid choose" << endl;
            n = choose();
            goto afterError;
        }
    }
}

template<typename t>
int Stack<t>::emptyPlaces() {
    if (numTop == -1){
        return Size;
    }else{
        return Size - numTop - 1;
    }
}

#endif //PROBLEM8_STACK_H
