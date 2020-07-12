#include "AVL.h"
#include <iostream>
#include <sstream>

namespace OtusAlgo {

void AVL::insert(KeyType key) {
    if (!root) {
        root = std::make_shared<AVLNode<KeyType>>(key);
    } else {
        insert(root, std::make_shared<AVLNode<KeyType>>(key));
    }
}

void AVL::insert(NodePtr parent, NodePtr child) {
    auto nodeToIns = parent;
    while (true) {
        if (child->key < nodeToIns->key) {
            if (!nodeToIns->left) {
                nodeToIns->left = child;
                nodeToIns->left->parent = nodeToIns;
                break;
            } else {
                nodeToIns = nodeToIns->left;
            }
        } else {
            if (!nodeToIns->right) {
                nodeToIns->right = child;
                nodeToIns->right->parent = nodeToIns;
                break;
            } else {
                nodeToIns = nodeToIns->right;
            }
        }
    }
    checkBalance(child);
}

size_t AVL::updateHeight(NodePtr node) {
    if (node == nullptr) return 0;
    return node->height = std::max(updateHeight(node->left), updateHeight(node->right)) + 1;
}

void AVL::checkBalance(NodePtr node) {
    while (node) {
        updateHeight(node);
        int left = node->left ? node->left->height : -1;
        int right = node->right ? node->right->height : -1;
        if (left - right >= 2) {
            int ll;
            if (!node->left || !node->left->left) {
                ll = 0;
            } else {
                ll = node->left->left->height;
            }
            int lr;
            if (!node->left || !node->left->right) {
                lr = 0;
            } else {
                lr = node->left->right->height;
            }
            if (ll >= lr) {
                smallRightTurn(node);
                node = node->parent;
            } else {
                bigRightTurn(node);
                node = node->parent;
            }
        } else if (left - right <= -2) {
            int rr;
            if (!node->right || !node->right->right) {
                rr = 0;
            } else {
                rr = node->right->right->height;
            }
            int rl;
            if (!node->right || !node->right->left) {
                rl = 0;
            } else {
                rl = node->right->left->height;
            }
            if (rr >= rl) {
                smallLeftTurn(node);
                node = node->parent;
            } else {
                bigLeftTurn(node);
                node = node->parent;
            }
        }
        if (node)
            node = node->parent;
    }
}

void AVL::smallLeftTurn(NodePtr a) {
    auto b = a->right;
    auto c = b->left;
    a->right = c;
    b->left = a;
    b->parent = a->parent;
    a->parent = b;
    if (c)
        c->parent = a;
    updateHeight(a);
    updateHeight(b);
    if (a == root) {
        root = b;
    } else {
        if (b->parent->left == a)
            b->parent->left = b;
        else
            b->parent->right = b;
    }
}

void AVL::smallRightTurn(NodePtr a) {
    auto b = a->left;
    auto c = b->right;
    a->left = c;
    b->right = a;
    b->parent = a->parent;
    a->parent = b;
    if (c)
        c->parent = a;
    updateHeight(a);
    updateHeight(b);
    if (a == root) {
        root = b;
    } else {
        if (b->parent->left == a)
            b->parent->left = b;
        else
            b->parent->right = b;
    }
}

void AVL::bigLeftTurn(NodePtr a) {
    auto b = a->right;
    smallLeftTurn(a);
    smallLeftTurn(a);
    smallRightTurn(b);
}

void AVL::bigRightTurn(NodePtr a) {
    auto b = a->left;
    smallRightTurn(a);
    smallRightTurn(a);
    smallLeftTurn(b);
}

std::string AVL::print() const {
    std::stringstream out;
    print(root, out);
    return out.str();
}

void AVL::print(NodePtr node, std::ostream& out) const {
    if (node == nullptr)
        return;
    print(node->left, out);
    out << node->key << "-";
    print(node->right, out);
}

bool AVL::search(KeyType key) const {
    return search(root, key) != nullptr;
}

auto AVL::search(NodePtr root, KeyType key) const -> NodePtr{
    NodePtr node = root;
    if (node == nullptr)
        return nullptr;
    while (node != nullptr) {
        if (key == node->key)
            return node;
        if (key < node->key) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    return nullptr;
}

void AVL::remove(KeyType key) {
    auto node = search(root, key);
    if (node != nullptr) {
        remove(node);
    }
}

void AVL::remove(NodePtr node) {
    if (node->parent) {
        if (node->parent->key > node->key) {
            node->parent->left.reset();
        } else {
            node->parent->right.reset();
        }

        if (node->left) {
            insert(node->parent, node->left);
        }
        if (node->right) {
            insert(node->parent, node->right);
        }
    } else {
        root.reset();
        if (node->left) {
            root = node->left;
            root->parent.reset();
        }
        if (node->right) {
            if (root) {
                insert(root, node->right);
            } else {
                root = node->right;
                root->parent.reset();
            }
        }
    }
    checkBalance(node->parent);
    node->parent.reset();
    node->left.reset();
    node->right.reset();
}

} // namespace OtusAlgo
