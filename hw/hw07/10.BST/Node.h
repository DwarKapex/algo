#pragma once

#include <memory>

namespace OtusAlgo {


template<typename Key = int>
struct Node {
    using NodePtr = Node<Key>*;
    Node(Key key_):
          key(key_)
    {}
    
    Key key;
    NodePtr left = nullptr;
    NodePtr right = nullptr;
};


template<typename KeyType = int>
struct AVLNode {
    using NodePtr = std::shared_ptr<AVLNode<KeyType>>;
    explicit AVLNode(KeyType key_) : key(key_) {};
    
    KeyType key;
    NodePtr left = nullptr;
    NodePtr right = nullptr;
    NodePtr parent = nullptr;
    
    size_t height = 0;
};



} //namespace OtusAlgo

