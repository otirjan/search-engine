#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include "DocParser.h"

TEST_CASE("Tokenization Test") {
    DocumentParser parser;
    string text = "This is a test document for tokenization";
    vector<string> expected_tokens = {"test", "document", "token"};
    vector<string> tokens = parser.tokenize(text);
    REQUIRE(tokens == expected_tokens);


    string text1 = "The largest block in the street is that one";
    vector<string> expected_tokens1 = {"largest", "block", "street"};
    vector<string> tokens1 = parser.tokenize(text1);
    REQUIRE(tokens1 == expected_tokens1);
    }


TEST_CASE("Stemming Test") {
    DocumentParser parser;
    string word = "running";
    string expected_stem = "run";
    string stem = parser.stemWord(word);
    REQUIRE(stem == expected_stem);


    string word1 = "programming";
    string expected_stem1 = "program";
    string stem1 = parser.stemWord(word1);
    REQUIRE(stem1 == expected_stem1);
}

TEST_CASE("Stopword Removal Test") {
    DocumentParser parser;
    string text_with_stopwords = "This is a test document with stopwords";
    string text_without_stopwords = "test document stopwords";
    vector<string> tokens = parser.tokenize(text_with_stopwords);
    for (const auto& token : tokens) {
        REQUIRE(token != "is");
        REQUIRE(token != "a");
        REQUIRE(token != "with");
    }
}


TEST_CASE("DocParse with File, Passing Correct words to Index Handler"){
    DocumentParser parser;   //make instance of the parser 
    
    std::string filePath = "sample_data/coll_1/news_0064567.json";    //manually read in file path 
    parser.parseDoc(filePath);               //call parsedoc on the file, should populate all the maps w/ words 

    //use find or contains function to check if the names contains the name
    IndexHandler& handler = parser.getIndexHandler();
    
    std::map<std::string, size_t> personMap = handler.searchPerson("eric schweitzer");   //make a map that populates if berlin appears 
    bool containsName = !personMap.empty();   //return true if name appears (it should)

    REQUIRE(containsName);

    //check that author is Reuters Editorial
    // std::map<std::string, size_t> wordMap = handler.searchWord("pessimistic");   //make a map that populates if berlin appears 
    // bool containsWord = !wordMap.empty();   //return true if name appears (it should)

    // REQUIRE(containsWord);

    
    //check that organizations is empty
    
}

// }