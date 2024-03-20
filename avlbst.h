#ifndef AVLBST_H
#define AVLBST_H

#include "bst.h"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>

struct KeyError {};

/**
 * A special kind of node for an AVL tree, which adds the balance as a data
 * member, plus other additional helper functions. You do NOT need to implement
 * any functionality or add additional data members or helper functions.
 */
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value> {
  public:
    // Constructor/destructor.
    AVLNode(const Key &key, const Value &value, AVLNode<Key, Value> *parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance() const;
    void setBalance(int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since
    // they return pointers to AVLNodes - not plain Nodes. See the Node class in
    // bst.h for more information.
    virtual AVLNode<Key, Value> *getParent() const override;
    virtual AVLNode<Key, Value> *getLeft() const override;
    virtual AVLNode<Key, Value> *getRight() const override;

  protected:
    int8_t balance_; // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
 * An explicit constructor to initialize the elements by calling the base class
 * constructor
 */
template <class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key &key, const Value &value,
                             AVLNode<Key, Value> *parent)
    : Node<Key, Value>(key, value, parent), balance_(0) {}

/**
 * A destructor which does nothing.
 */
template <class Key, class Value> AVLNode<Key, Value>::~AVLNode() {}

/**
 * A getter for the balance of a AVLNode.
 */
template <class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const {
    return balance_;
}

/**
 * A setter for the balance of a AVLNode.
 */
template <class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance) {
    balance_ = balance;
}

/**
 * Adds diff to the balance of a AVLNode.
 */
template <class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff) {
    balance_ += diff;
}

/**
 * An overridden function for getting the parent since a static_cast is
 * necessary to make sure that our node is a AVLNode.
 */
template <class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const {
    return static_cast<AVLNode<Key, Value> *>(this->parent_);
}

/**
 * Overridden for the same reasons as above.
 */
template <class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const {
    return static_cast<AVLNode<Key, Value> *>(this->left_);
}

/**
 * Overridden for the same reasons as above.
 */
template <class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const {
    return static_cast<AVLNode<Key, Value> *>(this->right_);
}

/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/

template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value> {
  public:
    virtual void insert(const std::pair<const Key, Value> &new_item);
    virtual void remove(const Key &key);
  protected:
    virtual void nodeSwap(AVLNode<Key, Value> *n1, AVLNode<Key, Value> *n2);

    // Add helper functions here
    void leftRotate(AVLNode<Key, Value> *n);
    void rightRotate(AVLNode<Key, Value> *n);
    void insertFix(AVLNode<Key, Value> *p, AVLNode<Key, Value> *n);
    void removeFix(AVLNode<Key, Value> *p, int8_t diff);
};

template <class Key, class Value>
void AVLTree<Key, Value>::leftRotate(AVLNode<Key, Value> *n) {
    AVLNode<Key, Value> *c = n->getRight();
    n->setRight(c->getLeft());
    if (c->getLeft() != NULL)
        c->getLeft()->setParent(n);
    c->setParent(n->getParent());
    if (n->getParent() == NULL)
        BinarySearchTree<Key, Value>::root_ = c;
    else if (n == n->getParent()->getLeft())
        n->getParent()->setLeft(c);
    else if (n == n->getParent()->getRight())
        n->getParent()->setRight(c);
    c->setLeft(n);
    n->setParent(c);
}

template <class Key, class Value>
void AVLTree<Key, Value>::rightRotate(AVLNode<Key, Value> *n) {
    AVLNode<Key, Value> *c = n->getLeft();
    n->setLeft(c->getRight());
    if (c->getRight() != NULL)
        c->getRight()->setParent(n);
    c->setParent(n->getParent());
    if (n->getParent() == NULL)
        BinarySearchTree<Key, Value>::root_ = c;
    else if (n == n->getParent()->getLeft())
        n->getParent()->setLeft(c);
    else if (n == n->getParent()->getRight())
        n->getParent()->setRight(c);
    c->setRight(n);
    n->setParent(c);
}

