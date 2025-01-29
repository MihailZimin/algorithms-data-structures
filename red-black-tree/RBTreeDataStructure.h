//
// Created by Mikhail on 28.01.2025.
//

#ifndef RBTREEDATASTRUCTURE_H
#define RBTREEDATASTRUCTURE_H


template <typename T>
struct Node {
    Node() = default;
    explicit Node(T& info): info(info) {}
    explicit Node(T&& info): info(info) {}

    T info;
    Node<T>* left{nullptr};
    Node<T>* right{nullptr};
    Node<T>* parent{nullptr};
    bool isBlack{true};
};

template <typename T>
class RBTree {
public:
    RBTree() {
        NIL = new Node<T>();
        root = NIL;
    }

    void insert(T&& el);
    void insert(T& el);
    void remove(T&& el);
    void remove(T& el);
    void print();
    void clear();
    T minimum() const;

    ~RBTree() {
        clear();
        delete NIL;
    }


private:
    Node<T>* root{nullptr};
    Node<T>* NIL{nullptr};


    void leftRotate(Node<T>* x);
    void rightRotate(Node<T>* y);
    void RBInsertFixUp(Node<T>* z);
    Node<T>* treeMinimum(Node<T>* v) const;
    void RBTransplant(Node<T>* u, Node<T>* v);
    void RBInsert(Node<T>* z);
    void RBRemoveFixUp(Node<T>* x);
    void RBRemove(Node<T>* z);
    Node<T> RBFind(Node<T>* v, T& key) const;
    void showTree(Node<T>* v) const;
    void clearTree(Node<T>* v);
};

#include "RBTreeDataStructureImplementation.h"
#endif //RBTREEDATASTRUCTURE_H
