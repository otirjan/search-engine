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
        REQUIRE(handler.searchOrg("Dell").empty());
    }
}