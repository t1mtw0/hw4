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
    if (c->getLeft() != nullptr)
        c->getLeft()->setParent(n);
    c->setParent(n->getParent());
    if (n->getParent() == nullptr)
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
    if (c->getRight() != nullptr)
        c->getRight()->setParent(n);
    c->setParent(n->getParent());
    if (n->getParent() == nullptr)
        BinarySearchTree<Key, Value>::root_ = c;
    else if (n == n->getParent()->getLeft())
        n->getParent()->setLeft(c);
    else if (n == n->getParent()->getRight())
        n->getParent()->setRight(c);
    c->setRight(n);
    n->setParent(c);
}

template <class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value> *p,
                                    AVLNode<Key, Value> *n) {
    if (p == nullptr || p->getParent() == nullptr)
        return;
    AVLNode<Key, Value> *g = p->getParent();
    if (p == g->getLeft()) {
        g->updateBalance(-1);
        if (g->getBalance() == 0)
            return;
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
        g->updateBalance(1);
        if (g->getBalance() == 0)
            return;
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
    if (p == nullptr)
        return;
    int8_t newdiff;
    if (p->getParent() != nullptr && p == p->getParent()->getLeft()) {
        newdiff = 1;
    } else if (p->getParent() != nullptr && p == p->getParent()->getRight()) {
        newdiff = -1;
    }
    if (diff == -1) {
        if (p->getBalance() + diff == -1) {
            p->updateBalance(diff);
            return;
        }
        if (p->getBalance() + diff == 0) {
            p->updateBalance(diff);
            removeFix(p->getParent(), newdiff);
        } else if (p->getBalance() + diff == -2) {
            AVLNode<Key, Value> *c = p->getLeft();
            if (c->getBalance() == -1) {
                rightRotate(p);
                p->setBalance(0);
                c->setBalance(0);
                removeFix(c->getParent(), newdiff);
            } else if (c->getBalance() == 0) {
                rightRotate(p);
                p->setBalance(-1);
                c->setBalance(1);
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
        if (p->getBalance() + diff == 1) {
            p->updateBalance(diff);
            return;
        }
        if (p->getBalance() + diff == 0) {
            p->updateBalance(diff);
            removeFix(p->getParent(), newdiff);
        } else if (p->getBalance() + diff == 2) {
            AVLNode<Key, Value> *c = p->getRight();
            if (c->getBalance() == 1) {
                leftRotate(p);
                p->setBalance(0);
                c->setBalance(0);
                removeFix(c->getParent(), newdiff);
            } else if (c->getBalance() == 0) {
                leftRotate(p);
                p->setBalance(1);
                c->setBalance(-1);
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
    AVLNode<Key, Value> *n =
        new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
    if (BinarySearchTree<Key, Value>::root_ == nullptr) {
        BinarySearchTree<Key, Value>::root_ = n;
        return;
    }
    AVLNode<Key, Value> *p =
        static_cast<AVLNode<Key, Value> *>(BinarySearchTree<Key, Value>::root_);
    AVLNode<Key, Value> *prev = nullptr;
    while (p) {
        if (new_item.first == p->getKey()) {
            p->setValue(new_item.second);
            delete n;
            return;
        } else if (new_item.first < p->getKey()) {
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
    AVLNode<Key, Value> *n = static_cast<AVLNode<Key, Value> *>(
        BinarySearchTree<Key, Value>::internalFind(key));
    if (n == nullptr)
        return;
    if (n->getLeft() != nullptr && n->getRight() != nullptr) {
        AVLNode<Key, Value> *tmp =
            static_cast<AVLNode<Key, Value> *>(this->predecessor(n));
        nodeSwap(n, tmp);
    }

    Node<Key, Value> *next = nullptr;
    if (n->getLeft() != nullptr) {
        next = n->getLeft();
    } else {
        next = n->getRight();
    }
    if (n->getParent() == nullptr) {
        BinarySearchTree<Key, Value>::root_ = next;
        if (next != nullptr)
            next->setParent(n->getParent());
        delete n;
        return;
    }
    AVLNode<Key, Value> *p = static_cast<AVLNode<Key, Value> *>(n->getParent());
    int8_t diff;
    if (n == n->getParent()->getLeft()) {
        n->getParent()->setLeft(next);
        diff = 1;
    } else if (n == n->getParent()->getRight()) {
        n->getParent()->setRight(next);
        diff = -1;
    }
    if (next != nullptr)
        next->setParent(n->getParent());
    delete n;
    removeFix(p, diff);
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
