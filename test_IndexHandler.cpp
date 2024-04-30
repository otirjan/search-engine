#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include "IndexHandler.h"
#include <iostream>

TEST_CASE("IndexHandler Tests") {
    IndexHandler handler;

    SECTION("Adding + Searching Words") {
        handler.addWord("computer", "file1.txt", 3);
        handler.addWord("block", "file2.txt", 5);
        handler.addWord("computer", "file3.txt", 2);

        REQUIRE(handler.searchWord("computer") == std::map<std::string, size_t>{{"file1.txt", 3}, {"file3.txt", 2}});
        REQUIRE(handler.searchWord("block") == std::map<std::string, size_t>{{"file2.txt", 5}});
        REQUIRE(handler.searchWord("orange").empty());
    }

    SECTION("Adding + Searching Persons") {
        handler.addPerson("Cameron Tofani", "file1.txt", 2);
        handler.addPerson("Makayla A", "file2.txt", 3);
        handler.addPerson("Cameron Tofani", "file3.txt", 1);

        REQUIRE(handler.searchPerson("Cameron Tofani") == std::map<std::string, size_t>{{"file1.txt", 2}, {"file3.txt", 1}});
        REQUIRE(handler.searchPerson("Makayla A") == std::map<std::string, size_t>{{"file2.txt", 3}});
        REQUIRE(handler.searchPerson("Liv T").empty());
    }

    SECTION("Adding + Searching Orgs") {
        handler.addOrg("Apple", "file1.txt", 10);
        handler.addOrg("Google", "file2.txt", 8);
        handler.addOrg("Apple", "file3.txt", 6);

        REQUIRE(handler.searchOrg("Apple") == std::map<std::string, size_t>{{"file1.txt", 10}, {"file3.txt", 6}});
        REQUIRE(handler.searchOrg("Google") == std::map<std::string, size_t>{{"file2.txt", 8}});
        REQUIRE(handler.searchOrg("Mac").empty());
    }

    SECTION("Error Handling"){
        std::stringstream errorStream;
        std::streambuf* oldCerrBuffer = std::cerr.rdbuf(errorStream.rdbuf());     //errors print to cerr, so we use this so we can read the contents of cerr

        //adding a word with an empty string
        std::string invalidWord = "";
        handler.addWord(invalidWord, "file1.txt", 3);
        REQUIRE(errorStream.str() == "Cannot add word. Must be a string.");

        // Clear the error stream
        errorStream.str("");

        // Test adding a person with an empty string
        std::string invalidPerson = "";
        handler.addPerson(invalidPerson, "file1.txt", 2);
        REQUIRE(errorStream.str() == "Cannot add Person. Must be a string.");

        // Clear the error stream
        errorStream.str("");

        // Test adding an organization with an empty string
        std::string invalidOrg = "";
        handler.addOrg(invalidOrg, "file1.txt", 5);
        REQUIRE(errorStream.str() == "Cannot add org. Must be a string.");

        // Restore cerr
        std::cerr.rdbuf(oldCerrBuffer);
    }

    SECTION("lowercasing"){ //PASSED 
        IndexHandler handler; 
        
        std::string word1 = "HAPPY"; 

        std::string lowerWord1 = handler.toLower(word1);

        REQUIRE(lowerWord1 == "happy");

        //std::cout << "Original: " << word1 << ", Lowercased: " << lowerWord1 << std::endl;
    }
}