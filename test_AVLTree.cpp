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

TEST_CASE("Avltree tests")
{
    //creating an instance of the avl tree
    AvlTree<std::string,std::string> exampleTree;

    SECTION("insert, contains, find")
    {
        //creating sample maps, which hold a frequency and a filepath (string)
       std::map<size_t, std::string> value1 = {{2, "filepathEx"}, {6, "filepathEx2"}};
       std::map<size_t, std::string> value2 = {{8, "filepathEx3"}, {1, "filepathEx4"}};

        //inserting node into AVL tree
        exampleTree.insert("hello", value1);
        exampleTree.insert("world", value2);

        //checking whether the nodes exist within the tree
        REQUIRE(exampleTree.contains("hello") == true);
        REQUIRE(exampleTree.contains("world") == true);

        //checking the map stored in the node "hello." it should give me back the filepath associated with a frequency
        REQUIRE(exampleTree.find("hello")[2] == "filepathEx");
    }

    SECTION ("insert, makeEmpty, isEmpty")
    {
        //creating sample maps, which hold a frequency and a filepath (string)
       std::map<size_t, std::string> value1 = {{2, "filepathEx"}, {6, "filepathEx2"}};
       std::map<size_t, std::string> value2 = {{8, "filepathEx3"}, {1, "filepathEx4"}};

        //inserting node into AVL tree
        exampleTree.insert("hello", value1);
        exampleTree.insert("world", value2);

        REQUIRE(exampleTree.isEmpty() == false);

        exampleTree.makeEmpty();

        REQUIRE(exampleTree.isEmpty());
    }

    SECTION("copy assignment and copy constructor")
    {
        //copy constructor
        AvlTree<std::string,std::string> exampleTree2(exampleTree);

        //copy assignment
        AvlTree<std::string,std::string> exampleTree3 = exampleTree;

        


    }
}

