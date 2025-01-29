#include <iostream>
#include "RBTreeDataStructure.h"



int main() {
    RBTree<int> tree;
    for (int i = 1; i <= 10; i++) {
        tree.insert(i);
    }
    tree.print();
    tree.clear();
    tree.print();
}
