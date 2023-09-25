#include <stack.hpp>

template<class T>
StackNode<T>::StackNode(T value, StackNode<T> *next, StackNode<T> *prev) {
    this->value = value;
    this->next = next;
    this->prev = prev;
}

template<class T>
StackNode<T>::~StackNode() {
    this->next = this->prev = NULL;
}

template<class T>
Stack<T>::Stack() {
    this->head = this->tail = NULL;
}

template<class T>
Stack<T>::~Stack() { //DECONSTRUCTOR
    StackNode<T>* p = this->head;
    StackNode<T>* q = nullptr;
    while (p != nullptr) {
        q = p->next;
        delete p;
        p = q;
    }
    this->head = nullptr;
    this->tail = nullptr;
}

template<class T>
bool Stack<T>::empty() { //EMPTY
    if ((this->head == nullptr) && (this->tail == nullptr)) {
        return true;
    }
    else {
        return false;
    }
}

template<class T>
T Stack<T>::pop() { //POP
    T value = this->tail->value; 
    StackNode<T>* p = tail;

    this->tail = p->prev; 
    delete p; 

    if (this->tail == nullptr) {
        this->head = nullptr;
    } else {
        this->tail->next = nullptr;
    }

    return value;
}

template<class T>
void Stack<T>::push(T value) { //PUSH
    StackNode<T> *p = new StackNode<T>(value, NULL, NULL);

    p->next = nullptr;

    if (this->head == nullptr) {
        this->head = this->tail = p;
    } else {
        this->tail->next = p;
        p->prev = this->tail;
        this->tail = p;
    }
}

template class Stack<int>;
