#ifndef TESTER_BINARY_SEARCH_TREE_BSTREE_H
#define TESTER_BINARY_SEARCH_TREE_BSTREE_H

#include "NodeBT.h"

template<typename T>
class BSTree {
private:
    NodeBT<T> *root;
    std::string preOrder;
    std::string inOrder;
    std::string postOrder;

public:
    BSTree() : root(nullptr) {}

    void insert(T value) {
        insert(this->root, value);
    }

    bool find(T value) {
        return find(this->root, value);
    }

    std::string displayInOrder() {
        this->inOrder = "";
        displayInOrder(this->root);
        return inOrder;
    }

    std::string displayPreOrder() {
        this->preOrder = "";
        displayPreOrder(this->root);
        return preOrder;
    }

    std::string displayPostOrder() {
        this->postOrder = "";
        displayPostOrder(this->root);
        return postOrder;
    }

    int height() {
        return height(this->root);
    }

    T minValue() {
        return minValue(this->root);
    }

    T maxValue() {
        return maxValue(this->root);
    }

    bool isBalanced() {
        return isBalanced(this->root);
    }

    int size() {
        return size(this->root);
    }

    void remove(T value) {
        remove(this->root, value);
    }

    ~BSTree() {
        if (this->root != nullptr) {
            this->root->killSelf();
        }
    }

private:
    void displayInOrder(NodeBT<T> *node);

    void displayPreOrder(NodeBT<T> *node);

    void displayPostOrder(NodeBT<T> *node);

    void insert(NodeBT<T> *&node, T value);

    bool find(NodeBT<T> *node, T value);

    int height(NodeBT<T> *node);

    bool isBalanced(NodeBT<T> *node);

    T minValue(NodeBT<T> *node);

    T maxValue(NodeBT<T> *node);

    int size(NodeBT<T> *node);

    void remove(NodeBT<T> *&node, T value);
};

template<typename T>
void BSTree<T>::insert(NodeBT<T> *&node, T value) {
    if (node == nullptr) node = new NodeBT<T>(value);
    else if(value == node->data) return;
    else if (value < node->data) insert(node->left, value);
    else insert(node->right, value);
}

template<typename T>
bool BSTree<T>::find(NodeBT<T> *node, T value) {
    if (node == nullptr)
        return false;
    else if (value < node->data)
        return find(node->left, value);
    else if (value > node->data)
        return find(node->right, value);
    else
        return true;
}

template<typename T>
int BSTree<T>::height(NodeBT<T> *node) {
    if (node == nullptr)
        return -1;
    else
        return std::max(height(node->left), height(node->right)) + 1;
}

template<typename T>
bool BSTree<T>::isBalanced(NodeBT<T> *node) {
    if (node == nullptr)
        return true;
    else
        return abs(height(node->left) - height(node->right)) <= 1 && isBalanced(node->left) && isBalanced(node->right);
}

template<typename T>
void BSTree<T>::displayPreOrder(NodeBT<T> *node) {
    if (node == nullptr)
        return;
    preOrder+=std::to_string(node->data) + " ";
    displayPreOrder(node->left);
    displayPreOrder(node->right);
}

template<typename T>
void BSTree<T>::displayInOrder(NodeBT<T> *node) {
    if (node == nullptr)
        return;
    displayInOrder(node->left);
    inOrder+=std::to_string(node->data) + " ";
    displayInOrder(node->right);
}

template<typename T>
void BSTree<T>::displayPostOrder(NodeBT<T> *node) {
    if (node == nullptr) return;
    displayPostOrder(node->left);
    displayPostOrder(node->right);
    postOrder+=std::to_string(node->data) + " ";
}

template<typename T>
T BSTree<T>::minValue(NodeBT<T> *node) {
    if (node == nullptr) throw ("The tree is empty");
    else if (node->left == nullptr) return node->data;
    else return minValue(node->left);
}

template<typename T>
T BSTree<T>::maxValue(NodeBT<T> *node) {
    if (node == nullptr) throw ("The tree is empty");
    else if (node->right == nullptr) return node->data;
    else return maxValue(node->right);
}

template<typename T>
int BSTree<T>::size(NodeBT<T> *node) {
    if (node == nullptr) return 0;
    else return 1 + size(node->left) + size(node->right);
}

template<typename T>
void BSTree<T>::remove(NodeBT<T> *&node, T value) {
    if (node == nullptr) return;
    else if (value < node->data) remove(node->left, value);
    else if (value > node->data) remove(node->right, value);
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            NodeBT<T> *temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            NodeBT<T> *temp = node;
            node = node->left;
            delete temp;
        } else {
            T temp = maxValue(node->left);
            node->data = temp;
            remove(node->left, temp);
        }
    }
}

#endif //TESTER_BINARY_SEARCH_TREE_BSTREE_H
