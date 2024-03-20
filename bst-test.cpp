#include "avlbst.h"
#include "bst.h"
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char *argv[]) {
    // Binary Search Tree tests
    BinarySearchTree<char, int> bt;
    bt.insert(std::make_pair('d', 5));
    bt.insert(std::make_pair('e', 9));
    bt.insert(std::make_pair('a', 1));
    bt.insert(std::make_pair('e', 8));
    bt.insert(std::make_pair('c', 3));
    bt.insert(std::make_pair('c', 4));
    bt.insert(std::make_pair('b', 2));
    bt.insert(std::make_pair('g', 2));
    bt.insert(std::make_pair('j', 2));
    bt.insert(std::make_pair('l', 2));
    bt.insert(std::make_pair('l', 2));
    bt.insert(std::make_pair('j', 2));
    bt.insert(std::make_pair('j', 2));
    bt.insert(std::make_pair('s', 2));
    bt.insert(std::make_pair('d', 2));
    bt.insert(std::make_pair('d', 2));
    bt.insert(std::make_pair('g', 2));
    bt.insert(std::make_pair('h', 2));
    bt.insert(std::make_pair('a', 2));
    bt.insert(std::make_pair('q', 2));
    bt.insert(std::make_pair('z', 2));
    bt.insert(std::make_pair('b', 2));
    bt.insert(std::make_pair('z', 2));
    bt.insert(std::make_pair('m', 2));
    bt.insert(std::make_pair('j', 2));
    bt.insert(std::make_pair('l', 2));
    bt.insert(std::make_pair('x', 2));
    bt.insert(std::make_pair('s', 2));
    bt.insert(std::make_pair('d', 2));
    bt.insert(std::make_pair('f', 2));
    bt.insert(std::make_pair('g', 2));
    bt.insert(std::make_pair('h', 2));
    bt.insert(std::make_pair('j', 2));
    bt.insert(std::make_pair('k', 2));
    bt.insert(std::make_pair('l', 2));
    bt.insert(std::make_pair('w', 2));
    bt.insert(std::make_pair('e', 2));
    bt.insert(std::make_pair('r', 2));
    bt.insert(std::make_pair('t', 2));
    bt.insert(std::make_pair('y', 2));
    bt.insert(std::make_pair('u', 2));
    bt.insert(std::make_pair('i', 2));
    bt.remove('c');
    bt.insert(std::make_pair('f', 10));

    cout << "Binary Search Tree contents:" << endl;
    for (BinarySearchTree<char, int>::iterator it = bt.begin(); it != bt.end();
         ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if (bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    } else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

    // AVL Tree Tests
    /*
    AVLTree<char, int> at;
    at.insert(std::make_pair('a', 1));
    at.insert(std::make_pair('b', 2));
    at.print();
    at.insert(std::make_pair('c', 3));
    at.print();

    cout << "\nAVLTree contents:" << endl;
    for (AVLTree<char, int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if (at.find('b') != at.end()) {
        cout << "Found b" << endl;
    } else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');

    at.print();
*/
    return 0;
}
