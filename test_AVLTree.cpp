#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "AVLTree.h"
#include <iostream>
#include <map>


/*
    avl functions:
        - root
        - copy constructor
        - deconstructor
        - copy assignment
        - contains 
        - isEmpty()
        - prettyPrintTree()
        - makeEmpty()
        - insert()
*/

TEST_CASE("testing insert")
{
    //creating an instance of the avl tree
    AvlTree<std::string,std::string> exampleTree;

    SECTION("inserting, checking to see if the values in the map are correct")
    {
       //creating a sample maps, which will hold a filepath (string) and a frequency
       std::map<std::string, size_t> value1 = {{"filepathEx", 2}, {"filepathEx2", 6}};
       //creating a sample map called value2, which will hold a filepath (string) and a frequency
       std::map<std::string, size_t> value2 = {{"filepathEx3", 8}, {"filepathEx4", 1}};

        //inserting node into AVL tree
        exampleTree.insert("hello", value1);
        exampleTree.insert("world", value2);

        //checking whether the nodes exist within the tree
        REQUIRE(exampleTree.contains("hello") == true);
        REQUIRE(exampleTree.contains("world") == true);

        //checking the node hello's frequency value, which is associated with a key (filepath) in a map
        REQUIRE(exampleTree.find("hello")["filepathEx"] == 2);



    }

}