template <class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value> *p, AVLNode<Key, Value> *n) {
    if (p == NULL || p->getParent() == NULL) return;
    if (p == p->getParent()->getLeft()) {
        AVLNode<Key, Value> *g = p->getParent();
        g->updateBalance(-1);
        if (g->getBalance() == 0) return;
        if (g->getBalance() == -1) {
            insertFix(g, p);
        } else if (g->getBalance() == -2) {
            if (n == p->getLeft()) {
                rightRotate(g);
                p->setBalance(0);
                g->setBalance(0);
            } else {
                leftRotate(p);
                rightRotate(g);
                if (n->getBalance() == -1) {
                    g->setBalance(1);
                    p->setBalance(0);
                } else if (n->getBalance() == 0) {
                    g->setBalance(0);
                    p->setBalance(0);
                } else {
                    g->setBalance(0);
                    p->setBalance(-1);
                }
                n->setBalance(0);
            }
        }
    } else {
        AVLNode<Key, Value> *g = p->getParent();
        g->updateBalance(1);
        if (g->getBalance() == 0) return;
        if (g->getBalance() == 1) {
            insertFix(g, p);
        } else if (g->getBalance() == 2) {
            if (n == p->getRight()) {
                leftRotate(g);
                p->setBalance(0);
                g->setBalance(0);
            } else {
                rightRotate(p);
                leftRotate(g);
                if (n->getBalance() == 1) {
                    g->setBalance(-1);
                    p->setBalance(0);
                } else if (n->getBalance() == 0) {
                    g->setBalance(0);
                    p->setBalance(0);
                } else {
                    g->setBalance(0);
                    p->setBalance(1);
                }
                n->setBalance(0);
            }
        }
    }
}

template <class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value> *p, int8_t diff) {
    std::cout << "bah3" << std::endl;
    if (p == NULL) return;
    int8_t newdiff;
    if (p->getParent() != NULL && p == p->getParent()->getLeft()) {
        newdiff = 1;
    } else if (p->getParent() != NULL && p == p->getParent()->getRight()) {
        newdiff = -1;
    }
    if (diff == -1) {
        if (p->getBalance() + diff == -1) return;
        if (p->getBalance() + diff == 0) {
            p->updateBalance(diff);
            removeFix(p->getParent(), newdiff);
        }
        if (p->getBalance() + diff == -2) {
            AVLNode<Key, Value> *c = p->getLeft();
            if (c->getBalance() == -1) {
                rightRotate(p);
                p->setBalance(0);
                c->setBalance(0);
                removeFix(c->getParent(), newdiff);
            } else {
                AVLNode<Key, Value> *g = c->getRight();
                leftRotate(c);
                rightRotate(p);
                if (g->getBalance() == -1) {
                    c->setBalance(0);
                    p->setBalance(1);
                } else if (g->getBalance() == 0) {
                    c->setBalance(0);
                    p->setBalance(0);
                } else {
                    c->setBalance(-1);
                    p->setBalance(0);
                }
                g->setBalance(0);
                removeFix(g->getParent(), newdiff);
            }
        }
    } else {
        if (p->getBalance() + diff == 1) return;
        if (p->getBalance() + diff == 0) {
            p->updateBalance(diff);
            removeFix(p->getParent(), newdiff);
        }
        if (p->getBalance() + diff == 2) {
            AVLNode<Key, Value> *c = p->getRight();
            if (c->getBalance() == 1) {
                leftRotate(p);
                p->setBalance(0);
                c->setBalance(0);
                removeFix(c->getParent(), newdiff);
            } else {
                AVLNode<Key, Value> *g = c->getLeft();
                rightRotate(c);
                leftRotate(p);
                if (g->getBalance() == 1) {
                    c->setBalance(0);
                    p->setBalance(-1);
                } else if (g->getBalance() == 0) {
                    c->setBalance(0);
                    p->setBalance(0);
                } else {
                    c->setBalance(1);
                    p->setBalance(0);
                }
                g->setBalance(0);
                removeFix(g->getParent(), newdiff);
            }
        }
    }
}

