#include "BST.h"
#include <iostream>
#include <sstream>

namespace OtusAlgo {

//----------------------------------
#pragma mark BST implementation
//----------------------------------

void BST::insert(KeyType x) {
    if (root == nullptr)
        root = new NodeType(x);

    NodePtr node = root;
    while (true) {
        if (x == node->key) {
            break;
        }
        if (x < node->key) {
            if (node->left == nullptr) {
                node->left = new NodeType(x);
                break;
            }
            node = node->left;
        }
        else{
            if (node->right == nullptr) {
                node->right = new NodeType(x);
                break;
            }
            node = node->right;
        }
    }
}

bool BST::search(KeyType x) const {
    return searchUtil(root, x);
}

bool BST::searchUtil(NodePtr root, KeyType x) const {
    NodePtr node = root;
    if (node == nullptr)
        return false;
    while (node != nullptr) {
        if (x == node->key)
            return true;
        if (x < node->key) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    return false;
}

auto BST::minValueNode(NodePtr node) -> NodePtr{
   NodePtr current = node;
   while (current && current->left != nullptr)
      current = current->left;
   return current;
}


auto BST::removeUtil(NodePtr node, KeyType key) -> NodePtr {
    if (node == nullptr) return node;
    if (key < node->key) {
        node->left = removeUtil(node->left, key);
    }
    else if (key > node->key) {
        node->right = removeUtil(node->right, key);
    }
    else{
        if (node->left == nullptr){
            NodePtr tmp = node->right;
            delete node;
            return tmp;
        }
        else if (node->right == nullptr){
            NodePtr tmp = node->left;
            delete node;
            return tmp;
        }
        NodePtr temp = minValueNode(node->right);
        node->key = temp->key;
        node->right = removeUtil(node->right, temp->key);
    }
    return node;
}

void BST::remove(KeyType key){
    root = removeUtil(root, key);
}

std::string BST::print() const {
    std::stringstream out;
    print(root, out);
    return out.str();
}

void BST::print(NodePtr node, std::ostream& out) const {
    if (node == nullptr)
        return;
    print(node->left, out);
    out << node->key << "-";
    print(node->right, out);
}

} //namespace OtusAlgo
