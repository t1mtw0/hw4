#include "avlbst.h"
#include "bst.h"
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char *argv[]) {
    // Binary Search Tree tests
    AVLTree<int, int> bt;
    bt.insert(std::make_pair(-94, -94));
    bt.insert(std::make_pair(-52, -52));
    bt.insert(std::make_pair(77, 77));
    bt.insert(std::make_pair(124, 124));
    bt.insert(std::make_pair(36, 36));
    bt.insert(std::make_pair(64, 64));
    bt.insert(std::make_pair(54, 54));
    bt.insert(std::make_pair(-73, -73));
    bt.insert(std::make_pair(52, 52));
    bt.insert(std::make_pair(51, 51));
    bt.insert(std::make_pair(8, 8));
    bt.insert(std::make_pair(-81, -81));
    bt.insert(std::make_pair(-43, -43));
    bt.insert(std::make_pair(129, 129));
    bt.insert(std::make_pair(9, 9));
    bt.insert(std::make_pair(117, 117));
    bt.insert(std::make_pair(-38, -38));
    bt.insert(std::make_pair(21, 21));
    bt.insert(std::make_pair(131, 131));
    bt.insert(std::make_pair(-90, -90));
    bt.insert(std::make_pair(34, 34));
    bt.insert(std::make_pair(5, 5));
    bt.insert(std::make_pair(-131, -131));
    bt.insert(std::make_pair(45, 45));
    bt.insert(std::make_pair(-4, -4));
    bt.insert(std::make_pair(130, 130));
    bt.insert(std::make_pair(13, 13));
    bt.insert(std::make_pair(10, 10));
    bt.insert(std::make_pair(72, 72));
    bt.insert(std::make_pair(-134, -134));
    bt.insert(std::make_pair(95, 95));

    // cout << "Binary Search Tree contents:" << endl;
    // for (BinarySearchTree<int, int>::iterator it = bt.begin(); it != bt.end();
        //  ++it) {
        // cout << it->first << " " << it->second << endl;
    // }
    bt.print();

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