/*
 * Recall: If key is already in the tree, you should
 * overwrite the current value with the updated value.
 */
template <class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item) {
    AVLNode<Key, Value> *n = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
    if (BinarySearchTree<Key, Value>::root_ == NULL) {
        BinarySearchTree<Key, Value>::root_ = n;
        return;
    }
    AVLNode<Key, Value> *p = static_cast<AVLNode<Key, Value> *>(BinarySearchTree<Key, Value>::root_);
    AVLNode<Key, Value> *prev = NULL;
    while (p) {
        if (new_item.first == p->getKey()) {
            p->setValue(new_item.second);
            delete n;
            return;
        }
        if (new_item.first < p->getKey()) {
            prev = p;
            p = p->getLeft();
        } else if (new_item.first > p->getKey()) {
            prev = p;
            p = p->getRight();
        }
    }
    if (new_item.first < prev->getKey()) {
        prev->setLeft(n);
        n->setParent(prev);
    } else if (new_item.first > prev->getKey()) {
        prev->setRight(n);
        n->setParent(prev);
    }
    std::cout << n->getKey() << std::endl;
    std::cout << prev->getKey() << std::endl;
    std::cout << (int)n->getBalance() << std::endl;
    std::cout << (int)prev->getBalance() << std::endl;
    if (n == prev->getLeft()) {
        if (prev->getBalance() - 1 == 0)
            prev->setBalance(0);
        else if (prev->getBalance() - 1 == -1) {
            prev->setBalance(-1);
            insertFix(prev, n);
        }
    } else if (n == prev->getRight()) {
        if (prev->getBalance() + 1 == 0)
            prev->setBalance(0);
        else if (prev->getBalance() + 1 == 1) {
            prev->setBalance(1);
            insertFix(prev, n);
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template <class Key, class Value>
void AVLTree<Key, Value>::remove(const Key &key) {
    AVLNode<Key, Value> *n = static_cast<AVLNode<Key, Value> *>(BinarySearchTree<Key, Value>::internalFind(key));
    if (n == NULL) return;
    if (n->getLeft() != NULL && n->getRight() != NULL) {
        AVLNode<Key, Value> *tmp = static_cast<AVLNode<Key, Value> *>(this->predecessor(n));
        nodeSwap(n, tmp);
    }
    std::cout << n->getKey() << std::endl;
    std::cout << n->getParent()->getKey() << std::endl;
    AVLNode<Key, Value> *p = n->getParent();
    if (n->getLeft() != NULL) {
        if (n->getParent() != NULL && n == n->getParent()->getLeft()) {
            n->getParent()->setLeft(n->getLeft());
            n->getLeft()->setParent(n->getParent());
        } else if (n->getParent() != NULL && n == n->getParent()->getRight()) {
            n->getParent()->setRight(n->getLeft());
            n->getLeft()->setParent(n->getParent());
        }
    } else if (n->getRight() != NULL) {
        if (n->getParent() != NULL && n == n->getParent()->getLeft()) {
            n->getParent()->setLeft(n->getRight());
            n->getRight()->setParent(n->getParent());
        } else if (n->getParent() != NULL && n == n->getParent()->getRight()) {
            n->getParent()->setRight(n->getRight());
            n->getRight()->setParent(n->getParent());
        }
    } else {
        if (n->getParent() != NULL && n == n->getParent()->getLeft()) {
            n->getParent()->setLeft(NULL);
        } else if (n->getParent() != NULL && n == n->getParent()->getRight()) {
            n->getParent()->setRight(NULL);
        }
    }
    std::cout << p->getKey() << std::endl;
    delete n;
    if (p->getParent() != NULL && p == p->getParent()->getLeft()) {
        removeFix(p, 1);
    } else if (p->getParent() != NULL && p == p->getParent()->getRight()) {
        removeFix(p, -1);
    }
}

template <class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key, Value> *n1,
                                   AVLNode<Key, Value> *n2) {
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

#endif
