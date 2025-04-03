#include "binary-search-tree.h"
#include <iostream>
#include <queue>

BinarySearchTree::Node::Node(DataType newVal) {
    val = newVal;
    left = nullptr;
    right = nullptr;
    avlBalance = 0;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    if (n == nullptr) return -1;
    return 1 + std::max(getNodeDepth(n->left), getNodeDepth(n->right));
}

BinarySearchTree::BinarySearchTree() {
    root_ = nullptr;
    size_ = 0;
}

void deleteTree(BinarySearchTree::Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

BinarySearchTree::~BinarySearchTree() {
    deleteTree(root_);
}

unsigned int BinarySearchTree::size() const {
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    if (root_ == nullptr) {
        throw std::invalid_argument("tree  is empty");
    }
    Node *current = root_;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const {
    if (root_ == nullptr) {
        throw std::invalid_argument("tree is empty");
    }
    Node *current = root_;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->val;
}

unsigned int BinarySearchTree::depth() const {
    return getNodeDepth(root_);
}

void BinarySearchTree::print() const {
    if (root_ == nullptr) {
        std::cout << "Empty tree" << std::endl;
        return;
    }
    std::queue<Node*> q;
    q.push(root_);
    while (!q.empty()) {
        Node *p = q.front();
        q.pop();
        std::cout << p->val << " "<<std::endl;
        if (p->left != nullptr) q.push(p->left);
        if (p->right != nullptr) q.push(p->right);
    }
}

bool BinarySearchTree::exists(DataType val) const {
    Node* current = root_;
    while (current != nullptr) {
        if (current->val == val) return true;
        if (val < current->val) current = current->left;
        else current = current->right;
    }
    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {
    if (exists(val)) return false;
    Node* newNode = new Node(val);
    if (root_ == nullptr) {
        root_ = newNode;
        size_++;
        return true;
    }
    Node *current = root_;
    while (true) {
        if (val < current->val) {
            if (current->left == nullptr) {
                current->left = newNode;
                size_++;
                return true;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = newNode;
                size_++;
                return true;
            }
            current = current->right;
        }
    }
}

bool BinarySearchTree::remove(DataType val) {
    if (root_ == nullptr) {
        std::cout << "The tree is empty." << std::endl;
        return false;
    }

    Node* current = root_;
    Node* previous = nullptr;
    bool isLeftChild = false;

    while (current != nullptr && current->val != val) {
        previous = current;
        if (val < current->val) {
            current = current->left;
            isLeftChild = true;
        } else {
            current = current->right;
            isLeftChild = false;
        }
    }

    if (current == nullptr) return false;

    if (current->left == nullptr && current->right == nullptr) {
        if (current == root_) {
            root_ = nullptr;
        } else if (isLeftChild) {
            previous->left = nullptr;
        } else {
            previous->right = nullptr;
        }
        delete current;
        size_--;
        return true;
    }

    if (current->left == nullptr || current->right == nullptr) {
        Node* child = (current->left != nullptr) ? current->left : current->right;
        if (current == root_) {
            root_ = child;
        } else if (isLeftChild) {
            previous->left = child;
        } else {
            previous->right = child;
        }
        delete current;
        size_--;
        return true;
    }

    Node* successor = current->right;
    Node* successorPrevious = current;

    while (successor->left != nullptr) {
        successorPrevious = successor;
        successor = successor->left;
    }

    if (successorPrevious != current) {
        successorPrevious->left = successor->right;
        successor->right = current->right;
    }
    successor->left = current->left;

    if (current == root_) {
        root_ = successor;
    } else if (isLeftChild) {
        previous->left = successor;
    } else {
        previous->right = successor;
    }

    delete current;
    size_--;
    return true;
}

