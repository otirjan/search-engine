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
        //inserting node into AVL tree
        exampleTree.insert("hello", "filepathEx", 2);
        exampleTree.insert("hello", "filepathEx2", 6);
        exampleTree.insert("world", "filepathEx3", 8);
        exampleTree.insert("world", "filepathEx4", 1);

        //checking whether the nodes exist within the tree
        REQUIRE(exampleTree.contains("hello") == true);
        REQUIRE(exampleTree.contains("world") == true);

        //checking the map stored in the node "hello." it should give me back the filepath associated with a frequency
        REQUIRE(exampleTree.find("hello")["filepathEx"] == 2);
    }

    SECTION ("insert, makeEmpty, isEmpty")
    {
        //inserting node into AVL tree
        exampleTree.insert("hello", "filepathEx", 5);
        exampleTree.insert("hello", "filepathEx2", 6);
        exampleTree.insert("world", "filepathEx3", 8);
        exampleTree.insert("world", "filepathEx4", 1);

        REQUIRE(exampleTree.isEmpty() == false);

        exampleTree.makeEmpty();

        REQUIRE(exampleTree.isEmpty());
    }
}
    TEST_CASE("all things copying")
    {
        AvlTree<std::string,std::string> exampleTree;

        //inserting node into AVL tree
        exampleTree.insert("hello", "filepathEx", 5);
        exampleTree.insert("hello", "filepathEx2", 6);
        exampleTree.insert("world", "filepathEx3", 8);
        exampleTree.insert("world", "filepathEx4", 1);

        //copy constructor
        AvlTree<std::string,std::string> exampleTree2(exampleTree);

        //copy assignment
        AvlTree<std::string,std::string> exampleTree3 = exampleTree;


        SECTION("copy assignment, copy constructor, getTotal")
        {
            REQUIRE(exampleTree.getTotal() == exampleTree2.getTotal());
            REQUIRE(exampleTree.getTotal() == exampleTree3.getTotal());

            REQUIRE(exampleTree.isEmpty() == exampleTree2.isEmpty());
            REQUIRE(exampleTree.isEmpty() == exampleTree3.isEmpty());

            exampleTree.makeEmpty();

            REQUIRE(exampleTree2.getTotal() == 2);
            REQUIRE(exampleTree3.getTotal() == 2);
            REQUIRE(exampleTree2.isEmpty() == false);
            REQUIRE(exampleTree3.isEmpty() == false);
        }

        SECTION("messing with the exampleTrees independently of each other")
        {
            //insert nodes
            exampleTree2.insert("apple", "filepathEx", 2);
            exampleTree2.insert("apple", "filepathEx2", 6);
            exampleTree2.insert("apple", "filepathEx3", 16);
            exampleTree2.insert("apple", "filepathEx4", 23);
            exampleTree3.insert("data", "filepathEx", 5);
            exampleTree3.insert("structures", "filepathEx", 80);
            exampleTree3.insert("structures", "filepathEx2", 4);
            exampleTree3.insert("structures", "filepathEx3", 9);
            exampleTree3.insert("structures", "filepathEx4", 1);
            exampleTree3.insert("structures", "filepathEx5", 13);

            REQUIRE(exampleTree2.getTotal() == 3);
            REQUIRE(exampleTree3.getTotal() == 4);

            REQUIRE(exampleTree2.isEmpty() == false);
            REQUIRE(exampleTree3.isEmpty() == false);

        }

        SECTION("extra copy assignment test")
        {
            AvlTree<std::string,std::string> exampleTree4;

            exampleTree4.insert("apple", "filepathEx", 2);
            exampleTree4.insert("apple", "filepathEx2", 6);
            exampleTree4.insert("apple", "filepathEx3", 16);
            exampleTree4.insert("apple", "filepathEx4", 23);
            exampleTree4.insert("data", "filepathEx", 5);
            exampleTree4.insert("structures", "filepathEx", 80);
            exampleTree4.insert("structures", "filepathEx2", 4);
            exampleTree4.insert("structures", "filepathEx3", 9);
            exampleTree4.insert("structures", "filepathEx4", 1);
            exampleTree4.insert("structures", "filepathEx5", 13);

            exampleTree4 = exampleTree;

            REQUIRE(exampleTree4.getTotal() == 2);
        }
    }

