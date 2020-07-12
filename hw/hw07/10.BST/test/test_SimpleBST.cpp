#define BOOST_TEST_MODULE SIMPLE_BST_TEST

#include "../BST.h"
#include "../AVL.h"

#include <boost/test/unit_test.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

//using namespace OtusAlgo;

BOOST_AUTO_TEST_CASE (BuildBST)
{
    [[maybe_unused]] OtusAlgo::BST tree;
    [[maybe_unused]] OtusAlgo::AVL tree2;
}

BOOST_AUTO_TEST_CASE (InsertAndSearch) {
    OtusAlgo::BST tree;
    tree.insert(10);
    std::string expected = "10-";
    std::string received = tree.print();
    BOOST_CHECK_MESSAGE(received == expected,
                        "expected print: " + expected + ", received: " + received);

    tree.insert(12);
    expected = "10-12-";
    received = tree.print();
    BOOST_CHECK_MESSAGE(received == expected,
                        "expected print: " + expected + ", received: " + received);

    tree.insert(1);
    expected = "1-10-12-";
    received = tree.print();
    BOOST_CHECK_MESSAGE(received == expected,
                        "expected print: " + expected + ", received: " + received);
    tree.insert(6);
    expected = "1-6-10-12-";
    received = tree.print();
    BOOST_CHECK_MESSAGE(received == expected,
                        "expected print: " + expected + ", received: " + received);

    // search
    BOOST_CHECK_MESSAGE(tree.search(10),
                        "expected print: True");
    BOOST_CHECK_MESSAGE(tree.search(12),
                        "expected print: True");
    BOOST_CHECK_MESSAGE(!tree.search(13),
                        "expected print: False");
}

BOOST_AUTO_TEST_CASE (Delete) {
    OtusAlgo::BST tree;
    tree.insert(10);
    tree.insert(12);
    tree.insert(1);
    tree.insert(6);
    
    tree.remove(5);
    std::string expected = "1-6-10-12-";
    std::string received = tree.print();
    BOOST_CHECK_MESSAGE(received == expected,
                        "expected print: " + expected + ", received: " + received);

    tree.remove(6);
    expected = "1-10-12-";
    received = tree.print();
    BOOST_CHECK_MESSAGE(received == expected,
                        "expected print: " + expected + ", received: " + received);

    tree.remove(10);
    expected = "1-12-";
    received = tree.print();
    BOOST_CHECK_MESSAGE(received == expected,
                        "expected print: " + expected + ", received: " + received);

}

//using namespace OtusAlgo;


BOOST_AUTO_TEST_CASE (AVL_InsertAndSerachSimple)
{
    OtusAlgo::AVL tree;
    tree.insert(10);
    std::string expected = "10-";
    std::string received = tree.print();
    BOOST_CHECK_MESSAGE(received == expected,
                        "expected print: " + expected + ", received: " + received);

    tree.insert(12);
    expected = "10-12-";
    received = tree.print();
    BOOST_CHECK_MESSAGE(received == expected,
                        "expected print: " + expected + ", received: " + received);

    tree.insert(1);
    expected = "1-10-12-";
    received = tree.print();
    BOOST_CHECK_MESSAGE(received == expected,
                        "expected print: " + expected + ", received: " + received);
    
    BOOST_CHECK_MESSAGE(tree.search(10),
                        "expected print: True");
    BOOST_CHECK_MESSAGE(tree.search(12),
                        "expected print: True");
    BOOST_CHECK_MESSAGE(!tree.search(13),
                        "expected print: False");
}

BOOST_AUTO_TEST_CASE (AVL_InsertWithBalance)
{
    OtusAlgo::AVL tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(6);
    tree.insert(5);
    tree.insert(8);
    tree.insert(7);
    tree.insert(9);
    
    std::string expected = "1-2-5-6-7-8-9-";
    std::string received = tree.print();
    BOOST_CHECK_MESSAGE(received == expected,
                        "expected print: " + expected + ", received: " + received);
    
    tree.remove(8);

    expected = "1-2-5-6-7-9-";
    received = tree.print();
    BOOST_CHECK_MESSAGE(received == expected,
                        "expected print: " + expected + ", received: " + received);

}

