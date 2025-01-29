#ifndef RBTreeDataStructureImplementation_h
#define RBTreeDataStructureImplementation_h

#include "RBTreeDataStructure.h"

#include <iostream>


template <typename T>
void RBTree<T>::leftRotate(Node<T>* x){
    Node<T>* y = x->right;
    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL){
        root = y;
    }
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}


template <typename T>
void RBTree<T>::rightRotate(Node<T>* y){
    Node<T>* x = y->left;
    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NIL)
        root = x;
    else if (y->parent->left == y)
        y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}


template <typename T>
void RBTree<T>::RBInsertFixUp(Node<T>* z){
    while (!z->parent->isBlack){
        if (z->parent == z->parent->parent->left){
            Node<T>* y = z->parent->parent->right;
            if (!y->isBlack){
                z->parent->isBlack = 1;
                y->isBlack = 1;
                z->parent->parent->isBlack = 0;
                z = z->parent->parent;
                continue;
            }
            if(z == z->parent->right){
                z = z->parent;
                leftRotate(z);
            }
            z->parent->isBlack = 1;
            z->parent->parent->isBlack = 0;
            rightRotate(z->parent->parent);
        }
        else{
            Node<T>* y = z->parent->parent->left;
            if (!y->isBlack){
                z->parent->isBlack = 1;
                y->isBlack = 1;
                z->parent->parent->isBlack = 0;
                z = z->parent->parent;
                continue;
            }
            if(z == z->parent->left){
                z = z->parent;
                rightRotate(z->parent);
            }
            z->parent->isBlack = 1;
            z->parent->parent->isBlack = 0;
            leftRotate(z->parent->parent);
        }
    }
    root->isBlack = 1;
}


template <typename T>
void RBTree<T>::RBInsert(Node<T>* z){
    Node<T>* y = NIL;
    Node<T>* x = root;
    while (x != NIL){
        y = x;
        if (z->info < x->info)
            x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == NIL)
        root = z;
    else if(z->info < y->info)
        y->left = z;
    else
        y->right = z;
    z->left = NIL;
    z->right = NIL;
    z->isBlack = 0;
    RBInsertFixUp(z);
}


template<typename T>
void RBTree<T>::insert(T&& el) {
    Node<T>* z = new Node<T>(el);
    RBInsert(z);
}

template<typename T>
void RBTree<T>::insert(T& el) {
    Node<T>* z = new Node<T>(el);
    RBInsert(z);
}



template <typename T>
Node<T>* RBTree<T>::treeMinimum(Node<T>* v) const {
    while (v->left != NIL) {
        v = v->left;
    }
    return v;
}

template<typename T>
T RBTree<T>::minimum() const {
    return treeMinimum(root).info;
}


template <typename T>
void RBTree<T>::RBTransplant(Node<T>* u, Node<T>* v) {
    if (u->parent == NIL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
    delete u;
}


template <typename T>
void RBTree<T>::RBRemoveFixUp(Node<T>* x) {
    while (x != root && x->isBlack) {
        if (x == x->parent->left) {
            Node<T>* w = x->parent->right;
            if (!w->isBlack) {
                w->isBlack = 1;
                x->parent->isBlack = 0;
                leftRotate(x->parent);
            }
            if (w->left->isBlack && w->right->isBlack) {
                w->isBlack = 0;
                x = x->parent;
            }
            else {
                if (w->right->isBlack) {
                    w->isBlack = 0;
                    w->left->isBlack = 1;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->isBlack = x->parent->isBlack;
                x->parent->isBlack = 1;
                w->right->isBlack = 1;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            Node<T>* w = x->parent->left;
            if (!w->isBlack) {
                w->isBlack = 1;
                x->parent->isBlack = 0;
                rightRotate(x->parent);
            }
            if (w->right->isBlack && w->left->isBlack) {
                w->isBlack = 0;
                x = x->parent;
            }
            else {
                if (w->left->isBlack) {
                    w->isBlack = 0;
                    w->right->isBlack = 1;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->isBlack = x->parent->isBlack;
                x->parent->isBlack = 1;
                w->right->isBlack = 1;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->isBlack = 1;
}

template <typename T>
void RBTree<T>::RBRemove(Node<T>* z) {
    Node<T>* y = z;
    Node<T>* x;
    bool yIsBlackOriginal = y->isBlack;

    if (z->left == NIL) {
        x = z->right;
        RBTransplant(z, z->right);
    }
    else if (z->right == NIL) {
        x = z->left;
        RBTransplant(z, z->left);
    }
    else {
        y = treeMinimum(z->right);
        yIsBlackOriginal = y->isBlack;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            RBTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RBTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->isBlack = z->isBlack;
    }
    if (yIsBlackOriginal)
        RBRemoveFixUp(y);
}

template <typename T>
Node<T> RBTree<T>::RBFind(Node<T>* v, T& key) const {
    if (key == v->info)
        return v;
    if (v == NIL)
        return NIL;
    if (key < v->info)
        return RBFind(v->left, key);
    return RBFind(v->right, key);
}


template<typename T>
void RBTree<T>::remove(T&& el) {
    Node<T>* z = RBFind(root, el);
    if (z == NIL) return;
    RBRemove(z);
}

template<typename T>
void RBTree<T>::remove(T& el) {
    Node<T>* z = RBFind(root, el);
    if (z == NIL) return;
    RBRemove(z);
}

template<typename T>
void RBTree<T>::showTree(Node<T>* v) const {
    if (v == NIL) return;
    if (v->left != NIL)
        showTree(v->left);
    std::cout << v->info << " ";
    if (v->right != NIL)
        showTree(v->right);
}


template<typename T>
void RBTree<T>::print() {
    showTree(root);
    std::cout << '\n';
}

template <typename T>
void RBTree<T>::clearTree(Node<T>* v) {
    if (v == NIL) return;
    if (v->left != NIL) {
        clearTree(v->left);
        v->parent->left = NIL;
    }
    if (v->right != NIL) {
        clearTree(v->right);
        v->parent->right = NIL;
    }
    delete v;
}

template <typename T>
void RBTree<T>::clear() {
    clearTree(root);
    root = NIL;
}

#endif