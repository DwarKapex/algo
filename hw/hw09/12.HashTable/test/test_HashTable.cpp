#define BOOST_TEST_MODULE SIMPLE_HASHTABLE_TEST

#include "../HashTable.h"


#include <boost/test/unit_test.hpp>

//using namespace OtusAlgo;

BOOST_AUTO_TEST_CASE (BuildHashTable)
{
    [[maybe_unused]] OtusAlgo::HashTable<int, char> table;
    
}


BOOST_AUTO_TEST_CASE (HashTableWork)
{
    OtusAlgo::HashTable<int, char> table;
    BOOST_TEST(!table.containsValue('b'));
    BOOST_TEST(!table.get(10).has_value());
    table.put(10, 'b');
    BOOST_TEST(table.containsValue('b'));
    BOOST_TEST(table.containsKey(10));
    BOOST_TEST(!table.containsKey(9));
    BOOST_TEST(table.get(10).value() == 'b');
    BOOST_TEST(table.size() == 1);
}

BOOST_AUTO_TEST_CASE (HashTableRehash)
{
    OtusAlgo::HashTable<int, char> table(1);
    BOOST_TEST(!table.containsValue('b'));
    BOOST_TEST(!table.get(10).has_value());
    table.put(10, 'b');
    BOOST_TEST(table.containsValue('b'));
    BOOST_TEST(table.containsKey(10));
    BOOST_TEST(!table.containsKey(9));
    BOOST_TEST(table.get(10).value() == 'b');
    BOOST_TEST(table.size() == 1);
    table.put(9, 'a');
    BOOST_TEST(table.containsValue('b'));
    BOOST_TEST(table.containsKey(10));
    BOOST_TEST(table.containsKey(9));
    BOOST_TEST(table.get(10).value() == 'b');
    BOOST_TEST(table.size() == 2);
}


