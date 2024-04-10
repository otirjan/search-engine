#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "AVLTree.h"
#include <iostream>
#include <map>

TEST_CASE("testing insert")
{
    //creating an instance of the avl tree
    AvlTree<std::string,std::string> exampleTree;

    SECTION("inserting")
    {
       // exampleTree.insert(std::string("hello"), {{"filepathEx", 2}, {"filepathEx2", 6}});
      // exampleTree.insert(std::string("hello"), std::map<std::string, size_t>{{"filepathEx", 2}, {"filepathEx2", 6}});


       // exampleTree.insert(std::string("world"), {{"filepathEx3", 8}, {"filpathEx4", 1}});

       std::map<std::string, size_t> value1 = {{"filepathEx", 2}, {"filepathEx2", 6}};
       std::map<std::string, size_t> value2 = {{"filepathEx3", 8}, {"filepathEx4", 1}};

        exampleTree.insert("hello", value1);
        exampleTree.insert("world", value2);


        REQUIRE(exampleTree.contains("hello") == true);
        REQUIRE(exampleTree.contains("world") == true);



    }

}