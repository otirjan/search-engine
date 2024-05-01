#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include "IndexHandler.h"
#include <iostream>

TEST_CASE("IndexHandler Tests") {
    IndexHandler handler;

    SECTION("Adding + Searching Words") {
        std::string word = "computer";
        handler.addWord(word, "file1.txt");
        
        std::string word2 = "block";
        handler.addWord(word2, "file2.txt");

        std::string word3 = "computer";
        handler.addWord(word3, "file3.txt");

        REQUIRE(handler.searchWord("computer") == std::map<std::string, size_t>{{"file1.txt", 1}, {"file3.txt", 1}});
        REQUIRE(handler.searchWord("block") == std::map<std::string, size_t>{{"file2.txt", 1}});
        REQUIRE(handler.searchWord("orange").empty());
    }

    SECTION("Adding + Searching Persons") {
         std::string word4 = "Cameron Tofani";
        handler.addPerson(word4, "file1.txt");

        std::string word5 = "Makayla A";
        handler.addPerson(word5, "file2.txt");

        REQUIRE(handler.searchPerson("Cameron Tofani") == std::map<std::string, size_t>{{"file1.txt", 1}});
        REQUIRE(handler.searchPerson("Makayla A") == std::map<std::string, size_t>{{"file2.txt", 1}});
        REQUIRE(handler.searchPerson("Liv T").empty());
    }

    SECTION("Adding + Searching Orgs") {
         std::string word7 = "Apple";
        handler.addOrg(word7, "file1.txt");

        std::string word8 = "Google";
        handler.addOrg(word8 ,"file2.txt");

        REQUIRE(handler.searchOrg("Apple") == std::map<std::string, size_t>{{"file1.txt", 1}});
        REQUIRE(handler.searchOrg("Google") == std::map<std::string, size_t>{{"file2.txt", 1}});
        REQUIRE(handler.searchOrg("Mac").empty());
    }

    SECTION("Error Handling"){
        std::stringstream errorStream;
        std::streambuf* oldCerrBuffer = std::cerr.rdbuf(errorStream.rdbuf());     //errors print to cerr, so we use this so we can read the contents of cerr

        //adding a word with an empty string
        std::string invalidWord = "";
        handler.addWord(invalidWord, "file1.txt");
        REQUIRE(errorStream.str() == "Cannot add word. Must be a string.");

        // Clear the error stream
        errorStream.str("");

        // Test adding a person with an empty string
        std::string invalidPerson = "";
        handler.addPerson(invalidPerson, "file1.txt");
        REQUIRE(errorStream.str() == "Cannot add Person. Must be a string.");

        // Clear the error stream
        errorStream.str("");

        // Test adding an organization with an empty string
        std::string invalidOrg = "";
        handler.addOrg(invalidOrg, "file1.txt");
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