#pragma once

#include "Node.h"

//----------------------------------------------------
#pragma mark AVL declaraion
//----------------------------------------------------

namespace OtusAlgo {


class AVL {
    using KeyType = int;
    using NodePtr = AVLNode<KeyType>::NodePtr;
public:
    void insert(KeyType key);
    std::string print() const;
    bool search(KeyType key) const;
    void remove(KeyType key);
    
private:
    void insert(NodePtr parent, NodePtr child);
    size_t updateHeight(NodePtr node);
    void checkBalance(NodePtr node);
    void smallLeftTurn(NodePtr node);
    void smallRightTurn(NodePtr node);
    void bigLeftTurn(NodePtr node);
    void bigRightTurn(NodePtr node);
    NodePtr search(NodePtr root, KeyType key) const;
    void print(NodePtr root, std::ostream& out) const;
    void remove(NodePtr node);
    
    NodePtr root;
};

} //namespace OtusAlgo

