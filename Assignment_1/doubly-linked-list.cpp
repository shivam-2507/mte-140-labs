//comment
#include "doubly-linked-list.h"
#include <iostream>

DoublyLinkedList::Node::Node(DataType data) {
    value = data;
    next = nullptr;
    prev = nullptr;
}


DoublyLinkedList::DoublyLinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}


DoublyLinkedList::~DoublyLinkedList() {
    Node *current = head_;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
}


unsigned int DoublyLinkedList::size() const {
    return size_;
}


unsigned int DoublyLinkedList::capacity() const {
    return CAPACITY;
}


bool DoublyLinkedList::empty() const {
    return size_ == 0;
}


bool DoublyLinkedList::full() const {
    return size_==CAPACITY;
}


DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const {
    if (index >= size_) {
        return (head_ && tail_) ? tail_->value : -1;
    }

    Node* current = head_;
    for (unsigned int i = 0; current && i < index; i++) {
        current = current->next;
    }

    return current ? current->value : -1;
}

unsigned int DoublyLinkedList::search(DataType value) const {
    Node* current = head_;
    unsigned int index = 0;

    while (current != nullptr) {
        if (current->value == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return size_;
}


void DoublyLinkedList::print() const {
    Node *current = head_;
    if (head_ == nullptr) {
        std::cout << "Empty list" << std::endl;
        return;
    }
    while (current != nullptr) {
        std::cout << current->value<<std::endl;
        current = current->next;
    }
}


DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const {
    if (index >= size_) {
        return nullptr;
    }

    Node* current = nullptr;

    if (index < size_ / 2) {
        current = head_;
        for (unsigned int i = 0; i < index; i++) {
            current = current->next;
        }
    } else {
        current = tail_;
        for (unsigned int i = size_ - 1; i > index; i--) {
            current = current->prev;
        }
    }

    return current;
}


bool DoublyLinkedList::insert(DataType value, unsigned int index) {
    if (index > size_) {
        return false;
    }

    if (index == 0) {
        return insert_front(value);
    }

    if (index == size_) {
        return insert_back(value);
    }

    Node* current = getNode(index);
    if (!current) {
        return false;
    }

    Node* newNode = new Node(value);
    newNode->next = current;
    newNode->prev = current->prev;

    if (current->prev) {
        current->prev->next = newNode;
    }
    current->prev = newNode;

    size_++;
    return true;
}

bool DoublyLinkedList::insert_front(DataType value) {
    Node* new_node = new Node(value);

    if (!head_) {
        head_ = tail_ = new_node;
    } else {
        new_node->next = head_;
        head_->prev = new_node;
        head_ = new_node;
    }

    size_++;
    return true;
}


bool DoublyLinkedList::insert_back(DataType value) {
    Node* new_node = new Node(value);

    if (!tail_) {
        head_ = tail_ = new_node;
    } else {
        new_node->prev = tail_;
        tail_->next = new_node;
        tail_ = new_node;
    }
    size_++;
    return true;
}


bool DoublyLinkedList::remove(unsigned int index) {
    Node* current = getNode(index);
    if (!current) {
        return false;
    }

    if (current == tail_) {
        return remove_back();
    }
    if (current == head_) {
        return remove_front();
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    size_--;

    return true;
}

bool DoublyLinkedList::remove_front() {
    if (!head_) {
        return false;
    }

    Node* current = head_;

    if (head_ == tail_) {
        head_ = tail_ = nullptr;
    } else {
        head_ = head_->next;
        head_->prev = nullptr;
    }

    delete current;
    size_--;
    return true;
}


bool DoublyLinkedList::remove_back() {
    if (!head_) {
        return false;
    }

    Node* current = tail_;

    if (head_ == tail_) {
        head_ = tail_ = nullptr;
    } else {
        tail_ = tail_->prev;
        tail_->next = nullptr;
    }

    delete current;
    size_--;
    return true;
}

bool DoublyLinkedList::replace(unsigned int index, DataType value) {
    Node* current = getNode(index);
    if (!current) {
        return false;
    }

    current->value = value;
    return true;
}
