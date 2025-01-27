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
void rightRotate(RBTree<T>& t, Node<T>* x){
    Node<T>* y = x->parent;
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
            rightRotate(t, z->parent);
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
                rightRotate(t, z);
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
    showSorted(tree.root, tree.NIL);
    return 0;
}
