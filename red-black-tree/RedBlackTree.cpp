//
// Created by Mikhail on 27.01.2025.
//

#include <iostream>
#include <vector>

template <typename T>
struct Node{
    explicit Node(T info) : info(info) {}
    Node() = default;
    Node<T>* left{nullptr};
    Node<T>* right{nullptr};
    Node<T>* parent{nullptr};
    bool isBlack{1};
    T info;
};

template <typename T>
struct RBTree{
    Node<T>* root;
    Node<T>* NIL;
    RBTree() {
        NIL = new Node<T>();
        root = NIL;
    }
};


template <typename T>
void leftRotate(RBTree<T>& t, Node<T>* x){
    Node<T>* y = x->right;
    x->right = y->left;

    if (y->left != t.NIL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == t.NIL){
        t.root = y;
    }
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

template <typename T>
void rightRotate(RBTree<T>& t, Node<T>* y){
    Node<T>* x = y->left;
    y->left = x->right;

    if (x->right != t.NIL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == t.NIL)
        t.root = x;
    else if (y->parent->left == y)
        y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}


template <typename T>
void RBInsertFixUp(RBTree<T>& t, Node<T>* z){
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
                leftRotate(t, z);
            }
            z->parent->isBlack = 1;
            z->parent->parent->isBlack = 0;
            rightRotate(t, z->parent->parent);
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
                rightRotate(t, z->parent);
            }
            z->parent->isBlack = 1;
            z->parent->parent->isBlack = 0;
            leftRotate(t, z->parent->parent);
        }
    }
    t.root->isBlack = 1;
}

template <typename T>
void RBInsert(RBTree<T>& t, Node<T>* z){
    Node<T>* y = t.NIL;
    Node<T>* x = t.root;
    while (x != t.NIL){
        y = x;
        if (z->info < x->info)
            x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == t.NIL)
        t.root = z;
    else if(z->info < y->info)
        y->left = z;
    else
        y->right = z;
    z->left = t.NIL;
    z->right = t.NIL;
    z->isBlack = 0;
    RBInsertFixUp(t, z);
}

template <typename T>
Node<T>* treeMinimum(RBTree<T> t, Node<T>* v) {
    while (v->left != t.NIL) {
        v = v->left;
    }
    return v;
}


template <typename T>
void RBTransplant(RBTree<T> t, Node<T>* u, Node<T>* v) {
    if (u->parent == t.NIL)
        t.root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}


template <typename T>
void RBDeleteFixUp(RBTree<T> t, Node<T>* x) {
    while (x != t.root && x->isBlack) {
        if (x == x->parent->left) {
            Node<T>* w = x->parent->right;
            if (!w->isBlack) {
                w->isBlack = 1;
                x->parent->isBlack = 0;
                leftRotate(t, x->parent);
            }
            if (w->left->isBlack && w->right->isBlack) {
                w->isBlack = 0;
                x = x->parent;
            }
            else {
                if (w->right->isBlack) {
                    w->isBlack = 0;
                    w->left->isBlack = 1;
                    rightRotate(t, w);
                    w = x->parent->right;
                }
                w->isBlack = x->parent->isBlack;
                x->parent->isBlack = 1;
                w->right->isBlack = 1;
                leftRotate(t, x->parent);
                x = t.root;
            }
        }
        else {
            Node<T>* w = x->parent->left;
            if (!w->isBlack) {
                w->isBlack = 1;
                x->parent->isBlack = 0;
                rightRotate(t, x->parent);
            }
            if (w->right->isBlack && w->left->isBlack) {
                w->isBlack = 0;
                x = x->parent;
            }
            else {
                if (w->left->isBlack) {
                    w->isBlack = 0;
                    w->right->isBlack = 1;
                    leftRotate(t, w);
                    w = x->parent->left;
                }
                w->isBlack = x->parent->isBlack;
                x->parent->isBlack = 1;
                w->right->isBlack = 1;
                rightRotate(t, x->parent);
                x = t.root;
            }
        }
    }
    x->isBlack = 1;
}

template <typename T>
void RBTreeDelete(RBTree<T> t, Node<T>* z) {
    Node<T>* y = z;
    Node<T>* x;
    bool yIsBlackOriginal = y->isBlack;

    if (z->left == t.NIL) {
        x = z->right;
        RBTransplant(t, z, z->right);
    }
    else if (z->right == t.NIL) {
        x = z->left;
        RBTransplant(t, z, z->left);
    }
    else {
        y = treeMinimum(t, z->right);
        yIsBlackOriginal = y->isBlack;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            RBTransplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RBTransplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->isBlack = z->isBlack;
    }
    if (yIsBlackOriginal)
        RBDeleteFixUp(t, y);
}

template <typename T>
Node<T>* RBFind(RBTree<T> t, Node<T>* v, T key) {
    if (key == v->info)
        return v;
    if (v == t.NIL)
        return t.NIL;
    if (key < v->info)
        return RBFind(t, v->left, key);
    return RBFind(t, v->right, key);
}

template <typename T>
void RBDelete(RBTree<T> t, T key) {
    Node<T>* z = RBFind(t, t.root, key);
    if (z == t.NIL) return;
    RBTreeDelete(t, z);
}

template <typename T>
void showSorted(Node<T>* t, Node<T>* NIL) {
    if (t->left != NIL)
        showSorted(t->left, NIL);
    std::cout << t->info << " ";
    if (t->right != NIL)
        showSorted(t->right, NIL);
}


int main(){
    RBTree<int> tree;
    for (int i = 0; i <= 10; ++i){
        Node<int>* node = new Node<int>{i};
        RBInsert(tree, node);
    }
    for (int i = 10; i >= 0; --i){
        Node<int>* node = new Node<int>{i};
        RBInsert(tree, node);
    }
    RBDelete(tree, 4);
    RBDelete(tree, 4);
    RBDelete(tree, 9);
    RBDelete(tree, 1);
    showSorted(tree.root, tree.NIL);
    return 0;
}
