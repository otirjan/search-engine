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
}
    TEST_CASE("all things copying")
    {
        AvlTree<std::string,std::string> exampleTree;

        std::map<size_t, std::string> value1 = {{2, "filepathEx"}, {6, "filepathEx2"}};
        std::map<size_t, std::string> value2 = {{8, "filepathEx3"}, {1, "filepathEx4"}};

        //inserting node into AVL tree
        exampleTree.insert("hello", value1);
        exampleTree.insert("world", value2);

        //copy constructor
        AvlTree<std::string,std::string> exampleTree2(exampleTree);

        //copy assignment
        AvlTree<std::string,std::string> exampleTree3 = exampleTree;


        SECTION("copy assignment, copy constructor, getTotal")
        {
            REQUIRE(exampleTree.getTotal() == 2);
            REQUIRE(exampleTree2.getTotal() == 2);
            REQUIRE(exampleTree3.getTotal() == 2);
            // REQUIRE(exampleTree.getTotal() == exampleTree2.getTotal());
            // REQUIRE(exampleTree.getTotal() == exampleTree3.getTotal());

            // REQUIRE(exampleTree.isEmpty() == exampleTree2.isEmpty());
            // REQUIRE(exampleTree.isEmpty() == exampleTree3.isEmpty());

            // exampleTree.makeEmpty();

            // REQUIRE(exampleTree2.getTotal() == 2);
            // REQUIRE(exampleTree3.getTotal() == 2);
            // REQUIRE(exampleTree2.isEmpty() == false);
            // REQUIRE(exampleTree3.isEmpty() == false);
        }

        SECTION("messing with the exampleTrees independently of each other")
        {
            std::map<size_t, std::string> value3 = {{2, "filepathEx"}, {6, "filepathEx2"}, {16, "filepathEx3"}, {23, "filepathEx4"}};
            std::map<size_t, std::string> value4 = {{20, "filepathEx"}};
            std::map<size_t, std::string> value5 = {{80, "filepathEx"}, {4, "filepathEx2"}, {9, "filepathEx3"}, {1, "filepathEx4"}, {13, "filepathEx5"}};

            exampleTree2.insert("apple", value3);
            exampleTree3.insert("data", value4);
            exampleTree3.insert("structures", value5);

            // REQUIRE(exampleTree2.getTotal() == 3);
            // REQUIRE(exampleTree3.getTotal() == 5);

            // REQUIRE(exampleTree2.isEmpty() == false);
            // REQUIRE(exampleTree3.isEmpty() == false);

        }

        SECTION("extra copy assignment test")
        {
            AvlTree<std::string,std::string> exampleTree4;

            std::map<size_t, std::string> value1 = {{2, "filepathEx"}, {6, "filepathEx2"}, {16, "filepathEx3"}, {23, "filepathEx4"}};
            std::map<size_t, std::string> value2 = {{20, "filepathEx"}};
            std::map<size_t, std::string> value3 = {{80, "filepathEx"}, {4, "filepathEx2"}, {9, "filepathEx3"}, {1, "filepathEx4"}, {13, "filepathEx5"}};

            exampleTree4.insert("apple", value1);
            exampleTree4.insert("data", value2);
            exampleTree4.insert("structures", value3);

            exampleTree4 = exampleTree;

           // REQUIRE(exampleTree4.getTotal() == 2);
        }
    }

    TEST_CASE("extra tests")
    {
        AvlTree<std::string,std::string> exampleTree;

        std::map<size_t, std::string> value1 = {{2, "filepathEx"}, {6, "filepathEx2"}};
        std::map<size_t, std::string> value2 = {{8, "filepathEx3"}, {1, "filepathEx4"}};

        //inserting node into AVL tree
        exampleTree.insert("hello", value1);
        exampleTree.insert("world", value2);


        SECTION("making sure there aren't duplicates")
        {
            //test adding a duplicate node
            std::map<size_t, std::string> value3 = {{2, "filepathEx"}, {6, "filepathEx2"}, {16, "filepathEx3"}, {23, "filepathEx4"}};

            exampleTree.insert("hello", value3);

            //should not have done anything because this is a duplicate
           // REQUIRE(exampleTree.getTotal() == 2);
        }

    }

