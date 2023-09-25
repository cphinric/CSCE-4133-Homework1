#include <linked_list.hpp>

template<class T>
LinkedListNode<T>::LinkedListNode(T value, LinkedListNode<T>* next, LinkedListNode<T>* prev) {
    this->value = value;
    this->next = next;
    this->prev = prev;
}

template<class T>
LinkedListNode<T>::~LinkedListNode() {
    this->next = NULL;
}


template<class T>
LinkedList<T>::LinkedList() {
     this->root = NULL;
}

template<class T>
LinkedList<T>::~LinkedList() { //DECONSTRUCTOR
    LinkedListNode<T>* p = root;
    while (p != nullptr) {
        LinkedListNode<T>* q = p -> next;
        delete p;
        p = q;
    }
}


template<class T>
LinkedListNode<T>* LinkedList<T>::insert(T value) { //INSERT
    LinkedListNode<T>* p = find(value);
    if (p != nullptr) {
        return p;
    }
    else {
        LinkedListNode<T>* q = new LinkedListNode<T>(value);
        q->next = root;
        root = q;
        return q;
    }
}

template<class T>
LinkedListNode<T>* LinkedList<T>::find(T value) { // FIND
    LinkedListNode<T>* p = root;
    while (p != nullptr && p->value != value){
        p = p->next;
    }

    return p;
}

template<class T>
LinkedListNode<T>* LinkedList<T>::remove(T value) { //REMOVE
    LinkedListNode<T>* p = root;
    LinkedListNode<T>* q = nullptr;

    while (p != nullptr) {
        if (p->value == value) {
            if (q == nullptr) {
                root = p->next;
                if (root != nullptr) {
                    root->prev = nullptr;
                }
            } else {
                q->next = p->next;
                if (p->next != nullptr) {
                    p->next->prev = q;
                }
            }
            delete p;
            return root;
        } else {
            q = p;
            p = p->next;
        }
    }

    return root;
}

template<class T>
int LinkedList<T>::size() { //SIZE
     int count = 0;
     LinkedListNode<T>* p = root;

     while (p != nullptr) {
        p = p->next;
        count++;
     }

     return count;
}

template class LinkedListNode<int>;
template class LinkedList<int>;
