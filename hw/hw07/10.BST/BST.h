#pragma once

#include "Node.h"
#include <string>
namespace OtusAlgo {


class IBST {
public:
    virtual void insert(int x) = 0;
    virtual bool search(int x) const = 0;
    virtual void remove(int x) = 0;
};

//----------------------------------------------------
#pragma mark BST declaraion
//----------------------------------------------------


class BST: public IBST {
    using KeyType = int;
    using NodeType = Node<KeyType>;
    using NodePtr = NodeType*;
    
public:
    void insert(KeyType x) override;
    bool search(KeyType x) const override;
    void remove(KeyType x) override;
    
    std::string print() const;
    
private:
    bool searchUtil(NodePtr root, KeyType x) const;
    NodePtr removeUtil(NodePtr node, KeyType key);
    void print(NodePtr node, std::ostream& out) const;
    NodePtr minValueNode(NodePtr node);
    NodePtr root = nullptr;
};



} //namespace OtusAlgo

