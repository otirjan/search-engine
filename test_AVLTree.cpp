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
        
        * I want to write a function or somehow figure out how to check that the frequencies in a map are correct
*/

TEST_CASE("testing insert")
{
    //creating an instance of the avl tree
    AvlTree<std::string,std::string> exampleTree;

    SECTION("inserting, checking to see if the values in the map are correct")
    {

       std::map<std::string, size_t> value1 = {{"filepathEx", 2}, {"filepathEx2", 6}};
       std::map<std::string, size_t> value2 = {{"filepathEx3", 8}, {"filepathEx4", 1}};

        exampleTree.insert("hello", value1);
        exampleTree.insert("world", value2);


        REQUIRE(exampleTree.contains("hello") == true);
        REQUIRE(exampleTree.contains("world") == true);

        REQUIRE(exampleTree.find("hello")["filepathEx"] == 2);

        //write find which will return a map. then i can access the map using the key which will be the filename, or loop over



    }

}